

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

3. C: Resource Server / API (Low-level Data)
To najbardziej ambitna część. Napisz mały serwer w C (np. oparty na bibliotece libmicrohttpd lub surowych socketach), który przechowuje "wrażliwe dane".

Uruchamianie:
 admin@host server % gcc index.c \
  -I$(brew --prefix openssl)/include \
  -L$(brew --prefix openssl)/lib \
  -lssl -lcrypto \
  -o jwt_validate

Zadanie: PHP wysyła zapytanie do serwera w C, dołączając token JWT w nagłówku Authorization: Bearer. Serwer w C musi sparsować ten token i zweryfikować sygnaturę kluczem publicznym pobranym z Javy.

Wyzwanie: Bezpieczne parsowanie JSON-a w C. To idealne miejsce na błędy typu buffer overflow, co jako gracz CTF możesz później sam spróbować zeskładować.

Jak to połączyć z Twoimi zainteresowaniami CTF?
Budując taki zestaw, możesz "zaszyć" w nim podatności, które sam spotykasz w zadaniach typu Web i Pwn:

PHP (Web): Celowo zaimplementuj podatność Insecure Deserialization przy przetwarzaniu danych sesji lub Type Juggling przy sprawdzaniu tokenów (jeśli użyjesz luźnych porównań == zamiast ===).

Java (Logic): Stwórz błąd logiczny w walidacji JWT, np. akceptowanie algorytmu none (klasyka gatunku) lub brak weryfikacji pola exp (expiration).

C (Pwn): Przy parsowaniu nagłówków HTTP w serwerze napisanym w C, użyj niebezpiecznych funkcji typu strcpy() lub sprintf() zamiast ich bezpiecznych odpowiedników. Dzięki temu Twój projekt stanie się Twoim własnym poligonem do ćwiczeń.

Od czego zacząć?
Najlepiej zacząć od Javy i generowania JWT. Gdy będziesz miał działający token, dopisz do niego prosty skrypt w PHP, który go wyświetli i zdekoduje. Na końcu dodaj C jako warstwę dostępu do danych.
