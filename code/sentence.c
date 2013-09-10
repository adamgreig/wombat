#include <string.h>
#include <stdio.h>

#include "sentence.h"

char sentence_pre_buffer[256 - 10];
char sentence_buffer[256];

uint16_t crc_update(uint16_t crc, uint8_t data);
uint16_t sentence_calc_checksum(void);
void sentence_finalise(void);

uint16_t crc_update(uint16_t crc, uint8_t data) {
    int i;

    crc = crc ^ ((uint16_t)data << 8);
    for (i=0; i<8; i++)
    {
        if (crc & 0x8000)
            crc = (crc << 1) ^ 0x1021;
        else
            crc <<= 1;
    }

    return crc;
}

uint16_t sentence_calc_checksum() {
    uint16_t crc = 0xFFFF;
    uint8_t i;
    for(i=0; i<strlen(sentence_pre_buffer); i++)
        crc = crc_update(crc, sentence_pre_buffer[i]);
    return crc;
}

void sentence_finalise() {
    uint16_t crc = sentence_calc_checksum();

    sprintf(sentence_buffer, "$$$$$$%s*%04X\n", sentence_pre_buffer, crc);
}

char* sentence_generate(sentence_data data) {
    sprintf(sentence_pre_buffer,
            "WOMBAT,%lu,%02u:%02u:%02u,%.5f,%.5f,%li,%.0f",
            data.counter,
            data.gps.hour, data.gps.minute, data.gps.second,
            data.gps.latitude, data.gps.longitude, data.gps.altitude,
            data.temperature);

    sentence_finalise();
    return sentence_buffer;
}

char* sentence_generate_invalid(sentence_data data) {
    sprintf(sentence_pre_buffer, "WOMBAT,%lu,INVALID GPS DATA", data.counter);
    
    sentence_finalise();
    return sentence_buffer;
}

char* sentence_generate_no_lock(sentence_data data) {
    sprintf(sentence_pre_buffer, "WOMBAT,%lu,NO GPS LOCK", data.counter);

    sentence_finalise();
    return sentence_buffer;
}
