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
	//色の数だけループ
	for (int Puyo = 0; Puyo < puyo->GetMaxPuyoColor(); Puyo++)
	{
		douseData.clear();
		groupCount = 0;
		//繋がりが４つ以上なら殺
		{
			std::vector<ConnectNum>::iterator it = ConnectData[Puyo].begin();
			while (it != ConnectData[Puyo].end())
			{
				groupCount++;
				if (it->Connect > 3)
				{
					//消すべきなぷよを別配列に格納
					douseData.push_back(groupCount);
					//ベクタのデータを消す
					it = ConnectData[Puyo].erase(it);
				}
				else
				{
					it++;
				}
			}
		}
		groupCount = 0;
		//消せるぷよを消去
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
						//繋がっているので消す
						//既に調べれている分だけ消去
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
				//下に何もないことを調べる
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
	//ベクタ初期化　再度内部データをチェックする
	for (int i = 0; i < puyo->GetMaxPuyoColor(); i++)
	{
		ConnectData[i].clear();
	}

	for (int y = 0; y < GetMapy(); y++)
	{
		for (int x = 0; x < GetMapx(); x++)
		{
			//ここでラスタスキャンのための初期化
			RasutaData[y][x] = 0;
		}
	}

	//再度関係性をリセット 色の数だけ関連を調べる
	//１足しているのは最初の数値が１のため
	for (int Color = RED; Color < puyo->GetMaxPuyoColor(); Color++)
	{
		groupCount = 0;
		//調べる場所から４方向をみて調べる
		//ラスタスキャンというらしい？流れは調べて,,
		for (int y = 0; y < GetMapy(); y++)
		{
			for (int x = 0; x < GetMapx(); x++)
			{
				miniNum = 0;
				SufferLabel = false;
				if (PuyoData[y][x] == Color)//------------------------------------------------
				{
					//範囲外を弾く
					if (y - 1 >= 0)
					{
						if (x - 1 >= 0)
						{
							//左上
							if (RasutaData[y - 1][x - 1] != 0 &&
								PuyoData[y - 1][x - 1] == Color)
							{
								miniNum = RasutaData[y - 1][x - 1];
							}
						}
						//上
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
							//右上
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
						//左
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
						//調べた結果新たなグループ作成の必要があった
						groupCount++;
						RasutaData[y][x] = groupCount;
					}
					else if (SufferLabel)
					{
						//複数のラベルを確認した要素として最小の番号を格納
						RasutaData[y][x] = 1;
					}
					else
					{
						//グループを確認出来たので格納
						RasutaData[y][x] = miniNum;
					}
				}//----------------------------------------------------------------------------
			}
		}
		//次にルックアップテーブルを使用（独自）
		//変な群を正規の群に補正
		for (int y = 0; y < GetMapy(); y++)
		{
			for (int x = GetMapx() - 1; x >= 0; x--)
			{
				//０以外の時は何か任意の色があるとき
				if (PuyoData[y][x] == Color)
				{
					if (x - 1 >= 0)
					{
						if (PuyoData[y][x - 1] == Color)
						{
							//左のあたいを現在の指定している座標の値に上書き
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
							//下のあたいを現在の指定している座標の値に上書き
							if (RasutaData[y][x] != RasutaData[y + 1][x])
							{
								RasutaData[y + 1][x] = RasutaData[y][x];
							}
						}
					}
				}
			}
		}

		//グループごとにつながりの数を渡していく
		for (int Num = 1; Num <= groupCount; Num++)
		{
			ConnectCheck.Connect = 0;
			//つながりを調べている
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
			//0以外の時入る
			if (ConnectCheck.Connect != 0)
			{
				//ベクタの後ろに格納
				ConnectData[Color].push_back(ConnectCheck);

				//つながりが４つ以上あればぷよを削除
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
	//つながっているかの判定の初期化用配列と使用する配列の初期設定
	checkPuyoColor = NON;
	douseFlag = false;
	fallFlag = false;
	NewPuyoFlag = false;
	SufferLabel = false;

	ColorNum = 0;

	douseData.clear();

	//配列を初期化
	for (int i = 0; i < 5; i++)
	{
		ConnectData[i].clear();
	}
	//ラスタデータを初期化
	for (int y = 0; y < Mapy; y++)
	{
		for (int x = 0; x < Mapx; x++)
		{
			RasutaData[y][x] = 0;
			PuyoData[y][x] = NON;
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