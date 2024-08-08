#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "stm32f1xx_hal.h"

#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏


#define LCD_W 240
#define LCD_H 240

extern SPI_HandleTypeDef hspi2;

//-----------------LCD端口定义---------------- 

#define LCD_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)//SCL=SCLK
#define LCD_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)

#define LCD_MOSI_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_7)//SDA=MOSI
#define LCD_MOSI_Set() GPIO_SetBits(GPIOA,GPIO_Pin_7)

#define LCD_RES_Clr()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,0)//RES  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,0)
#define LCD_RES_Set()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,1)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,0)//DC
#define LCD_DC_Set()   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,1)

#define LCD_BLK_Clr()  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,0)//BLK
#define LCD_BLK_Set()  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,1)



void LCD_Writ_Bus(uint8_t dat);
void LCD_WR_DATA8(uint8_t dat);//写入一个字节
void LCD_WR_DATA(uint16_t dat);//写入两个字节
void LCD_WR_REG(uint8_t dat);//写入一个指令
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//设置坐标函数
void LCD_Init(void);//LCD初始化
#endif




