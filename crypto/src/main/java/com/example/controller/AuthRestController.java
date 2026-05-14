package com.example.controller;

import com.example.dto.LoginRequest;
import com.example.security.TokenService;

import jakarta.servlet.http.HttpServletResponse;

import org.springframework.beans.factory.annotation.Autowired;
import jakarta.servlet.http.Cookie;
import org.springframework.web.bind.annotation.*;
import java.io.File;                  // Import the File class
import java.io.FileNotFoundException; // Import this class to handle errors
import java.util.Scanner;  
import java.io.OutputStream;
import java.net.Socket;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;
import java.net.Socket;
import java.io.OutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

@RestController
@RequestMapping("/api/auth")
public class AuthRestController {
    @Autowired
    private TokenService tokenService;
    
    @PostMapping("/login")
    public Map<String, String> login(@RequestBody LoginRequest loginRequest, HttpServletResponse response) {
        // Generujemy token na podstawie username z żądania
        String token = tokenService.generateJWT(loginRequest.getUsername());

        Cookie jwtCookie = new Cookie("jwt_token", token);
        jwtCookie.setHttpOnly(true);
        jwtCookie.setSecure(true);
        jwtCookie.setPath("/");
        jwtCookie.setMaxAge(3600);

        response.addCookie(jwtCookie);
        return Map.of("status", "ok");
    }

    @GetMapping("/jwtsecret")
    public Map<String, String> getJwtSecret(
        @RequestParam("secret") String secret,
        HttpServletResponse response) {

    try {
        Path filePath = Paths.get("/Users/admin/Desktop/Authorization-server-OAuth2-JWT/server/pass.txt");
        // Używamy trim(), aby pozbyć się białych znaków z pliku
        String expected = Files.readString(filePath).trim();

        if (!secret.equals(expected)) {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
            return Map.of("status", "unauthorized");
        }

        String SECRET_KEY = tokenService.jwt_secret();

        // Próba wysłania przez Socket do C
        try (Socket socket = new Socket("127.0.0.1", 1337);
            OutputStream out = socket.getOutputStream()) {
            out.write(SECRET_KEY.getBytes());
            out.flush();
        } catch (Exception e) {
            // Jeśli C nie odbierze, logujemy błąd, ale nie psujemy odpowiedzi HTTP
            System.err.println("Nie udało się wysłać klucza do serwera C: " + e.getMessage());
        }

        return Map.of("status", "ok", "message", "Secret sent to socket");
        
    } catch (Exception e) {
        e.printStackTrace();
        response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
        return Map.of("error", e.getMessage());
    }
}
}

