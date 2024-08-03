# WiFi Controlled Robot Car with NodeMCU

## Overview
This project is a WiFi-controlled robot car using the NodeMCU ESP8266 module. The robot can move forward, backward, turn left, and turn right, and it has an automatic mode for line following using infrared (IR) sensors. It also includes a web interface for remote control.

## Components
- **NodeMCU ESP8266**: Modul mikrokontroler dengan WiFi terintegrasi.
- **Motor Driver**: Mengontrol kecepatan dan arah motor DC.
- **IR Sensors**: Mendeteksi garis pada permukaan untuk mode otomatis.
- **DC Motors**: Menggerakkan robot ke berbagai arah.

## Pin Configuration
- **Motor Driver Pins**:
  - ENA: Pin 14 (Mengontrol kecepatan motor A)
  - ENB: Pin 12 (Mengontrol kecepatan motor B)
  - IN1: Pin 15 (Mengontrol arah motor A)
  - IN2: Pin 13 (Mengontrol arah motor A)
  - IN3: Pin 2 (Mengontrol arah motor B)
  - IN4: Pin 0 (Mengontrol arah motor B)
  
- **IR Sensors**:
  - IR_LEFT: Pin 16 (Sensor IR kiri)
  - IR_RIGHT: Pin 5 (Sensor IR kanan)

## Code Description

### Initialization
- Menyiapkan pin untuk output (motor) dan input (sensor IR).
- Menginisialisasi koneksi WiFi dalam mode Access Point dengan SSID "NodeMCU_Car".
- Memulai server web untuk menangani perintah.

### Motor Control Functions
- **goAhead()**: Menggerakkan robot maju.
- **goBack()**: Menggerakkan robot mundur.
- **goRight()**: Menggerakkan robot ke kanan.
- **goLeft()**: Menggerakkan robot ke kiri.
- **stopRobot()**: Menghentikan robot.

### Automatic Mode
- **followLine()**: Menggerakkan robot mengikuti garis berdasarkan input dari sensor IR.
- Robot akan berhenti jika tidak ada garis yang terdeteksi oleh kedua sensor IR.

### Web Server
- Menangani permintaan dari klien web untuk mengontrol robot.
- Berbagai perintah seperti "F" (maju), "B" (mundur), "L" (kiri), "R" (kanan), dan "S" (berhenti) dikirim melalui antarmuka web.

## How It Works

1. Ketika robot dinyalakan, NodeMCU membuat jaringan WiFi dengan SSID "NodeMCU_Car".
2. Pengguna terhubung ke jaringan ini dan mengakses antarmuka web untuk mengontrol robot.
3. Dalam mode manual, pengguna mengirim perintah melalui antarmuka web untuk menggerakkan robot.
4. Dalam mode otomatis, robot menggunakan sensor IR untuk mendeteksi dan mengikuti garis.
