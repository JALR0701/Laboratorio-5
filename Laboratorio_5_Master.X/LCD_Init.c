#include <stdint.h>
#include <pic16f887.h>
#include <stdio.h>
#include <stdlib.h>
#include "LCD_Init.h"



void initLCD (void){
__delay_ms(15);
//Inicialización
lcd_cmd(0x030);
__delay_ms(5);

lcd_cmd(0x030);
__delay_ms(11);

lcd_cmd(0x030);
__delay_us(160);
/////////////////
lcd_cmd(0x38);//Set interface Length
lcd_cmd(0x10);//Turn off the Display
lcd_cmd(0x01);//Clear the display
lcd_cmd(0x06);//Set cursor behavior
lcd_cmd(0x0C);//Enable display
}



void lcd_cmd(uint8_t command){
    PORTBbits.RB6 = 0;//Mandar datos. 
    PORTD = command;
    PORTBbits.RB7 = 1;
    __delay_ms(4);
    PORTBbits.RB7 = 0;
}

void lcd_clr (void){
    lcd_cmd(0x01);//Clear the display
}

void lcd_set_cursor(uint8_t posx, uint8_t posy){
    if(posy == 1){
        lcd_cmd (0x80 + posx - 1);//Adress de coordenadas
    }
    if(posy == 2){
        lcd_cmd (0xC0 + posx - 1);
    }
}

void lcd_write_char(char var){
    PORTBbits.RB6 = 1;//Modo escritura
    PORTD = var;//Char a imprimir
    PORTBbits.RB7 = 1;//Pulso para mandar datos
    __delay_ms(4);
    PORTBbits.RB7 = 0;
}

void lcd_write_string(char *var){
    int i;
	for(i=0;var[i]!='\0';i++)//Separa los caracteres y los manda uno a uno.
	   lcd_write_char(var[i]);
}

void lcd_write_int(uint8_t numero){
    char buffer [4];
    sprintf (buffer, "%d", numero); //Convierte el int en string
    lcd_write_string(buffer);
}
