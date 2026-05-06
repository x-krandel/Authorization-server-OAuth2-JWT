package com.example.controller;

import com.example.dto.LoginRequest;
import com.example.security.TokenService;

import jakarta.servlet.http.HttpServletResponse;

import org.springframework.beans.factory.annotation.Autowired;
import jakarta.servlet.http.Cookie;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.Map;

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
}
