#include"GameManager.h"
#include"Puyo.h"
#include"Map.h"

GameManager::GameManager()
{
	SPEED = 60;//��1�b
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
			//�����������ɂԂ�����
			map->StorePuyoData(puyo);
			puyo->NewPuyoData();
			contactPuyoLeft = false;
			contactPuyoRight = false;
			CurrentSpeed = 0;
		}
		else if (contactPuyoLeft == true || contactPuyoRight == true)
		{
			//�ǂ���Е��������ɂԂ�����
			puyo->FallPuyo(map,gMane);
			CurrentSpeed = 0;
		}
		else
		{
			//���i�֗���
			puyo->FallPuyo(map,gMane);
			CurrentSpeed = 0;
		}
		EnterFlag = false;
	}
}

