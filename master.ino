#define BLYNK_TEMPLATE_ID "TMPL6E25xNSM1"
#define BLYNK_TEMPLATE_NAME "adilah"
#define BLYNK_AUTH_TOKEN
"7EvnnXSphEmCfCQZKtnwnfCoLVBy3AID"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <math.h>
// Definisi Pin dan Sensor
#define DHTPIN D4 // Pin DHT11 terhubung ke D4
#define DHTTYPE DHT11 // Tipe sensor DHT
#define MQ135_PIN A0 // Pin MQ135 terhubung ke A0
#define BUZZER_PIN D3 // Pin Buzzer terhubung ke D3
DHT dht(DHTPIN, DHTTYPE);
// Pengaturan OLED
#define SCREEN_WIDTH 128 // Lebar layar OLED
#define SCREEN_HEIGHT 64 // Tinggi layar OLED
#define OLED_RESET -1 // Reset pin (digunakan untuk I2C)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire,
OLED_RESET);
// Variabel untuk MQ135
const float RL = 10.0; // Nilai resistansi load (dalam kOhm)
float R0 = 10.0; // Nilai kalibrasi di udara bersih (Anda perlu kalibrasi di
lingkungan udara bersih)
// Blynk
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Adillah09"; // Ganti dengan nama WiFi
char pass[] = "Maudong123"; // Ganti dengan password WiFi
// Fungsi untuk menghitung konsentrasi CO2 dari Rs/R0
float calculateCO2(float ratio) {
float ppm = 116.6020682 * pow(ratio, -2.769034857); // Persamaan untuk CO2
dari datasheet MQ-135
return ppm;
}
// Fungsi untuk kalibrasi sensor di lingkungan bersih dengan 400 ppm CO2
void calibrateSensor(float Rs_clean_air) {
R0 = Rs_clean_air; // Kalibrasi: Rs_clean_air adalah Rs di udara bersih
}
void setup() {
// Inisialisasi Serial Monitor
Serial.begin(115200);
// Inisialisasi DHT11
dht.begin();
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
Serial.println(F("OLED tidak ditemukan"));
while(true); // Berhenti jika OLED tidak ditemukan
}
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0);
display.println(F("Air Quality Monitor"));
display.display();
delay(2000);
// Kalibrasi sensor dengan Rs di udara bersih
float Rs_clean_air = 15.0; // Contoh Rs di udara bersih, ganti dengan nilai hasil
pengukuran Anda
calibrateSensor(Rs_clean_air); // Kalibrasi sensor
// Inisialisasi koneksi ke Wi-Fi dan Blynk
Blynk.begin(auth, ssid, pass);
// Inisialisasi pin buzzer
pinMode(BUZZER_PIN, OUTPUT);
digitalWrite(BUZZER_PIN, LOW); // Pastikan buzzer mati saat awal
}
void loop() {
// Membaca sensor DHT11
float humidity = dht.readHumidity();
float temperature = dht.readTemperature();
// Membaca sensor MQ135 (kualitas udara)
int mq135_value = analogRead(MQ135_PIN);
// Menghitung Rs dari nilai analog
float Vout = mq135_value * (5.0 / 1023.0); // Mengubah nilai analog ke
tegangan (dengan Vcc = 5V)
float Rs = ((5.0 - Vout) / Vout) * RL; // Menghitung Rs (dalam kOhm)
// Menghitung rasio Rs/R0
float ratio = Rs / R0;
// Menghitung konsentrasi CO2
float co2_ppm = calculateCO2(ratio);
// Tampilkan hasil di Serial Monitor
Serial.print("Suhu: ");
Serial.print(temperature);
Serial.println(" C");
Serial.print("Kelembapan: ");
Serial.print(humidity);
Serial.println(" %");
Serial.print("Nilai Air Quality (MQ135): ");
Serial.println(mq135_value);
Serial.print("Konsentrasi CO2: ");
Serial.print(co2_ppm);
Serial.println(" ppm");
// Tampilkan hasil di OLED
display.clearDisplay();
// Menampilkan judul "Monitoring Kualitas Udara"
display.setCursor(0, 0);
display.setTextSize(1);
display.println("Monitoring Kualitas");
display.setCursor(0, 10); // Baris kedua
display.println("Udara");
// Menampilkan data sensor
display.setCursor(0, 20); // Baris ketiga
display.print("Temp: ");
display.print(temperature);
display.println(" C");
display.setCursor(0, 30); // Baris keempat
display.print("Humidity: ");
display.print(humidity);
display.println(" %");
display.setCursor(0, 40); // Baris kelima
display.print("CO2: ");
display.print(co2_ppm); // Tampilkan konsentrasi CO2 dalam ppm
display.println(" ppm");
display.display();
// Kirim data ke Blynk
Blynk.virtualWrite(V0, temperature); // Gauge untuk Temperature
Blynk.virtualWrite(V1, humidity); // Gauge untuk Humidity
Blynk.virtualWrite(V2, co2_ppm); // Gauge untuk CO2
// Aktifkan buzzer jika CO2 lebih dari 2000 ppm
if (co2_ppm > 2000) {
digitalWrite(BUZZER_PIN, HIGH); // Buzzer ON
Blynk.logEvent("high_co2_warning", "Peringatan! Konsentrasi CO2 melebihi
2000 ppm!");
} else {
digitalWrite(BUZZER_PIN, LOW); // Buzzer OFF
}
// Jalankan Blynk
Blynk.run();
delay(1000);
}