// SDL interface layer
// for the Build Engine
// by Jonathon Fowler (jf@jonof.id.au)

#ifndef build_interface_layer_
#define build_interface_layer_ SDL

#include "sdl_inc.h"
#include "compat.h"
#include "baselayer.h"

extern int32_t maxrefreshfreq;

#ifdef _WIN32
HWND win_gethwnd(void);
HINSTANCE win_gethinstance(void);
#endif

#include "sdlappicon.h"

#if (SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION < 3) // SDL 1.2
int32_t SDL_WaitEventTimeout(SDL_Event *event, int32_t timeout);
#endif

#define SDL_GL_ATTRIBUTES(iter, attrib)                                                                                \
    for (iter = 0; iter < (int32_t)ARRAY_SIZE(attrib); iter++)                                                         \
    {                                                                                                                  \
        j = attrib[iter].value;                                                                                        \
        if (!multisamplecheck &&                                                                                       \
            (attrib[iter].attr == SDL_GL_MULTISAMPLEBUFFERS || attrib[iter].attr == SDL_GL_MULTISAMPLESAMPLES))        \
        {                                                                                                              \
            j = 0;                                                                                                     \
        }                                                                                                              \
        SDL_GL_SetAttribute(attrib[iter].attr, j);                                                                     \
    }

#define SDL_ADDMODE(x, y, c, f)                                                                                        \
    do                                                                                                                 \
    {                                                                                                                  \
        if (validmodecnt < MAXVALIDMODES)                                                                              \
        {                                                                                                              \
            int32_t mn;                                                                                                \
            for (mn = 0; mn < validmodecnt; mn++)                                                                      \
                if (validmode[mn].xdim == x && validmode[mn].ydim == y && validmode[mn].bpp == c &&                    \
                    validmode[mn].fs == f)                                                                             \
                    break;                                                                                             \
            if (mn == validmodecnt)                                                                                    \
            {                                                                                                          \
                validmode[validmodecnt].xdim = x;                                                                      \
                validmode[validmodecnt].ydim = y;                                                                      \
                validmode[validmodecnt].bpp = c;                                                                       \
                validmode[validmodecnt].fs = f;                                                                        \
                validmodecnt++;                                                                                        \
                /*initprintf("  - %dx%d %d-bit %s\n", x, y, c, (f&1)?"fullscreen":"windowed");*/                       \
            }                                                                                                          \
        }                                                                                                              \
    } while (0)

#define SDL_CHECKMODE(w, h) ((w < maxx) && (h < maxy))

#define SDL_CHECKFSMODES(w, h)                                                                                         \
    if (w == 0 && h == 0)                                                                                              \
    {                                                                                                                  \
        initprintf("No fullscreen modes available!\n");                                                                \
        w = MAXXDIM;                                                                                                   \
        h = MAXYDIM;                                                                                                   \
    }

#if SDL_MAJOR_VERSION != 1
#define SDL2_VIDEO_ERR(XX)                                                                                             \
    {                                                                                                                  \
        initprintf("Unable to set video mode: " XX " failed: %s\n", SDL_GetError());                                   \
        destroy_window_resources();                                                                                    \
        return -1;                                                                                                     \
    }

#define SDL2_VIDEO_FALLBACK(XX)                                                                                        \
    {                                                                                                                  \
        initprintf("Falling back to SDL_GetWindowSurface: " XX " failed: %s\n", SDL_GetError());                       \
    }
#define SDL2_RENDERER_DESTROY(XX) SDL_DestroyRenderer(XX), XX = NULL
#endif

static inline void idle_waitevent_timeout(uint32_t timeout)
{
    SDL_WaitEventTimeout(NULL, timeout);
}

static inline void idle_waitevent(void)
{
    SDL_WaitEvent(NULL);
}

static inline void idle(void)
{
#ifndef _WIN32
    usleep(1000);
#else
    Sleep(1);
#endif
}

#else
#if (build_interface_layer_ != SDL)
#error "Already using the " build_interface_layer_ ". Can't now use SDL."
#endif
#endif // build_interface_layer_

