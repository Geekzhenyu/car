//
// Created by MaoZhenYu on 24-8-15.
//

#include "vofa.h"
#include "stdarg.h"
#include "stdio.h"

// 按printf格式写，最后必须加\r\n
void Vofa_print(const char *format, ...)
{
    uint8_t txBuffer[124];
    uint32_t n;
    va_list args;
    va_start(args, format);
    n = vsnprintf((char *)txBuffer, 124, format, args);
    //....在此替换你的串口发送函数...........
    HAL_UART_Transmit(&huart1, (uint8_t *)txBuffer, n,100);
    //......................................
    va_end(args);
}