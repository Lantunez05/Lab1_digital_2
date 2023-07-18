/* 
 * File:   Interrupcion.h
 * Author: Luis Antunez
 *
 * Created on 13 de julio de 2023, 03:45 PM
 */

#ifndef INTERRUPCION_H
#define	INTERRUPCION_H

#include <xc.h> // include processor files - each processor file is guarded.

void iocb_init (uint8_t pin);
void ioc_config (int pin);

// Configuracion del ADC
void adc_init(int channel);
int adc_read ();
void adc_change_channel(int channel);
int adc_get_channel();

//Displays
int Disp_bajos(int vADC);
int Disp_altos (int vADC);
uint8_t tabla (int display);

// Configuracion del timer0
void timer0_config (void);


#endif	/* INTERRUPCION_H */
