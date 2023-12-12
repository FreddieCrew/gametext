# Re-implementation of SA-MP Game Texts (Work in Progress)

This is not ready at all; it's just a draft for now, and therefore, I don't recommend using it for production at the moment.

# Functions:

```cpp
ShowGameTextForPlayer(playerid, const content[], fade_delay, type, font = GAMETEXT_FONT_DEFAULT) // Displays game text for a player.
ShowGameTextForAll(const content[], fade_delay, type, font) // Displays game text for all online players.
bool: IsGameTextShowingForPlayer(playerid) // Returns true if game text is being shown for the player, and false if not.
```

# Callbacks:

```cpp
OnGameTextShow(playerid, type) - Called when game text is shown for the player.
OnGameTextFadeOut(playerid, type) - Called when the game text fades out.
```