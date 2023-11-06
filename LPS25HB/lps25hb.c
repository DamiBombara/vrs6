/*
 * lps25hb.c
 *
 *  Created on: Nov 6, 2023
 *      Author: bomba
 */

#include "lps25hb.h"
#include <math.h>

int32_t pressure = 0;

uint8_t whoAmI_LPS()
{
	if (i2c_master_read_byte(LPS25HB_READ_ADDRESS, LPS25HB_WHO_AM_I_ADDRES) == LPS25HB_WHO_AM_I_VALUE){
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
	return ((288.15/0.0065) * log(101325/pressure));
}

int32_t getPressure()
{
    if (whoAmI_LPS())
    {
    	uint8_t pressureXL = i2c_master_read_byte(LPS25HB_READ_ADDRESS, PRESS_OUT_XL_ADDRES);
    	uint8_t pressureL = i2c_master_read_byte(LPS25HB_READ_ADDRESS, PRESS_OUT_L_ADDRES);
    	uint8_t pressureH = i2c_master_read_byte(LPS25HB_READ_ADDRESS, PRESS_OUT_H_ADDRES);

    	pressure = (int32_t) pressureH << 16 | (int32_t) pressureL << 8 | pressureXL;
    	pressure = pressure / 4096.0f;
    }
    return pressure;
}
