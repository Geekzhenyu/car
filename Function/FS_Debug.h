#ifndef FS_DEBUG
#define FS_DEBUG

#include "stm32f1xx_hal.h"

#define DEBUG_EN 1


void FS_Debug(char *p,...) ;  //  printf 
void print(UART_HandleTypeDef* huart, const char* buf, ...);

#endif

