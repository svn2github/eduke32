/* The Lunatic Interpreter, part of EDuke32. Common, engine-side stuff. */

#ifndef ENGINE_LUNATIC_H_
#define ENGINE_LUNATIC_H_

#include <lua.h>


typedef struct
{
    char *name;
    lua_State *L;
} L_State;


// -- functions --

// helpers taking the lua_State directly:
void L_SetupDebugTraceback(lua_State *L);
void L_CheckAndRegisterFunction(lua_State *L, void *regkeyaddr);

// Callback on Lua error. <str> must be used immediately or strdup'd.
void (*L_ErrorFunc)(const char *str);

int L_CreateState(L_State *estate, const char *name, void (*StateSetupFunc)(lua_State *));
void L_DestroyState(L_State *estate);
int L_RunOnce(L_State *estate, const char *fn);
int L_RunString(L_State *estate, char *buf, int dofreebuf);

static inline int L_IsInitialized(const L_State *estate) { return (estate->L != NULL); }

#endif
