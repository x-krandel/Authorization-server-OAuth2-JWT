package com.example.dto;

public class LoginRequest {
    private String username;

    // Gettery i settery są niezbędne dla Springa
    public String getUsername() { return username; }
    public void setUsername(String username) { this.username = username; }
}