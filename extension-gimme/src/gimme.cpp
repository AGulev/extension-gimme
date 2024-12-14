// Extension lib defines
#define LIB_NAME "GimmeExtension"
#define MODULE_NAME "gimme"

#include <dmsdk/sdk.h>
#if defined(DM_PLATFORM_VENDOR)
#include <dmsdk/dlib/hash_vendor.h>
#elif defined(__linux__) && !defined(__ANDROID__)
#define DM_HASH_LONG_FMT "%lu"
#else
#define DM_HASH_LONG_FMT "%llu"
#endif

static int Gimme_HashVal(lua_State* L)
{
    dmhash_t hash = 0;
    if (lua_type(L, 1) == LUA_TSTRING)
    {
        hash = dmHashString64(luaL_checkstring(L, 1));
    }
    else
    {
        hash = dmScript::CheckHash(L, 1);
    }
    char buffer[64];
    dmSnPrintf(buffer, sizeof(buffer), DM_HASH_LONG_FMT, hash);
    lua_pushstring(L, buffer);
    return 1;
}

#undef DM_HASH_LONG_FMT

static const luaL_reg Module_methods[] =
{
    {"hash_val", Gimme_HashVal},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);

    // Register lua names
    luaL_register(L, MODULE_NAME, Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

dmExtension::Result InitializeGimmeExtension(dmExtension::Params* params)
{
    // Init Lua
    LuaInit(params->m_L);
    dmLogDebug("Registered '%s' Extension\n", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(GimmeExtension, LIB_NAME, 0, 0, InitializeGimmeExtension, 0, 0, 0)
