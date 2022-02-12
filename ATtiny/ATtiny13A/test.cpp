#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PB0                     // PB0 as a LED pin

int
main(void)
{
        /* loop */
        while (1) {
                _delay_ms(500);
        }
}