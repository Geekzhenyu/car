#include "pca.h"

extern I2C_HandleTypeDef hi2c2;

HAL_StatusTypeDef i2c_tx(uint8_t reg,uint8_t data){
    return HAL_I2C_Mem_Write(&hi2c2,PCA9685_IIC_ADDR,reg,
                             I2C_MEMADD_SIZE_8BIT,&data,1,1000);
}

HAL_StatusTypeDef i2c_rx(uint8_t reg,uint8_t* data){
    return HAL_I2C_Mem_Read(&hi2c2,PCA9685_IIC_ADDR,reg,
                            I2C_MEMADD_SIZE_8BIT,data,1,1000);
}

void PCA_Init(){
    i2c_tx(PCA9685_REG_MODE1,0x00);
}

//true:开启睡眠，false：关闭睡眠
void PCA_Sleep(bool sleep){
    uint8_t mode;
    i2c_rx(PCA9685_REG_MODE1,&mode);

    if(sleep) mode |= 0x01<<PCA9685_BIT_SLEEP;
    else mode &= ~(0x01<<PCA9685_BIT_SLEEP);

    i2c_tx(PCA9685_REG_MODE1,mode);
}



/*
 *选用的是PCA9685内部的时钟（25MHZ），freq最大为1526HZ；最小：24HZ
 * return 0 -> normal
 * return 1 -> freq too low/high
 * */
uint8_t PCA_SetFreq(float freq){

    float preScale = (float)(PCA9685_INTERNAL_OSC)/(4096.0f*freq)-1;
    if(preScale<3||preScale>255) return 1;

    PCA_Sleep(true);

    i2c_tx(PCA9685_REG_FREQ,(uint8_t)(preScale+0.5f));

    PCA_Sleep(false);

    return 0;
}

/*
 * 改变PWM输出的占空比
 * channel的取值：（1,2)-M3;(3,4)-M2;(12,13)-M1;(14,15)-M4
 * return 0 -> normal
 * return 1-> ratio error
*/
uint8_t PCA_SetOutput(uint8_t channel,float ratio) {
    if (ratio < 0 || ratio > 1) return 1;

    uint16_t on, off;
    if (ratio == 1) {
        on = 4096;
        off = 0;
    }
    else if (ratio == 0) {
        on = 0;
        off = 4096;
    }
    else {
        on = (uint16_t) (4096.0f * 0 + 0.5f);//延时输出了0.5个pwm周期
        off = (uint16_t) (4096.0f * ratio + 0.5f);
    }

    i2c_tx(PCA9685_REG_BASE_ON_L  + channel * 4, (uint8_t) on);
    i2c_tx(PCA9685_REG_BASE_ON_H  + channel * 4, (uint8_t) (on >> 8));
    i2c_tx(PCA9685_REG_BASE_OFF_L + channel * 4, (uint8_t) off);
    i2c_tx(PCA9685_REG_BASE_OFF_H + channel * 4, (uint8_t) (off >> 8));

    return 0;
}

uint8_t PCA_SetAll(float ratio){
    if(ratio<0||ratio>1) return 1;

    uint16_t on,off;
    if(ratio==1){on=4096;off=0;}
    else if(ratio==0){on=0;off=4096;}
    else{
        on = (uint16_t)(4096.0f * 0+0.5f);
        off = (uint16_t)(4096.0f*ratio+0.5f);
    }

    i2c_tx(PCA9685_REG_ALL_ON_L,(uint8_t)on);
    i2c_tx(PCA9685_REG_ALL_ON_H,(uint8_t)(on>>8));
    i2c_tx(PCA9685_REG_ALL_OFF_L,(uint8_t)off);
    i2c_tx(PCA9685_REG_ALL_OFF_H,(uint8_t)(off>>8));

    return 0;
}
