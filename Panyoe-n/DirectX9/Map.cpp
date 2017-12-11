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
	//つながっているかどうか調べるため初期化
	for (int y = 0; y < GetMapy(); y++)
	{
		for (int x = 0; x < GetMapx(); x++)
		{
			connectPuyo[y][x] = false;
			checkPuyo[y][x] = false;
			dousePuyo[y][x] = false;
		}
	}
	//つながっているかどうかを判断//y軸基準に
	for (int x = 0; x < GetMapx(); x++)
	{
		for (int y = 0; y < GetMapy(); y++)
		{
			//その場所にぷよがあることを示す
			//既につながりが確認されている場所ははじく
			if (PuyoData[y][x] != NON && checkPuyo[y][x] != true)
			{
				//調べる色とつながりを示すtrueを格納
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
						//一つ以上のつながりが確認できるので消す
						if (ConnectCount > 3)
						{
							dousePuyo[y][x] = true;
							douseFlag = true;
						}
					}
					//次の施行に使うため初期化
					connectPuyo[y][x] = false;
				}
			}
			ConnectCount = 0;
		}
	}
}

void Map::CheckConnectPuyo(int x, int y)
{
	//縦軸に見る
	for (int Cx = x; Cx < GetMapx(); Cx++)
	{
		for (int Cy = 0; Cy < GetMapy(); Cy++)
		{
			//既に調べてあるぷよは弾く
			if (checkPuyo[Cy][Cx] != true && connectPuyo[Cy][Cx] != true)
			{
				//色が同じである
				if (PuyoData[Cy][Cx] == checkPuyoColor)
				{
					//十字判定用のループ（配列使えや馬 + 鹿）
					for (int C = -1; C < 2; C += 2)
					{
						//現在調べている位置が現在つながりを調べている場所と
						//つながっているかどうか判断
						//配列的に配列外を示さないように弾いている
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
					//つながっていることを確認したのでそこから十字に確認
					if (connectPuyo[Cy][Cx])
					{
						ConnectCount++;
						for (int C = -1; C < 2; C += 2)
						{
							//調べて同じ色の場合trueに
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
	//逆から見る
	for (int Cx = GetMapx(); Cx > x; Cx--)
	{
		for (int Cy = GetMapy(); Cy < y; Cy--)
		{
			//既に調べてあるぷよは弾く
			if (checkPuyo[Cy][Cx] != true && connectPuyo[Cy][Cx] != true)
			{
				//色が同じである
				if (PuyoData[Cy][Cx] == checkPuyoColor)
				{
					//十字判定用のループ（配列使えや馬 + 鹿）
					for (int C = -1; C < 2; C += 2)
					{
						/*現在調べている位置が現在つながりを調べている場所と
						つながっているかどうか判断
						配列的に配列外を示さないように弾いている*/
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
					//つながっていることを確認したのでそこから十字に確認
					if (connectPuyo[Cy][Cx])
					{
						ConnectCount++;
						for (int C = -1; C < 2; C += 2)
						{
							//調べて同じ色の場合trueに
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
					//下の者が消えちゃったので下に移動
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
	//つながっているかの判定の初期化用配列と使用する配列の初期設定
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


/*//上みてー下みてー左見てと
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