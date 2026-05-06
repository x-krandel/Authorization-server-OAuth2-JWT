package com.example.security;

import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.security.Keys;
import org.springframework.stereotype.Service;
import javax.crypto.SecretKey;
import java.util.Date;

@Service
public class TokenService {

    // W produkcji ten klucz powinien być wczytywany z zmiennych środowiskowych!
    private static final String SECRET = "wole_miec_secret_polaczony_z_olaboga_minimum_32_znaki";
    private final SecretKey key = Keys.hmacShaKeyFor(SECRET.getBytes());

    public String generateJWT(String username) {
        long now = System.currentTimeMillis();
        return Jwts.builder()
                .subject(username)
                .issuedAt(new Date(now))
                .expiration(new Date(now + 3600000)) // 1h
                .signWith(key)
                .compact();
    }
}