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
			//�����������ɂԂ�����
			puyo->NewPuyoData();
			contactPuyoLeft = false;
			contactPuyoRight = false;
			SetFlag = false;
			CurrentSpeed = 0;
		}
	}
	else if (CurrentSpeed == SPEED && (contactPuyoLeft == true || contactPuyoRight == true))
	{
		//�ǂ���Е��������ɂԂ�����
		puyo->FallPuyo(map, gMane);
		CurrentSpeed = 0;
	}
	else if(CurrentSpeed == SPEED || EnterFlag == true)
	{
		//���i�֗���
		puyo->FallPuyo(map, gMane);
		CurrentSpeed = 0;
	}
	EnterFlag = false;
}


