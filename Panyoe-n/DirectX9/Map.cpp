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
//つながっているかどうか確認する処理の部分
void Map::CheckConnectPuyo(Puyo* puyo)
{
	//四方向を見てつながりの数を見る
	Puyo::PuyoColor pData =
		puyo->GetPuyoInfo(1);

	//上以外のつながりを確認
	//操作しているぷよから見て左のぷよのつながりを見る
	
	for (int cheak = 0; cheak < 2; cheak++)
	{
		ConnectCount = 1;
		//色を調べる
		//最初左
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

		//左右
		for (int x = -1; x < 2; x += 2)
		{
			if (PuyocheakX + x >= 0 && PuyocheakX + x < GetMapx() &&
				RasutaData[PuyocheakY][PuyocheakX + x] != 0)//範囲外を排除
			{
				if (PuyoData[PuyocheakY][PuyocheakX + x] == ColorNum)
				{
					ConnectCount = ConnectCount +
						ConnectData[ColorNum][RasutaData[PuyocheakY][PuyocheakX + x] - 1].Connect;
				}
			}
		}
		//下
		if (PuyocheakY + 1 < GetMapy())//範囲外を排除
		{
			//左右と同じ組だとはじく
			if (PuyoData[PuyocheakY + 1][PuyocheakX] == ColorNum && ConnectCount < 4 &&
				RasutaData[PuyocheakY + 1][PuyocheakX] != 0)
			{
				ConnectCount = ConnectCount +
					ConnectData[ColorNum][RasutaData[PuyocheakY + 1][PuyocheakX] - 1].Connect;
			}
		}
		//上は二回目しか入る必要がなく縦に積んでいるときにしか調べる必要がない
		if (PuyocheakY - 1 >= 0 && cheak == 1 && PuyocheakY - 1 == pData.PuyoLefty &&
			RasutaData[PuyocheakY - 1][PuyocheakX] != 0)//範囲外を排除
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
			//左右と同じ組だとはじく
			if (PuyoData[PuyocheakY - 1][PuyocheakX] == ColorNum && Connectflag)
			{
				ConnectCount = ConnectCount +
					ConnectData[ColorNum][RasutaData[PuyocheakY - 1][PuyocheakX] - 1].Connect;
			}
		}
		//4つ以上くっついていることが確認できました
		if (ConnectCount > 3)
		{
			douseFlag = true;
		}
		//1つ以上の繋がりを確認しました
		else if (ConnectCount > 1)
		{
			cheakflag = true;
			//Connectflag = false;
			////左
			//if (PuyocheakX - 1 >= 0)
			//{
			//	if (PuyoData[PuyocheakY][PuyocheakX - 1] == ColorNum)
			//	{
			//		RasutaData[PuyocheakY][PuyocheakX] = RasutaData[PuyocheakY][PuyocheakX - 1];
			//		ConnectData[ColorNum][RasutaData[PuyocheakY][PuyocheakX] - 1].Connect++;
			//		Connectflag = true;
			//	}
			//}
			////右
			//if (PuyocheakX + 1 < GetMapx())
			//{
			//	if (PuyoData[PuyocheakY][PuyocheakX + 1] == ColorNum && !Connectflag)
			//	{
			//		RasutaData[PuyocheakY][PuyocheakX] = RasutaData[PuyocheakY][PuyocheakX + 1];
			//		ConnectData[ColorNum][RasutaData[PuyocheakY][PuyocheakX] - 1].Connect++;
			//		Connectflag = true;
			//	}
			//	//繋がりは３つ以下なのでここに入ったということは一つと二回つながったということ
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
			////下
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
			////上
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
	//色の数だけループ
	for (int Puyo = 0; Puyo < puyo->GetMaxPuyoColor(); Puyo++)
	{
		douseData.clear();
		groupCount = 0;
		//繋がりが４つ以上なら殺
		for (std::vector<ConnectNum>::iterator it = ConnectData[Puyo].begin();
			it != ConnectData[Puyo].end(); it++)
		{
			groupCount++;
			if (it->Connect > 3)
			{
				//消すべきなぷよを別配列に格納
				douseData.push_back(groupCount);
				//ベクタのデータを消す
				it=ConnectData[Puyo].erase(it);
				if (it == ConnectData[Puyo].end())
				{
					break;
				}
				else
				{
					it--;
				}
				
				//消すフラグ成立
				if(!douseFlag)
				douseFlag = true;
			}
		}
		if (douseFlag)
		{
			//消せるぷよを消去
			for (std::list<int>::iterator it = douseData.begin();
				it != douseData.end(); it++)
			{
				for (int y = 0; y < GetMapy(); y++)
				{
					for (int x = 0; x < GetMapx(); x++)
					{
						if (PuyoData[y][x] == Puyo && RasutaData[y][x] == *it)
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
				//下に何もないことを調べる
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
				if (RasutaData[y][x] != 0)
				{
					if (PuyoData[y][x - 1] == Color)
					{
						if (x - 1 >= 0)
						{
							//左のあたいを現在の指定している座標の値に上書き
							if (RasutaData[y][x] != RasutaData[y][x - 1] &&
								PuyoData[y][x - 1] == Color)
							{
								RasutaData[y][x - 1] = RasutaData[y][x];
							}
						}
						if (y + 1 < GetMapy())
						{
							//下のあたいを現在の指定している座標の値に上書き
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
			//ベクタの後ろに格納
			ConnectData[Color].push_back(ConnectCheck);
		}
	}
}

void Map::Release()
{
	//つながっているかの判定の初期化用配列と使用する配列の初期設定
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