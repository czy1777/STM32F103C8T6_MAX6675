#ifndef _BSP_SYSTEM_H
#define _BSP_SYSTEM_H

#include "main.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "math.h"

#include "sys.h"
#include "adc.h"
#include "tim.h"
#include "i2c.h"
#include "usart.h"
#include "spi.h"

#include "scheduler.h"
#include "ringbuffer.h"
#include "max6675.h"

extern uint16_t uart_rx_index;
extern uint32_t uart_rx_ticks;
extern uint8_t uart_rx_buffer[10];

extern uint8_t uart_rx_dma_buffer[1000];    // 接收缓存

#endif
