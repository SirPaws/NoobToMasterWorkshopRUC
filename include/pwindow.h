#ifndef PSTD_WINDOW_HEADER
#define PSTD_WINDOW_HEADER

#ifndef PSTD_WINDOW_STANDALONE
#   include "general.h"
#else
#if defined(_WIN32) || defined(_WIN64)
#    define PSTD_WINDOWS
#elif defined(__linux__) || defined(__unix__)
#    define PSTD_LINUX
#elif defined(__APPLE__)
#    define PSTD_MACOS
#else
#   error platform not supported
#endif

#if !(defined(_MSC_FULL_VER) && !defined(__clang__)) // not an msvc compiler
#define PSTD_GNU_COMPATIBLE
#else
#define PSTD_MSVC
#define __builtin_expect(a, b) (a)
#endif

#if defined(PSTD_MSVC) && (defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL)
#pragma message("Warning: the traditional msvc preprocessor does not support 'complicated' macros use /Zc:preprocessor") 
#define PSTD_HAS_SECOND(...) 0
#else
#define PSTD_HAS_SECOND_TEST__(_0, _1, _2, ...) _2
#define PSTD_HAS_SECOND_TRIGGER(...) ,
#define PSTD_HAS_SECOND_TEST_(...) PSTD_HAS_SECOND_TEST__(__VA_ARGS__)
#define PSTD_HAS_SECOND_TEST(...)  PSTD_HAS_SECOND_TEST_(PSTD_HAS_SECOND_TRIGGER __VA_ARGS__ (), 0, 1, 0) 
#define PSTD_HAS_SECOND(a, ...)    PSTD_HAS_SECOND_TEST(__VA_ARGS__)
#endif

#define PSTD_CONCAT_( a, b ) a##b
#define PSTD_CONCAT( a, b ) PSTD_CONCAT_( a, b )

#define PSTD_STRINGIFY_(x) #x
#define PSTD_STRINGIFY(x) PSTD_STRINGIFY_(x)

#if defined(__STDC_VERSION__)
#   if __STDC_VERSION__ == 199901
#      define PSTD_C99 1
#      define PSTD_C89 1
#   elif __STDC_VERSION__ == 201112
#      define PSTD_C11 1
#      define PSTD_C99 1
#      define PSTD_C89 1
#   elif __STDC_VERSION__ == 201710
#      define PSTD_C18 1
#      define PSTD_C17 1
#      define PSTD_C11 1
#      define PSTD_C99 1
#      define PSTD_C89 1
#   endif
#elif defined(__STDC__)
#       define PSTD_C89 1
#endif

#if defined(__cplusplus) && !defined(PSTD_I_KNOW_WHAT_IM_DOING)
#if defined(PSTD_MSVC)
#pragma message pstd was written with c in mind so c++ might not work as intended. Please run your compiler in c mode
#else
#   warning pstd was written with c in mind so c++ might not work as intended. Please run your compiler in c mode
#endif
#endif

#if defined(__STDC_NO_VLA__)
#   define PSTD_HAS_VLA 0
#elif PSTD_C11 && !defined(PSTD_MSVC)
#   define PSTD_HAS_VLA 1
#endif


#if defined(__has_c_attribute)
#   define PSTD_HAS_ATTRIBUTE __has_c_attribute
#   if __STDC_VERSION__ >= 201710 
#       define PSTD_C23 1
#   endif 
#else
#   define PSTD_HAS_ATTRIBUTE(x) 0
#endif


#if PSTD_HAS_ATTRIBUTE(maybe_unused)
#define PSTD_UNUSED [[maybe_unused]]
#elif defined(PSTD_GNU_COMPATIBLE)
#define PSTD_UNUSED __attribute__((unused))
#else
#define PSTD_UNUSED
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <stdint.h>
#include <stdlib.h>

#if _WIN32 || _WIN64
    #if _WIN64
        #define PSTD_64
    #else
        #define PSTD_32
    #endif
#elif __GNUC__
    #if __x86_64__ || __ppc64__
        #define PSTD_64
    #else
        #define PSTD_32
    #endif
#elif UINTPTR_MAX > UINT_MAX
    #define PSTD_64
#else
    #define PSTD_32
#endif

#ifndef countof
#define countof(x) ((sizeof(x))/(sizeof((x)[0])))
#endif 

typedef int8_t    i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef int64_t   i64;

typedef int8_t    s8;
typedef int16_t   s16;
typedef int32_t   s32;
typedef int64_t   s64;

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;

typedef ptrdiff_t isize;
typedef ptrdiff_t ssize;

typedef size_t    usize;

typedef float     f32;
typedef double    f64;

#if !defined(__cplusplus)
typedef enum { false, true } pBool;
#else
enum pBool { pFalse, pTrue };
#endif

#ifndef pReallocateBuffer
#    define pReallocateBuffer realloc
#endif
#ifndef pAllocateBuffer
#   define pAllocateBuffer malloc
#endif
#ifndef pFreeBuffer
#   define pFreeBuffer free
#endif
#if defined(PSTD_GNU_COMPATIBLE)
#ifndef pZeroAllocateBuffer
#define pZeroAllocateBuffer(size) ({                \
    void *pZeroAllocateBuffer_tmp = malloc(size);   \
    memset(pZeroAllocateBuffer_tmp, 0, (size));     \
    pZeroAllocateBuffer_tmp;                        \
})
#endif
#else
#ifndef pZeroAllocateBuffer
    static void* pZeroAllocateBuffer(usize size) {
        void* pZeroAllocateBuffer_tmp = pAllocateBuffer(size);
        assert(pZeroAllocateBuffer_tmp);
        memset(pZeroAllocateBuffer_tmp, 0, (size));
        return pZeroAllocateBuffer_tmp;
    }
#define pZeroAllocateBuffer pZeroAllocateBuffer
#endif
#endif
#endif

/*
    if compiled to WASM we only support 1 window
*/

enum pWindowFlags {
    PSTD_NO_WINDOW_FLAGS,
    PSTD_FULL_SCREEN = (1 << 0),
    PSTD_NO_RESIZE   = (1 << 1),
};
typedef enum pWindowFlags pWindowFlags;

typedef struct pWindowInfo pWindowInfo;
struct pWindowInfo {
    int x, y; 
    int width, height;
    char *title;
    pWindowFlags flags;
};

typedef struct pWindow pWindow;

enum pState {
    PSTD_PRESSED  = 1,
    PSTD_HELD     = 2,
    PSTD_RELEASED = 0,
};
typedef enum pState pState;

enum pMods {
    PSTD_MOD_SHIFT   = (1 << 0),
    PSTD_MOD_CONTROL = (1 << 1),
    PSTD_MOD_ALT     = (1 << 2),
    PSTD_MOD_SUPER   = (1 << 3),
};
typedef enum pMods pMods;

enum pKey {
    PSTD_SPACE          = ' ',
    PSTD_KEY_0          = '0',
    PSTD_KEY_1          = '1',
    PSTD_KEY_2          = '2',
    PSTD_KEY_3          = '3',
    PSTD_KEY_4          = '4',
    PSTD_KEY_5          = '5',
    PSTD_KEY_6          = '6',
    PSTD_KEY_7          = '7',
    PSTD_KEY_8          = '8',
    PSTD_KEY_9          = '9',
    PSTD_KEY_A          = 'a',
    PSTD_KEY_B          = 'b',
    PSTD_KEY_C          = 'c',
    PSTD_KEY_D          = 'd',
    PSTD_KEY_E          = 'e',
    PSTD_KEY_F          = 'f',
    PSTD_KEY_G          = 'g',
    PSTD_KEY_H          = 'h',
    PSTD_KEY_I          = 'i',
    PSTD_KEY_J          = 'j',
    PSTD_KEY_K          = 'k',
    PSTD_KEY_L          = 'l',
    PSTD_KEY_M          = 'm',
    PSTD_KEY_N          = 'n',
    PSTD_KEY_O          = 'o',
    PSTD_KEY_P          = 'p',
    PSTD_KEY_Q          = 'q',
    PSTD_KEY_R          = 'r',
    PSTD_KEY_S          = 's',
    PSTD_KEY_T          = 't',
    PSTD_KEY_U          = 'u',
    PSTD_KEY_V          = 'v',
    PSTD_KEY_W          = 'w',
    PSTD_KEY_X          = 'x',
    PSTD_KEY_Y          = 'y',
    PSTD_KEY_Z          = 'z',
    
    PSTD_ENTER          = 256,
    PSTD_TAB            = 258,
    PSTD_DELETE         = 259,
    PSTD_END            = 260,
    PSTD_HOME           = 261,
    PSTD_INSERT         = 262,
    PSTD_PAGE_DOWN      = 263,
    PSTD_PAGE_UP        = 264,
    PSTD_ARROW_DOWN     = 265,
    PSTD_ARROW_LEFT     = 266,
    PSTD_ARROW_RIGHT    = 267,
    PSTD_ARROW_UP       = 268,
    PSTD_ESCAPE         = 269,
    PSTD_CAPSLOCK       = 270,
    
    PSTD_LEFT_ALT       = 273,
    PSTD_RIGHT_ALT      = 274,
    PSTD_ALT = PSTD_LEFT_ALT | PSTD_RIGHT_ALT,

    PSTD_LEFT_CONTROL   = 289,
    PSTD_RIGHT_CONTROL  = 290,
    PSTD_CONTROL = PSTD_LEFT_CONTROL | PSTD_RIGHT_CONTROL,

    PSTD_LEFT_SUPER     = 321,
    PSTD_RIGHT_SUPER    = 322,
    PSTD_SUPER = PSTD_LEFT_SUPER | PSTD_RIGHT_SUPER,

    PSTD_LEFT_SHIFT     = 385,
    PSTD_RIGHT_SHIFT    = 386,
    PSTD_SHIFT = PSTD_LEFT_SHIFT | PSTD_RIGHT_SHIFT,
    NUM_KEYS,
};
typedef enum pKey pKey;

enum pMouseButton {
    PSTD_MOUSE_0  =  0,
    PSTD_MOUSE_1  =  1,
    PSTD_MOUSE_2  =  2,
    PSTD_MOUSE_3  =  3,
    PSTD_MOUSE_4  =  4,
    PSTD_MOUSE_5  =  5,
    PSTD_MOUSE_6  =  6,
    PSTD_MOUSE_7  =  7,
    PSTD_MOUSE_8  =  8,
    PSTD_MOUSE_9  =  9,
    PSTD_MOUSE_10 = 10,
    PSTD_MOUSE_11 = 11,
    PSTD_MOUSE_12 = 12,
    PSTD_MOUSE_13 = 13,
    PSTD_MOUSE_14 = 14,
    PSTD_MOUSE_15 = 15,
    PSTD_MOUSE_16 = 16,
    PSTD_MOUSE_17 = 17,
    PSTD_MOUSE_18 = 18,
    PSTD_MOUSE_19 = 19,
    PSTD_MOUSE_20 = 20,
    PSTD_MOUSE_21 = 21,
    PSTD_MOUSE_22 = 22,
    PSTD_MOUSE_23 = 23,
    PSTD_MOUSE_24 = 24,
    PSTD_MOUSE_25 = 25,
    PSTD_MOUSE_26 = 26,
    PSTD_MOUSE_27 = 27,
    PSTD_MOUSE_28 = 28,
    PSTD_MOUSE_29 = 29,
    PSTD_MOUSE_30 = 30,
    PSTD_MOUSE_31 = 31,

    PSTD_MOUSE_LEFT   = PSTD_MOUSE_0,
    PSTD_MOUSE_RIGHT  = PSTD_MOUSE_1,
    PSTD_MOUSE_MIDDLE = PSTD_MOUSE_2,
};
typedef enum pMouseButton pMouseButton;

typedef struct pMonitorDimensions pMonitorDimensions;
struct pMonitorDimensions {
    int width, height;
};

typedef pBool pKeyboardEventHandler(     pWindow *, pState state, int key,    int mods);
typedef pBool pMouseButtonEventHandler(  pWindow *, pState state, int button, int mods);
typedef pBool pMousePositionEventHandler(pWindow *, double x,  double y);
typedef pBool pMouseScrollEventHandler(  pWindow *, double dx, double dy);

pWindow *pCreateWindow(pWindowInfo info);
pWindow *pSetActiveWindow(pWindow *window);

void pGetMonitorDimensions(pMonitorDimensions *);

void pPushKeyboardEventHandler(     pWindow *, pKeyboardEventHandler*);
void pPushMouseButtonEventHandler(  pWindow *, pMouseButtonEventHandler*);
void pPushMousePositionEventHandler(pWindow *, pMousePositionEventHandler*);
void pPushMouseScrollEventHandler(  pWindow *, pMouseScrollEventHandler*);

enum pEventHandlerType {
    PSTD_KEYBOARD       = 1,
    PSTD_MOUSE_BUTTON   = 2,
    PSTD_MOUSE_POSITION = 3,
    PSTD_MOUSE_SCROLL   = 4,
};

void pPushEventHandler(enum pEventHandlerType handler_type, pWindow *window, void *handler) {
    switch(handler_type) {
    case PSTD_KEYBOARD:       pPushKeyboardEventHandler(window, handler);     break;
    case PSTD_MOUSE_BUTTON:   pPushMouseButtonEventHandler(window, handler);  break;
    case PSTD_MOUSE_POSITION: pPushMousePositionEventHandler(window, handler);break;
    case PSTD_MOUSE_SCROLL:   pPushMouseScrollEventHandler(window, handler);  break;
    }
} 

#if !defined(NDEBUG)
void pDebugUpdate(void);
#endif


#endif // PSTD_WINDOW_HEADER
