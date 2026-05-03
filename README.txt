Propozycja projektu: Ekosystem Autoryzacji "SafeStack"
Możesz podzielić projekt na trzy główne komponenty:

<<<<<<< HEAD
Propozycja projektu: Ekosystem Autoryzacji "SafeStack"
Możesz podzielić projekt na trzy główne komponenty:

=======
>>>>>>> dd93218914094852100116c1793e365555af8137
1. Java: Authorization Server (Serce)
To tutaj dzieje się "ciężka" kryptografia. Java świetnie nadaje się do obsługi standardów takich jak OAuth2 czy OpenID Connect.

Zadanie: Generowanie tokenów JWT, obsługa kluczy prywatnych/publicznych (RSA/ECDSA) oraz weryfikacja logowania.

Wyzwanie: Napisz własną implementację podpisywania JWT, zamiast używać gotowych bibliotek typu Spring Security, aby zrozumieć strukturę nagłówka, payloadu i sygnatury.

2. PHP: Client Application / Dashboard (Frontend & Logic)
PHP może pełnić rolę aplikacji, która "konsumuje" tokeny z Javy. To tutaj najczęściej pojawiają się luki typu Broken Access Control.

Zadanie: Strona użytkownika (np. prosty panel managera plików). Aplikacja wysyła użytkownika do serwera w Javie, odbiera token JWT i przechowuje go w bezpiecznym ciasteczku (HttpOnly, Secure).

Wyzwanie: Zaimplementuj mechanizm SSO (Single Sign-On). Dodaj w PHP logikę, która sprawdza ważność tokena przy każdym przeładowaniu strony.

3. C: Resource Server / API (Low-level Data)
To najbardziej ambitna część. Napisz mały serwer w C (np. oparty na bibliotece libmicrohttpd lub surowych socketach), który przechowuje "wrażliwe dane".

Zadanie: PHP wysyła zapytanie do serwera w C, dołączając token JWT w nagłówku Authorization: Bearer. Serwer w C musi sparsować ten token i zweryfikować sygnaturę kluczem publicznym pobranym z Javy.

Wyzwanie: Bezpieczne parsowanie JSON-a w C. To idealne miejsce na błędy typu buffer overflow, co jako gracz CTF możesz później sam spróbować zeskładować.

Jak to połączyć z Twoimi zainteresowaniami CTF?
Budując taki zestaw, możesz "zaszyć" w nim podatności, które sam spotykasz w zadaniach typu Web i Pwn:

PHP (Web): Celowo zaimplementuj podatność Insecure Deserialization przy przetwarzaniu danych sesji lub Type Juggling przy sprawdzaniu tokenów (jeśli użyjesz luźnych porównań == zamiast ===).

Java (Logic): Stwórz błąd logiczny w walidacji JWT, np. akceptowanie algorytmu none (klasyka gatunku) lub brak weryfikacji pola exp (expiration).

C (Pwn): Przy parsowaniu nagłówków HTTP w serwerze napisanym w C, użyj niebezpiecznych funkcji typu strcpy() lub sprintf() zamiast ich bezpiecznych odpowiedników. Dzięki temu Twój projekt stanie się Twoim własnym poligonem do ćwiczeń.

Od czego zacząć?
Najlepiej zacząć od Javy i generowania JWT. Gdy będziesz miał działający token, dopisz do niego prosty skrypt w PHP, który go wyświetli i zdekoduje. Na końcu dodaj C jako warstwę dostępu do danych.
<<<<<<< HEAD
