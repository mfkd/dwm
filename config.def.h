/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font Mono:size=10", "monospace:size=10" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font Mono:size=10";
static const char normbordercolor[] = "#0d1117";
static const char normbgcolor[]     = "#0d1117";
static const char normfgcolor[]     = "#b3b1ad";
static const char selbordercolor[]  = "#73b7f2";
static const char selbgcolor[]      = "#0d1117";
static const char selfgcolor[]      = "#73b7f2";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel] =  { selfgcolor,  selbgcolor,  selbordercolor },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", normbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *kitty1[]  = { "kitty", "-1", NULL };
static const char *browser[]  = { "google-chrome-stable", NULL };
static const char *pbrowser[]  = { "google-chrome-stable", "--incognito", NULL };
static const char *darkbrowser[]  = { "google-chrome-stable", "--enable-features=WebUIDarkMode", "--force-dark-mode", NULL };
static const char *slock[]  = { "slock", NULL };
static const char *volup[]  = { "pulseaudio-ctl-xob", "up", NULL };
static const char *voldown[]  = { "pulseaudio-ctl-xob", "down", NULL };
static const char *volmute[]  = { "pulseaudio-ctl-xob", "mute", NULL };
static const char *clipmenu[] = { "clipmenu", "-i", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", normbordercolor, "-sf", selfgcolor, NULL };
static const char *passmenu[] = { "passmenu", "-i", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", normbordercolor, "-sf", selfgcolor, NULL };
static const char *dunstclose[] = { "dunstctl", "close", NULL };

static const Key keys[] = {
	/* modifier                     key            function        argument */
	{ MODKEY,               XK_slash,        spawn,          {.v = dmenucmd } },
	{ MODKEY,               XK_Return,       spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,   XK_Return,       spawn,          {.v = kitty1 } },
	{ MODKEY,               XK_backslash,    spawn,          {.v = browser } },
	{ MODKEY|ControlMask,   XK_backslash,    spawn,          {.v = pbrowser } },
	{ MODKEY|ShiftMask,     XK_backslash,    spawn,          {.v = darkbrowser } },
	{ MODKEY,               XK_bracketright, spawn,          {.v = clipmenu } },
	{ MODKEY|ControlMask,   XK_bracketright, spawn,          {.v = passmenu } },
	{ MODKEY|ShiftMask,     XK_minus,        spawn,          {.v = volmute } },
	{ MODKEY,               XK_minus,        spawn,          {.v = voldown } },
	{ MODKEY,               XK_equal,        spawn,          {.v = volup } },
	{ MODKEY,               XK_Delete,       spawn,          {.v = slock } },
	{ MODKEY|ControlMask,   XK_space,        spawn,          {.v = dunstclose } },
	{ MODKEY,               XK_b,            togglebar,      {0} },
	{ MODKEY,               XK_comma,        focusstack,     {.i = +1 } },
	{ MODKEY,               XK_period,       focusstack,     {.i = -1 } },
	{ MODKEY|ControlMask,   XK_comma,        incnmaster,     {.i = +1 } },
	{ MODKEY|ControlMask,   XK_period,       incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_comma,        setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,     XK_period,       setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,     XK_Return,       zoom,           {0} },
	{ MODKEY,               XK_Tab,          view,           {0} },
	{ MODKEY|ShiftMask,     XK_c,            killclient,     {0} },
	{ MODKEY,               XK_t,            setlayout,      {.v = &layouts[0]} },
	{ MODKEY,               XK_f,            setlayout,      {.v = &layouts[1]} },
	{ MODKEY,               XK_m,            setlayout,      {.v = &layouts[2]} },
	{ MODKEY,               XK_space,        setlayout,      {0} },
	{ MODKEY|ShiftMask,     XK_space,        togglefloating, {0} },
	{ MODKEY|ShiftMask,     XK_0,            tag,            {.ui = ~0 } },
	{ MODKEY|ControlMask,   XK_3,            focusmon,       {.i = -1 } },
	{ MODKEY|ControlMask,   XK_4,            focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_3,            tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_4,            tagmon,         {.i = +1 } },
	TAGKEYS(                XK_i,                            0)
	TAGKEYS(                XK_o,                            1)
	TAGKEYS(                XK_p,                            2)
	TAGKEYS(                XK_k,                            3)
	TAGKEYS(                XK_l,                            4)
	TAGKEYS(                XK_semicolon,                    5)
	TAGKEYS(                XK_apostrophe,                   6)
	TAGKEYS(                XK_8,                            7)
	TAGKEYS(                XK_9,                            8)
	{ MODKEY|ShiftMask,     XK_q,            quit,           {0} },
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

