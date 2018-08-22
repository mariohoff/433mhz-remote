
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 9600000

int main (void)
{
    uint8_t btn;
    rc_init();
    //Set button inputs
    DDRB &= ~((1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4));

    while(1)
    {
        btn = PINB & ((1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4));
        switch(btn) {
            case (1 << PB1):
                rc_set(0, 1);
                break;
            case (1 << PB2):
                rc_set(1, 1);
                break;
            case (1 << PB3):
                rc_set(1, 0);
                break;
            case (1 << PB4):
                rc_set(0, 0);
                break;
        }
    }

    return 1; //never reached
} //main()
