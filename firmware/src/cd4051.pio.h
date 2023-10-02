// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ------ //
// cd4051 //
// ------ //

#define cd4051_wrap_target 0
#define cd4051_wrap 3

static const uint16_t cd4051_program_instructions[] = {
            //     .wrap_target
    0xe081, //  0: set    pindirs, 1                 
    0xe001, //  1: set    pins, 1                    
    0xe000, //  2: set    pins, 0                    
    0x0001, //  3: jmp    1                          
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program cd4051_program = {
    .instructions = cd4051_program_instructions,
    .length = 4,
    .origin = -1,
};

static inline pio_sm_config cd4051_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + cd4051_wrap_target, offset + cd4051_wrap);
    return c;
}
#endif

