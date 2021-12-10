/*
*
*   uart.c
*
*   @author Zoe Davis, Ella Godfrey
*   @date
*/

#include "uart.h"
#include <math.h>
#include "button.h"
#include "lcd.h"

void uart_init(int baud){
    //TODO
    SYSCTL_RCGCGPIO_R   |= 0x02;             //enable sysclock
    SYSCTL_RCGCUART_R   |= 0x02;             //enable UART module
    //set up registers for enable CLOCK, DEN, DIR, Interrupts
    timer_waitMillis(1);                     //wait for command to be effectuated
    GPIO_PORTB_AFSEL_R  |= 0x03;             // alternate function select
    //clear and set each register
    GPIO_PORTB_PCTL_R   &= 0x11;
    GPIO_PORTB_PCTL_R   |= 0x11;
    GPIO_PORTB_DEN_R    &= 0x03;
    GPIO_PORTB_DEN_R    |= 0x03;
    GPIO_PORTB_DIR_R    &= 0x02;
    GPIO_PORTB_DIR_R    |= 0x02;
    //configure UART module
    UART1_CTL_R         &= 0xFFFE;

    double brd;
    double fbrd = 0;
    double ibrd = 0;
    brd = 16e6/(16*baud);
    fbrd = modf(brd, &ibrd);                   // page 903
    fbrd = (fbrd * 64 + 0.5);

    //setting baud rate
    UART1_IBRD_R        = (int)ibrd;
    UART1_FBRD_R        = 0x2B;
    UART1_LCRH_R        = 0x60;
    UART1_CC_R          = 0x0;
    UART1_CTL_R         |= 0x0301;


}

void uart_sendChar(char data){
    while(UART1_FR_R & 0x20)
        {
        }

        UART1_DR_R = data;
}

char uart_receive(void){
    char data = 0;

        while(UART1_FR_R & UART_FR_RXFE)    {
        }

        data = (char) (UART1_DR_R & 0xFF);

        return data;
}

void uart_sendStr(const char *data){
    while(*data != '\0'){
            uart_sendChar(*data);
            data++;
        }
}

void uart_echo(const char *in) {
        uart_sendChar(*in);
        uart_sendChar('\r');
        uart_sendChar('\n');
    }

void uart_interrupt_init()
{
    // Enable interrupts for receiving bytes through UART1
    UART1_IM_R |= 0x0010; //enable interrupt on receive - page 924

    // Find the NVIC enable register and bit responsible for UART1 in table 2-9
    // Note: NVIC register descriptions are found in chapter 3.4
    NVIC_EN0_R |= 0x00000040; //enable uart1 interrupts - page 104

    // Find the vector number of UART1 in table 2-9 ! UART1 is 22 from vector number page 104
    IntRegister(INT_UART1, uart_interrupt_handler); //give the microcontroller the address of our interrupt handler - page 104 22 is the vector number

}

void uart_interrupt_handler()
{

    if(UART1_MIS_R & 0x0010){
        flag = true;
        uart_data = uart_receive();
        UART1_ICR_R |= 0x0010;
    }

}
