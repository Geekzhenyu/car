//
// Created by MaoZhenYu on 24-8-15.
//

#include "vofa.h"
#include "stdarg.h"
#include "stdio.h"

// ��printf��ʽд���������\r\n
void Vofa_print(const char *format, ...)
{
    uint8_t txBuffer[124];
    uint32_t n;
    va_list args;
    va_start(args, format);
    n = vsnprintf((char *)txBuffer, 124, format, args);
    //....�ڴ��滻��Ĵ��ڷ��ͺ���...........
    HAL_UART_Transmit(&huart1, (uint8_t *)txBuffer, n,100);
    //......................................
    va_end(args);
}