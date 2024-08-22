#include "ps2.h"
#include "string.h"

#define CPU_FREQUENCY_MHZ 72
PS2Control PS2;

void delay_us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;
    while (delay != 0){
        temp = delay > 900 ? 900 : delay;
        last = SysTick->VAL;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
            do val = SysTick->VAL;
            while ((val < last) && (val >= curr));
        else{
            curr += CPU_FREQUENCY_MHZ * 1000;
            do val = SysTick->VAL;
            while ((val <= last) || (val > curr));
        }
        delay -= temp;
    }
}

uint8_t ps2Data[9];

void PS2_SPI_Init(){
    PS2_ClockH();
}

void PS2_WriteByte(uint8_t txData){
    uint8_t ref=0x01;
    ps2Data[1]=0x00;
    for(uint8_t i=0;i<8;i++){
        if(ref&txData) PS2_WriteH();
        else PS2_WriteL();
        PS2_ClockH();
        delay_us(10);
        PS2_ClockL();
        delay_us(10);
        PS2_ClockH();
        if(PS2_Read()) ps2Data[1]=ref|ps2Data[1];
        ref<<=1;
    }
}
//手柄进入初始化（类似于呼叫）
void PS2_ShortPoll(){
    PS2_Start();
    delay_us(10);
    PS2_WriteByte(0x01);
    PS2_WriteByte(0x42);
    PS2_WriteByte(0x00);
    PS2_WriteByte(0x00);
    PS2_WriteByte(0x00);
    PS2_Close();
}
//进入配置模式
void PS2_EnterConfig(){
    PS2_Start();
    delay_us(10);
    PS2_WriteByte(0x01);
    PS2_WriteByte(0x43);
    PS2_WriteByte(0x00);
    PS2_WriteByte(0x01);
    PS2_WriteByte(0x00);
    PS2_WriteByte(0x00);
    PS2_WriteByte(0x00);
    PS2_WriteByte(0x00);
    PS2_WriteByte(0x00);
    PS2_Close();
}

void PS2_TurnToAnalog(){
    PS2_Start();
    delay_us(10);
    PS2_WriteByte(0x01);
    PS2_WriteByte(0x44);
    PS2_WriteByte(0x00);
    PS2_WriteByte(0x01);//analog=0x01；   digital=0x00;
    PS2_WriteByte(0x00);
    PS2_WriteByte(0x00);
    PS2_WriteByte(0x00);
    PS2_WriteByte(0x00);
    PS2_Close();
}
//震动设置
void PS2_VibrationConfig(){
    PS2_Start();
    delay_us(10);
    PS2_WriteByte(0x01);
    PS2_WriteByte(0x4D);
    PS2_WriteByte(0x00);
    PS2_WriteByte(0x00);
    PS2_WriteByte(0x01);
    PS2_Close();
}
//保存配置
void PS2_ExitConfig(){
    PS2_Start();
    delay_us(10);
    PS2_WriteByte(0x01);
    PS2_WriteByte(0x43);
    PS2_WriteByte(0x00);
    PS2_WriteByte(0x00);
    PS2_WriteByte(0x5A);
    PS2_WriteByte(0x5A);
    PS2_WriteByte(0x5A);
    PS2_WriteByte(0x5A);
    PS2_WriteByte(0x5A);
    PS2_Close();
}

void PS2_Init(){
    PS2_ShortPoll();
    PS2_ShortPoll();
    PS2_ShortPoll();
    PS2_EnterConfig();
    PS2_TurnToAnalog();
    PS2_VibrationConfig();
    PS2_ExitConfig();
}

void PS2_GetData(){
    memset(ps2Data,0x00,sizeof(ps2Data));
    uint8_t byte=0;
    uint8_t ref=0x01;
    PS2_Start();
    PS2_WriteByte(0x01);
    PS2_WriteByte(0x42);
    for(byte=2;byte<9;byte++){
        ref=0x01;
        for(uint8_t i=0;i<8;i++){
            PS2_ClockH();
            PS2_ClockL();
            delay_us(10);
            PS2_ClockH();
            if(PS2_Read()) ps2Data[byte]=ref|ps2Data[byte];
            ref<<=1;
        }
        delay_us(10);
    }
    PS2_Close();

}

uint8_t PS2_GetAnalog(uint8_t key){
    if(key<PS2_RX||key>PS2_LY) return 0;
    return ps2Data[key];
}

uint8_t PS2_IsKey(uint8_t key){
    if(key<PS2_SELECT||key>PS2_SQUARE) return 0x00;
    uint16_t KEY = ps2Data[4]<<8|ps2Data[3];
    uint16_t MASK=0x01;
    MASK<<=(key-1);
    return MASK&key;
}
