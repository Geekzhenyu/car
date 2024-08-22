#ifndef PIONEER_V0_MOTOR_H
#define PIONEER_V0_MOTOR_H

#include "stm32f1xx_hal.h"
#define S 0.143 //S=L/2+H/2,µ¥Î»Îªm

typedef struct{
    uint8_t channel_a,channel_b;
    float speed;
}motor;

void motor_init();
void motor_output(float value_vx,float value_vy,float value_w);
void motor_speed(uint8_t which,float speed);
void motor_init_struct();


#endif //PIONEER_V0_MOTOR_H
