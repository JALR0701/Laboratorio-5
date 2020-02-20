/* 
 * File:   LCD_Init.h
 * Author: jorge
 *
 * Created on 5 de febrero de 2020, 01:39 PM
 */

#ifndef LCD_INIT_H
#define	LCD_INIT_H

#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 4000000

void initLCD (void); //Prototipos
void lcd_cmd (uint8_t command);
void lcd_clr (void);
void lcd_set_cursor(uint8_t posy, uint8_t posx);
void lcd_write_char(char var);
void lcd_write_string(char *var);
void lcd_write_int(uint8_t numero);

#endif	/* LCD_INIT_H */
