#ifndef KEYNAMES_H
#define KEYNAMES_H

#include <SDL/SDL_keysym.h>

typedef struct
{
	SDLKey sym;
	char name[25];
} KeyName;

static unsigned int s_keyNamesSz = 42;

static KeyName s_keyNames[] =
{
	{SDLK_BACKSPACE, "backspace"},
	{SDLK_TAB, "tab"},
	{SDLK_CLEAR, "clear"},
	{SDLK_RETURN, "enter"},
	{SDLK_PAUSE, "pause"},
	{SDLK_ESCAPE, "esc"},
	{SDLK_SPACE, "space"},
	{SDLK_0, "0"},
	{SDLK_1, "1"},
	{SDLK_2, "2"},
	{SDLK_3, "3"},
	{SDLK_4, "4"},
	{SDLK_5, "5"},
	{SDLK_6, "6"},
	{SDLK_7, "7"},
	{SDLK_8, "8"},
	{SDLK_9, "9"},
	{SDLK_UP, "up"},
	{SDLK_DOWN, "down"},
	{SDLK_RIGHT, "right"},
	{SDLK_LEFT, "left"},
	{SDLK_F1, "f1"},
	{SDLK_F2, "f2"},
	{SDLK_F3, "f3"},
	{SDLK_F4, "f4"},
	{SDLK_F5, "f5"},
	{SDLK_F6, "f6"},
	{SDLK_F7, "f7"},
	{SDLK_F8, "f8"},
	{SDLK_F9, "f9"},
	{SDLK_F10, "f10"},
	{SDLK_F11, "f11"},
	{SDLK_F12, "f12"},
	{SDLK_F13, "f13"},
	{SDLK_F14, "f14"},
	{SDLK_F15, "f15"},
	{SDLK_RSHIFT, "rshift"},
	{SDLK_LSHIFT, "lshift"},
	{SDLK_RCTRL, "rctrl"},
	{SDLK_LCTRL, "lctrl"},
	{SDLK_RALT, "ralt"},
	{SDLK_LALT, "lalt"}
};

#endif // KEYNAMES_H
