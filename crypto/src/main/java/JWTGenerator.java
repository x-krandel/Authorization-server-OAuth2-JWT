import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.security.Keys;
import javax.crypto.SecretKey;
import java.util.Date;
import java.nio.charset.StandardCharsets;

public class JWTGenerator {

    private static final String SECRET = "wole_miec_secret_polaczony_z_olaboga";
    private static final SecretKey key = Keys.hmacShaKeyFor(SECRET.getBytes());

    public static String generateJWT(String username) {
        
        long now = System.currentTimeMillis();
        return Jwts.builder()
                .subject(username)
                .issuedAt(new Date(now))
                .expiration(new Date(now + 3600000)) // Ważny 1h
                .signWith(key)
                .compact();
                

    }

    public static void main(String[] args) {
       System.out.println("-- Gen JWT --");
       String token = generateJWT("krandel");
       System.out.println("Twoje JWT:");
       System.out.println(token);
    }
}
