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


void Puyo::SideMovePuyo(int w)
{ 
	//�ړ��悪�g�O�Ȃ�s���Ȃ�
	if ( 0 < pPuyoColor[1].PuyoLeftx + w && pPuyoColor[1].PuyoRightx + w < map.GetMapx())
	{
		//�ړ�
		pPuyoColor[1].PuyoLeftx = pPuyoColor[1].PuyoLeftx + w;
		pPuyoColor[1].PuyoRightx = pPuyoColor[1].PuyoRightx + w;
	}
}

void Puyo::RotaPuyo(int wh)
{
	//�����̏��
	if (pPuyoColor[1].PuyoLeftx < pPuyoColor[1].PuyoRightx && pPuyoColor[1].PuyoLefty == pPuyoColor[1].PuyoRighty)
	{
			
			pPuyoColor[1].PuyoLeftx = pPuyoColor[1].PuyoLeftx + wh;
			pPuyoColor[1].PuyoLefty = pPuyoColor[1].PuyoLefty + wh;
	}
	//�������ɂ��������̂��E�ɂ��鎞
	else if (pPuyoColor[1].PuyoLeftx > pPuyoColor[1].PuyoRightx && pPuyoColor[1].PuyoLefty == pPuyoColor[1].PuyoRighty)
	{
		pPuyoColor[1].PuyoLeftx = pPuyoColor[1].PuyoLeftx - wh;
		pPuyoColor[1].PuyoLefty = pPuyoColor[1].PuyoLefty - wh;
	}
	//�������ɂ��������̂���ɂ��鎞
	else if (pPuyoColor[1].PuyoLeftx == pPuyoColor[1].PuyoRightx && pPuyoColor[1].PuyoLefty > pPuyoColor[1].PuyoRighty)
	{
		//�ړ��悪�g�O�ł͂Ȃ����𔻒f
		if (0 < pPuyoColor[1].PuyoLeftx + wh && pPuyoColor[1].PuyoLeftx + wh < map.GetMapx())
		{
			pPuyoColor[1].PuyoLeftx = pPuyoColor[1].PuyoLeftx + wh;
			pPuyoColor[1].PuyoLefty = pPuyoColor[1].PuyoLefty - wh;
		}
	}
	//�������ɂ��������̂����ɂ��鎞
	else if (pPuyoColor[1].PuyoLeftx == pPuyoColor[1].PuyoRightx && pPuyoColor[1].PuyoLefty > pPuyoColor[1].PuyoRighty)
	{
		if (0 < pPuyoColor[1].PuyoLeftx + wh && pPuyoColor[1].PuyoLeftx + wh < map.GetMapx())
		{
			//�ړ��悪�g�O�ł͂Ȃ����𔻒f
			pPuyoColor[1].PuyoLeftx = pPuyoColor[1].PuyoLeftx - wh;
			pPuyoColor[1].PuyoLefty = pPuyoColor[1].PuyoLefty + wh;
		}
	}
}

void Puyo::FallPuyo(GameManager* gMane)
{
	//�Ղ悪�����ɓ��������������͉��ɂ��ǂ蒅����
	if (pPuyoColor[1].PuyoLefty + 1 == map.GetMapy() || pPuyoColor[1].PuyoRighty + 1 == map.GetMapy())
	{
		//���̂Ղ擊������
		gMane->SetContactPuyoLeft(true);
		gMane->SetContactPuyoRight(true);
	}
	else if ((map.GetPuyoData(pPuyoColor[1].PuyoLeftx, pPuyoColor[1].PuyoLefty + 1) != map.NON ||
		map.GetPuyoData(pPuyoColor[1].PuyoRightx, pPuyoColor[1].PuyoRighty + 1) != map.NON) &&
		pPuyoColor[1].PuyoLeftx != pPuyoColor[1].PuyoRightx)
	{
		//�Е��̂ݓ��������ꍇ
		//���̂ݗ���
		if (map.GetPuyoData(pPuyoColor[1].PuyoLeftx, pPuyoColor[1].PuyoLefty + 1) == map.NON)
		{
			pPuyoColor[1].PuyoLefty = pPuyoColor[1].PuyoLefty + 1;
		}
		else
		{
			//�������Ă���������͉��ɂ��ǂ蒅����
			gMane->SetContactPuyoLeft(true);
		}
		//�E�̂ݗ���
		if (map.GetPuyoData(pPuyoColor[1].PuyoRightx, pPuyoColor[1].PuyoRighty + 1) == map.NON)
		{
			pPuyoColor[1].PuyoRighty = pPuyoColor[1].PuyoRighty + 1;
		}
		else
		{
			//�������Ă���������͉��ɂ��ǂ蒅����
			gMane->SetContactPuyoRight(true);
		}
	}
	else
	{
		pPuyoColor[1].PuyoLefty = pPuyoColor[1].PuyoLefty + 1;
		pPuyoColor[1].PuyoRighty = pPuyoColor[1].PuyoRighty + 1;
	}
}

void Puyo::NewPuyoData()
{
	//�ҋ@���Ă����Ղ�̃f�[�^���i�[
	pPuyoColor[1] = pPuyoColor[0];
	//�ŏ��̏����ʒu��ݒ�
	pPuyoColor[1].PuyoLeftx = 3;
	pPuyoColor[1].PuyoLefty = 4;
	//�V�����F���擾�i�ҋ@�f�[�^�j
	pPuyoColor[0].PuyoLeftColor = rand() % MaxPuyoColor;
	pPuyoColor[0].PuyoRightColor = rand() % MaxPuyoColor;
}

void Puyo::Release()
{
	//�o��f�[�^���҂��f�[�^��������
	for (int i = 0; i < 2; i++)
	{
		//�F�������_���Ɏ��
		pPuyoColor[i].PuyoLeftColor = rand() % MaxPuyoColor;
		pPuyoColor[i].PuyoRightColor = rand() % MaxPuyoColor;
		if (i != 0)
		{
			//�ŏ��ɏo��f�[�^�̍��W���i�[
			pPuyoColor[i].PuyoLeftx = 3;
			pPuyoColor[i].PuyoLefty = 0;
			pPuyoColor[i].PuyoRightx = 4;
			pPuyoColor[i].PuyoRighty = 0;
		}
		else
		{
			//�ҋ@�f�[�^���i�[
			pPuyoColor[i].PuyoLeftx = 0;
			pPuyoColor[i].PuyoLefty = 0;
			pPuyoColor[i].PuyoRightx = 0;
			pPuyoColor[i].PuyoRighty = 0;
		}
	}
}