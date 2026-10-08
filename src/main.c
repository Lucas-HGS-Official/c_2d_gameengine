#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <raylib.h>
#include <raymath.h>


static int c_swap(lua_State *L) {
    double arg1 = luaL_checknumber(L, 1);
    double arg2 = luaL_checknumber(L, 2);

    lua_pushnumber(L, arg2);
    lua_pushnumber(L, arg1);

    return 2;
}

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, c_swap);
    lua_setglobal(L, "c_swap");

    luaL_dostring(L, "print(c_swap(4, 5))");

    const int screenWidth = 800;
    const int screenHeight = 450;
    Vector2 screen_size = { .x=screenWidth, .y=screenHeight };

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    lua_close(L);

    return 0;
}
