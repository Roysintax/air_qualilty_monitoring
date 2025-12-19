# 🌿 Smart Air Quality Monitoring System (IoT)

> Sistem pemantauan kualitas udara cerdas berbasis IoT menggunakan ESP8266, sensor MQ-135, dan integrasi aplikasi Blynk.

![Wiring Diagram](Wiring%20Diagram.jpg)
*(Pastikan file gambar Wiring Diagram.jpg ada di folder repository Anda)*

## 📖 Tentang Proyek
Proyek ini bertujuan untuk memantau kualitas udara, suhu, dan kelembapan secara *real-time*. Data ditampilkan langsung melalui layar OLED dan dapat dipantau dari jarak jauh menggunakan aplikasi **Blynk** di smartphone.

Sistem ini dilengkapi dengan fitur **Sistem Peringatan Dini**: Jika kadar CO2 terdeteksi melebihi batas aman (> 2000 ppm), Buzzer akan berbunyi dan notifikasi akan dikirim ke smartphone Anda.

## ✨ Fitur Utama
* **Real-time Monitoring:** Memantau Suhu, Kelembapan, dan Estimasi CO2 (PPM).
* **Dual Display:** Menampilkan data di layar OLED 0.96" dan Dashboard Blynk.
* **Smart Alert:** Alarm Buzzer otomatis aktif saat udara buruk.
* **IoT Connected:** Terhubung via WiFi menggunakan modul ESP8266.

## 🛠️ Perangkat Keras (Hardware)
Komponen yang digunakan dalam proyek ini:
1.  **ESP8266 NodeMCU** (Microcontroller)
2.  **Sensor MQ-135** (Kualitas Udara/Gas)
3.  **Sensor DHT11** (Suhu & Kelembapan)
4.  **OLED Display 0.96"** (I2C SSD1306)
5.  **Buzzer** (Active Buzzer)
6.  **Kabel Jumper & Breadboard**

## 🔌 Skema Rangkaian (Pinout)

Berdasarkan konfigurasi kode `master.ino`:

| Komponen | Pin NodeMCU (ESP8266) | Keterangan |
| :--- | :--- | :--- |
| **MQ-135** | **A0** | Output Analog |
| **DHT11** | **D4** | Data Signal |
| **Buzzer** | **D3** | Output Alarm |
| **OLED SCL** | **D1** (Default I2C) | Clock |
| **OLED SDA** | **D2** (Default I2C) | Data |

## 💻 Instalasi & Penggunaan

### 1. Persiapan Software
Pastikan Anda telah menginstal **Arduino IDE** dan library berikut melalui *Library Manager*:
* `Blynk` by Volodymyr Shymanskyy
* `DHT sensor library` by Adafruit
* `Adafruit GFX Library`
* `Adafruit SSD1306`

### 2. Konfigurasi Blynk
Buat project baru di aplikasi Blynk dan atur **Datastream** (Virtual Pins) sebagai berikut:
* **V0**: Temperature (Gauge/Value)
* **V1**: Humidity (Gauge/Value)
* **V2**: CO2 PPM (Gauge/Graph)

### 3. Konfigurasi Kode
Buka file `master.ino` dan sesuaikan bagian berikut dengan kredensial Anda:

```cpp
#define BLYNK_TEMPLATE_ID "TMPLxxxxxx"      // ID Template Blynk Anda
#define BLYNK_TEMPLATE_NAME "Nama Project"  // Nama Template
#define BLYNK_AUTH_TOKEN "AuthTokenAnda"    // Token Auth dari Blynk

char ssid[] = "NamaWiFiAnda";               // Nama WiFi
char pass[] = "PasswordWiFiAnda";           // Password WiFi
