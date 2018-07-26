#pragma once

#include <SPI.h>
#include "Config.h"

//! @name LTC2636 Command Codes
//!@{
//! OR'd together with the DAC address to form the command byte
#define  LTC2636_CMD_WRITE               0x00  //!< Write to input register n
#define  LTC2636_CMD_UPDATE              0x10  //!< Update (power up) DAC register n
#define  LTC2636_CMD_WRITE_UPDATE_ALL    0x20  //!< Write to input register n, update (power up) all
#define  LTC2636_CMD_WRITE_UPDATE        0x30  //!< Write to input register n, update (power up) all
#define  LTC2636_CMD_POWER_DOWN          0x40  //!< Power down n
#define  LTC2636_CMD_POWER_DOWN_ALL      0x50  //!< Power down chip (all DACs and reference)
#define  LTC2636_CMD_INTERNAL_REFERENCE  0x60  //!< Select internal reference (power up reference)
#define  LTC2636_CMD_EXTERNAL_REFERENCE  0x70  //!< Select external reference (power down internal reference)
#define  LTC2636_CMD_NO_OPERATION        0xF0  //!< No operation
//!@}

//! @name LTC2636 DAC addresses
//! @{
//! Which DAC to operate on
#define  LTC2636_DAC_A     0x00
#define  LTC2636_DAC_B     0x01
#define  LTC2636_DAC_C     0x02
#define  LTC2636_DAC_D     0x03
#define  LTC2636_DAC_E     0x04
#define  LTC2636_DAC_F     0x05
#define  LTC2636_DAC_G     0x06
#define  LTC2636_DAC_H     0x07
#define  LTC2636_DAC_ALL   0x0F
//! @}

#define QUADMUX_MAXVALUE 4095


class QuadMux
{
	int Clock;
	int ChipSelect;

public:
	QuadMux(int clock, int chipSelect) {
		Clock = clock;
		ChipSelect = chipSelect;
		SPI.begin(); 					//see: https://www.pjrc.com/teensy/td_libs_SPI.html
		SPI.setSCK(SCK);				//move SPI to alernate pin 
	}

	void Reset() {
		Write(LTC2636_CMD_WRITE_UPDATE_ALL, 0, 0);
	}

	void Write16(int cmd, int addr, int value) {
		digitalWrite(ChipSelect, LOW);
		SPI.transfer(cmd | addr);
		SPI.transfer16(value);
		digitalWrite(ChipSelect, HIGH);
	}

	void Write(int cmd, int addr, int value_12bit) {
		Write16(cmd, addr, value_12bit << 4);
	}

	void Write(int addr, int value) {
		Write(LTC2636_CMD_WRITE_UPDATE, addr, value);
	}
};
