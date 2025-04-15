/*
 * adxl345.c
 *
 *  Created on: Mar 17, 2025
 *      Author: husey
 */

#include "adxl345.h"

uint8_t deviceAddress = 0;                             // Cihaza atanacak geçici I2C adresi
uint8_t readData;                                      // Tek bir register'dan okunan veri

void ADXL345_WriteRegister(I2C_HandleTypeDef *hi2c,
                           uint8_t writeAddress,
                           uint8_t writeRegister,
                           uint8_t writeValue)
{
	uint8_t data[2] = {writeRegister, writeValue};     // Yazılacak adres ve değer
	HAL_I2C_Master_Transmit(hi2c, writeAddress, data, sizeof(data), 100); // Register'a veri yaz
}

void ADXL345_ReadRegister(I2C_HandleTypeDef *hi2c,
                          uint8_t deviceAddress,
                          uint8_t registerAddress,
                          uint8_t* data,
                          uint16_t size)
{
	HAL_I2C_Mem_Read(hi2c, deviceAddress, registerAddress, 1, data, size, 100); // Register'dan veri oku
}

void ADXL345_Init(I2C_HandleTypeDef *hi2c, UART_HandleTypeDef *huart4)
{
	uint8_t succesFindDeviceAddressMessage[] = "Cihaz adresi bulundu";
	uint8_t notFindDeviceAddressMessage[]    = "Cihaz adresi bulunamadi";

	for(deviceAddress = 0; deviceAddress <= 255; deviceAddress++)     // I2C adres taraması
	{
		if(HAL_I2C_IsDeviceReady(hi2c, deviceAddress, 1, 100) == HAL_OK)
		{
			HAL_UART_Transmit(huart4, succesFindDeviceAddressMessage, sizeof(succesFindDeviceAddressMessage), 100);
			break;
		}
		else
		{
			HAL_UART_Transmit(huart4, notFindDeviceAddressMessage, sizeof(notFindDeviceAddressMessage), 100);
		}
	}

	ADXL345_ReadRegister(hi2c, REG_READ_ADDRESS, DEVID, &readData, 1);           // Cihaz ID'sini oku

	ADXL345_WriteRegister(hi2c, REG_WRITE_ADDRESS, POWER_CTL, 0x00);             // Güç kontrol modlarını sıfırla
	ADXL345_WriteRegister(hi2c, REG_WRITE_ADDRESS, POWER_CTL, 0x08);             // Ölçüm modunu aktifleştir

	ADXL345_WriteRegister(hi2c, REG_WRITE_ADDRESS, DATA_FORMAT, 0x01);           // ±4g aralığını seç

	ADXL345_WriteRegister(hi2c, REG_WRITE_ADDRESS, INT_MAP, 0x00);               // INT1 pinine yönlendir

	ADXL345_WriteRegister(hi2c, REG_WRITE_ADDRESS, INT_ENABLE, 0x64);            // Tek/double tap + free-fall interrupt'larını aktifleştir

	ADXL345_WriteRegister(hi2c, REG_WRITE_ADDRESS, TAP_AXES, 0x01);              // Yalnızca Z ekseni için tap aktif

	ADXL345_WriteRegister(hi2c, REG_WRITE_ADDRESS, THRESH_TAP, 40);              // Tap için eşik: 40 x 62.5mg = 2.5g

	ADXL345_WriteRegister(hi2c, REG_WRITE_ADDRESS, DUR, 32);                     // Tap süresi: 32 x 625µs = 20ms

	ADXL345_WriteRegister(hi2c, REG_WRITE_ADDRESS, LATENT, 20);                  // Tap sonrası gecikme: 25ms

	ADXL345_WriteRegister(hi2c, REG_WRITE_ADDRESS, WINDOW, 200);                 // Çift tap zaman penceresi: 250ms

	ADXL345_WriteRegister(hi2c, REG_WRITE_ADDRESS, THRESH_FF, 0x06);             // Free-fall eşik değeri: 0.375g

	ADXL345_WriteRegister(hi2c, REG_WRITE_ADDRESS, TIME_FF, 0x1E);               // Free-fall süresi: ~150ms
}

void ADXL345_READ_ALL_AXIS(I2C_HandleTypeDef *hi2c, int16_t *x, int16_t *y, int16_t *z)
{
	uint8_t axisValues[6];                                                      // 6 byte veri: X0,X1,Y0,Y1,Z0,Z1
	ADXL345_ReadRegister(hi2c, REG_READ_ADDRESS, DATAX0, axisValues, 6);

	*x = axisValues[1] << 8 | axisValues[0];                                    // X ekseni 16-bit
	*y = axisValues[3] << 8 | axisValues[2];                                    // Y ekseni 16-bit
	*z = axisValues[5] << 8 | axisValues[4];                                    // Z ekseni 16-bit
}

int16_t ADXL345_READ_X_AXIS(I2C_HandleTypeDef *hi2c)
{
	uint8_t axisValues[2];
	ADXL345_ReadRegister(hi2c, REG_READ_ADDRESS, DATAX0, axisValues, 2);
	return axisValues[1] << 8 | axisValues[0];                                  // X ekseni değeri (16-bit)
}

int16_t ADXL345_READ_Y_AXIS(I2C_HandleTypeDef *hi2c)
{
	uint8_t axisValues[2];
	ADXL345_ReadRegister(hi2c, REG_READ_ADDRESS, DATAY0, axisValues, 2);
	return axisValues[1] << 8 | axisValues[0];                                  // Y ekseni değeri (16-bit)
}

int16_t ADXL345_READ_Z_AXIS(I2C_HandleTypeDef *hi2c)
{
	uint8_t axisValues[2];
	ADXL345_ReadRegister(hi2c, REG_READ_ADDRESS, DATAZ0, axisValues, 2);
	return axisValues[1] << 8 | axisValues[0];                                  // Z ekseni değeri (16-bit)
}

void ADXL345_READ_ALL_G_VALUE(I2C_HandleTypeDef *hi2c, float *xG, float *yG, float *zG)
{
	int16_t x, y, z;
	ADXL345_READ_ALL_AXIS(hi2c, &x, &y, &z);
	*xG = x * ADXL345_SCALE_FACTOR;                                             // X eksenini G'ye çevir
	*yG = y * ADXL345_SCALE_FACTOR;                                             // Y eksenini G'ye çevir
	*zG = z * ADXL345_SCALE_FACTOR;                                             // Z eksenini G'ye çevir
}

float ADXL345_READ_X_G_VALUE(I2C_HandleTypeDef *hi2c)
{
	int16_t x = ADXL345_READ_X_AXIS(hi2c);
	return x * ADXL345_SCALE_FACTOR;                                            // X eksenini G cinsine çevir
}

float ADXL345_READ_Y_G_VALUE(I2C_HandleTypeDef *hi2c)
{
	int16_t y = ADXL345_READ_Y_AXIS(hi2c);
	return y * ADXL345_SCALE_FACTOR;                                            // Y eksenini G cinsine çevir
}

float ADXL345_READ_Z_G_VALUE(I2C_HandleTypeDef *hi2c)
{
	int16_t z = ADXL345_READ_Y_AXIS(hi2c);
	return z * ADXL345_SCALE_FACTOR;                                            // Z eksenini G cinsine çevir
}

uint8_t ADXL345_READ_TAP(I2C_HandleTypeDef *hi2c)
{
	uint8_t intSource, tapResult = 0;
	ADXL345_ReadRegister(hi2c, REG_READ_ADDRESS, INT_SOURCE, &intSource, 1);    // INT_SOURCE oku

	if((intSource >> 5 ) & 0x01) tapResult = 2;                                 // Çift tap (D5 set)
	else if ((intSource >> 6) & 0x01) tapResult = 1;                            // Tek tap (D6 set)
	else tapResult = 0;                                                         // Tap yok

	return tapResult;
}

uint8_t ADXL345_READ_FREE_FALL(I2C_HandleTypeDef *hi2c)
{
	uint8_t freeFallSource, freeFallResult = 0;
	ADXL345_ReadRegister(hi2c, REG_READ_ADDRESS, INT_SOURCE, &freeFallSource, 1);
	if((freeFallSource >> 2) & 0x01) freeFallResult = 1;                        // Serbest düşme algılandı (D2 set)
	else freeFallResult = 0;                                                   // Serbest düşme yok

	return freeFallResult;
}
