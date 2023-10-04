/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 0;        /* vertical padding of bar */
static const int sidepad            = 0;        /* horizontal padding of bar */
static const char *fonts[]          = {
	"hack:size=10:pixelsize=12:antialias=true:autohint=true",
	"hacknerdfont:pixelsize=14:antialias=true:autohint=true",
};
static const char dmenufont[]       = "hack:size=10";
static char normfgcolor[]           = "#654735";
static char normbgcolor[]           = "#fbf1c7";
static char normbordercolor[]       = "#928374";
static char selfgcolor[]            = "#282828";
static char selbgcolor[]            = "#ebdbb2";
static char selbordercolor[]        = "#fb4934";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

#define ICONSIZE 16   /* icon size */
#define ICONSPACING 5 /* space between icon and title */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class             instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "st-256color",     NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "Brave-browser",   NULL,     NULL,           1 << 1,    0,          0,          -1,        -1 },
	{ "Firefox",         NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "discord",         NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "TelegramDesktop", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ NULL,              NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
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
static const char *dmenucmd[] = {
	"dmenu_run",
	"-fn", dmenufont,
	"-nb", normbgcolor,
	"-nf", normfgcolor,
	"-sb", selbordercolor,
	"-sf", selfgcolor,
	NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

#include "functions.c"         /* additional functions */
#include <X11/XF86keysym.h>    /* additional keycodes */

static const Key keys[] = {
	/* modifier                     key        function        argument */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	{ MODKEY,                       XK_Tab,    shiftview,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,    shiftview,      {.i = -1 } },
	/* { MODKEY,                       XK_q,      killclient,     {0} }, */
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	/* { MODKEY,                       XK_w,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_e,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_t,      spawn,          {.v = (const char*[]){ "toggle-touchpad", NULL } } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = (const char*[]){ "toggle-xbanish", NULL } } },
	/* { MODKEY,                       XK_y,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_y,      spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_u,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_u,      spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_i,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_i,      spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_p,      spawn,          {.v = (const char*[]){ "mpc", "toggle", NULL } } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = (const char*[]){ "mpc", "stop", NULL } } },
	/* { MODKEY,                       XK_bracketleft,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_bracketleft,      spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_bracketright,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_bracketright,      spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_backslash,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_backslash,      spawn,          SHCMD("") }, */

	/* { MODKEY,                       XK_a,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_a,      spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_s,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = (const char*[]){ "passmenu", "-i", NULL } } },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          SHCMD("$GUIFILEMANAGER") },
	/* { MODKEY,                       XK_g,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_g,      spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.01} },
	/* { MODKEY|ShiftMask,             XK_h,      spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.01} },
	/* { MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_semicolon,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_semicolon,      spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_apostrophe,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_apostrophe,      spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	/* { MODKEY|ShiftMask,             XK_Return, spawn,          SHCMD("") }, */

	/* { MODKEY,                       XK_z,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_z,      spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_x,      spawn,          SHCMD("") }, */
	{ MODKEY|ShiftMask,             XK_x,      spawn,          {.v = (const char*[]){ "shutdown_script", NULL }} },
	/* { MODKEY,                       XK_c,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_c,      spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_v,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_v,      spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_b,      spawn,          SHCMD("$BROWSER") },
	{ MODKEY|Mod1Mask,              XK_b,      togglebar,      {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_b,      toggleborder,   {0} },
	/* { MODKEY,                       XK_n,      spawn,          SHCMD("") }, */
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = (const char*[]){ "restart-dunst", NULL } } },
	{ MODKEY,                       XK_m,      spawn,          {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
	/* { MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_comma,     spawn,       {.v = (const char*[]){ "mpc", "prev", NULL } } },
	{ MODKEY|ShiftMask,             XK_comma,     spawn,       {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	{ MODKEY,                       XK_period,    spawn,       {.v = (const char*[]){ "mpc", "next", NULL } } },
	{ MODKEY|ShiftMask,             XK_period,    spawn,       {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },

	{ MODKEY,                       XK_space,     zoom,           {0} }, // sets master window
	{ MODKEY|ShiftMask,             XK_space,     togglefloating, {0} }, // toggles floating for selected window
	{ 0,                            XK_Print,     spawn,          {.v = (const char *[]){ "screenshot", "1", NULL} } }, // screenshot
	{ ShiftMask,                    XK_Print,     spawn,          {.v = (const char *[]){ "screenshot", "2", NULL} } }, // screenshot into clipboard
	{ MODKEY,                       XK_Page_Up,   shiftview,      {.i = -1 } }, // tab id - 1
	{ MODKEY,                       XK_Page_Down, shiftview,      {.i = +1 } }, // tab id + 1
	{ MODKEY,                       XK_Left,      focusmon,	      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Left,      tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_Right,     focusmon,       {.i = +1 } },

	{ MODKEY,                       XK_F1,     spawn,          SHCMD("man -Tpdf dwm | zathura -") },
	/* { MODKEY,                       XK_F2,     spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_F3,     spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_F4,     spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
	/* { MODKEY,                       XK_F6,     spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_F7,     spawn,          {.v = (const char *[]){ "idea", NULL } } },
	/* { MODKEY,                       XK_F8,     spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_F9,     spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_F9,     spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_F10,    spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_F11,    spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_F12,    spawn,          {.v = (const char *[]){ "toggle_theme", NULL }} }, // change global theme

	{ 0, XF86XK_AudioMute,                     spawn,          SHCMD("pamixer -t; kill -10 $(pidof slstatus)") },                 // volume mute
	{ 0, XF86XK_AudioLowerVolume,	           spawn,          SHCMD("pamixer --allow-boost -d 2; kill -10 $(pidof slstatus)") }, // volume down
	{ 0, XF86XK_AudioRaiseVolume,              spawn,          SHCMD("pamixer --allow-boost -i 2; kill -10 $(pidof slstatus)") }, // volume up
	/* { 0, XF86XK_AudioMute,                     spawn,          SHCMD("pamixer -t; kill -35 $(pidof slbar)") },                 // volume mute */
	/* { 0, XF86XK_AudioLowerVolume,              spawn,          SHCMD("pamixer --allow-boost -d 2; kill -35 $(pidof slbar)") }, // volume down */
	/* { 0, XF86XK_AudioRaiseVolume,              spawn,          SHCMD("pamixer --allow-boost -i 2; kill -35 $(pidof slbar)") }, // volume up */
	{ 0, XF86XK_AudioMicMute,                  spawn,          SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") }, // mic mute
	{ 0, XF86XK_MonBrightnessDown,             spawn,          {.v = (const char *[]){ "brightness", "-5", NULL } } },  // brightness down
	{ 0, XF86XK_MonBrightnessUp,               spawn,          {.v = (const char *[]){ "brightness", "+5", NULL } } },  // grightness up
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

