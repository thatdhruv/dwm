/* See LICENSE file for copyright and license details. */
 
/* appearance */
static const unsigned int radiuspx  = 3;
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 5;
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Terminus:style=regular:pixelsize=18:antialias=true:autohint=true" };
static const char dmenufont[]       = "Terminus:style=regular:pixelsize=18:antialias=true:autohint=true";
static const char col_gray1[]       = "#242424";
static const char col_gray2[]       = "#242424";
static const char col_gray3[]       = "#ffffff";
static const char col_gray4[]       = "#242424";
static const char col_selection[]   = "#d4d4d4";
static const unsigned int baralpha = 0xe3;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_selection,  col_selection  },
};
static const unsigned int alphas[][3]      = {
    /*               fg      bg        border     */
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
    [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};
 
/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
 
static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            1,           -1 },
    { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};
 
/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
 
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "",      tile },    /* first entry is default */
    { "",      NULL },    /* no layout function means floating behavior */
    { "",      monocle },
};
 
/* key definitions */
#define MODKEY Mod4Mask //use Mod1Mask for Alt
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
 
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
 
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_selection, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
 
static const char *firefoxcmd[] = { "firefox", NULL };
static const char *mutecmd[] = { "pamixer", "-t", NULL };
static const char *poweroffcmd[] = { "poweroff", NULL };
 
static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,		    XK_space,  togglebar,      {0} },
    { MODKEY,			    XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_comma,  setlayout,      {.v = &layouts[0]} },
    { MODKEY|ShiftMask,		    XK_comma,  setlayout,      {.v = &layouts[1]} },
    { MODKEY|ControlMask,	    XK_comma,  setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_period, setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_period, togglefloating, {0} },
    { MODKEY|ControlMask,	    XK_period, zoom,           {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,		    XK_l,      incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,		    XK_h,      incnmaster,     {.i = -1 } },
    { MODKEY,			    XK_q,      killclient,     {0} },
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY|ShiftMask,		    XK_slash,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_slash,  focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask|ControlMask, XK_slash,  tagmon,         {.i = -1 } },
    { MODKEY|ControlMask,	    XK_slash,  tagmon,         {.i = +1 } },

    /* start of user-defined bindings */
    { MODKEY|ControlMask,	    XK_q,      spawn,	       SHCMD("${HOME}/.scripts/logout.sh") },
    { MODKEY|ShiftMask|ControlMask, XK_q,      spawn,	       {.v = poweroffcmd} },
    { MODKEY,			    XK_w,      spawn,	       {.v = firefoxcmd} },
    { MODKEY|ShiftMask,		    XK_w,      spawn,	       SHCMD("${HOME}/.scripts/set_wallpaper.sh") },
    { MODKEY,			    XK_s,      spawn,	       SHCMD("${HOME}/.scripts/screenshot.sh") },
    { MODKEY,			    XK_v,      spawn,	       SHCMD("${HOME}/.scripts/increase_volume.sh") },
    { MODKEY|ShiftMask,		    XK_v,      spawn,	       SHCMD("${HOME}/.scripts/decrease_volume.sh") },
    { MODKEY,			    XK_m,      spawn,	       { .v = mutecmd } },
    /* end of user-defined bindings */
    
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
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
