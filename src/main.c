#include "pwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include "game_general.h"
#include "pio.h"
#include "pmath.h"
#include "util.h"
#include "bat.h"
#include "ball.h"

#ifndef EMSCRIPTEN
typedef void (*em_str_callback_func)(const char *);
int emscripten_run_preload_plugins(const char *file, em_str_callback_func onload, em_str_callback_func onerror);
#endif
 
 
pBool keyboard_event(pWindow *window, pState state, int key, int mods);
pBool mouse_move_event(pWindow *window, double x,  double y);
pBool mouse_pressed_event(pWindow *window, pState state, int button, int mods);

pBool key_states[NUM_KEYS] = {0};
static f32 prev_time = 0, current_time = 0;
double mouseX = 0, mouseY = 0;
pBool mouse_left_status = false;

#define SET(high, low) (((high) << 8) | (low))

static Bat player1 = {
    .x = 32,
    .y = 540.0f/2.0f,
    .width = BREAKOUT_SIZE, .height = BREAKOUT_SIZE,
    .key_up = 'w', .key_down = 's',
    .break_out_bits = (0xffff<<16) | 0xffff  
};
    
static Bat player2 = {
    .x = 960 - 48,
    .y = 540.0f/2.0f,
    .width = BREAKOUT_SIZE, .height = BREAKOUT_SIZE,
    .key_up = PSTD_ARROW_UP, .key_down = PSTD_ARROW_DOWN,
    .break_out_bits = (0xffff<<16) | 0xffff  
};
static Ball ball = { 
    .x = 960/2.0f,
    .y = 540.0f/2.0f,
};

enum {
    MAIN_MENU,
    PAUSE, 
    PLAY,
} game_state = MAIN_MENU;


void soft_reset(void) {
    player1.x = 32;
    player1.y = 540.0f/2.0f;
    player1.break_out_bits = (0xffff<<16) | 0xffff;

    player2.x = 960 - 48;
    player2.y = 540.0f/2.0f;
    player2.break_out_bits = (0xffff<<16) | 0xffff;

    ball.x  = 960/2.0f;
    ball.y  = 540.0f/2.0f;
    ball.vx = 0;
    ball.vy = 0;
    game_state = PAUSE;
}

void gameUpdate(f32 delta) {
    if (game_state == PLAY) {
        updateBat(&player1, delta);
        updateBat(&player2, delta);
        updateBall(&ball, &player1, &player2);

        if (player1.break_out_bits == 0 || ball.x - BALL_RADIUS <= 0) {
            player2.score++; 
            soft_reset();
        }
        else if (player2.break_out_bits == 0 || ball.x + BALL_RADIUS >= 960) {
            player1.score++; 
            soft_reset();
        }
    }
}

void update(f32 delta) {
    switch (game_state) {
    case MAIN_MENU: break;
    case PAUSE: {
            if (key_states[' ']) game_state = PLAY; 
        }   break;
    case PLAY: gameUpdate(delta);
    }
}

void draw(void) {

    drawBat(&player1);
    drawBat(&player2);
    drawBall(&ball);

    setFont(20, "Kenney Blocks");
    textAlign(ALIGN_LEFT, BASELINE_MIDDLE);
    fill(0, 0, 0, 255);   
    char buf[1000] = {0};
    int size = snprintf(buf, 1000, "score: %lli", player1.score);
    buf[size] = '\0';
    text(buf, 200, 20);
    
    size = snprintf(buf, 1000, "score: %lli", player2.score);
    buf[size] = '\0';

    textAlign(ALIGN_RIGHT, BASELINE_MIDDLE);
    text(buf, 960 - 200, 20);


    if (game_state == MAIN_MENU) {
        fill(127, 127, 127, 127);   
        rect(0, 0, 960, 540);

        setFont(50, "Kenney Blocks");
        textAlign(ALIGN_CENTER, BASELINE_MIDDLE);
        fill(255, 255, 255, 255);   
        text("GAME", 960/2, 64);

        if (mouseX >= 960.0f/2 - 80 && mouseX < 960.0f/2 - 80 + 150
        &&  mouseY >= 540.0f/2 - 50 && mouseY < 540.0f/2) {
            fill(255,   0,   0, 255);   
            if (mouse_left_status) game_state = PAUSE;
        } else fill(255, 255, 255, 255);   
        text("PLAY", 960/2, 540/2);
    } 
    else if (game_state == PAUSE) {
        text("PRESS SPACE TO START!!!", 960/2, 540/2);
    }
}

void main_loop(void) {
#if !defined(NDEBUG)
    pDebugUpdate();
#endif
    drawImage("assets/images/Backdrop.png", 0, 0, 960, 540);
    current_time = pGetTimeSeconds(f64, pGetTick(PSTD_HIGH_RESOLUTION_CLOCK));
    f32 delta_time = current_time - prev_time;
    prev_time = current_time;

    update(delta_time);
    draw();
}
#undef window

int size_index = 0;


int main(void) {
    loadFont("Kenney Blocks", "assets/fonts/Kenney\\ Blocks.ttf");

    pWindow *win = pCreateWindow((pWindowInfo){.title = "window"});
    pSetActiveWindow(win);
    
    pPushEventHandler(PSTD_KEYBOARD, win, keyboard_event);
    pPushEventHandler(PSTD_MOUSE_BUTTON, win, mouse_pressed_event);
    pPushEventHandler(PSTD_MOUSE_POSITION, win, mouse_move_event);

    emscripten_set_main_loop(main_loop, 0, true);

}

pBool keyboard_event(pWindow *window, pState state, int key, int mods) {
    (void)window;
    (void)mods;

    if(state == PSTD_HELD) state = PSTD_PRESSED;
    key_states[key] = state == PSTD_PRESSED;
   
    if (key_states[' '] && game_state == PAUSE) {
        game_state = PLAY;
    }
    if (key_states['r']) {
        soft_reset();
    }


    return true;
}

pBool mouse_move_event(pWindow *window, double x,  double y) {
    (void)window;
    mouseX = x;
    mouseY = y;
    return true;
}

pBool mouse_pressed_event(pWindow *window, pState state, int button, int mods) {
    (void)window;
    (void)mods;
    (void)state;
    (void)button;

    if (button == PSTD_MOUSE_LEFT) {
        mouse_left_status = state > 0;
    }

    return true;
}
