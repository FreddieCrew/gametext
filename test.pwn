#include <a_samp>
#include <Pawn.CMD>
#include <gametext>

CMD:gametext(playerid, const params[]) {
    ShowGameTextForPlayer(playerid, "hello", 50, 0, 2);
	return 1;
}
