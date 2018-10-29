/*
 * File:   main.c
 * Author: SERVARIVERA
 *
 * Created on 8 de octubre de 2018, 06:10 PM
 */
#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 32000000
int timer1 = 15536;
int cont = 0;
void main(void) {
    OSCFRQbits.HFFRQ = 0b110; //MHz
    //puertos
    PORTA=0; //limpia puerto A
    PORTC=0; //limpia puerto C
    TRISA=0b00000001; //puerto A como salida
    TRISC=0b00000010; //puerto C como salida
    ANSELA=0; //puerto A como digital
    ANSELC=0; //puerto C como digital
    
    WPUA0 = 1; //pullup en A0
    
    //Configuración de la interrupcion 
    INTPPS = 0x00;
    //Interrupción INT
    INTCONbits.INTEDG = 1;//flanco de subida
    PIR0bits.INTF = 0;//limpiar bandera
    PIE0bits.INTE = 1;//habilitar interrupción
    
    //Configuracion Timer1
    T1CONbits.CKPS = 0b11; //valor del prescaler 1:8
    T1CONbits.RD16=1; // 
    T1CONbits.nT1SYNC = 1; // no 
    T1CLKbits.CS = 0b00001; //fosc/4
    T1CONbits.ON = 1; //habilitar el Timer
    TMR1 = timer1;
    
    PIR4bits.TMR1IF = 0; //bandera
    PIE4bits.TMR1IE = 1; // 
    INTCONbits.PEIE = 1; //habilitar la interrupción por perifericos
    INTCONbits.GIE = 1; //habilitar la interrupción global
   
    while (1);
    return;
}
void __interrupt () tinmer (void){
    LATC3 = LATC3 + 1;
    TMR1 = timer1;
    if (PIR0bits.INTF==1){
        cont = cont + 1;
        __delay_ms(300);
    }
    if (cont == 3){
        cont = 1;
    }
    if (cont == 1){
        timer1 = 60536;
    }
    if (cont == 2){
        timer1=15536;
    }
    PIR0bits.INTF = 0;
    PIR4bits.TMR1IF = 0;
}
