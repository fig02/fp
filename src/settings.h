#ifndef SETTINGS_H
#define SETTINGS_H
#include <stdint.h>
#include "input.h"
#include "commands.h"
#include "pm64.h"

#define SETTINGS_VERSION            0x0001

#define SETTINGS_WATCHES_MAX        18
#define SETTINGS_TELEPORT_MAX       9
#define SETTINGS_MEMFILE_MAX        10
#define SETTINGS_BIND_MAX           COMMAND_MAX
#define SETTINGS_LOG_MAX            4

#define SETTINGS_LAG_FRAMES         0
#define SETTINGS_LAG_SECONDS        1

#define SETTINGS_BREAK_NORMAL       0
#define SETTINGS_BREAK_AGGRESSIVE   1

enum cheats {
    CHEAT_HP,
    CHEAT_FP,
    CHEAT_BP,
    CHEAT_COINS,
    CHEAT_STAR_POWER,
    CHEAT_STAR_POINTS,
    CHEAT_STAR_PIECES,
    CHEAT_PERIL,
    CHEAT_ENCOUNTER,
    CHEAT_BREAK,
    CHEAT_MAX
};

struct watch_info{
    uint8_t type          : 4;
    uint8_t anchored      : 1;
    uint8_t position_set  : 1;
};

struct settings_bits{
    uint32_t font_resource   : 4;
    uint32_t drop_shadow     : 1;
    uint32_t input_display   : 1;
    uint32_t log             : 1;
};

struct settings_data{
    /* order elements by size for space-efficient packing */
    uint32_t              watch_address[SETTINGS_WATCHES_MAX];
    uint32_t              cheats;
    struct settings_bits  bits;
    int16_t               menu_x;
    int16_t               menu_y;
    int16_t               input_display_x;
    int16_t               input_display_y;
    int16_t               log_x;
    int16_t               log_y;
    int16_t               watch_x[SETTINGS_WATCHES_MAX];
    int16_t               watch_y[SETTINGS_WATCHES_MAX];
    uint16_t              binds[SETTINGS_BIND_MAX];
    struct watch_info     watch_info[SETTINGS_WATCHES_MAX];
    uint8_t               teleport_slot;
    uint8_t               n_watches;
};

struct settings_header{
    uint16_t  version;
};

struct settings{
    struct settings_header  header;
    struct settings_data    data;
};

void  settings_load_default();
void  apply_menu_settings();
void  settings_save(int profile);
_Bool settings_load(int profile);

extern struct settings_data *settings;

#endif