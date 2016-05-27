// Hacer lo que falta para los pulsadores y los iniciadores de las
// funciones ("Init").

/*
ORT_BB01_Init()
    ORT_BB01_Leds_Init()
        ORT_BB01_LedsOnOff(numLed,estado)
        ORT_BB01_LedsToggle(numLed)
    ORT_BB01_PB_Init()
        ORT_BB01_PBGetState(numPB)
    ORT_BB01_SW_Init()
        ORT_BB01_SWGetState(numSW)
*/

// define buttons
#define PB_1_PIN 1
#define PB_2_PIN 2
#define PB_3_PIN 3
#define PB_4_PIN 4
// define switches
#define SW_1_PIN 15
#define SW_2_PIN 14
#define SW_3_PIN 13
#define SW_4_PIN 12

typedef enum { LED_1 = 0, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7, LED_8 } Led_t ;
typedef enum { PB_1 = 0, PB_2, PB_3, PB_4 } Button_t ;
typedef enum { SW_1 = 0, SW_2, SW_3, SW_4 } Switch_t ;

// LED
void ORT_BB01_LedsOnOff ( Led_t d, bool estado )
{
    if ( estado ) // 1 = true
        GPIO_SetBits ( GPIOC, d ) ;
    else          // 0 = false
        GPIO_ResetBits (GPIOC, d ) ;
}

// Button
const uint16_t BUTTON_PIN[4] = { PB_1_PIN, PB_2_PIN, PB_3_PIN, PB_4_PIN } ;

bool ORT_BB01_PBGetState ( Button_t numPB )
{
    bool res = GPIO_ReadInputDataBit ( GPIOB, BUTTON_PIN[numPB] ) ;
    return res ;
}


// Switch
const uint16_t SWITCH_PIN[4] = { SW_1_PIN, SW_2_PIN, SW_3_PIN, SW_4_PIN } ;

bool ORT_BB01_SWGetState ( Switch_t numSW )
{
    bool res = GPIO_ReadInputDataBit ( GPIOB, SWITCH_PIN[numSW] ) ;
    return res ;
}
