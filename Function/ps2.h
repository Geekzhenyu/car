#ifndef PIONEER_V0_PS2_H
#define PIONEER_V0_PS2_H

#include "stm32f1xx_hal.h"
#include "main.h"

#define PS2_Start() HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_RESET)
#define PS2_Close() HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_SET)

#define PS2_ClockH() HAL_GPIO_WritePin(CLK_GPIO_Port,CLK_Pin,GPIO_PIN_SET)
#define PS2_ClockL() HAL_GPIO_WritePin(CLK_GPIO_Port,CLK_Pin,GPIO_PIN_RESET)

#define PS2_WriteH() HAL_GPIO_WritePin(MOSI_GPIO_Port,MOSI_Pin,GPIO_PIN_SET)
#define PS2_WriteL() HAL_GPIO_WritePin(MOSI_GPIO_Port,MOSI_Pin,GPIO_PIN_RESET)

#define PS2_Read() HAL_GPIO_ReadPin(MISO_GPIO_Port,MISO_Pin)

#define PS2_SELECT 1
#define PS2_L3 2
#define PS2_R3 3
#define PS2_START 4
#define PS2_UP 5
#define PS2_RIGHT 6
#define PS2_DOWN 7
#define PS2_LEFT 8
#define PS2_L2 9
#define PS2_R2 10
#define PS2_L1 11
#define PS2_R1 12
#define PS2_TRIANGLE 13
#define PS2_CYCLE 14
#define PS2_X 15
#define PS2_SQUARE 16

#define PS2_RX 5
#define PS2_RY 6
#define PS2_LX 7
#define PS2_LY 8

typedef struct{
    float lx;
    float ly;
    float rx;
}PS2Control;

void delay_us(__IO uint32_t delay);
void PS2_Init();
void PS2_SPI_Init();
void PS2_GetData();//已经将计算x，y，w的算法加入，直接可以计算出手柄想要达到的速度
uint8_t PS2_GetAnalog(uint8_t key);
uint8_t PS2_IsKey(uint8_t key);

#endif //PIONEER_V0_PS2_H
