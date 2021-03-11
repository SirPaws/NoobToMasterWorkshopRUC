#include "cbuild.h"
// #pragma comment(lib, "cbuild/cbuild.lib")

char *include_directories[] = {
    "include/pstd", 
    "include", 
    "src", 
    "src/pstd", 
};
char *files[] = {
    "include/pstd/pio.h",
    "include/pstd/pmath.h",
    "include/pstd/pplatform.h",
    "include/pstd/pstring.h",
    "include/pstd/stretchy_buffer.h",
    "include/pstd/util.h",
    "include/general.h",
    "include/pwindow.h",
    "include/bat.h",
    "include/ball.h",
    "src/pstd/pio.c",
    "src/pstd/pplatform.c",
    "src/pstd/pstring.c",
    "src/pstd/util.c",
    "src/controller.c",
    "src/ball.c",
    "src/main.c",
};

char *cargs[] = {
    "-Wall",
    "-Wextra",
    "-Wno-gnu-binary-literal",
    "-std=gnu2x",
    "-fno-ms-compatibility",
    "-fdeclspec",
//TODO: remove in release build
    "-gdwarf-4", 
}; 

int main(int argc, char *argv[argc]) {
    BuildContext ctx = {0};
    buildSetDefaults(&ctx);
    setCompiler(&ctx, EMCC|HTML);

    setOutputName(&ctx, "game");
    setBuildType(&ctx, EXECUTABLE|UNITY_BUILD);
    setBuildMode(&ctx, MODE_RELEASE);

    addIncludeDirs(&ctx, countof(include_directories), include_directories);
    addBuildFiles(&ctx, countof(files), files);

    constructCompileCommands(&ctx);

    setBuildFlag(&ctx, "--js-library src/libraryLib.js");
    setBuildFlag(&ctx, "--js-library src/game_general.js");
    execute(&ctx);
    return 0;
}














