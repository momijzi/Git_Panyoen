#include"GameManager.h"
#include"Puyo.h"
#include"Map.h"

GameManager::GameManager()
{
	SPEED = 120;//��1�b
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
		//���i�֗���
		puyo->FallPuyo(&gMane);
		CurrentSpeed = 0;
	}
	else if (contactPuyoLeft == true && contactPuyoRight == true)
	{
		//�����������ɂԂ�����
		puyo->NewPuyoData();
		map->StorePuyoData(puyo);
		CurrentSpeed = 0;
	}
	else if(contactPuyoLeft == true || contactPuyoRight == true)
	{
		//�ǂ���Е��������ɂԂ�����
		puyo->FallPuyo(&gMane);
	}
}

