/*
 * File:   main.c
 * Author: Jorge Lorenzana
 * Ejemplo de uso de I2C Master
 * Created on 19 de febrero de 2020
 */
//*****************************************************************************
// Palabra de configuración
//*****************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <stdint.h>
#include <pic16f887.h>
#include "I2C_Init.h"
#include "LCD_Init.h"
#include <xc.h>
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000

uint8_t enteroadc = 0, decimaladc = 0, count = 0;
float adc = 0, decimalfloatadc = 0;
//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************

void main(void) {
    
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0;
    TRISB = 0;
    TRISD = 0;
    PORTA = 0;
    PORTB = 0;
    PORTD = 0;
    initLCD(); //Inicializar LCD
    I2C_Master_Init(100000);
    lcd_clr();//Limpiar LCD
    lcd_set_cursor(2,1);//Posicionar cursor
    lcd_write_string ("ADC");//Escribir texto
    lcd_set_cursor(7,1);
    lcd_write_string ("COUNT");
    lcd_set_cursor(13,1);
    lcd_write_string ("SNSR");
    
    while(1){        
        
        I2C_Master_Start();
        I2C_Master_Write(0x51);
        adc = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(10);
        
        I2C_Master_Start();
        I2C_Master_Write(0x61);
        count = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(10);
        
        adc = adc * 5/255;
        enteroadc = adc;
        decimalfloatadc = (adc - enteroadc)*100;
        decimaladc = decimalfloatadc;
        
        lcd_set_cursor(1,2);
        lcd_write_int(enteroadc);
        lcd_write_char('.');
        if (decimaladc >= 10){
            lcd_write_int(decimaladc);
        }else{
            lcd_write_char('0');
            lcd_write_int(decimaladc);
        }
        lcd_write_char('V');
        
        if(count < 10){
            lcd_set_cursor(8,2);
            lcd_write_string("00");
            lcd_write_int(count);
        } else if(count >= 10 && count < 100){
            lcd_set_cursor(8,2);
            lcd_write_string("0");
            lcd_write_int(count);
        }else{
            lcd_set_cursor(8,2);
            lcd_write_int(count);
        }
    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************