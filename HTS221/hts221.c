/*
 * hts221.c
 *
 *  Created on: Nov 6, 2023
 *      Author: bomba
 */

#include "hts221.h"

void htsInit()
{
	if (whoAmI())
	{
		i2c_send_byte(HTS221_WRITE_ADDRESS,CTRL_REG1_ADDRES, INIT_REG1);
	}
}

uint8_t whoAmI()
{
	if (i2c_master_read_byte(HTS221_READ_ADDRESS, HTS221_WHO_AM_I_ADDRES) == HTS221_WHO_AM_I_VALUE)
	{
		return 1;
	}else return 0;
}

float rawTemp()
{
	uint8_t buffer[2];

	buffer[0] = i2c_master_read_byte(HTS221_READ_ADDRESS,TEMP_OUT_L_ADDRES);
	buffer[1] = i2c_master_read_byte(HTS221_READ_ADDRESS,TEMP_OUT_H_ADDRES);

	return ((buffer[1] << 8) | buffer[0]) / 10;
}

float rawHum()
{
	uint8_t humBuff[2];

	humBuff[0] = i2c_master_read_byte(HTS221_READ_ADDRESS,HUMIDITY_OUT_L_ADDRESS);
	humBuff[1] = i2c_master_read_byte(HTS221_READ_ADDRESS,HUMIDITY_OUT_H_ADDRESS);

	return ((humBuff[1] << 8) | humBuff[0]) / 1000;
}
