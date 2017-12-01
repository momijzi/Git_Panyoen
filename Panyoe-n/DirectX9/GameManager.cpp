#include"GameManager.h"
#include"Puyo.h"
#include"Map.h"

GameManager::GameManager()
{
	SPEED = 120;//–ñ1•b
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
		//ŽŸ’i‚Ö—Ž‰º
		puyo->FallPuyo(&gMane);
		CurrentSpeed = 0;
	}
	else if (contactPuyoLeft == true && contactPuyoRight == true)
	{
		//—¼•û‚ª‰½‚©‚É‚Ô‚Â‚©‚Á‚½
		puyo->NewPuyoData();
		map->StorePuyoData(puyo);
		CurrentSpeed = 0;
	}
	else if(contactPuyoLeft == true || contactPuyoRight == true)
	{
		//‚Ç‚¿‚ç•Ð•û‚ª‰½‚©‚É‚Ô‚Â‚©‚Á‚½
		puyo->FallPuyo(&gMane);
	}
}

