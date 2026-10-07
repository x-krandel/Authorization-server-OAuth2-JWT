

## Small overview

**This project represents authorization implementaion of common aplication in which several aplications collaborating with each other via REST API.**

**Main components are:**

1. Java server, to run use:

```
mvn clean spring-boot:run
```

2. Client-side PHP app, witch is sending user to Java server, and getting JWT token placing him in cookie, to run use:

```
php -S localhost:8000
```
*PHP part was extended by some included vulnerabilies as well. You can explore basic vulnerabilities combination such as SSRF + IDOR*

*To check it use:*

```
http://localhost:8000/index.php?page=home&reference=http://127.0.0.1:3000/api/users/view?id=777
```

**`You also need to run main app from:`**
```
git clone https://github.com/x-krandel/Cloud-Native-Microservices.git
```

Also you can see in this app SSO (Single Sign-On) implementation, which is validating tocken with each page refreshing.

3. Resource Server / API (Low-level Data) written in C, which validating JWT token from Java server, comparing `exp` field as well.

```
gcc index.c validate_jwt
./validate_jwt
```
