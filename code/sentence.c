#include <string.h>
#include <stdio.h>

#include "sentence.h"

char sentence_pre_buffer[256 - 10];
char sentence_buffer[256];

u16 crc_update(u16 crc, u8 data) {
    int i;

    crc = crc ^ ((u16)data << 8);
    for (i=0; i<8; i++)
    {
        if (crc & 0x8000)
            crc = (crc << 1) ^ 0x1021;
        else
            crc <<= 1;
    }

    return crc;
}

u16 sentence_calc_checksum(void) {
    u16 crc = 0xFFFF;
    u8 i;
    for(i=0; i<strlen(sentence_pre_buffer); i++)
        crc = crc_update(crc, sentence_pre_buffer[i]);
    return crc;
}

void sentence_finalise(void) {
    u16 crc = sentence_calc_checksum();

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
