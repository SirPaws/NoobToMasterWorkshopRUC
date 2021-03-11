#include "ball.h"
#include "pio.h"

extern pBool key_states[NUM_KEYS];
static SpriteSheet *ball_sheet;
static Sprite ball_sprite = {
    .x = 0,
    .y = 0,
    .width  = 64,
    .height = 64
};
enum HitLocation {
    HIT_NONE,
    HIT_TOP, HIT_BOTTOM,
    HIT_LEFT, HIT_RIGHT,
};
typedef enum HitLocation HitLocation;

f32 getAngleX(Vec2f a) {
    // Vec2f tmp = pNormalize(a);
    f32 angle = acosf(a.x) * (180/PSTD_PI);
    if (a.y < 0)
         return 180+(180-angle);
    else return angle;
}

HitLocation hasCollided(Vec2f ellipse, Vec2f radii, Vec2f box_pos, Vec2f size) {
    Vec2f debug_ellipse = ellipse; 
    Vec2f debug_radii   = radii;
    Vec2f debug_box_pos = box_pos;
    Vec2f debug_size    = size;

    f32 length_x = box_pos.x - ellipse.x;
    f32 length_y = box_pos.y - ellipse.y;

    f32 dist_x = fabsf(length_x);
    f32 dist_y = fabsf(length_y);
    if(dist_x < size.x/2.0f + radii.x && dist_y < size.y/2.0f + radii.y) {
        f32 angle = acosf(pDot(ellipse, box_pos)) * (180/PSTD_PI);

        Vec2f top_left     = pMul(size, ((Vec2f){.x=-0.5, .y=-0.5f}));
        Vec2f top_right    = pMul(size, ((Vec2f){.x= 0.5, .y=-0.5f}));
        Vec2f bottom_left  = pMul(size, ((Vec2f){.x=-0.5, .y= 0.5f}));
        Vec2f bottom_right = pMul(size, ((Vec2f){.x= 0.5, .y= 0.5f}));

        top_left     = pSub(box_pos, top_left);
        top_right    = pSub(box_pos, top_right);
        bottom_right = pSub(box_pos, bottom_right);
        bottom_left  = pSub(box_pos, bottom_left);
        
        top_left     = pSub(top_left,     box_pos);
        top_right    = pSub(top_right,    box_pos);
        bottom_right = pSub(bottom_right, box_pos);
        bottom_left  = pSub(bottom_left,  box_pos);

        top_left     = pNormalize(top_left);
        top_right    = pNormalize(top_right);   
        bottom_right = pNormalize(bottom_right); 
        bottom_left  = pNormalize(bottom_left); 

        Vec2f diff = pSub(ellipse, box_pos);
        diff = pNormalize(diff);

        f32 angle0 = getAngleX(top_left);
        f32 angle1 = getAngleX(top_right);
        f32 angle2 = getAngleX(bottom_left);
        f32 angle3 = getAngleX(bottom_right);

        f32 angle4 = getAngleX(diff);

        /**/ if (angle4 < angle3 && angle4 > angle2) return HIT_BOTTOM;
        else if (angle4 < angle2 && angle4 > angle1) return HIT_LEFT;
        else if (angle4 < angle1 && angle4 > angle0) return HIT_TOP;
        else return HIT_RIGHT;

    }
    return HIT_NONE;
}

void reflectBall(Ball *ball, Bat *bat, HitLocation location, pBool flip) {
        Vec2f normal = { 0 };

        switch(location) {
        case HIT_TOP:    normal.y = 1; break;
        case HIT_BOTTOM: normal.y =-1; break;
        case HIT_LEFT:   normal.x = flip ?  1 : -1; break;
        case HIT_RIGHT:  normal.x = flip ? -1 :  1; break;
        }

        int value = key_states[bat->key_down] - key_states[bat->key_up];
        value *= -1;
        normal.y += (f32)value;

        f32 dot = pDot(normal, ball->velocity);
        Vec2f tmp0 = pMul(normal, dot);
        Vec2f reflection = pMul(tmp0, 2);
        ball->velocity = pSub(ball->velocity, reflection);
}

void testBat(int hit_enum, Bat *bat, Ball *ball, pBool flip) {
    f32 width  = bat->width;
    f32 height = bat->height;

    f32 full_width  = width*ROW_LENGTH;
    f32 full_height = height*COLUMN_LENGTH;
    
    f32 start_x = bat->x - full_width/2.0f;
    f32 start_y = bat->y - full_height/2.0f;

    for (int y = 0; y < COLUMN_LENGTH; y++) {
        for (int x = 0; x < ROW_LENGTH; x++) {
            u64 bit = (1 << (y + x*COLUMN_LENGTH));
            Vec2f center = {
                .x = start_x + x*width + width/2.0f, 
                .y = start_y + y*height + height/2.0f
            };
            Vec2f size = {.x = width, .y = height};
            HitLocation location = hasCollided(ball->position, 
                    (Vec2f){.x = BALL_RADIUS, .y=BALL_RADIUS}, center, size);
            if (location && (bat->break_out_bits & bit)) {
                reflectBall(ball, bat, location, flip);
                bat->break_out_bits  ^= bit;
                ball->last_hit = hit_enum;
                pPrintf("%llb\n", bat->break_out_bits);
                goto yeet;
            }
        }
    }
yeet:if(0) { /*intentional no-op*/ }
}


void updateBall(Ball *ball, Bat *left, Bat *right) {
    f32 ball_x = ball->x;
    f32 ball_y = ball->y;

    if (ball->vx == 0 && ball->vy == 0) {
        switch(ball->last_hit) {
        case NONE:  { 
                f32 value = emscripten_random();
                if (value > 0.5f) 
                    ball->vx =   BALL_SPEED;
                else ball->vx = -BALL_SPEED;
            } break;
        case LEFT:  ball->vx =  BALL_SPEED; break;
        case RIGHT: ball->vx = -BALL_SPEED; break;
        }
    }
    
    Vec2f left_full_size  = { 
        .x = left->width*ROW_LENGTH,
        .y = left->height*COLUMN_LENGTH
    };
    
    Vec2f right_full_size  = { 
        .x = right->width*ROW_LENGTH,
        .y = right->height*COLUMN_LENGTH
    };
   
    // maybe do this with prediction: ball->position + ball-velocity

    Vec2f size = {.x=BALL_RADIUS, .y=BALL_RADIUS};
    HitLocation left_hit  = hasCollided(ball->position, size, left->position, left_full_size);
    HitLocation right_hit = hasCollided(ball->position, size, right->position, right_full_size);
    if (left_hit) {
        testBat(LEFT, left, ball, true);
    }
    else if (right_hit) {
        testBat(RIGHT, right, ball, false);
    }

    Vec2f prediction = pAdd(ball->position, ball->velocity);
    if (prediction.y + BALL_RADIUS >= 540) {
        Vec2f normal = {.y = 1};
        f32 dot = pDot(normal, ball->velocity);
        Vec2f tmp0 = pMul(normal, dot);
        Vec2f reflection = pMul(tmp0, 2);
        ball->velocity = pSub(ball->velocity, reflection);
    }
    else if (prediction.y - BALL_RADIUS <= 0) {
        Vec2f normal = {.y = 1};
        f32 dot = pDot(normal, ball->velocity);
        Vec2f tmp0 = pMul(normal, dot);
        Vec2f reflection = pMul(tmp0, 2);
        ball->velocity = pSub(ball->velocity, reflection);
    }

    ball->position = pAdd(ball->position, ball->velocity);
}

void drawBall(Ball *ball) {
    if (expect(!ball_sheet, 0)) {
        ball_sheet = loadSpriteSheet("assets/images/Ball.png");
        ball_sprite.spritesheet_id = ball_sheet->id;
    }
    
    if (expect(!ball_sheet->is_loaded, 0)) {
        fill(228, 34, 34, 255);
    } else {
        f32 scale_x = (f32)(BALL_RADIUS*2)/ball_sprite.width;
        f32 scale_y = (f32)(BALL_RADIUS*2)/ball_sprite.height;

        drawSprite(&ball_sprite, ball->x - BALL_RADIUS, ball->y - BALL_RADIUS, scale_x, scale_y);
    }
}

