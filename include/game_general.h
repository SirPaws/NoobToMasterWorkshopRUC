#ifndef PSTD_GAME_HEADER
#define PSTD_GAME_HEADER
#if EMSCRIPTEN
#include <emscripten.h>
#include <GLES2/gl2.h>
#else
#include "glad/glad.h"
char *emscripten_get_preloaded_image_data(const char *path, int *w, int *h);
float emscripten_random(void);
#endif 

#include "general.h"
#define expect __builtin_expect


typedef struct SpriteSheet SpriteSheet;
struct SpriteSheet {
    u32 is_loaded, id;
    u32 width, height;
};

typedef struct Sprite Sprite;
struct Sprite {
    u32 spritesheet_id;
    u32 x, y;
    u32 width, height;
};

enum TextAlign {
    ALIGN_LEFT, ALIGN_CENTER, ALIGN_RIGHT,
};
typedef enum TextAlign TextAlign;

enum TextBaseline {
    BASELINE_TOP, BASELINE_MIDDLE, BASELINE_BOTTOM, 
    BASELINE_DEFAULT
};
typedef enum TextBaseline TextBaseline;


SpriteSheet *loadSpriteSheet(char *url);
void loadFont(char *family, char *url);


void background(int r, int g, int b, int a);
void drawSprite(Sprite *sprite, int x, int y, float scale_x, float scale_y);
void drawImage(char *url, int x, int y, float width, float height);

void fill(int r, int g, int b, int a);
void stroke(int r, int g, int b, int a);

void rect(int x, int y, int width, int height);
void ellipse(int x, int y, int radius_x, int radius_y);

void textAlign(TextAlign, TextBaseline);
void setFont(int px, char *font);
void text(char *text, int x, int y);



 
static inline float map(float value, float from1, float to1, float from2, float to2) {
    return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
}



#endif ///PSTD_GAME_HEADER
