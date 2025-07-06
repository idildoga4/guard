#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>

// --- PIN Tanımlamaları ---
#define DHT_PIN 21
#define DHT_TYPE DHT22
#define LED_PIN 22
#define BUZZER_PIN 23

// --- Nesne Tanımları ---
DHT dht(DHT_PIN, DHT_TYPE);

// --- Wi-Fi Ayarları ---
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* serverUrl = "http://10.0.2.2:7287/api/sensordata"; // .NET API endpointi

void setup() {
  Serial.begin(9600);

  // Pin modları
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // DHT başlat
  dht.begin();

  // Wi-Fi bağlantısı
  WiFi.begin(ssid, password);
  Serial.print("Wi-Fi bağlantısı bekleniyor");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi bağlantısı sağlandı!");
}

void loop() {
  float temperature = dht.readTemperature();  // °C
  float humidity = dht.readHumidity();        // %

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Sensör verisi okunamadı!");
    return;
  }

  // Sensör verilerini yazdır
  Serial.print("Sıcaklık: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Nem: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Şartlara göre LED ve buzzer kontrolü
  if (temperature > 70 || humidity > 80) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // API'ye veri gönder
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // JSON verisi oluştur
    String jsonData = "{\"deviceId\":1,\"temperature\":" + String(temperature) +
                      ",\"humidity\":" + String(humidity) +
                      ",\"timestamp\":\"2025-07-06T17:30:00\"}";

    // POST isteği gönder
    int httpResponseCode = http.POST(jsonData);

    Serial.print("HTTP yanıt kodu: ");
    Serial.println(httpResponseCode);

    http.end();
  } else {
    Serial.println("Wi-Fi bağlantısı yok.");
  }

  delay(5000); // 5 saniyede bir veri gönder
}
