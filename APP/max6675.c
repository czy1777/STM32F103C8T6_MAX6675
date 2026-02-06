#include "max6675.h"

// 布尔值定义
#define TRUE  1
#define FALSE 0

// 声明温度传感器结构体
ThermoCouple thermo = {&hspi1, GPIOB, GPIO_PIN_1, 0, 0.0f, false};

// SPI接收1字节
static uint8_t SPI_RxByte(SPI_HandleTypeDef *hspi)
{
  uint8_t dummy = 0xFF, data = 0;
  while (HAL_SPI_GetState(hspi) != HAL_SPI_STATE_READY);  // 等待SPI就绪
  HAL_SPI_TransmitReceive(hspi, &dummy, &data, 1, SPI_TIMEOUT);  // 收发1字节
  return data;
}

// 读取MAX6675数据并更新到结构体
void ReadThermoCouple(ThermoCouple *Th)
{
	unsigned short data;

	HAL_GPIO_WritePin(Th->Thx_CS_Port, Th->Thx_CS_Pin, GPIO_PIN_RESET);  // 拉低片选，开始通信
	
	// 读取16位原始数据
	data = SPI_RxByte(Th->hspi) << 8;
	data |= SPI_RxByte(Th->hspi);
	
	HAL_GPIO_WritePin(Th->Thx_CS_Port, Th->Thx_CS_Pin, GPIO_PIN_SET);  // 拉高片选，结束通信
	
	Th->Thx_rawdata = data;  // 保存原始数据
	
	// 判断热电偶连接状态（bit3为1则断开）
	Th->connected = (data & 4) ? FALSE : TRUE;
	
	// 计算温度（右移3位去除状态位，乘以0.25℃/步）
	Th->Thx_celcius = (data >> 3) * 0.25f;
}

// 温度读取任务
void read_temp_task(void) 
{
    ReadThermoCouple(&thermo);
    // 打印温度
    my_printf(&huart1, "Temp: %.2f C, Connected: %d\r\n", 
             thermo.Thx_celcius, thermo.connected);
}
