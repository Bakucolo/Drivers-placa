//typedef me sirve para definir nuevos tipos de variables
//Ejemplo: typedef unsigned (sin signo) char uint8_t

//los typedef van en el .h porque son publicos

#deine SW_1_PIN 15
#deine SW_1_PIN 14
#deine SW_1_PIN 13
#deine SW_1_PIN 13

const uint16_t SWITCH_PIN[4]={SW_1_PIN,SW_1_PIN,SW_1_PIN,SW_1_PIN}; //los const el compilador los manda a la rom

typedef enum    //enum autonumera
{
    led_1=0,
    led_2,
    led_3,
    led_4,
    led_5,
    led_6,
    led_7,
    led_8
} led_t;


typedef enum
{
    sw_5=0,
    sw_6,
    sw_7,
    sw_8
}switch_t;

void ORT_BBO1_LedsOnOff(led_t d, bool estado)
{
    if(estado)
    {
            GPIO_SetBits(GPIOC,d);
    }
    else
    {
            GPIO_ResetBits(GPIOC,d);
    }
}

bool ORT_BBO1_SW_GetState(switch_t numSW)
{
    bool res;

    res = GPIO_ReadInputDataBit(GPIOB, SWITCH_PIN[numSW]);

    return res;

}

