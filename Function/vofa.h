//
// Created by MaoZhenYu on 24-8-15.
//

#ifndef VOFA_H
#define VOFA_H

//����VOFA��λ���ĸ�ʽ������鿴����

#include "stm32f1xx_hal.h"

extern   UART_HandleTypeDef huart1;//����򿪵��Ǵ���1�������޸�Ϊ��Ĵ���

void Vofa_print(const char *format, ...);

#endif //VOFA_H
