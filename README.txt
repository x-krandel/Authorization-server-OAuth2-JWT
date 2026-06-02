Propozycja projektu: Ekosystem Autoryzacji "SafeStack"
Możesz podzielić projekt na trzy główne komponenty:


1. Java -> Done 
  **To run use command: `mvn clean spring-boot:run` **

2. PHP: Client Application / Dashboard (Frontend & Logic)
PHP może pełnić rolę aplikacji, która "konsumuje" tokeny z Javy. To tutaj najczęściej pojawiają się luki typu Broken Access Control.

Zadanie: Strona użytkownika (np. prosty panel managera plików). Aplikacja wysyła użytkownika do serwera w Javie, odbiera token JWT i przechowuje go w bezpiecznym ciasteczku (HttpOnly, Secure).

# php -S localhost:8000


[!] PHP aplikacja została rozszerzona o SSRF + IDOR z Cloud-Native-Microservices, check: http://localhost:8000/index.php?page=home&reference=http://127.0.0.1:3000/api/users/view?id=777
    Żeby sprawdzić, trzeba odpalić api-gateway, render-service, user-service, oraz serwer Java, który generuje JWT sprawdzane przez Cloude-Native-Microservices

Wyzwanie: Zaimplementuj mechanizm SSO (Single Sign-On). Dodaj w PHP logikę, która sprawdza ważność tokena przy każdym przeładowaniu strony.

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
