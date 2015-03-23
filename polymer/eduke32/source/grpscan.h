//-------------------------------------------------------------------------
/*
Copyright (C) 2010 EDuke32 developers and contributors

This file is part of EDuke32.

EDuke32 is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License version 2
as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
//-------------------------------------------------------------------------

#ifndef grpscan_h_
#define grpscan_h_

#define MAXLISTNAMELEN 32

// List of internally-known GRP files
#define DUKE13_CRC  (int32_t)0xBBC9CE44
#define DUKEKR_CRC  (int32_t)0xAA4F6A40
#define DUKE15_CRC  (int32_t)0xFD3DCFF1
#define DUKEPP_CRC  (int32_t)0xF514A6AC
#define DUKE099_CRC (int32_t)0x02F18900
#define DUKE10_CRC  (int32_t)0xA28AA589
#define DUKE11_CRC  (int32_t)0x912E1E8D
#define DUKESW_CRC  (int32_t)0x983AD923
#define DUKEMD_CRC  (int32_t)0xC5F71561
#define DUKEDC13_CRC (int32_t)0xA9242158
#define DUKEDCPP_CRC (int32_t)0xB79D997F
#define DUKEDC_CRC  (int32_t)0xA8CF80DA
#define VACA13_CRC  (int32_t)0x4A2DBB62
#define VACAPP_CRC  (int32_t)0x2F4FCCEE
#define VACA15_CRC  (int32_t)0xB62B42FD
#define DUKECB_CRC  (int32_t)0x18F01C5B
#define DUKENW_CRC  (int32_t)0xF1CAE8E4
#define NAM_CRC     (int32_t)0x75C1F07B
#define NAPALM_CRC  (int32_t)0x3DE1589A
#define WW2GI_CRC   (int32_t)0x907B82BF

enum addon_t {
    ADDON_NONE,
    ADDON_DUKEDC,
    ADDON_NWINTER,
    ADDON_CARIBBEAN,
    NUMADDONS
};

typedef struct grpfile {
	char *name;
	int32_t crcval;
	int32_t size;
	int32_t game;
    int32_t dependency;
    char *scriptname;
    char *defname;
    void (*postprocessing)(int32_t);
	struct grpfile *next;
} grpfile_type;

extern struct grpfile internalgrpfiles[];
extern struct grpfile *foundgrps;
extern struct grpfile *listgrps;

extern struct grpfile * FindGroup(int32_t crcval);
int32_t ScanGroups(void);
void FreeGroups(void);

#endif
