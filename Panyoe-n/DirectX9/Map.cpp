#include"Map.h"
#include"Puyo.h"

Map::Map() 
{


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
	}
}

void Map::ConnectPuyo(Puyo* puyo)
{
	for (int y = 0; y < GetMapy(); y++)
	{
		for (int x = 0; x < GetMapx(); x++)
		{
			//�Ȃ����Ă��邩�ǂ������ׂ邽�ߊm�F
			connectPuyo[y][x] = false;
		}
	}
	for (int y = 0; y < GetMapy(); y++)
	{
		for (int x = 0; x < GetMapx(); x++)
		{
			//�Ȃ�������łɌ������Ă��镨�͊O��
			if (GetPuyoData(x, y) != NON && connectPuyo[y][x] != true)
			{
				for (int i = 0; i < 2; i++)
				{
					//�����猩�邪�[�łȂ����Ɗm�F
					if (GetPuyoData(x, y) == GetPuyoData(x + AroundData[0], y) &&
						x + AroundData[0] > 0)
					{
						connectPuyo[y][x + AroundData[0]] = true;
					}
				}
			}
		}
	}
}

void Map::Release()
{
	for (int y = 0; y < Mapy; y++)
	{
		for (int x = 0; x < Mapx; x++)
		{
			PuyoData[y][x] = NON;
			connectPuyo[y][x] = false;
		}
	}
}