/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 4;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Liberation Mono:size=14", "Font Awesome:size=14"};
static const char dmenufont[]       = "Liberation Mono:size=14";
static const char col_normbg[]       = "#111111";
static const char col_normborder[]   = "#b294bb";
static const char col_normfg[]       = "#cccccc";
static const char col_selbg[]        = "#825c8f";
static const char col_selborder[]    = "#0e0e0e";
static const char col_selfg[]        = "#f2f2f2";
static const char col1[]            = "#ffffff";
static const char col2[]            = "#ffffff";
static const char col3[]            = "#ffffff";
static const char col4[]            = "#ffffff";
static const char col5[]            = "#ffffff";
static const char col6[]            = "#ffffff";

enum { SchemeNorm, SchemeSel, SchemeCol1, SchemeCol2, SchemeCol3, SchemeCol4,
       SchemeCol5, SchemeCol6 }; /* color schemes */

static const char *colors[][3]      = {
	/*               fg          bg          border   */
	[SchemeNorm] = { col_normfg, col_normbg, col_normborder },
	[SchemeSel]  = { col_selfg,  col_selbg,  col_selborder  },
	[SchemeCol1]  = { col1,      col_normbg, col_normborder },
	[SchemeCol2]  = { col2,      col_normbg, col_normborder },
	[SchemeCol3]  = { col3,      col_normbg, col_normborder },
	[SchemeCol4]  = { col4,      col_normbg, col_normborder },
	[SchemeCol5]  = { col5,      col_normbg, col_normborder },
	[SchemeCol6]  = { col6,      col_normbg, col_normborder },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "firefox",  NULL,       NULL,       1 << 2,       0,           -1 },
	{ NULL,       NULL,       "nnn",      1 << 1,       0,           -1 },
	{ "docnav",   NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Vivado",   NULL,       NULL,       1 << 5,       0,           -1 },
	{ "java",     NULL,       NULL,       1 << 7,       1,           -1 },
	{ "Vitis IDE",NULL,       NULL,       1 << 5,       0,           -1 },
	{ "Zathura",  NULL,       NULL,       1 << 3,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
#define TERMINAL "st"
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_normbg, "-nf", col_normfg, "-sb", col_selbg, "-sf", col_selfg, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *printScreen[] = { "/bin/sh", "-c", "sleep 0.1; scrot -z ~/Pictures/screenshot/%Y%m%d-%H%M%S.png", NULL };
static const char *printActive[] = { "/bin/sh", "-c", "sleep 0.1; scrot -z -u ~/Pictures/screenshot/%Y%m%d-%H%M%S.png", NULL };
static const char *printArea[] = { "/bin/sh", "-c", "sleep 0.2; scrot -z -s ~/Pictures/screenshot/%Y%m%d-%H%M%S.png", NULL };
static const char *firefox[] = { "firefox", NULL };
static const char *nnn[] = { TERMINAL, "-e", "nnn", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          SHCMD("killall xinit") },
	{ MODKEY|ShiftMask,             XK_w,      quit,           {0} },
	{ MODKEY,                       XK_space,  zoom,           {0} },

	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = 0  } },

	{ MODKEY,                       XK_p,      spawn,          {.v = printScreen } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = printActive } },
	{ MODKEY|ControlMask,           XK_p,      spawn,          {.v = printArea } },
	{ MODKEY,                 XK_bracketleft,  spawn,          SHCMD("pamixer --allow-boost -d 5 && sigdwmblocks 4") },
	{ MODKEY,                 XK_bracketright, spawn,          SHCMD("pamixer --allow-boost -i 5 && sigdwmblocks 4") },
	{ MODKEY|ShiftMask,       XK_bracketleft,  spawn,          SHCMD("pamixer -t && sigdwmblocks 4") },
	{ MODKEY|ShiftMask,       XK_bracketright, spawn,          SHCMD("sigdwmblocks 4 3") },

	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = firefox } },
	{ MODKEY|ShiftMask,             XK_g,      spawn,          {.v = nnn } },


	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY,                       XK_grave,  view,           {0} },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	{ MODKEY,                       XK_z,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_x,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_v,      setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_v,      togglefloating, {0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
//	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
//	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1 } },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2 } },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3 } },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4 } },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5 } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

