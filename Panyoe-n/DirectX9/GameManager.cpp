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
	SetFlag = false;
}
GameManager:: ~GameManager()
{

}

GameManager gMane;

void GameManager::MovePuyo(Puyo* puyo, Map* map, GameManager* gMane)
{
	CurrentSpeed++;

	if (contactPuyoLeft == true && contactPuyoRight == true)
	{
		if (SetFlag != true)
		{
			map->StorePuyoData(puyo);
			SetFlag = true;
		}
		map->ConnectPuyo();
		if (map->GetDouseFlag())
		{
			map->DousePuyo();
		}
		else if (map->GetFallFlag())
		{
			map->mFallPuyo();
		}
		else
		{
			//—¼•û‚ª‰½‚©‚É‚Ô‚Â‚©‚Á‚½
			puyo->NewPuyoData();
			contactPuyoLeft = false;
			contactPuyoRight = false;
			SetFlag = false;
			CurrentSpeed = 0;
		}
	}
	else if (CurrentSpeed == SPEED && (contactPuyoLeft == true || contactPuyoRight == true))
	{
		//‚Ç‚¿‚ç•Ð•û‚ª‰½‚©‚É‚Ô‚Â‚©‚Á‚½
		puyo->FallPuyo(map, gMane);
		CurrentSpeed = 0;
	}
	else if(CurrentSpeed == SPEED || EnterFlag == true)
	{
		//ŽŸ’i‚Ö—Ž‰º
		puyo->FallPuyo(map, gMane);
		CurrentSpeed = 0;
	}
	EnterFlag = false;
}


