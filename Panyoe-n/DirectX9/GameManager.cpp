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

	
	if ((contactPuyoLeft != contactPuyoRight ))
	{
		//�ǂ���Е��������ɂԂ�����
		puyo->FallPuyo(map, gMane);
		CurrentSpeed = 0;
	}
	else if((CurrentSpeed == SPEED || EnterFlag) && !contactPuyoLeft && !contactPuyoRight)
	{
		//���i�֗���
		puyo->FallPuyo(map, gMane);
		CurrentSpeed = 0;
		EnterFlag = false;
	}
	
	if (contactPuyoLeft && contactPuyoRight )
	{
		//�Ղ悪�����؂����̂ő��̃f�[�^�Ɗ֘A�t��
		if (SetFlag != true)
		{
			SetPuyoFlag(true);
			SetFlag = true;
			Puyo::PuyoColor pData =
				puyo->GetPuyoInfo(1);

			//�Ղ�����C���̃f�[�^�ɓK��
			map->SetPuyoData(pData.PuyoLeftx, pData.PuyoLefty, pData.PuyoLeftColor);
			map->SetPuyoData(pData.PuyoRightx, pData.PuyoRighty, pData.PuyoRightColor);
		}
		if (CurrentSpeed == SPEED)
		{
			if (!map->GetFallFlag())
			{
				//�q�����Ă���v�f���m�F����
				map->RastaPuyoData(puyo);
			}

			if (map->GetDouseFlag())
			{
				SetPuyoFlag(false);
				//�Ȃ����Ă���ӏ������o�����̂ŏ���
				map->DousePuyo(puyo);
			}
			else if (map->GetFallFlag())
			{
				//��ŏ�����ė�������Ղ�𗎉�������
				map->mFallPuyo();
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
			}
			CurrentSpeed = 0;
		}
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
	PuyoFlag = false;
}

