/*
 * lps25hb.c
 *
 *  Created on: Nov 6, 2023
 *      Author: bomba
 */

#include "lps25hb.h"
#include <math.h>

float firstHeight = 0;
float lastHeight = 0;

float returnHeight()
{
	if (whoAmILPS())
	{
		return calculateHeight();
	} else return 0.0;
}

float calculateHeight()
{
	returnPressure();
    //return (T / L) * (1 - pow(lastHeight  / firstHeight , (R * L) / (g * M)));
	return 0;
}

void lpsInit()
{
	i2c_send_byte(LPS25HB_WRITE_ADDRESS, LPS25HB_CTRL_REG1 , LPS25HB_INIT_REG1);
	firstHeight = returnPressure();
}

uint8_t whoAmILPS()
{
	if (i2c_master_read_byte(LPS25HB_READ_ADDRESS, LPS25HB_WHO_AM_I_ADDRES) == LPS25HB_WHO_AM_I_VALUE){
		return 1;
	} else return 0;
}

int32_t rawPressure()
{
    uint8_t pressureXL = i2c_master_read_byte(LPS25HB_READ_ADDRESS, PRESS_OUT_XL_ADDRES);
    uint8_t pressureL = i2c_master_read_byte(LPS25HB_READ_ADDRESS, PRESS_OUT_L_ADDRES);
    uint8_t pressureH = i2c_master_read_byte(LPS25HB_READ_ADDRESS, PRESS_OUT_H_ADDRES);

    int32_t raw_pressure = (int32_t) pressureH << 16 | (int32_t) pressureL << 8 | pressureXL;

    return raw_pressure;
}

float returnPressure()
{
	float pressure_hPa = 0;

	if (whoAmILPS())
	{
		float raw_pressure = rawPressure();

		pressure_hPa = raw_pressure / 4096.0f;

		lastHeight = pressure_hPa;
	}
	return pressure_hPa;
}
