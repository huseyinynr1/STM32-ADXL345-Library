/*
 * adxl345_Register.h
 *
 *  Created on: Mar 18, 2025
 *      Author: husey
 */

#ifndef INC_ADXL345_REGISTER_H_
#define INC_ADXL345_REGISTER_H_

#define REG_WRITE_ADDRESS  0xA6    // ADXL345 I2C yazma adresi (0x53 << 1)
#define REG_READ_ADDRESS   0xA7    // ADXL345 I2C okuma adresi (0x53 << 1 | 0x01)

#define DEVID              0x00    // Cihaz kimliği (her zaman 0xE5, sensör tanıma)

#define THRESH_TAP         0x1D    // Tap (dokunma) eşiği, 62.5 mg/LSB
#define OFSX               0x1E    // X ekseni ofset ayarı
#define OFSY               0x1F    // Y ekseni ofset ayarı
#define OFSZ               0x20    // Z ekseni ofset ayarı

#define DUR                0x21    // Tap süresi, 625 µs/LSB
#define LATENT             0x22    // Tap gecikme süresi, 1.25 ms/LSB
#define WINDOW             0x23    // Çift tap penceresi, 1.25 ms/LSB

#define THRESH_ACT         0x24    // Aktivite eşiği, 62.5 mg/LSB
#define THRESH_INACT       0x25    // İnaktivite eşiği, 62.5 mg/LSB
#define TIME_INACT         0x26    // İnaktivite süresi, 1 s/LSB

#define THRESH_FF          0x28    // Serbest düşüş eşiği, 62.5 mg/LSB
#define TIME_FF            0x29    // Serbest düşüş süresi, 5 ms/LSB

#define TAP_AXES           0x2A    // Hangi eksenlerin tap algılayacağını seçer (X/Y/Z)

#define POWER_CTL          0x2D    // Güç kontrolü, ölçüm modunu ayarlamak için
#define INT_ENABLE         0x2E    // Hangi olayların interrupt oluşturacağını belirler
#define INT_MAP            0x2F    // Interrupt pin eşlemesi (INT1 / INT2)
#define INT_SOURCE         0x30    // Hangi olayın interrupt ürettiğini gösterir (Read-only)

#define DATA_FORMAT        0x31    // Veri aralığı (±2g, ±4g...) ve çözünürlük ayarları
#define DATAX0             0x32    // X ekseni düşük byte
#define DATAX1             0x33    // X ekseni yüksek byte
#define DATAY0             0x34    // Y ekseni düşük byte
#define DATAY1             0x35    // Y ekseni yüksek byte
#define DATAZ0             0x36    // Z ekseni düşük byte
#define DATAZ1             0x37    // Z ekseni yüksek byte

#endif /* INC_ADXL345_REGISTER_H_ */
