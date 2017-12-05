#include"GameManager.h"
#include"Puyo.h"
#include"Map.h"

GameManager::GameManager()
{
	SPEED = 60;//約1秒
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
			//両方が何かにぶつかった
			map->StorePuyoData(puyo);
			puyo->NewPuyoData();
			contactPuyoLeft = false;
			contactPuyoRight = false;
			CurrentSpeed = 0;
		}
		else if (contactPuyoLeft == true || contactPuyoRight == true)
		{
			//どちら片方が何かにぶつかった
			puyo->FallPuyo(map,gMane);
			CurrentSpeed = 0;
		}
		else
		{
			//次段へ落下
			puyo->FallPuyo(map,gMane);
			CurrentSpeed = 0;
		}
		EnterFlag = false;
	}
}

