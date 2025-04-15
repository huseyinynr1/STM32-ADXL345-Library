# ADXL345-STM32-Library

## 🧠 Özellikler / Features

Bu kütüphane, STM32 mikrodenetleyiciler ile ADXL345 ivmeölçer sensörünün I2C haberleşmesi üzerinden kullanılmasını sağlar.  
This library enables interfacing the ADXL345 accelerometer with STM32 microcontrollers via I2C communication.

### Desteklenen Özellikler / Supported Features

- X, Y, Z eksenlerinde ivme ölçümü (g cinsinden)  
  Acceleration measurement on X, Y, Z axes (in g)
- Tek dokunuş ve çift dokunuş algılama  
  Single and double tap detection
- Serbest düşüş algılama  
  Free-fall detection
- STM32 HAL tabanlı yapı / Based on STM32 HAL drivers
- Modüler, genişletilebilir ve açık kaynaklıdır  
  Modular, extensible and open source

---

## 🚀 Başlangıç / Getting Started

### Gerekli Dosyalar / Required Files

- `adxl345.h`
- `adxl345.c`
- `adxl345_Register.h`

Bu dosyaları projenizin `Drivers` veya uygun dizinine ekleyin.  
Add these files to the appropriate folder in your STM32 project (e.g., `Drivers` or `Src/Inc`).

### Donanım Bağlantısı / Hardware Connection

| ADXL345 Pin | STM32 Pin (Örnek) |
|-------------|-------------------|
| VCC         | 3.3V              |
| GND         | GND               |
| SDA         | I2C1_SDA (PB7)    |
| SCL         | I2C1_SCL (PB6)    |

> ⚠️ ADXL345 sensörü 3.3V ile çalışır. 5V vermeyin.  
> ⚠️ ADXL345 operates at 3.3V. Do not apply 5V.

---

## 📂 Fonksiyonlar / Functions

### İvme Değerleri / Acceleration Values

```c
int16_t ADXL345_READ_X_AXIS(I2C_HandleTypeDef *hi2c);
float ADXL345_READ_X_G_VALUE(I2C_HandleTypeDef *hi2c);
```

### Dokunma Algılama / Tap Detection

```c
uint8_t ADXL345_READ_TAP(I2C_HandleTypeDef *hi2c);
// 0: tap yok / no tap
// 1: tek dokunuş / single tap
// 2: çift dokunuş / double tap
```

### Serbest Düşüş / Free Fall

```c
uint8_t ADXL345_READ_FREE_FALL(I2C_HandleTypeDef *hi2c);
// 0: düşüş yok / no fall
// 1: serbest düşüş algılandı / free-fall detected
```

---

## 📌 Lisans / License

Bu proje açık kaynaklıdır ve MIT lisansı ile lisanslanmıştır.  
This project is open-source and licensed under the MIT License.

---

Hazırlayan / Developed by: **Hüseyin Yanar**  
Tarih / Date: **Mart 2025**