
#include "bat.h"
extern pBool key_states[NUM_KEYS];
static SpriteSheet *bat_blocks_map = NULL;
Vec4i block_colors[] = { // used when image is not loaded
    {.elements= {178,  44,  44, 255}},
    {.elements= {178, 112,  44, 255}},
    {.elements= { 58, 178,  44, 255}},
    {.elements= { 44, 171, 178, 255}},
    {.elements= { 48,  44, 178, 255}},
    {.elements= {135,  44, 178, 255}},
    {.elements= {175,  44, 178, 255}},
    {.elements= {178,  44, 116, 255}},
};

void updateBat(Bat *bat, f32 delta_time) {
    int up_down = key_states[bat->key_down] - key_states[bat->key_up];
    bat->y += (up_down * SPEED);
}

void drawBat(Bat *bat) {
    if (expect(!bat_blocks_map, 0)) {
        bat_blocks_map = loadSpriteSheet("assets/images/Blocks.png");
    }

    f32 width  = bat->width;
    f32 height = bat->height;

    f32 full_width  = width*ROW_LENGTH;
    f32 full_height = height*COLUMN_LENGTH;
    
    f32 start_x = bat->x - full_width/2.0f;
    f32 start_y = bat->y - full_height/2.0f;

    for (int y = 0; y < COLUMN_LENGTH; y++) {
        for (int x = 0; x < ROW_LENGTH; x++) {
            u64 offset = (y + x*COLUMN_LENGTH);
            u64 bit = (1 << offset);
            int index = offset % 8;

            if (bat->break_out_bits & bit) {
                if (expect(!bat_blocks_map->is_loaded, 0)) {
                    Vec4i color = block_colors[index];
                    fill(color.r, color.g, color.b, color.a);
                    rect(start_x + x*width, start_y + y*height, width, height);
                } else {
                    Sprite spr = {
                        .spritesheet_id = bat_blocks_map->id,
                        .height = 16,
                        .width  = 16,
                        .x      = 16 * index,
                        .y      = 0
                    };
                    f32 scale_x = width/spr.width;
                    f32 scale_y = height/spr.height;
                    drawSprite(&spr, start_x + x*width, start_y + y*height, scale_x, scale_y);
                }
            }
        }
    }
}
