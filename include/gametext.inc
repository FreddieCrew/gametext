/* 
MIT License

Copyright (c) 2023 John M. Reyes

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#if defined _inc_gametext
	#undef _inc_gametext
#endif
#if defined _gametext_included
	#endinput
#endif
#define _gametext_included

#include <a_samp>
#include <fader>

enum _GameTextInfo {
	PlayerText: __gf_id,
	bool: __gf_IsShowing,
	__gf_type
};
new __GameTextInfo[MAX_PLAYERS][_GameTextInfo];

#define INVALID_GAMETEXT_ID (-1)
#define GAMETEXT_FONT_DIPLOMA (0)
#define GAMETEXT_FONT_DEFAULT (1)
#define GAMETEXT_FONT_SLIM (2)
#define GAMETEXT_FONT_PRICEDOWN (3)

// Forwards
forward OnGameTextShow(playerid, type);
forward OnGameTextFadeOut(playerid, type);


// Functions
stock ShowGameTextForPlayer(playerid, const content[], fade_delay, type, font = GAMETEXT_FONT_DEFAULT) {
	switch (type) {
		case 0: {
			PlayerTextDrawFont(playerid, __GameTextInfo[playerid][__gf_id], font);
			PlayerTextDrawLetterSize(playerid, __GameTextInfo[playerid][__gf_id], 0.6, 2.0);
 			PlayerTextDrawTextSize(playerid, __GameTextInfo[playerid][__gf_id], 200*2.0, 5.0*3.4);
 			PlayerTextDrawSetOutline(playerid, __GameTextInfo[playerid][__gf_id], 0);
 			PlayerTextDrawSetShadow(playerid, __GameTextInfo[playerid][__gf_id], 0);
			PlayerTextDrawAlignment(playerid, __GameTextInfo[playerid][__gf_id], 1);
			PlayerTextDrawFade(playerid, __GameTextInfo[playerid][__gf_id], -1, 0x000000AA, fade_type_text, fade_delay, .from_outline_color = 255, .to_outline_color = 0x00);
			PlayerTextDrawSetString(playerid, __GameTextInfo[playerid][__gf_id], content);
			__GameTextInfo[playerid][__gf_IsShowing] = true;
			__GameTextInfo[MAX_PLAYERS][__gf_type] = type;
			CallLocalFunction("OnGameTextShow", "ii", playerid, type)
		}
	}
	return 1;
}

stock ShowGameTextForAll(const content[], fade_delay, type, font) {
	for (new i = 0; i < MAX_PLAYERS; i++) {
		if (!IsPlayerConnected(i)) continue;

		ShowGameTextForPlayer(i, content, fade_delay, type, font)
	}
	return 1;
}

stock bool: IsGameTextShowingForPlayer(playerid) {
	return __GameTextInfo[playerid][__gf_IsShowing];
}

// Callbacks
public OnPlayerTextDrawFaded(playerid, PlayerText: playertext, fade_type: type, from_color, to_color, from_outline_color, to_outline_color) {
	if (PlayerText: playertext == PlayerText: __GameTextInfo[playerid][__gf_id]) {
		PlayerTextDrawHide(playerid, __GameTextInfo[playerid][__gf_id]);
		CallLocalFunction("OnGameTextFadeOut", "ii", playerid, __GameTextInfo[playerid][__gf_type]);

		__GameTextInfo[playerid][__gf_IsShowing] = false;
		__GameTextInfo[playerid][__gf_type] = INVALID_GAMETEXT_ID;
	}

    #if defined _GameText_OnPlayerTextDrawFaded
        _GameText_OnPlayerTextDrawFaded(playerid, PlayerText: playertext, fade_type: type, from_color, to_color, from_outline_color, to_outline_color);
    #endif
	return 1;
}

public OnPlayerConnect(playerid) {
	print("OnPlayerConnect called");
	__GameTextInfo[playerid][__gf_id] = CreatePlayerTextDraw(playerid, 25.0*11.56, 15.0*15.0, "");

    #if defined _GameText_OnPlayerConnect
        _GameText_OnPlayerConnect(playerid);
    #endif
    return 1;
}

// ALS meta

// OnPlayerConnect
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect _GameText_OnPlayerConnect
#if defined _GameText_OnPlayerConnect
    forward _GameText_OnPlayerConnect(playerid);
#endif

// OnPlayerTextDrawFaded
#if defined _ALS_OnPlayerTextDrawFaded
    #undef OnPlayerTextDrawFaded
#else
    #define _ALS_OnPlayerTextDrawFaded
#endif
#define OnPlayerTextDrawFaded _GameText_OnPlayerTextDrawFaded
#if defined _GameText_OnPlayerTextDrawFaded
    forward _GameText_OnPlayerTextDrawFaded(playerid, PlayerText: playertext, fade_type: type, from_color, to_color, from_outline_color, to_outline_color);
#endif