#include"GameManager.h"
#include"Puyo.h"
#include"Map.h"

GameManager::GameManager()
{
	SPEED = 60;//–ñ1•b
	CurrentSpeed = 0;
	contactPuyoLeft = false;
	contactPuyoRight = false;
	EnterFlag = false;
}
GameManager:: ~GameManager()
{

}

GameManager gMane;

void GameManager::MovePuyo(Puyo* puyo ,Map* map,GameManager* gMane)
{
	CurrentSpeed++;
	
	if (CurrentSpeed == SPEED || EnterFlag == true)
	{
		if (contactPuyoLeft == true && contactPuyoRight == true)
		{
			//—¼•û‚ª‰½‚©‚É‚Ô‚Â‚©‚Á‚½
			map->StorePuyoData(puyo);
			puyo->NewPuyoData();
			contactPuyoLeft = false;
			contactPuyoRight = false;
			CurrentSpeed = 0;
		}
		else if (contactPuyoLeft == true || contactPuyoRight == true)
		{
			//‚Ç‚¿‚ç•Ð•û‚ª‰½‚©‚É‚Ô‚Â‚©‚Á‚½
			puyo->FallPuyo(map,gMane);
			CurrentSpeed = 0;
		}
		else
		{
			//ŽŸ’i‚Ö—Ž‰º
			puyo->FallPuyo(map,gMane);
			CurrentSpeed = 0;
		}
		EnterFlag = false;
	}
}

