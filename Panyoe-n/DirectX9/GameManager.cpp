#include"GameManager.h"
#include"Puyo.h"
#include"Map.h"

GameManager::GameManager()
{
	Release();
}
GameManager:: ~GameManager()
{

}

GameManager gMane;

void GameManager::MovePuyo(Puyo* puyo, Map* map, GameManager* gMane)
{
	CurrentSpeed++;

	if (contactPuyoLeft && contactPuyoRight)
	{
		//�Ղ悪�����؂����̂ő��̃f�[�^�Ɗ֘A�t��
		if (SetFlag != true)
		{
			SetFlag = true;
			//�Ȃ����Ă��邩�ǂ����̔��f
			map->CheckConnectPuyo(puyo);
		}

		if (map->GetDouseFlag() && !map->GetFallFlag())
		{
			//�q�����Ă���v�f���m�F����
			map->RastaPuyoData(puyo);
			//�Ȃ����Ă���ӏ������o�����̂ŏ���
			map->DousePuyo(puyo);
		}
		else if(map->GetFallFlag())
		{
			//��ŏ�����ė�������Ղ�𗎉�������
			map->mFallPuyo();
		}
		else if (map->GetCheakFlag())
		{
			map->RastaPuyoData(puyo);
		}
		//�Ȃ����Ă���ӏ����m�F�ł��Ȃ�����
		//���̂Ղ�𐶐�
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
	else if ((contactPuyoLeft || contactPuyoRight ))
	{
		//�ǂ���Е��������ɂԂ�����
		puyo->FallPuyo(map, gMane);
		CurrentSpeed = 0;
	}
	else if(CurrentSpeed == SPEED || EnterFlag)
	{
		//���i�֗���
		puyo->FallPuyo(map, gMane);
		CurrentSpeed = 0;
		EnterFlag = false;
	}
}

void GameManager::Release()
{
	SPEED = 60;//��1�b
	CurrentSpeed = 0;
	contactPuyoLeft = false;
	contactPuyoRight = false;
	EnterFlag = false;
	SetFlag = false;
}

