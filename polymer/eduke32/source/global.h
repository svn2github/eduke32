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

#ifndef global_h_
#define global_h_

#ifdef global_c_
    #define G_EXTERN
#else
    #define G_EXTERN extern
#endif

#define MAXINTERPOLATIONS MAXSPRITES
// KEEPINSYNC lunatic/con_lang.lua
#define MAXSKILLS 7

// duke3d global soup :(

#include "compat.h"
#include "build.h"

G_EXTERN int32_t g_numInterpolations;
G_EXTERN int32_t g_interpolationLock;
G_EXTERN int32_t oldipos[MAXINTERPOLATIONS];
G_EXTERN int32_t *curipos[MAXINTERPOLATIONS];
G_EXTERN int32_t bakipos[MAXINTERPOLATIONS];

#include "mmulti.h"

#include "duke3d.h"
#include "sector.h"
#include "quotes.h"

#ifdef __cplusplus
extern "C" {
#endif

G_EXTERN DukeStatus_t sbar;
G_EXTERN actor_t actor[MAXSPRITES];
// g_tile: tile-specific data THAT DOES NOT CHANGE during the course of a game
G_EXTERN tiledata_t g_tile[MAXTILES];
G_EXTERN animwalltype animwall[MAXANIMWALLS];
G_EXTERN char *ScriptQuotes[MAXQUOTES],*ScriptQuoteRedefinitions[MAXQUOTES];
G_EXTERN char *label;
G_EXTERN int32_t g_musicIndex;
G_EXTERN char g_loadFromGroupOnly;
G_EXTERN char g_numSkills;
G_EXTERN char myjumpingtoggle,myonground,myhardlanding,myreturntocenter;
G_EXTERN char pus,pub;
G_EXTERN char ready2send;
#define MAXPLAYERNAME 32
G_EXTERN char szPlayerName[MAXPLAYERNAME];
// XXX: menutextbuf overflow possible?
G_EXTERN char tempbuf[MAXSECTORS<<1],packbuf[PACKBUF_SIZE],menutextbuf[128],buf[1024];
#define TYPEBUFSIZE 141
G_EXTERN char typebuf[TYPEBUFSIZE];
G_EXTERN input_t avg;
G_EXTERN input_t loc;
G_EXTERN input_t recsync[RECSYNCBUFSIZ];
G_EXTERN int16_t SpriteDeletionQueue[1024],g_spriteDeleteQueuePos;
G_EXTERN int16_t animatesect[MAXANIMATES];
G_EXTERN int16_t g_curViewscreen;
G_EXTERN int16_t cyclers[MAXCYCLERS][6],g_numCyclers;
G_EXTERN int16_t g_globalRandom;
G_EXTERN int16_t g_mirrorWall[64],g_mirrorSector[64],g_mirrorCount;
G_EXTERN int16_t g_numAnimWalls;
G_EXTERN int16_t g_numClouds,clouds[128],cloudx[128],cloudy[128];
G_EXTERN int16_t myang,omyang,mycursectnum,myjumpingcounter;
G_EXTERN int16_t myhoriz,omyhoriz,myhorizoff,omyhorizoff;
G_EXTERN int32_t *animateptr[MAXANIMATES];
G_EXTERN int32_t animategoal[MAXANIMATES],animatevel[MAXANIMATES],g_animateCount;
G_EXTERN int32_t cloudtotalclock;
G_EXTERN int32_t g_currentFrameRate;
G_EXTERN int32_t g_damageCameras,g_freezerSelfDamage;
G_EXTERN int32_t g_doQuickSave;
G_EXTERN uint16_t g_earthquakeTime;
G_EXTERN int32_t g_gameQuit;
G_EXTERN int32_t g_impactDamage,g_maxPlayerHealth;
G_EXTERN int32_t g_musicSize;
G_EXTERN int32_t g_numLabels,g_numDefaultLabels;
G_EXTERN int32_t g_scriptDebug;
G_EXTERN int32_t g_showShareware;
G_EXTERN int8_t g_numPlayerSprites;
G_EXTERN int32_t g_tripbombLaserMode;
G_EXTERN int32_t msx[2048],msy[2048];
G_EXTERN int32_t neartaghitdist,lockclock,g_startArmorAmount;
G_EXTERN int32_t playerswhenstarted;
G_EXTERN int32_t screenpeek;
G_EXTERN int32_t startofdynamicinterpolations;
G_EXTERN int32_t ototalclock;
G_EXTERN intptr_t *g_parsingActorPtr;
G_EXTERN intptr_t *g_scriptPtr;
G_EXTERN int32_t *labelcode,*labeltype;
G_EXTERN intptr_t *script;
G_EXTERN map_t MapInfo[(MAXVOLUMES+1)*MAXLEVELS];  // +1 volume for "intro", "briefing" and "loading" music
#pragma pack(push,1)
G_EXTERN playerdata_t g_player[MAXPLAYERS];
G_EXTERN playerspawn_t g_playerSpawnPoints[MAXPLAYERS];
G_EXTERN input_t inputfifo[MOVEFIFOSIZ][MAXPLAYERS];
#pragma pack(pop)
G_EXTERN projectile_t ProjectileData[MAXTILES];
G_EXTERN projectile_t SpriteProjectile[MAXSPRITES];
G_EXTERN sound_t g_sounds[MAXSOUNDS];
G_EXTERN uint32_t everyothertime;
G_EXTERN uint32_t g_moveThingsCount;
G_EXTERN vec3_t my,omy,myvel;
G_EXTERN volatile char g_soundlocks[MAXSOUNDS];
G_EXTERN int32_t g_restorePalette;
G_EXTERN int32_t g_screenCapture;
G_EXTERN int32_t g_noEnemies;

#ifndef global_c_
G_EXTERN const char *s_buildDate;
G_EXTERN int32_t g_spriteGravity;
G_EXTERN int16_t g_spriteDeleteQueueSize;
G_EXTERN char EpisodeNames[MAXVOLUMES][33];
G_EXTERN char SkillNames[MAXSKILLS][33];
G_EXTERN char GametypeNames[MAXGAMETYPES][33];
G_EXTERN int32_t GametypeFlags[MAXGAMETYPES];
G_EXTERN char g_numGametypes;
G_EXTERN char g_numVolumes;
G_EXTERN int32_t g_timerTicsPerSecond;
G_EXTERN int32_t g_actorRespawnTime;
G_EXTERN int32_t g_itemRespawnTime;
G_EXTERN int32_t g_scriptSize;
G_EXTERN int16_t BlimpSpawnSprites[15];
G_EXTERN int32_t g_playerFriction;
G_EXTERN int32_t g_numFreezeBounces;
G_EXTERN int32_t g_lastSaveSlot;
G_EXTERN int32_t g_rpgBlastRadius;
G_EXTERN int32_t g_pipebombBlastRadius;
G_EXTERN int32_t g_tripbombBlastRadius;
G_EXTERN int32_t g_shrinkerBlastRadius;
G_EXTERN int32_t g_morterBlastRadius;
G_EXTERN int32_t g_bouncemineBlastRadius;
G_EXTERN int32_t g_seenineBlastRadius;
G_EXTERN char CheatKeys[2];
G_EXTERN char setupfilename[BMAX_PATH];
#endif

#ifdef __cplusplus
}
#endif

#endif
