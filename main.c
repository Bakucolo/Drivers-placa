/******************************************************************************
 * Sistemas Embebidos
 * Project	:	Práctica N°3
 * File			: Programa principal
 * Autor		: GA
 ******************************************************************************
  Historial de cambios:

    Marzo 2014 - Version 1.0

******************************************************************************/
#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"

// ----------------------------------------------------------------------------
// Global variables
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Function prototypes
// ----------------------------------------------------------------------------
void delay(const int d);

// ----------------------------------------------------------------------------
// Main
// ----------------------------------------------------------------------------
int main(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  uint16_t c;

  // --------------------------------------------------------------------------
  // Inicializa USART1
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  // Setup pines PA9 y PA10 como Tx y Rx
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 115200;
  USART_Init(USART1, &USART_InitStructure);

  USART_Cmd(USART1, ENABLE);

	// --------------------------------------------------------------------------
  // Inicializa pines para manejo de los LEDS
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  // Configura los pines de los leds (PC8 y PC9) como salida
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_Init(GPIOC, &GPIO_InitStructure); // setup para PC8
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_Init(GPIOC, &GPIO_InitStructure); // setup para PC9


  // --------------------------Lazo principal----------------------------------
  while(1)
  {
    // Set PC9, Reset PC8
		GPIO_SetBits(GPIOC, GPIO_Pin_9);
		GPIO_ResetBits(GPIOC, GPIO_Pin_8);

		// Espera por un dato por la línea serie
    while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET){
			;
		}
    c = USART_ReceiveData(USART1);

		c++;

    // Transmite el caracter recibido + 1
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){
			;
		}
    USART_SendData( USART1, c );

    // Demora ~ 1 s
    delay(SystemCoreClock/8);

    // Reset PC9, Set PC8
		GPIO_ResetBits(GPIOC, GPIO_Pin_9);
		GPIO_SetBits(GPIOC, GPIO_Pin_8);

  }
}

void delay(const int d)
{
  volatile int i;

  for(i=d; i>0; i--){ ; }

  return;
}
