#ifndef PSTD_BALL_HEADER
#define PSTD_BALL_HEADER
#include "general.h"
#include "pmath.h"

#include "pwindow.h"
#include "game_general.h"
#include "bat.h"

#define BALL_RADIUS 8
#define BALL_SPEED 8

typedef struct Ball Ball;
struct Ball {
    union {
        Vec2f position;
        struct { f32 x, y; };
    };
    union {
        Vec2f velocity;
        struct { f32 vx, vy; };
    };

    enum {
        NONE, LEFT, RIGHT
    } last_hit;
};

void updateBall(Ball *, Bat *left, Bat *right);
void drawBall(Ball *);


#endif // PSTD_BALL_HEADER
