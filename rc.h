
#ifndef RC_H
#define RC_H

#include <avr/io.h>
#include <util/delay.h>

#define RC_REG DDRB
#define RC_PORT PORTB
#define RC_PIN PB0

#define ON      "0f"
#define OFF     "f0"

#define BASE    "0fff0"

enum msg {
        ZERO,
        ONE,
        SYNC
};

const char *switches[] = {
        "0ffff", // A
        "f0fff", // B
        "ff0ff"  // C
};

const char *states[] = {
        "f0", //OFF
        "0f"  //ON
};

void rc_init();
void rc_set(uint8_t sw, uint8_t state);

#endif
