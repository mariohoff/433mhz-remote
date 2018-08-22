
#include "rc.h"
#include <avr/io.h>
#include <util/delay.h>
#include <ctype.h>

#define PULSE_LEN   350
#define SEND_REPEAT 3
#define PULSEDELAY(type, level) _delay_us(type##_##level*PULSE_LEN)

//number of pulses needed
#define SYNC_HIGH   1
#define SYNC_LOW    31
#define ZERO_HIGH   1
#define ZERO_LOW    3
#define ONE_HIGH    3
#define ONE_LOW     1

void send_msg(enum msg msg)
{
        RC_PORT |= (1 << RC_PIN);

        switch(msg) {
                case ONE:
                        PULSEDELAY(ONE, HIGH); break;
                case ZERO:
                        PULSEDELAY(ZERO, HIGH); break;
                case SYNC:
                        PULSEDELAY(SYNC, HIGH); break;
        }
        RC_PORT &= ~(1 << RC_PIN);
        switch(msg) {
                case ONE:
                        PULSEDELAY(ONE, LOW); break;
                case ZERO:
                        PULSEDELAY(ZERO, LOW); break;
                case SYNC:
                        PULSEDELAY(SYNC, LOW); break;
        }
}

void rc_init()
{
        RC_REG |= (1 << RC_PIN);
        RC_PORT &= ~(1 << RC_PIN);
}

void send_uid(const char *uid, const char len)
{
        int i;
        for(i = 0; i < len; i++) {
                send_msg(ZERO);
                send_msg(tolower(uid[i]) == 'f');
        }
}

void rc_set(uint8_t sw, uint8_t state)
{
        int j;
        for(j = 0; j < SEND_REPEAT; j++) {
                send_uid(BASE, 5);
                send_uid(switches[sw], 5);
                send_uid(states[state], 2);
                send_msg(SYNC);
        }
}

