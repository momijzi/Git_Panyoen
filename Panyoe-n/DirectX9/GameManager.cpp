#include"GameManager.h"
#include"Puyo.h"
#include"Map.h"

GameManager::GameManager()
{
	SPEED = 120;//約1秒
	CurrentSpeed = 0;
	contactPuyoLeft = false;
	contactPuyoRight = false;
}
GameManager:: ~GameManager()
{

}

GameManager gMane;

void GameManager::MovePuyo(Puyo* puyo ,Map* map)
{
	CurrentSpeed++;
	if (CurrentSpeed == SPEED)
	{
		//次段へ落下
		puyo->FallPuyo(&gMane);
		CurrentSpeed = 0;
	}
	else if (contactPuyoLeft == true && contactPuyoRight == true)
	{
		//両方が何かにぶつかった
		puyo->NewPuyoData();
		map->StorePuyoData(puyo);
		CurrentSpeed = 0;
	}
	else if(contactPuyoLeft == true || contactPuyoRight == true)
	{
		//どちら片方が何かにぶつかった
		puyo->FallPuyo(&gMane);
	}
}

