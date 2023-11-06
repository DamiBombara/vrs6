/*
 * lps25hb.c
 *
 *  Created on: Nov 6, 2023
 *      Author: bomba
 */

#include "lps25hb.h"
#include <math.h>

float pressure = 0;

uint8_t whoAmI_LPS()
{
	if (i2c_master_read_byte(LPS25HB_READ_ADDRESS, LPS25HB_WHO_AM_I_ADDRESS) == LPS25HB_WHO_AM_I_VALUE)
	{
		return 1;
	} else return 0;
}

void lpsInit()
{
	if (whoAmI_LPS())
	{
		i2c_send_byte(LPS25HB_WRITE_ADDRESS, LPS25HB_CTRL_REG1 , LPS25HB_INIT_REG1);
	}
}

float calculateHeight()
{
	float R = 8.314;
	float T0 = 288.15;
	float P0 = 994.44;
	float L = 0.0065;
	float g = 9.81;

	return -((T0 / L) * (1 - powf((pressure / P0), (R * L / g))));
}

float getPressure()
{
    if (whoAmI_LPS())
    {
    	uint8_t pressureXL = i2c_master_read_byte(LPS25HB_READ_ADDRESS, PRESS_OUT_XL_ADDRESS);
    	uint8_t pressureL = i2c_master_read_byte(LPS25HB_READ_ADDRESS, PRESS_OUT_L_ADDRESS);
    	uint8_t pressureH = i2c_master_read_byte(LPS25HB_READ_ADDRESS, PRESS_OUT_H_ADDRESS);

    	pressure = (int32_t) pressureH << 16 | (int32_t) pressureL << 8 | pressureXL;
    	pressure = pressure / 4096.f;
    }
    return pressure;
}
