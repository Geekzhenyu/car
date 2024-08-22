#include <math.h>
#include "motor.h"
#include "pca.h"

motor M[4];


void motor_init_struct()
{
    M[0].channel_a=13;M[0].channel_b=12;M[0].speed=0.0f;
    M[1].channel_a=3; M[1].channel_b=4; M[1].speed=0.0f;
    M[2].channel_a=1; M[2].channel_b=2; M[2].speed=0.0f;
    M[3].channel_a=14;M[3].channel_b=15;M[3].speed=0.0f;
}

void motor_speed(uint8_t which,float speed)
{
    if(speed==0.0f){
        PCA_SetOutput(M[which].channel_a,0.0f);
        PCA_SetOutput(M[which].channel_b,0.0f);
    }else if(fabsf(speed)>1.0f){
        PCA_SetOutput(M[which].channel_a,1.0f);
        PCA_SetOutput(M[which].channel_b,1.0f);
    }else{
        PCA_SetOutput(M[which].channel_a, (speed>0? fabsf(speed):0.0f));//我们需要更改通道的pwm编号保证其可以都正转
        PCA_SetOutput(M[which].channel_b, (speed<0? fabsf(speed):0.0f));
    }
}
//x，y，w速度如何均归一化?
void  motor_output(float value_vx,float value_vy,float value_w)
{
    //float total=4*value_vx;

    M[0].speed =value_vx + value_vy +value_w*S;
   // M[0].speed =M[0].speed/total;
    motor_speed(0,M[0].speed);

    M[1].speed =value_vx -value_vy -value_w*S;
   // M[1].speed =M[1].speed/total;
    motor_speed(1,M[1].speed);

    M[2].speed =value_vx + value_vy -value_w*S;
   // M[2].speed =M[2].speed/total;
    motor_speed(2,M[2].speed);

    M[3].speed =value_vx -value_vy +value_w*S;
   // M[3].speed =M[3].speed/total;
    motor_speed(3,M[3].speed);
}

void motor_init()
{
    PCA_Init();
    PCA_SetFreq(1526);
    PCA_SetOutput(0,1.0f);//限流A4950
    motor_init_struct();
}