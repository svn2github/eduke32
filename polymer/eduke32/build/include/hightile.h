#ifndef HIGHTILE_PRIV_H
#define HIGHTILE_PRIV_H

#ifdef __cplusplus
extern "C" {
#endif

struct hicskybox_t {
    char *face[6];
};

typedef struct hicreplc_t {
    struct hicreplc_t *next;
    char *filename;
    struct hicskybox_t *skybox;
    vec2f_t scale;
    float alphacut, specpower, specfactor;
    char palnum, flags;
} hicreplctyp;

extern palette_t hictinting[MAXPALOOKUPS];
extern hicreplctyp *hicreplc[MAXTILES];
extern int32_t hicinitcounter;

typedef struct texcachehead_t
{
    char magic[4];	// 'PMST', was 'Polymost'
    int xdim, ydim;	// of image, unpadded
    int flags;		// 1 = !2^x, 2 = has alpha, 4 = lzw compressed
    int quality;    // r_downsize at the time the cache was written
} texcacheheader;

typedef struct texcachepic_t
{
    int size;
    int format;
    int xdim, ydim;	// of mipmap (possibly padded)
    int border, depth;
} texcachepicture;

hicreplctyp * hicfindsubst(int picnum, int palnum);
hicreplctyp * hicfindskybox(int picnum, int palnum);

static inline int have_basepal_tint(void)
{
    return (hictinting[MAXPALOOKUPS-1].r != 255 ||
            hictinting[MAXPALOOKUPS-1].g != 255 ||
            hictinting[MAXPALOOKUPS-1].b != 255);
}

static inline void hictinting_apply(float *color, int32_t palnum)
{
    color[0] *= (float)hictinting[palnum].r * (1.f/255.f);
    color[1] *= (float)hictinting[palnum].g * (1.f/255.f);
    color[2] *= (float)hictinting[palnum].b * (1.f/255.f);
}

static inline void hictinting_apply_ub(uint8_t *color, int32_t palnum)
{
    color[0] = (uint8_t)(color[0] * (float)hictinting[palnum].r * (1.f/255.f));
    color[1] = (uint8_t)(color[1] * (float)hictinting[palnum].g * (1.f/255.f));
    color[2] = (uint8_t)(color[2] * (float)hictinting[palnum].b * (1.f/255.f));
}

// texcacheheader cachead.flags bits
enum
{
    CACHEAD_NONPOW2 = 1,
    CACHEAD_HASALPHA = 2,
    CACHEAD_COMPRESSED = 4,
    CACHEAD_NOCOMPRESS = 8,
};

// hicreplctyp hicr->flags bits
enum
{
    HICR_NOSAVE = 1,

    HICR_NOCOMPRESS = 16,
};

// hictinting[].f / gloadtile_hi() and daskinloader() <effect> arg bits
enum
{
    HICTINT_GRAYSCALE = 1,
    HICTINT_INVERT = 2,
    HICTINT_COLORIZE = 4,
    HICTINT_USEONART = 8,

    HICEFFECTMASK = (1|2|4|8),
};

#define GRAYSCALE_COEFF_RED 0.3
#define GRAYSCALE_COEFF_GREEN 0.59
#define GRAYSCALE_COEFF_BLUE 0.11

#ifdef __cplusplus
}
#endif

#endif
