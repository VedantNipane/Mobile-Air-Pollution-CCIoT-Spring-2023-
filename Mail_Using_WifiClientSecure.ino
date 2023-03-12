#include <WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  float temp = 51.0; // Replace with actual temperature value
  if (temp > 50.0) {
    sendEmail("recipient_email@example.com", "Temperature Alert", "Temperature is above 50 degrees Celsius.");
  }
}

void sendEmail(const char* to, const char* subject, const char* message) {
  WiFiClientSecure client;
  if (!client.connect("smtp.gmail.com", 465)) {
    Serial.println("Connection to SMTP server failed!");
    return;
  }
  if (!client.verify(fingerprint, "smtp.gmail.com")) {
    Serial.println("SMTP server certificate verification failed!");
    return;
  }
  client.println("EHLO esp32");
  delay(1000);
  client.println("AUTH LOGIN");
  delay(1000);
  client.println(base64::encode(user));
  delay(1000);
  client.println(base64::encode(password));
  delay(1000);
  client.println("MAIL FROM:<sender_email@gmail.com>");
  delay(1000);
  client.println("RCPT TO:<" + String(to) + ">");
  delay(1000);
  client.println("DATA");
  delay(1000);
  client.println("From: <sender_email@gmail.com>");
  client.println("To: <" + String(to) + ">");
  client.println("Subject: " + String(subject));
  client.println("");
  client.println(String(message));
  client.println(".");
  delay(1000);
  client.println("QUIT");
  delay(1000);
  client.stop();
  Serial.println("Email sent!");
}

void loop() {}
