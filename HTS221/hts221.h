/*
 * hts221.h
 *
 *  Created on: Nov 6, 2023
 *      Author: bomba
 */

#ifndef HTS221_H_
#define HTS221_H_

#include "stm32f3xx.h"
#include "i2c.h"

#define 	HTS221_READ_ADDRESS			0xBFU
#define 	HTS221_WRITE_ADDRESS		0xBEU

#define 	HTS221_WHO_AM_I_VALUE		0xBCU
#define 	HTS221_WHO_AM_I_ADDRESS		0x0FU

#define 	CTRL_REG1_ADDRESS			0x20U
#define 	INIT_REG1               	0x86U

#define 	TEMP_OUT_H_ADDRESS			0x2BU
#define 	TEMP_OUT_L_ADDRESS			0x2AU

#define 	HUMIDITY_OUT_H_ADDRESS		0x29U
#define 	HUMIDITY_OUT_L_ADDRESS		0x28U


uint8_t whoAmI();

void htsInit();

float getTemp();
float getHum();

#endif /* HTS221_H_ */
