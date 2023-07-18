#include "Interrupcion.h"
#define _XTAL_FREQ 4000000
uint8_t get = 0;

// Programacion de la interrupcion en el puerto B
void iocb_init (uint8_t pin)
{
    if (INTCONbits.RBIF)
    {
        if (RB0 == 0)
        {
            PORTD++;
            __delay_ms(500);
        }
        else if (RB1 == 0)
        {
            PORTD--;
            __delay_ms(500);
        
        }
        else if (get == 0)
        {
           PORTD = 0;
           PORTD = adc_get_channel();
        }
    }
    
    RBIF = 0;
    
    return;

}

void ioc_config (int pin)
{
    // PULL_UPS (PUERTO B)
    TRISB |= (1<<pin);
    OPTION_REGbits.nRBPU = 0;
    WPUB |= (1<<pin);
    IOCB |= (1<<pin);
    
    // Interrupcion del purto B
    INTCONbits.RBIF = 0; // Borrar la bandera de interrupción por cambio de estado del puerto B
    PORTB = PORTB;
    INTCONbits.RBIE = 1; // Habilitar la interrupción por cambio de estado del puerto B
    INTCONbits.GIE = 1;  // Interrupciones globales
    
}

// Programacion del ADC
void adc_init(int channel)
{
    //Activar el ADC
    ADCON0bits.ADON = 1;
    
    __delay_ms(2);
    
    if ( channel == 1)
    {
        ADCON0bits.CHS = 0b00000001; // Seleccion del canal AN1
    }  
    
    //voltaje de referencia
    ADCON1bits.VCFG1 = 0;      // Volatje de referencia 0
    ADCON1bits.VCFG0 = 0;      // Volatje de referencia 0   
    
    //interrupciones
    PIE1bits.ADIE = 1;
    ADIF = 0;
 
    ADCON0bits.ADCS = 0b01; // divisor de reloj de 32
    ADCON1bits.ADFM = 0;    // Justificado a la izquierda 
}

int adc_read()
{
    return ADRESH;
}

void adc_change_channel(int channel)
{
    if(channel < 14)
        ADCON0bits.CHS = 0b00000001;  
    return;
}

int adc_get_channel()
{
    char chan = ADCON0bits.CHS;
    return chan; 
}

// Porgramacion de los displays
int Disp_bajos(int vADC)
{
    //int bit_bajo = 0X0F;
    int bajo = (vADC & 0X0F);
    return bajo;
}
int Disp_altos (int vADC)
{
    //int bit_alto = 0XF0;
    int alto = (vADC & 0XF0);
    return alto;
}

uint8_t tabla (int display)
{
    switch (display) {
            case 0:
                return  0b00111111;
                break;
            case 1:
                return  0b10000110;
                break;
            case 2:
                return  0b11011011;
                break;
            case 3:
                return  0b11001111;
                break;
            case 4:
                return  0b11100110;
                break;
            case 5:
                return  0b11101101;
                break;
            case 6:
                return  0b11111101;
                break;
            case 7:
                return  0b10000111;
                break;
            case 8:
                return  0b11111111;
                break;
            case 9:
                return  0b11100111;
                break;
            case 10:
                return 0b01110111;  //A
                break;
            case 11:
                return 0b01111100;  //b
                break;
            case 12:
                return 0b00111001;  //C
                break;
            case 13:
                return 0b01011110;  //d
                break;
            case 14:
                return 0b01111001;  //E
                break;
            case 15:
                return 0b01110001;  //F
                break;
            default:
                return 0b00111111;  //0
                break;    
    }

}

void timer0_config (void)
{
    // Configuracion del timer0
    OPTION_REGbits.T0CS = 0;      
    
    OPTION_REGbits.T0SE = 0;      
    OPTION_REGbits.PSA = 0;       
    
    OPTION_REGbits.PS2 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 1;      //prescaler 1:256
    INTCONbits.T0IE = 1;
    return;
}
