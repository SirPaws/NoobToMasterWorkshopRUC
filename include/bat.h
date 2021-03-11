#ifndef PSTD_BAT_HEADER
#define PSTD_BAT_HEADER
#include "general.h"
#include "pmath.h"

#include "pwindow.h"
#include "game_general.h"

#define COLUMN_LENGTH  (16)
#define ROW_LENGTH     ( 2)
#define SPEED          (16)
#define BREAKOUT_SIZE  (24)

typedef struct Bat Bat;
struct Bat {
    union {
        Vec2f position;
        struct { f32 x, y; };
    };
    f32 width, height;  // width and height of a sub block
    u16 key_up;         // I hate that 1 fucking bit
    u16 key_down;       // I hate that 1 fucking bit
    u64 break_out_bits; // bitfield of the bats sub components
    u64 score;
};
void updateBat(Bat *bat, f32 delta_time);
void drawBat(Bat *bat);
#endif // PSTD_BAT_HEADER
