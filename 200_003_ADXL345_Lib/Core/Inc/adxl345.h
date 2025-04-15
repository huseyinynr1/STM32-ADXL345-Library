/*
 * adxl345.h
 *
 *  Created on: Mar 17, 2025
 *      Author: husey
 */

#ifndef INC_ADXL345_H_
#define INC_ADXL345_H_

#include "stm32f4xx_hal.h"           // STM32 HAL kütüphanesi (temel donanım işlevleri için)
#include "stm32f4xx_hal_i2c.h"       // I2C haberleşmesi için HAL fonksiyonları
#include "adxl345_Register.h"        // ADXL345 register tanımlarını içeren başlık dosyası

#define ADXL345_SCALE_FACTOR  0.0078f   // ±4g aralığı için ölçüm başına düşen G değeri (1 LSB = 7.8 mg)

// Global UART handle (isteğe bağlı UART debug için kullanılabilir)
extern UART_HandleTypeDef huart4;

// ADXL345 sensörünü başlatır ve gerekli register ayarlarını yapar
void ADXL345_Init();

// Tüm eksenlerin (X, Y, Z) ham verilerini okur
void ADXL345_READ_ALL_AXIS(I2C_HandleTypeDef *hi2c, int16_t *x, int16_t *y, int16_t *z);

// X ekseni ham verisini (int16_t) okur
int16_t ADXL345_READ_X_AXIS(I2C_HandleTypeDef *hi2c);

// Y ekseni ham verisini (int16_t) okur
int16_t ADXL345_READ_Y_AXIS(I2C_HandleTypeDef *hi2c);

// Z ekseni ham verisini (int16_t) okur
int16_t ADXL345_READ_Z_AXIS(I2C_HandleTypeDef *hi2c);

// X ekseni değerini G cinsinden (float) döner
float ADXL345_READ_X_G_VALUE(I2C_HandleTypeDef *hi2c);

// Y ekseni değerini G cinsinden (float) döner
float ADXL345_READ_Y_G_VALUE(I2C_HandleTypeDef *hi2c);

// Z ekseni değerini G cinsinden (float) döner
float ADXL345_READ_Z_G_VALUE(I2C_HandleTypeDef *hi2c);

// Tap (dokunma) olayını kontrol eder, 1: tek tap, 2: çift tap, 0: tap yok
uint8_t ADXL345_READ_TAP(I2C_HandleTypeDef *hi2c);

// Serbest düşüş olup olmadığını kontrol eder, 1: var, 0: yok
uint8_t ADXL345_READ_FREE_FALL(I2C_HandleTypeDef *hi2c);

#endif /* INC_ADXL345_H_ */
