#include"Map.h"
#include"Puyo.h"

Map::Map() 
{
	Release();
}
Map::~Map()
{

}

void Map::StorePuyoData(Puyo* puyo)
{
	Puyo::PuyoColor pData =
		puyo->GetPuyoInfo(1);

	SetPuyoData(pData.PuyoLeftx, pData.PuyoLefty, pData.PuyoLeftColor);
	SetPuyoData(pData.PuyoRightx, pData.PuyoRighty, pData.PuyoRightColor);
}

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

void Map::ConnectPuyo()
{
	//�Ȃ����Ă��邩�ǂ������ׂ邽�ߏ�����
	for (int y = 0; y < GetMapy(); y++)
	{
		for (int x = 0; x < GetMapx(); x++)
		{
			connectPuyo[y][x] = false;
			checkPuyo[y][x] = false;
			dousePuyo[y][x] = false;
		}
	}
	//�Ȃ����Ă��邩�ǂ����𔻒f//y�����
	for (int x = 0; x < GetMapx(); x++)
	{
		for (int y = 0; y < GetMapy(); y++)
		{
			//���̏ꏊ�ɂՂ悪���邱�Ƃ�����
			//���ɂȂ��肪�m�F����Ă���ꏊ�͂͂���
			if (PuyoData[y][x] != NON && checkPuyo[y][x] != true)
			{
				//���ׂ�F�ƂȂ��������true���i�[
				checkPuyoColor = PuyoData[y][x];
				connectPuyo[y][x] = true;

				CheckConnectPuyo(x, y);
			}

			for (int y = 0; y < GetMapy(); y++)
			{
				for (int x = 0; x < GetMapx(); x++)
				{
					if (connectPuyo[y][x])
					{
						checkPuyo[y][x] = true;
						//��ȏ�̂Ȃ��肪�m�F�ł���̂ŏ���
						if (ConnectCount > 3)
						{
							dousePuyo[y][x] = true;
							douseFlag = true;
						}
					}
					//���̎{�s�Ɏg�����ߏ�����
					connectPuyo[y][x] = false;
				}
			}
			ConnectCount = 0;
		}
	}
}

void Map::CheckConnectPuyo(int x, int y)
{
	//�c���Ɍ���
	for (int Cx = x; Cx < GetMapx(); Cx++)
	{
		for (int Cy = 0; Cy < GetMapy(); Cy++)
		{
			//���ɒ��ׂĂ���Ղ�͒e��
			if (checkPuyo[Cy][Cx] != true && connectPuyo[Cy][Cx] != true)
			{
				//�F�������ł���
				if (PuyoData[Cy][Cx] == checkPuyoColor)
				{
					//�\������p�̃��[�v�i�z��g����n + ���j
					for (int C = -1; C < 2; C += 2)
					{
						//���ݒ��ׂĂ���ʒu�����݂Ȃ���𒲂ׂĂ���ꏊ��
						//�Ȃ����Ă��邩�ǂ������f
						//�z��I�ɔz��O�������Ȃ��悤�ɒe���Ă���
						if (Cy + C >= 0 && Cy + C < GetMapy())
						{
							if (connectPuyo[Cy + C][Cx])
							{
								connectPuyo[Cy][Cx] = true;
							}
						}
						if (Cx + C >= 0 && Cx + C < GetMapx())
						{
							if (connectPuyo[Cy][Cx + C])
							{
								connectPuyo[Cy][Cx] = true;
							}
						}
					}
					//�Ȃ����Ă��邱�Ƃ��m�F�����̂ł�������\���Ɋm�F
					if (connectPuyo[Cy][Cx])
					{
						ConnectCount++;
						for (int C = -1; C < 2; C += 2)
						{
							//���ׂē����F�̏ꍇtrue��
							if (Cy + C >= 0 && Cy + C < GetMapy() &&
								Cy + C != y &&
								connectPuyo[Cy + C][Cx])
							{
								if (PuyoData[Cy + C][Cx] == checkPuyoColor)
								{
									connectPuyo[Cy + C][Cx] = true;
									ConnectCount++;
								}
							}
							if (Cx + C >= 0 && Cx + C < GetMapx() &&
								Cx + C != x &&
								connectPuyo[Cy][Cx + C])
							{
								if (PuyoData[Cy][Cx + C] == checkPuyoColor)
								{
									connectPuyo[Cy][Cx + C] = true;
									ConnectCount++;
								}
							}
						}
					}
				}
			}
		}
	}
	//�t���猩��
	for (int Cx = GetMapx(); Cx > x; Cx--)
	{
		for (int Cy = GetMapy(); Cy < y; Cy--)
		{
			//���ɒ��ׂĂ���Ղ�͒e��
			if (checkPuyo[Cy][Cx] != true && connectPuyo[Cy][Cx] != true)
			{
				//�F�������ł���
				if (PuyoData[Cy][Cx] == checkPuyoColor)
				{
					//�\������p�̃��[�v�i�z��g����n + ���j
					for (int C = -1; C < 2; C += 2)
					{
						/*���ݒ��ׂĂ���ʒu�����݂Ȃ���𒲂ׂĂ���ꏊ��
						�Ȃ����Ă��邩�ǂ������f
						�z��I�ɔz��O�������Ȃ��悤�ɒe���Ă���*/
						if (Cy + C >= 0 && Cy + C < GetMapy())
						{
							if (connectPuyo[Cy + C][Cx])
							{
								connectPuyo[Cy][Cx] = true;
							}
						}
						if (Cx + C >= 0 && Cx + C < GetMapx())
						{
							if (connectPuyo[Cy][Cx + C])
							{
								connectPuyo[Cy][Cx] = true;
							}
						}
					}
					//�Ȃ����Ă��邱�Ƃ��m�F�����̂ł�������\���Ɋm�F
					if (connectPuyo[Cy][Cx])
					{
						ConnectCount++;
						for (int C = -1; C < 2; C += 2)
						{
							//���ׂē����F�̏ꍇtrue��
							if (Cy + C >= 0 && Cy + C < GetMapy() &&
								Cy + C != y &&
								connectPuyo[Cy + C][Cx])
							{
								if (PuyoData[Cy + C][Cx] == checkPuyoColor)
								{
									connectPuyo[Cy + C][Cx] = true;
									ConnectCount++;
								}
							}
							if (Cx + C >= 0 && Cx + C < GetMapx() &&
								Cx + C != x &&
								connectPuyo[Cy][Cx + C])
							{
								if (PuyoData[Cy][Cx + C] == checkPuyoColor)
								{
									connectPuyo[Cy][Cx + C] = true;
									ConnectCount++;
								}
							}
						}
					}
				}
			}
		}
	}
}
void Map::DousePuyo()
{
	for (int y = 0; y < GetMapy(); y++)
	{
		for (int x = 0; x < GetMapx(); x++)
		{
			if (dousePuyo[y][x])
			{
				SetPuyoData(x, y, -1);
			}
		}
	}
	douseFlag = false;
	fallFlag = true;
}

void Map::mFallPuyo()
{
	if (fallFlag)
	{
		fallFlag = false;
		for (int y = GetMapy(); y > 0; y--)
		{
			for (int x = GetMapx(); x > 0; x--)
			{
				if (PuyoData[y][x] != NON)
				{
					//���̎҂�������������̂ŉ��Ɉړ�
					if (y + 1 < GetMapy() && PuyoData[y + 1][x] != NON)
					{
						PuyoData[y + 1][x] = PuyoData[y][x];
						PuyoData[y][x] = NON;
						fallFlag = true;
					}
				}
			}
		}
	}
	NewPuyoFlag = true;
}

void Map::Release()
{
	//�Ȃ����Ă��邩�̔���̏������p�z��Ǝg�p����z��̏����ݒ�
	ConnectCount = 0;
	checkPuyoColor = NON;
	douseFlag = false;
	fallFlag = false;
	NewPuyoFlag = false;
	for (int y = 0; y < Mapy; y++)
	{
		for (int x = 0; x < Mapx; x++)
		{
			PuyoData[y][x] = NON;
			connectPuyo[y][x] = false;
			checkPuyo[y][x] = false;
			dousePuyo[y][x] = false;
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