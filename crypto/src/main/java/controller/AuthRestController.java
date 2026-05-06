package controller;

import com.example.dto.LoginRequest;
import com.example.security.TokenService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.Map;

@RestController
@RequestMapping("/api/auth")
public class AuthRestController {

    @Autowired
    private TokenService tokenService;

    @PostMapping("/login")
    public Map<String, String> login(@RequestBody LoginRequest loginRequest) {
        // Generujemy token na podstawie username z żądania
        String token = tokenService.generateJWT(loginRequest.getUsername());

        // Zwracamy wynik jako JSON: {"token": "..."}
        Map<String, String> response = new HashMap<>();
        response.put("token", token);
        return response;
    }
}
