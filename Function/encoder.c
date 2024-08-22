#include "encoder.h"
#include "FS_Debug.h"

Encoder eA1,eA2,eB1,eB2;

void Encoder_Setup(TIM_HandleTypeDef* EA1, TIM_HandleTypeDef* EA2, TIM_HandleTypeDef* EB1, TIM_HandleTypeDef* EB2){
    eA1.timer = EA1;
    HAL_TIM_Encoder_Start(eA1.timer,TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(eA1.timer,TIM_CHANNEL_2);
    eA1.round=0;
    eA1.position=0;
    eA1.speed=0;
   __HAL_TIM_SetCounter(eA1.timer,0);
   __HAL_TIM_ENABLE_IT(eA1.timer,TIM_IT_UPDATE);
    FS_Debug("EA1 init\r\n");

    eA2.timer = EA2;
    HAL_TIM_Encoder_Start(eA2.timer,TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(eA2.timer,TIM_CHANNEL_2);
    eA2.round=0;
    eA2.position=0;
    eA2.speed=0;
    __HAL_TIM_SetCounter(eA2.timer,0);
    __HAL_TIM_ENABLE_IT(eA2.timer,TIM_IT_UPDATE);
    FS_Debug("EA2 init\r\n");

    eB1.timer = EB1;
    HAL_TIM_Encoder_Start(eB1.timer,TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(eB1.timer,TIM_CHANNEL_2);
    eB1.round=0;
    eB1.position=0;
    eB1.speed=0;
    __HAL_TIM_SetCounter(eB1.timer,0);
    __HAL_TIM_ENABLE_IT(eB1.timer,TIM_IT_UPDATE);
    FS_Debug("EB1 init\r\n");

    eB2.timer = EB2;
    HAL_TIM_Encoder_Start(eB2.timer,TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(eB2.timer,TIM_CHANNEL_2);
    eB2.round=0;
    eB2.position=0;
    eB2.speed=0;
    __HAL_TIM_SetCounter(eB2.timer,0);
    __HAL_TIM_ENABLE_IT(eB2.timer,TIM_IT_UPDATE);
    FS_Debug("EB2 init\r\n");

}
//interval 单位是s
float Encoder_Calculate(uint8_t which,float interval){
    Encoder* enc;
    float position;
    if(which==0) enc=&eA1;
    else if(which ==1) enc=&eB1;
    else if(which ==2) enc=&eA2;
    else enc=&eB2;//这里不知道为什么列成which==‘Ax’不能超过2个
    int16_t pulse=__HAL_TIM_GetCounter(enc->timer);
    __HAL_TIM_SetCounter(enc->timer,0);
    position = enc->round*65536+pulse;
    enc->round=0;
    position=pulse;
    position/=(REDUCE*PULSES);
    enc->position+=position*0.17;
    enc->speed=position/interval;
    enc->speed*=0.17;
    return enc->speed;
}