#ifndef _MAX6675_H
#define _MAX6675_H

#include "bsp_system.h"

// SPI通信超时时间（毫秒）
#define SPI_TIMEOUT 1000

// MAX6675设备结构体定义
typedef struct {
    SPI_HandleTypeDef *hspi;    // 指向SPI句柄的指针
    GPIO_TypeDef* Thx_CS_Port;  // 片选引脚所在的GPIO端口
    uint16_t Thx_CS_Pin;        // 片选引脚编号
    uint16_t Thx_rawdata;       // 最近一次读取的原始数据（16位）
    float   Thx_celcius;        // 最近一次转换后的温度值
    bool    connected;          // FALSE为热电偶连接断开，TRUE为连接正常
} ThermoCouple;

// 读取MAX6675的温度数据
void ReadThermoCouple(ThermoCouple *Th);
void read_temp_task(void);

#endif
