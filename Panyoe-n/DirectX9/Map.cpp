#include"Map.h"
#include"Puyo.h"

Map::Map() 
{
	Release();
}
Map::~Map()
{

}

//void Map::StorePuyoData(Puyo* puyo)
//{
//	Puyo::PuyoColor pData =
//		puyo->GetPuyoInfo(1);
//
//	SetPuyoData(pData.PuyoLeftx, pData.PuyoLefty, pData.PuyoLeftColor);
//	SetPuyoData(pData.PuyoRightx, pData.PuyoRighty, pData.PuyoRightColor);
//}

void Map::SetPuyoData(int x, int y, int num)
{
	switch (num)
	{
		case 0:
			PuyoData[y][x] = RED;
			break;
		case 1:
			PuyoData[y][x] = GREEN;
			break;
		case 2:
			PuyoData[y][x] = BLUE;
			break;
		case 3:
			PuyoData[y][x] = YELLOW;
			break;
		case 4:
			PuyoData[y][x] = PURPLE;
			break;
		default:
			PuyoData[y][x] = NON;
			break;
	}
}

//---------------------------------------------------------------------------------------------
//�Ȃ����Ă��邩�ǂ����m�F���鏈���̕���
void Map::CheckConnectPuyo(Puyo* puyo)
{
	//�l���������ĂȂ���̐�������
	Puyo::PuyoColor pData =
		puyo->GetPuyoInfo(1);

	//��ȊO�̂Ȃ�����m�F
	//���삵�Ă���Ղ悩�猩�č��̂Ղ�̂Ȃ��������
	
	for (int cheak = 0; cheak < 2; cheak++)
	{
		ConnectCount = 1;
		//�F�𒲂ׂ�
		//�ŏ���
		if (cheak == 0)
		{
			ColorNum = pData.PuyoLeftColor;
			PuyocheakX = pData.PuyoLeftx;
			PuyocheakY = pData.PuyoLefty;
			SetPuyoData(pData.PuyoLeftx, pData.PuyoLefty, pData.PuyoLeftColor);
		}
		else
		{
			ColorNum = pData.PuyoRightColor;
			PuyocheakX = pData.PuyoRightx;
			PuyocheakY = pData.PuyoRighty;
			SetPuyoData(pData.PuyoRightx, pData.PuyoRighty, pData.PuyoRightColor);
		}

		std::vector<ConnectNum>::iterator it = ConnectData[ColorNum].begin();

		//���E
		for (int x = -1; x < 2; x += 2)
		{
			if (PuyocheakX + x >= 0 && PuyocheakX + x < GetMapx() &&
				RasutaData[PuyocheakY][PuyocheakX + x] != 0)//�͈͊O��r��
			{
				if (PuyoData[PuyocheakY][PuyocheakX + x] == ColorNum)
				{
					ConnectCount = ConnectCount +
						ConnectData[ColorNum][RasutaData[PuyocheakY][PuyocheakX + x] - 1].Connect;
				}
			}
		}
		//��
		if (PuyocheakY + 1 < GetMapy())//�͈͊O��r��
		{
			//���E�Ɠ����g���Ƃ͂���
			if (PuyoData[PuyocheakY + 1][PuyocheakX] == ColorNum && ConnectCount < 4 &&
				RasutaData[PuyocheakY + 1][PuyocheakX] != 0)
			{
				ConnectCount = ConnectCount +
					ConnectData[ColorNum][RasutaData[PuyocheakY + 1][PuyocheakX] - 1].Connect;
			}
		}
		//��͓��ڂ�������K�v���Ȃ��c�ɐς�ł���Ƃ��ɂ������ׂ�K�v���Ȃ�
		if (PuyocheakY - 1 >= 0 && cheak == 1 && PuyocheakY - 1 == pData.PuyoLefty &&
			RasutaData[PuyocheakY - 1][PuyocheakX] != 0)//�͈͊O��r��
		{
			Connectflag = true;
			if (PuyocheakX + 1 < GetMapx())
			{
				if (RasutaData[PuyocheakY][PuyocheakX + 1] != RasutaData[PuyocheakY - 1][PuyocheakX])
				{
					Connectflag = false;
				}
			}
			if (PuyocheakX - 1 >= 0 && !Connectflag)
			{
				if (RasutaData[PuyocheakY][PuyocheakX - 1] != RasutaData[PuyocheakY - 1][PuyocheakX])
				{
					Connectflag = false;
				}
			}
			//���E�Ɠ����g���Ƃ͂���
			if (PuyoData[PuyocheakY - 1][PuyocheakX] == ColorNum && Connectflag)
			{
				ConnectCount = ConnectCount +
					ConnectData[ColorNum][RasutaData[PuyocheakY - 1][PuyocheakX] - 1].Connect;
			}
		}
		//4�ȏキ�����Ă��邱�Ƃ��m�F�ł��܂���
		if (ConnectCount > 3)
		{
			douseFlag = true;
		}
		//1�ȏ�̌q������m�F���܂���
		else if (ConnectCount > 1)
		{
			cheakflag = true;
			//Connectflag = false;
			////��
			//if (PuyocheakX - 1 >= 0)
			//{
			//	if (PuyoData[PuyocheakY][PuyocheakX - 1] == ColorNum)
			//	{
			//		RasutaData[PuyocheakY][PuyocheakX] = RasutaData[PuyocheakY][PuyocheakX - 1];
			//		ConnectData[ColorNum][RasutaData[PuyocheakY][PuyocheakX] - 1].Connect++;
			//		Connectflag = true;
			//	}
			//}
			////�E
			//if (PuyocheakX + 1 < GetMapx())
			//{
			//	if (PuyoData[PuyocheakY][PuyocheakX + 1] == ColorNum && !Connectflag)
			//	{
			//		RasutaData[PuyocheakY][PuyocheakX] = RasutaData[PuyocheakY][PuyocheakX + 1];
			//		ConnectData[ColorNum][RasutaData[PuyocheakY][PuyocheakX] - 1].Connect++;
			//		Connectflag = true;
			//	}
			//	//�q����͂R�ȉ��Ȃ̂ł����ɓ������Ƃ������Ƃ͈�Ɠ��Ȃ������Ƃ�������
			//	else if(PuyoData[PuyocheakY][PuyocheakX + 1] == ColorNum)
			//	{
			//		it = ConnectData[ColorNum].begin();
			//		it += RasutaData[PuyocheakY][PuyocheakX + 1] - 1;
			//		it = ConnectData[ColorNum].erase(it);
			//		it = ConnectData[ColorNum].begin();
			//		RasutaData[PuyocheakY][PuyocheakX + 1] = RasutaData[PuyocheakY][PuyocheakX];
			//		ConnectData[ColorNum][RasutaData[PuyocheakY][PuyocheakX] - 1].Connect++;
			//	}
			//}
			////��
			//if (PuyocheakY + 1 < GetMapy())
			//{
			//	if (PuyoData[PuyocheakY + 1][PuyocheakX] == ColorNum && !Connectflag)
			//	{
			//		RasutaData[PuyocheakY][PuyocheakX] = RasutaData[PuyocheakY + 1][PuyocheakX];
			//		ConnectData[ColorNum][RasutaData[PuyocheakY][PuyocheakX] - 1].Connect++;
			//		Connectflag = true;
			//	}
			//	else if(PuyoData[PuyocheakY + 1][PuyocheakX] == ColorNum && Connectflag)
			//	{
			//		it = ConnectData[ColorNum].begin();
			//		it += RasutaData[PuyocheakY + 1][PuyocheakX] - 1;
			//		it = ConnectData[ColorNum].erase(it);
			//		it = ConnectData[ColorNum].begin();
			//		RasutaData[PuyocheakY + 1][PuyocheakX] = RasutaData[PuyocheakY][PuyocheakX];
			//		ConnectData[ColorNum][RasutaData[PuyocheakY][PuyocheakX] - 1].Connect++;
			//	}
			//}
			////��
			//if (PuyocheakY - 1 < GetMapy() && cheak == 1)
			//{
			//	if (PuyoData[PuyocheakY - 1][PuyocheakX] == ColorNum && !Connectflag)
			//	{
			//		RasutaData[PuyocheakY][PuyocheakX] = RasutaData[PuyocheakY - 1][PuyocheakX];
			//		ConnectData[ColorNum][RasutaData[PuyocheakY][PuyocheakX] - 1].Connect++;
			//		Connectflag = true;
			//	}
			//	else if (PuyoData[PuyocheakY - 1][PuyocheakX] == ColorNum && Connectflag)
			//	{
			//		it = ConnectData[ColorNum].begin();
			//		it += RasutaData[PuyocheakY - 1][PuyocheakX] - 1;
			//		it = ConnectData[ColorNum].erase(it);
			//		it = ConnectData[ColorNum].begin();
			//		RasutaData[PuyocheakY - 1][PuyocheakX] = RasutaData[PuyocheakY][PuyocheakX];
			//		ConnectData[ColorNum][RasutaData[PuyocheakY][PuyocheakX] - 1].Connect++;
			//	}
			//}
		}
		else
		{
			ConnectCheck.Connect = 1;
			ConnectData[ColorNum].push_back(ConnectCheck);
			RasutaData[PuyocheakY][PuyocheakX] = ConnectData[ColorNum].size();
		}
	}
}
void Map::DousePuyo(Puyo* puyo)
{
	douseFlag = false;
	//�F�̐��������[�v
	for (int Puyo = 0; Puyo < puyo->GetMaxPuyoColor(); Puyo++)
	{
		douseData.clear();
		groupCount = 0;
		//�q���肪�S�ȏ�Ȃ�E
		for (std::vector<ConnectNum>::iterator it = ConnectData[Puyo].begin();
			it != ConnectData[Puyo].end(); it++)
		{
			groupCount++;
			if (it->Connect > 3)
			{
				//�����ׂ��ȂՂ��ʔz��Ɋi�[
				douseData.push_back(groupCount);
				//�x�N�^�̃f�[�^������
				it=ConnectData[Puyo].erase(it);
				if (it == ConnectData[Puyo].end())
				{
					break;
				}
				else
				{
					it--;
				}
				
				//�����t���O����
				if(!douseFlag)
				douseFlag = true;
			}
		}
		if (douseFlag)
		{
			//������Ղ������
			for (std::list<int>::iterator it = douseData.begin();
				it != douseData.end(); it++)
			{
				for (int y = 0; y < GetMapy(); y++)
				{
					for (int x = 0; x < GetMapx(); x++)
					{
						if (PuyoData[y][x] == Puyo && RasutaData[y][x] == *it)
						{
							//�q�����Ă���̂ŏ���
							//���ɒ��ׂ�Ă��镪��������
							PuyoData[y][x] = NON;
							if (!fallFlag)
							{
								fallFlag = true;
							}
						}
					}
				}
			}
		}
	}
}

void Map::mFallPuyo()
{
	fallFlag = false;
	for (int x = GetMapx() - 1; x >= 0; x--)
	{
		for (int y = GetMapy() - 2; y >= 0; y--)
		{
			if (PuyoData[y][x] != NON)
			{
				//���ɉ����Ȃ����Ƃ𒲂ׂ�
				if (PuyoData[y + 1][x] == NON)
				{
					PuyoData[y + 1][x] = PuyoData[y][x];
					PuyoData[y][x] = NON;
					if (!fallFlag)
						fallFlag = true;

					if (!douseFlag)
						douseFlag = true;
				}
			}
		}
	}
}

void Map::RastaPuyoData(Puyo* puyo)
{
	if (cheakflag)
	{
		cheakflag = false;
	}
	//�x�N�^�������@�ēx�����f�[�^���`�F�b�N����
	for (int i = 0; i < puyo->GetMaxPuyoColor(); i++)
	{
		ConnectData[i].clear();
	}

	for (int y = 0; y < GetMapy(); y++)
	{
		for (int x = 0; x < GetMapx(); x++)
		{
			//�����Ń��X�^�X�L�����̂��߂̏�����
			RasutaData[y][x] = 0;
		}
	}

	//�ēx�֌W�������Z�b�g �F�̐������֘A�𒲂ׂ�
	//�P�����Ă���͍̂ŏ��̐��l���P�̂���
	for (int Color = RED; Color < puyo->GetMaxPuyoColor(); Color++)
	{
		groupCount = 0;
		//���ׂ�ꏊ����S�������݂Ē��ׂ�
		//���X�^�X�L�����Ƃ����炵���H����͒��ׂ�,,
		for (int y = 0; y < GetMapy(); y++)
		{
			for (int x = 0; x < GetMapx(); x++)
			{
				miniNum = 0;
				SufferLabel = false;
				if (PuyoData[y][x] == Color)//------------------------------------------------
				{
					//�͈͊O��e��
					if (y - 1 >= 0)
					{
						if (x - 1 >= 0)
						{
							//����
							if (RasutaData[y - 1][x - 1] != 0 &&
								PuyoData[y - 1][x - 1] == Color)
							{
								miniNum = RasutaData[y - 1][x - 1];
							}
						}
						//��
						if (RasutaData[y - 1][x] != 0 && !SufferLabel &&
							PuyoData[y - 1][x] == Color)
						{
							if (miniNum == 0)
							{
								miniNum = RasutaData[y - 1][x];
							}		
							else if (miniNum != RasutaData[y - 1][x])
							{
								SufferLabel = true;
							}
						}
						if (x + 1 >= GetMapx() && !SufferLabel)
						{
							//�E��
							if (RasutaData[y - 1][x + 1] != 0 &&
								PuyoData[y - 1][x + 1] == Color)
							{
								if (miniNum == 0)
								{
									miniNum = RasutaData[y - 1][x + 1];
								}
								else if (miniNum != RasutaData[y - 1][x + 1])
								{
									SufferLabel = true;
								}
							}
						}
					}
					if (x - 1 >= 0 && !SufferLabel)
					{
						//��
						if (RasutaData[y][x - 1] != 0 &&
							PuyoData[y][x - 1] == Color)
						{
							if (miniNum == 0)
							{
								miniNum = RasutaData[y][x - 1];
							}
							else if (miniNum != RasutaData[y][x - 1])
							{
								SufferLabel = true;
							}
						}
					}
					if (miniNum == 0)
					{
						//���ׂ����ʐV���ȃO���[�v�쐬�̕K�v��������
						groupCount++;
						RasutaData[y][x] = groupCount;
					}
					else if (SufferLabel)
					{
						//�����̃��x�����m�F�����v�f�Ƃ��čŏ��̔ԍ����i�[
						RasutaData[y][x] = 1;
					}
					else
					{
						//�O���[�v���m�F�o�����̂Ŋi�[
						RasutaData[y][x] = miniNum;
					}
				}//----------------------------------------------------------------------------
			}
		}
		//���Ƀ��b�N�A�b�v�e�[�u�����g�p�i�Ǝ��j
		//�ςȌQ�𐳋K�̌Q�ɕ␳
		for (int y = 0; y < GetMapy(); y++)
		{
			for (int x = GetMapx() - 1; x >= 0; x--)
			{
				//�O�ȊO�̎��͉����C�ӂ̐F������Ƃ�
				if (RasutaData[y][x] != 0)
				{
					if (PuyoData[y][x - 1] == Color)
					{
						if (x - 1 >= 0)
						{
							//���̂����������݂̎w�肵�Ă�����W�̒l�ɏ㏑��
							if (RasutaData[y][x] != RasutaData[y][x - 1] &&
								PuyoData[y][x - 1] == Color)
							{
								RasutaData[y][x - 1] = RasutaData[y][x];
							}
						}
						if (y + 1 < GetMapy())
						{
							//���̂����������݂̎w�肵�Ă�����W�̒l�ɏ㏑��
							if (RasutaData[y][x] != RasutaData[y + 1][x] &&
								PuyoData[y + 1][x] == Color)
							{
								RasutaData[y + 1][x] = RasutaData[y][x];
							}
						}
					}
				}
			}
		}
		//�O���[�v���ƂɂȂ���̐���n���Ă���
		for (int Num = 1; Num <= groupCount; Num++)
		{
			ConnectCheck.Connect = 0;
			//�Ȃ���𒲂ׂĂ���
			for (int y = 0; y < GetMapy(); y++)
			{
				for (int x = 0; x < GetMapx(); x++)
				{
					if (RasutaData[y][x] == Num 
						&& PuyoData[y][x] == Color)
					{
						ConnectCheck.Connect++;
					}
				}
			}
			//�x�N�^�̌��Ɋi�[
			ConnectData[Color].push_back(ConnectCheck);
		}
	}
}

void Map::Release()
{
	//�Ȃ����Ă��邩�̔���̏������p�z��Ǝg�p����z��̏����ݒ�
	checkPuyoColor = NON;
	overFlag = false;
	inspectFlag = false;
	douseFlag = false;
	fallFlag = false;
	NewPuyoFlag = false;
	SufferLabel = false;
	Connectflag = false;
	cheakflag = false;

	ColorNum = 0;

	douseData.clear();

	//�z���������
	for (int i = 0; i < 5; i++)
	{
		ConnectData[i].clear();
	}
	//���X�^�f�[�^��������
	for (int y = 0; y < Mapy; y++)
	{
		for (int x = 0; x < Mapx; x++)
		{
			RasutaData[y][x] = 0;
			PuyoData[y][x] = NON;
		}
	}
}


/*//��݂ā[���݂ā[�����Ă�
if (connectFlag[1].Upflag != true)
{
	if (connectFlag[1].Downflag != true)
	{
		if (connectFlag[1].Leftflag != true)
		{
			if (connectFlag[1].Rightflag != true)
			{

			}
		}
	}
}*/