/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "hack:size=10:pixelsize=12:antialias=true:autohint=true", "symbola:pixelsize=14:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=10";

#ifdef SWEET_DARK
static const char *colors[][3] = {
  /*               fg          bg         border */
  [SchemeNorm] = { "#c1b0b0", "#181b28", "#12151f" },
  [SchemeSel]  = { "#f3f3f3", "#181b28", "#c50ed2" },
};
#elif GRUVBOX
static const char *colors[][3] = {
  /*               fg          bg         border */
  [SchemeNorm] = { "#9c8d74", "#1d2021", "#8f8072" },
  [SchemeSel]  = { "#d4be98", "#1d2021", "#e76861" },
};
#else
static const char *colors[][3] = {
  /*               fg          bg         border */
  [SchemeNorm] = { "#bbbbbb", "#222222", "#444444" },
  [SchemeSel]  = { "#eeeeee", "#005577", "#005577" },
};
#endif

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class             instance  title  tags mask  isfloating  monitor */
  { "Brave-browser",   NULL,     NULL,  1 << 1,    0,          -1 },
  { "Chromium",        NULL,     NULL,  1 << 1,    0,          -1 },
  { "librewolf",       NULL,     NULL,  1 << 1,    0,          -1 },
  { "discord",         NULL,     NULL,  1 << 8,    0,          -1 },
  { "TelegramDesktop", NULL,     NULL,  1 << 8,    0,          -1 },
  { "Steam",           NULL,     NULL,  1 << 7,    0,          -1 },
  { "Bottles",         NULL,     NULL,  1 << 7,    0,          -1 },
  { "Lutris",          NULL,     NULL,  1 << 7,    0,          -1 },
  { "heroic",          NULL,     NULL,  1 << 7,    0,          -1 },
  { "Minigalaxy",      NULL,     NULL,  1 << 7,    0,          -1 },
  { "Minecraft 1.18",  NULL,     NULL,  1 << 7,    0,          -1 },
  { "heroes3 hd.exe",  NULL,     NULL,  1 << 7,    1,          -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

#include "func.c"

#include <X11/XF86keysym.h>

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

static Key keys[] = {
  /* modifier                     key           function           argument */
  TAGKEYS(                        XK_1,                             0) // TAGKEYS for tab 1
  TAGKEYS(                        XK_2,                             1) // TAGKEYS for tab 2
  TAGKEYS(                        XK_3,                             2) // TAGKEYS for tab 3
  TAGKEYS(                        XK_4,                             3) // TAGKEYS for tab 4
  TAGKEYS(                        XK_5,                             4) // TAGKEYS for tab 5
  TAGKEYS(                        XK_6,                             5) // TAGKEYS for tab 6
  TAGKEYS(                        XK_7,                             6) // TAGKEYS for tab 7
  TAGKEYS(                        XK_8,                             7) // TAGKEYS for tab 8
  TAGKEYS(                        XK_9,                             8) // TAGKEYS for tab 9
  { MODKEY,                       XK_0,         view,              {.ui = ~0 } }, // view all tabs
  { MODKEY|ShiftMask,             XK_0,         tag,               {.ui = ~0 } }, // moves window to all tags

  /* { MODKEY|Mod1Mask,              XK_0,         togglegaps,        {0} }, */
  /* { MODKEY|Mod1Mask|ShiftMask,    XK_0,         defaultgaps,       {0} }, */
  /* { MODKEY|Mod1Mask,              XK_minus,     incrgaps,          {.i = -3 } }, */
  /* { MODKEY|Mod1Mask,              XK_equal,     incrgaps,          {.i = +3 } }, */
  /* { MODKEY,                       XK_BackSpace, spawn,              SHCMD("") }, */
  /* { MODKEY|ShiftMask,             XK_BackSpace, spawn,              SHCMD("") }, */

  { MODKEY,                       XK_Tab,       shiftview,      {.i = +1 } }, // tab id + 1
  { MODKEY|ShiftMask,             XK_Tab,       shiftview,      {.i = -1 } }, // tab id - 1
  /* { MODKEY,                       XK_q,         layoutscroll,   {.i = -1 } }, // scroll through layouts */
  { MODKEY|ShiftMask,             XK_q,         killclient,     {0} }, // kill focused process
  /* { MODKEY,                       XK_w,         layoutscroll,   {.i = +1 } }, // scroll thorough layouts */
  /* { MODKEY|ShiftMask,             XK_w,         spawn,           SHCMD("") }, */
  { MODKEY,                       XK_e,         setlayout,      {.v = &layouts[0]} }, // tiling
  { MODKEY|ShiftMask,             XK_e,         quit,           {0} }, // exit DWM
  { MODKEY,                       XK_r,         setlayout,      {.v = &layouts[1]} }, // floating
  { MODKEY|ShiftMask,             XK_r,         setlayout,      {.v = &layouts[2]} }, // monocle
  { MODKEY,                       XK_t,         spawn,           SHCMD("toggle-touchpad") },
  { MODKEY|ShiftMask,             XK_t,         spawn,           SHCMD("toggle-xbanish") },
  /* { MODKEY,                       XK_y,         spawn,           SHCMD("") }, */
  /* { MODKEY|ShiftMask,             XK_y,         spawn,           SHCMD("") }, */
  /* { MODKEY,                       XK_u,         spawn,           SHCMD("") }, */
  /* { MODKEY|ShiftMask,             XK_u,         spawn,           SHCMD("") }, */
  /* { modkey,                       XK_l,         spawn,           SHCMD("") }, */
  /* { modkey|ShiftMask,             XK_l,         spawn,           SHCMD("") }, */
  { MODKEY,                       XK_o,         incnmaster,     {.i = +1 } }, // add 1 client to master area
  { MODKEY|ShiftMask,             XK_o,         incnmaster,     {.i = -1 } }, // subtract 1 client from master area
  { MODKEY,                       XK_p,         spawn,           SHCMD("mpc toggle") }, // pause / unpause mpd
  { MODKEY|ShiftMask,             XK_p,         spawn,           SHCMD("mpc stop") }, // stop mpd
  /* { MODKEY,                       XK_bracketleft,         spawn,           SHCMD("") }, */
  /* { MODKEY|ShiftMask,             XK_bracketleft,         spawn,           SHCMD("") }, */
  /* { MODKEY,                       XK_bracketright,        spawn,           SHCMD("") }, */
  /* { MODKEY|ShiftMask,             XK_bracketright,        spawn,           SHCMD("") }, */
  /* { MODKEY,                       XK_backslash, spawn,           SHCMD("") }, */
  /* { MODKEY|ShiftMask,             XK_backslash, spawn,           SHCMD("") }, */

  /* { MODKEY,                       XK_a,         spawn,           SHCMD("") }, */
  /* { MODKEY|ShiftMask,             XK_a,         spawn,           SHCMD("") }, */
  /* { MODKEY,                       XK_s,         spawn,           SHCMD("") }, */
  /* { MODKEY|ShiftMask,             XK_s,         spawn,           SHCMD("") }, */
  { MODKEY,                       XK_d,         spawn,          {.v = dmenucmd } }, // dmenu
  { MODKEY|ShiftMask,             XK_d,         spawn,           SHCMD("passmenu") }, // passmenu
  { MODKEY,                       XK_f,         togglefullscr,  {0} }, // toggle full screen
  { MODKEY|ShiftMask,             XK_f,         spawn,           SHCMD("$GUIFILEMANAGER") }, // start gui file manager
  /* { MODKEY,                       XK_g,         spawn,           SHCMD("") }, */
  /* { MODKEY|ShiftMask,             XK_g,         spawn,           SHCMD("") }, */
  { MODKEY,                       XK_h,         setmfact,       {.f = -0.01} }, // change window size
  /* { MODKEY|ShiftMask,             XK_h,         spawn,           SHCMD("") }, */
  { MODKEY,                       XK_j,         focusstack,     {.i = +1 } }, // change window focus
  { MODKEY|ShiftMask,             XK_j,         movestack,      {.i = +1 } }, // move window down inside client list
  { MODKEY,                       XK_k,         focusstack,     {.i = -1 } }, // change window focus
  { MODKEY|ShiftMask,             XK_k,         movestack,      {.i = -1 } }, // move window up inside client list
  { MODKEY,                       XK_l,         setmfact,       {.f = +0.01} }, // change window size
  /* { MODKEY|ShiftMask,             XK_l,         spawn,           SHCMD("") }, */
  /* { MODKEY,                       XK_semicolon, spawn,           SHCMD("") }, */
  /* { MODKEY|ShiftMask,             XK_semicolon, spawn,           SHCMD("") }, */
  /* { MODKEY,                       XK_apostrophe,spawn,           SHCMD("") }, */
  /* { MODKEY|ShiftMask,             XK_apostrophe,spawn,           SHCMD("") }, */
  { MODKEY,                       XK_Return,    spawn,          {.v = termcmd } }, // terminal
  /* { MODKEY|ShiftMask,             XK_Return,    spawn,           SHCMD("") }, */

  /* { MODKEY|ShiftMask,             XK_z,         spawn,           SHCMD("") }, */
  /* { MODKEY|ShiftMask,             XK_z,         spawn,           SHCMD("") }, */
  { MODKEY|ShiftMask,             XK_x,         spawn,           SHCMD("shutdown_script") },
  /* { MODKEY|ShiftMask,             XK_x,         spawn,           SHCMD("") }, */
  /* { MODKEY,                       XK_c,         spawn,           SHCMD("") }, */
  /* { MODKEY|ShiftMask,             XK_c,         spawn,           SHCMD("") }, */
  /* { MODKEY,                       XK_v,         spawn,           SHCMD("") }, */
  /* { MODKEY|ShiftMask,             XK_v,         spawn,           SHCMD("") }, */
  { MODKEY,                       XK_b,         spawn,           SHCMD("$BROWSER") }, // start browser
  { MODKEY|Mod1Mask,              XK_b,         togglebar,      {0} }, // toggle bar visibility
  { MODKEY|Mod1Mask|ShiftMask,    XK_b,         toggleborder,   {0} }, // toggle border visibility
  /* { MODKEY,                       XK_n,         spawn,           SHCMD("") }, */
  { MODKEY|ShiftMask,             XK_n,         spawn,           SHCMD("restart-dunst") },
  { MODKEY,                       XK_m,         spawn,           SHCMD(TERMINAL " -e ncmpcpp") }, // run ncmpcpp
  /* { MODKEY|ShiftMask,             XK_m,         spawn,           SHCMD("") }, */
  { MODKEY,                       XK_comma,     spawn,           SHCMD("mpc prev") }, // prev song
  { MODKEY|ShiftMask,             XK_comma,     spawn,           SHCMD("mpc seek -10") }, // backward 10s
  { MODKEY,                       XK_period,    spawn,           SHCMD("mpc next") }, // next song
  { MODKEY|ShiftMask,             XK_period,    spawn,           SHCMD("mpc seek +10") }, // forward 10s

  { MODKEY,                       XK_space,     zoom,           {0} }, // sets master window
  { MODKEY|ShiftMask,             XK_space,     togglefloating, {0} }, // toggles floating for selected window
  { 0,                            XK_Print,     spawn,           SHCMD("screenshot 1") }, // screenshot
  { ShiftMask,                    XK_Print,     spawn,           SHCMD("screenshot 2") }, // screenshot into clipboard
  { MODKEY,                       XK_Page_Up,   shiftview,      {.i = -1 } }, // tab id - 1
  { MODKEY,                       XK_Page_Down, shiftview,      {.i = +1 } }, // tab id + 1
 	{ MODKEY,			                  XK_Left,	    focusmon,	      {.i = -1 } },
  { MODKEY|ShiftMask,		          XK_Left,	    tagmon,		      {.i = -1 } },
  { MODKEY,			                  XK_Right,	    focusmon,	      {.i = +1 } },
	{ MODKEY|ShiftMask,		          XK_Right,	    tagmon,		      {.i = +1 } },
  
  { MODKEY,                       XK_F1,        spawn,           SHCMD("man -Tpdf dwm | zathura -") },
  /* { MODKEY,                       XK_F2,        spawn,           SHCMD("") }, */
  /* { MODKEY,                       XK_F3,        spawn,           SHCMD("") }, */
  /* { MODKEY,                       XK_F4,        spawn,           SHCMD("") }, */
  /* { MODKEY,                       XK_F5,        spawn,           SHCMD("") }, */
  /* { MODKEY,                       XK_F6,        spawn,           SHCMD("") }, */
  /* { MODKEY,                       XK_F7,        spawn,           SHCMD("idea") }, */
  /* { MODKEY,                       XK_F8,        spawn,           SHCMD("") }, */
  /* { MODKEY,                       XK_F9,        spawn,           SHCMD("") }, */
  /* { MODKEY,                       XK_F9,        spawn,           SHCMD("") }, */
  /* { MODKEY,                       XK_F10,       spawn,           SHCMD("") }, */
  /* { MODKEY,                       XK_F11,       spawn,           SHCMD("") }, //   mount usb */
  /* { MODKEY,                       XK_F12,       spawn,           SHCMD("") }, // unmount usb */

  { 0, XF86XK_AudioMute,                        spawn,           SHCMD("pamixer -t; kill -35 $(pidof slbar)") },                 // volume mute
  { 0, XF86XK_AudioLowerVolume,	                spawn,           SHCMD("pamixer --allow-boost -d 2; kill -35 $(pidof slbar)") }, // volume down
  { 0, XF86XK_AudioRaiseVolume,                 spawn,           SHCMD("pamixer --allow-boost -i 2; kill -35 $(pidof slbar)") }, // volume up
  { 0, XF86XK_AudioMicMute,                     spawn,           SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") }, // mic mute
  { 0, XF86XK_MonBrightnessDown,                spawn,           SHCMD("brightness -5") },  // brightness down
  { 0, XF86XK_MonBrightnessUp,                  spawn,           SHCMD("brightness +5") },  // grightness up
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
