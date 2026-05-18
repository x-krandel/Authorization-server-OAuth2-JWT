#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>




int main() {
    FILE *token;
    token = fopen("secret.txt", "r");
    char myToken[256];
    fgets(myToken, 256, token);
    printf("[+] Your secret is = > %s", myToken);
}

