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

void Map::SetPuyoData(int x, int y, int color)
{
	switch (color)
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

void Map::DousePuyo(Puyo* puyo)
{
	//�F�̐��������[�v
	for (int Puyo = 0; Puyo < puyo->GetMaxPuyoColor(); Puyo++)
	{
		douseData.clear();
		groupCount = 0;
		//�q���肪�S�ȏ�Ȃ�E
		{
			std::vector<ConnectNum>::iterator it = ConnectData[Puyo].begin();
			while (it != ConnectData[Puyo].end())
			{
				groupCount++;
				if (it->Connect > 3)
				{
					//�����ׂ��ȂՂ��ʔz��Ɋi�[
					douseData.push_back(groupCount);
					//�x�N�^�̃f�[�^������
					it = ConnectData[Puyo].erase(it);
				}
				else
				{
					it++;
				}
			}
		}
		groupCount = 0;
		//������Ղ������
		for (std::list<int>::iterator it = douseData.begin();
			it != douseData.end(); it++)
		{
			groupCount++;
			for (int y = 0; y < GetMapy(); y++)
			{
				for (int x = 0; x < GetMapx(); x++)
				{
					if (PuyoData[y][x] == Puyo && RasutaData[y][x] == groupCount)
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
	douseFlag = false;
	DrowFlag = false;
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
					{
						fallFlag = true;
					}
				}
			}
		}
	}
}

void Map::RastaPuyoData(Puyo* puyo)
{
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
				if (PuyoData[y][x] == Color)
				{
					if (x - 1 >= 0)
					{
						if (PuyoData[y][x - 1] == Color)
						{
							//���̂����������݂̎w�肵�Ă�����W�̒l�ɏ㏑��
							if (RasutaData[y][x] != RasutaData[y][x - 1])
							{
								RasutaData[y][x - 1] = RasutaData[y][x];
							}
						}
					}
					if (y + 1 < GetMapy())
					{
						if (PuyoData[y + 1][x] == Color)
						{
							//���̂����������݂̎w�肵�Ă�����W�̒l�ɏ㏑��
							if (RasutaData[y][x] != RasutaData[y + 1][x])
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
			//0�ȊO�̎�����
			if (ConnectCheck.Connect != 0)
			{
				//�x�N�^�̌��Ɋi�[
				ConnectData[Color].push_back(ConnectCheck);

				//�Ȃ��肪�S�ȏ゠��΂Ղ���폜
				if (ConnectCheck.Connect > 3 && !douseFlag)
				{
					douseFlag = true;
				}
			}
		}
	}
}

void Map::Release()
{
	//�Ȃ����Ă��邩�̔���̏������p�z��Ǝg�p����z��̏����ݒ�
	checkPuyoColor = NON;
	douseFlag = false;
	fallFlag = false;
	NewPuyoFlag = false;
	SufferLabel = false;

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