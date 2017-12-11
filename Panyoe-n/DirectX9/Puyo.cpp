#include"Puyo.h"
#include"time.h"
#include"windows.h"
#include"GameManager.h"
#include"Map.h"

Puyo::Puyo()
{
	MaxPuyoColor = 0;
}
Puyo::~Puyo()
{

}

Map map;


void Puyo::SideMovePuyo(int w ,Map* map)
{ 
	//�ړ��悪�g�O�Ȃ�s���Ȃ�
	if ( 0 <= PuyoData[1].PuyoLeftx + w && PuyoData[1].PuyoLeftx + w < map->GetMapx() &&
		0 <= PuyoData[1].PuyoRightx + w && PuyoData[1].PuyoRightx + w < map->GetMapx() &&
		map->GetPuyoData(PuyoData[1].PuyoLeftx + w,PuyoData[1].PuyoLefty) == map->NON &&
		map->GetPuyoData(PuyoData[1].PuyoRightx + w, PuyoData[1].PuyoRighty)== map->NON)
	{
		//�ړ�
		PuyoData[1].PuyoLeftx = PuyoData[1].PuyoLeftx + w;
		PuyoData[1].PuyoRightx = PuyoData[1].PuyoRightx + w;
	}
}

void Puyo::RotaPuyo(int wh ,Map* map, GameManager* gMane)
{
	//�����̏��
	if (PuyoData[1].PuyoLeftx < PuyoData[1].PuyoRightx && PuyoData[1].PuyoLefty == PuyoData[1].PuyoRighty)
	{
		//����l�ɂ��㉺�s���邩������
		if (map->GetPuyoData(PuyoData[1].PuyoLeftx, PuyoData[1].PuyoLefty - wh) == map->NON &&
			map->GetPuyoData(PuyoData[1].PuyoLeftx + 1, PuyoData[1].PuyoLefty - wh) == map->NON &&
			PuyoData[1].PuyoLefty < map->GetMapy() - 1)
		{
			PuyoData[1].PuyoLeftx = PuyoData[1].PuyoLeftx + 1;
			PuyoData[1].PuyoLefty = PuyoData[1].PuyoLefty - wh;
		}
	}
	//�������ɂ��������̂��E�ɂ��鎞
	else if (PuyoData[1].PuyoLeftx > PuyoData[1].PuyoRightx && PuyoData[1].PuyoLefty == PuyoData[1].PuyoRighty)
	{
		if (map->GetPuyoData(PuyoData[1].PuyoLeftx, PuyoData[1].PuyoLefty + wh) == map->NON &&
			map->GetPuyoData(PuyoData[1].PuyoLeftx - 1, PuyoData[1].PuyoLefty + wh) == map->NON &&
			PuyoData[1].PuyoLefty < map->GetMapy() - 1)
		{
			PuyoData[1].PuyoLeftx = PuyoData[1].PuyoLeftx - 1;
			PuyoData[1].PuyoLefty = PuyoData[1].PuyoLefty + wh;
		}
	}
	//�������ɂ��������̂����ɂ��鎞
	else if (PuyoData[1].PuyoLeftx == PuyoData[1].PuyoRightx && PuyoData[1].PuyoLefty > PuyoData[1].PuyoRighty)
	{
		//�ړ��悪�g�O�ł͂Ȃ����𔻒f
		if (0 < PuyoData[1].PuyoLeftx + (wh * -1) && PuyoData[1].PuyoLeftx + (wh * -1) < map->GetMapx() &&
			map->GetPuyoData(PuyoData[1].PuyoLeftx - wh, PuyoData[1].PuyoLefty - 1) == map->NON &&
			map->GetPuyoData(PuyoData[1].PuyoLeftx - wh, PuyoData[1].PuyoLefty) == map->NON)
		{
			PuyoData[1].PuyoLeftx = PuyoData[1].PuyoLeftx + (wh * -1);
			PuyoData[1].PuyoLefty = PuyoData[1].PuyoLefty - 1;
		}
	}
	//�������ɂ��������̂���ɂ��鎞
	else if (PuyoData[1].PuyoLeftx == PuyoData[1].PuyoRightx && PuyoData[1].PuyoLefty < PuyoData[1].PuyoRighty)
	{
		if (0 < PuyoData[1].PuyoLeftx + wh && PuyoData[1].PuyoLeftx + wh < map->GetMapx() &&
			map->GetPuyoData(PuyoData[1].PuyoLeftx + wh, PuyoData[1].PuyoLefty + 1) == map->NON &&
			map->GetPuyoData(PuyoData[1].PuyoLeftx + wh, PuyoData[1].PuyoLefty) == map->NON)
		{
			PuyoData[1].PuyoLeftx = PuyoData[1].PuyoLeftx + wh;
			PuyoData[1].PuyoLefty = PuyoData[1].PuyoLefty + 1;
		}
	}
}

void Puyo::FallPuyo(Map* map,GameManager* gMane)
{
	//�Ղ悪�����ɓ��������������͉��ɂ��ǂ蒅����
	if (PuyoData[1].PuyoLefty == map->GetMapy() - 1 || PuyoData[1].PuyoRighty == map->GetMapy() - 1)
	{
		//���̂Ղ擊������
		gMane->SetContactPuyoLeft(true);
		gMane->SetContactPuyoRight(true);
	}
	//�Е����܂��������Ă��Ȃ�
	else if ((map->GetPuyoData(PuyoData[1].PuyoLeftx, PuyoData[1].PuyoLefty + 1) != map->NON ||
		map->GetPuyoData(PuyoData[1].PuyoRightx, PuyoData[1].PuyoRighty + 1) != map->NON))
	{
		//�����������̏�ɑ��݂��邽�ߓ����Ȃ�����
		if (PuyoData[1].PuyoLeftx != PuyoData[1].PuyoRightx)
		{
			if (gMane->GetContactPuyoLeft() != true)
			{
				//�Е��̂ݓ��������ꍇ	//���̂ݗ���
				if (map->GetPuyoData(PuyoData[1].PuyoLeftx, PuyoData[1].PuyoLefty + 1) == map->NON)
				{
					PuyoData[1].PuyoLefty = PuyoData[1].PuyoLefty + 1;
				}
				else
				{
					//�������Ă���������͉��ɂ��ǂ蒅����
					gMane->SetContactPuyoLeft(true);
				}
			}
			
			//�E�̂ݗ���
			if (gMane->GetContactPuyoRight() != true)
			{
				if (map->GetPuyoData(PuyoData[1].PuyoRightx, PuyoData[1].PuyoRighty + 1) == map->NON)
				{
					PuyoData[1].PuyoRighty = PuyoData[1].PuyoRighty + 1;
				}
				else
				{
					//�������Ă���������͉��ɂ��ǂ蒅����
					gMane->SetContactPuyoRight(true);
				}
			}
		}
		else//�c�ɏd�Ȃ��Ă���ꍇ
		{
			//���̂Ղ擊������
			gMane->SetContactPuyoLeft(true);
			gMane->SetContactPuyoRight(true);
		}
	}
	else
	{		
		PuyoData[1].PuyoLefty = PuyoData[1].PuyoLefty + 1;
		PuyoData[1].PuyoRighty = PuyoData[1].PuyoRighty + 1;
	}
}

void Puyo::NewPuyoData()
{
	//�ҋ@���Ă����Ղ�̃f�[�^���i�[
	PuyoData[1] = PuyoData[0];
	//�ŏ��̏����ʒu��ݒ�
	PuyoData[1].PuyoLeftx = 2;
	PuyoData[1].PuyoRightx = 3;
	//�V�����F���擾�i�ҋ@�f�[�^�j
	PuyoData[0].PuyoLeftColor = rand() % MaxPuyoColor;
	PuyoData[0].PuyoRightColor = rand() % MaxPuyoColor;
}

void Puyo::Release()
{
	//�o��f�[�^���҂��f�[�^��������
	for (int i = 0; i < 2; i++)
	{
		//�F�������_���Ɏ��
		PuyoData[i].PuyoLeftColor = rand() % MaxPuyoColor;
		PuyoData[i].PuyoRightColor = rand() % MaxPuyoColor;
		if (i != 0)
		{
			//�ŏ��ɏo��f�[�^�̍��W���i�[
			PuyoData[i].PuyoLeftx = 2;
			PuyoData[i].PuyoLefty = 0;
			PuyoData[i].PuyoRightx = 3;
			PuyoData[i].PuyoRighty = 0;
		}
		else
		{
			//�ҋ@�f�[�^���i�[
			PuyoData[i].PuyoLeftx = 0;
			PuyoData[i].PuyoLefty = 0;
			PuyoData[i].PuyoRightx = 0;
			PuyoData[i].PuyoRighty = 0;
		}
	}
}