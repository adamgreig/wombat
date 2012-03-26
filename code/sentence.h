#ifndef WOMBAT_SENTENCE_H
#define WOMBAT_SENTENCE_H

#include <libopencm3/cm3/common.h>

#include "gps.h"

typedef struct sentence_data_struct {
    u32 counter;
    gps_data gps;
    float temperature;
} sentence_data;

char* sentence_generate(sentence_data data);
char* sentence_generate_invalid(sentence_data data);
char* sentence_generate_no_lock(sentence_data data);

#endif
