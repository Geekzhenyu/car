//
// Created by MaoZhenYu on 24-8-15.
//

#ifndef VOFA_H
#define VOFA_H

//适配VOFA上位机的格式，方便查看数据

#include "stm32f1xx_hal.h"

extern   UART_HandleTypeDef huart1;//这里打开的是串口1，可以修改为别的串口

void Vofa_print(const char *format, ...);

#endif //VOFA_H
