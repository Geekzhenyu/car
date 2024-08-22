#ifndef PIONEER_V0_PCA_H
#define PIONEER_V0_PCA_H

#include "stm32f1xx_hal.h"

typedef uint8_t bool;
#define false (0x00u)
#define true (!false)

void PCA_Init();
uint8_t PCA_SetAll(float ratio);
uint8_t PCA_SetOutput(uint8_t channel,float ratio);
uint8_t PCA_SetFreq(float freq);
void PCA_Sleep(bool sleep);

#define PCA9685_IIC_ADDR (0x40<<1)
#define PCA9685_INTERNAL_OSC 25000000

#define PCA9685_BIT_RESET   7
#define PCA9685_BIT_EXTCLK  6
#define PCA9685_BIT_AI      5
#define PCA9685_BIT_SLEEP   4
#define PCA9685_BIT_SUBADR1 3
#define PCA9685_BIT_SUBADR2 2
#define PCA9685_BIT_SUBADR3 1
#define PCA9685_BIT_ALLCALL 0

#define PCA9685_REG_MODE1       0x00
#define PCA9685_REG_MODE2       0x01
#define PCA9685_REG_SUB_ADDR1   0x02
#define PCA9685_REG_SUB_ADDR2   0x03
#define PCA9685_REG_SUB_ADDR3   0x04
#define PCA9685_REG_ALL_CALL    0x05
#define PCA9685_REG_BASE_ON_L   0x06
#define PCA9685_REG_BASE_ON_H   0x07
#define PCA9685_REG_BASE_OFF_L  0x08
#define PCA9685_REG_BASE_OFF_H  0x09
#define PCA9685_REG_ALL_ON_L    0xFA
#define PCA9685_REG_ALL_ON_H    0xFB
#define PCA9685_REG_ALL_OFF_L   0xFC
#define PCA9685_REG_ALL_OFF_H   0xFD
#define PCA9685_REG_FREQ        0xFE

#endif //PIONEER_V0_PCA_H
