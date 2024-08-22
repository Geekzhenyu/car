#ifndef PIONEER_V0_ENCODER_H
#define PIONEER_V0_ENCODER_H

#include "stm32f1xx_hal.h"

#define REDUCE 30
#define PULSES 2000

typedef struct{
    TIM_HandleTypeDef* timer;
    int16_t round;
    float position,speed;
} Encoder;

void Encoder_Setup(TIM_HandleTypeDef* EA1, TIM_HandleTypeDef* EA2, TIM_HandleTypeDef* EB1, TIM_HandleTypeDef* EB2);
float Encoder_Calculate(unsigned char which,float interval);

#endif //PIONEER_V0_ENCODER_H
