#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <openssl/hmac.h>

#define JAVA_PORT 8080
#define C_SERVER_PORT 1337




int validate_jwt(const char *token, const char *secret) {
    const char *p1 = strchr(token, '.');
    const char *p2 = p1 ? strchr(p1 + 1, '.') : NULL;
    if (!p2) return 0;

    unsigned char hmac[48];
    unsigned int  hlen;
    HMAC(EVP_sha384(), secret, strlen(secret),  
         (unsigned char *)token, p2 - token, hmac, &hlen);

    static const char b64[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
    char sig[128];                              
    int i, j;
    for (i = 0, j = 0; i < 48; i += 3) {    
        uint32_t t = ((uint32_t)hmac[i] << 16) |
                     (i+1 < 48 ? (uint32_t)hmac[i+1] << 8 : 0) |
                     (i+2 < 48 ? (uint32_t)hmac[i+2]      : 0);  
        sig[j++] = b64[(t >> 18) & 0x3F];
        sig[j++] = b64[(t >> 12) & 0x3F];
        if (i+1 < 48) sig[j++] = b64[(t >> 6) & 0x3F];            
        if (i+2 < 48) sig[j++] = b64[(t     ) & 0x3F];             
    }
    sig[j] = '\0';

    return CRYPTO_memcmp(sig, p2 + 1, j) == 0;
}

char* get_SECRET_KEY() {
    FILE *f = fopen("pass.txt", "r");
    if (!f) { perror("fopen"); return NULL; }
    char myToken[256] = {0};
    fgets(myToken, sizeof(myToken), f);
    fclose(f);
    myToken[strcspn(myToken, "\r\n")] = '\0';  

   
    char request[1024];
    snprintf(request, sizeof(request),
        "GET /api/auth/jwtsecret?secret=%s HTTP/1.1\r\n"
        "Host: 127.0.0.1:%d\r\n"
        "Connection: close\r\n\r\n",
        myToken, JAVA_PORT
    );


    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) { perror("socket"); return NULL; }
    
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(JAVA_PORT)
    };
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect to Java failed");
        close(fd);
        return NULL;
    }

    send(fd, request, strlen(request), 0);

    char *result = malloc(4096);
    memset(result, 0, 4096);
    int total = 0;
    ssize_t n;
    while ((n = recv(fd, result + total, 4095 - total, 0)) > 0) {
        total += n;
    }
    close(fd);
    return result;
}

char* extract_jwt(const char* http_request) {

    const char *start = strstr(http_request, "jwt_token=");
    if (!start) return NULL;

    start += 10; 

  
    const char *end = strpbrk(start, " \r\n;");
    
    size_t len = end ? (size_t)(end - start) : strlen(start);
  
    char *token = malloc(len + 1);
    if (!token) return NULL;

    strncpy(token, start, len);
    token[len] = '\0';

    return token;
}


int main() {
    // Setup serwera nasłuchującego na port 1337
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in serv = {
        .sin_family = AF_INET,
        .sin_port = htons(C_SERVER_PORT),
        .sin_addr.s_addr = INADDR_ANY
    };
    
    if (bind(server_fd, (struct sockaddr*)&serv, sizeof(serv)) < 0) {
        perror("bind failed");
        return 1;
    }
    listen(server_fd, 1);
    printf("[*] Serwer C nasłuchuje na porcie %d...\n", C_SERVER_PORT);


    printf("[*] Wysyłam żądanie HTTP do Javy...\n");
    char *response = get_SECRET_KEY();


    //Akceptowanie połączenia zwrotnego
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("accept failed");
        return 1;
    }


    char key[4096] = {0};
    ssize_t n = recv(client_fd, key, sizeof(key) - 1, 0);
    if (n > 0) {
        printf("\n[!] KLUCZ ODEBRANY Z JAVY: %s\n", key);
        printf("[*] Czekam na token od aplikacji PHP ...");
    }



    
    

    int php_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (php_fd < 0) {
        perror("accept PHP failed");
        return 1;
    }
    
    char resp[4096] = {0};
    listen(server_fd, 1);
    ssize_t n2 = recv(php_fd, resp, sizeof(resp) - 1, 0);
    if (n2 > 0) {
        printf("\n[!] Odebrane żądanie od aplikacji PHP:\n%s\n", resp);


        char *resp = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 2\r\nConnection: close\r\n\r\nOK";
        send(php_fd, resp, strlen(resp), 0);
    }

    char *extracted_token = extract_jwt(resp);

    if (extracted_token != NULL) {
        printf("\n[SUCCESS] Wycięty token JWT: %s\n", extracted_token);

        bool chk_resp=validate_jwt(extracted_token, key);
        if (chk_resp){
            printf("[*] Valid !");
        } else {
            printf("[!] Invalid !");
        }
        


        free(extracted_token);
    } else {
        printf("\n[ERROR] Nie znaleziono tokena w żądaniu PHP.\n");
    }
    free(response);








    close(client_fd);
    close(server_fd);

    


    return 0;
}
