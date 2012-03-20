#include <stdint.h>

uint8_t buf[4] = {0x06, 0x24, 0x00, 0x00};

void main() {
    uint8_t a = 0, b = 0;
    uint8_t i;
    for(i=0; i<4; i++) {
        a = a + buf[i];
        b = b + a;
    }
    printf("a: %x\r\nb: %x\r\n\r\n", a, b);
}
