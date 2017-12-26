﻿
#include <Windows.h>
#pragma comment(lib,"winmm.lib")

#include <tchar.h>

#include"Direct3D.h"

#include "Sprite.h"
#include "Texture.h"

#include "DirectInput.h"

#include"time.h"
#include"GameManager.h"
#include"Map.h"
#include"Puyo.h"

#define screenWidth 960
#define screenHeight 960
#define Pixel 64

//ウィンドウプロシージャ
LRESULT CALLBACK WndPrc
(
	HWND hWnd,	//ウィンドウのハンドル
	UINT msg,	//メッセージ
	WPARAM wParam,
	LPARAM lParam
)
{
	//メッセージ処理のための関数
	//DispatchMessageによって呼び出される

	//ウィンドウクラスの登録時に
	//各ウィンドウに設定される

	//アプリケーションがメッセージを
	//取得したら呼び出される

	//メッセージの例

	//WM_DESTROY ウィンドウが破棄された
	//			 ×ボタンが押された時など
	//WM_MOVE    ウィンドウが移動
	//WM_SIZE    ウィンドウサイズの変更
	//等

	//特別な処理を必要とする場合
	//または自分で独自の処理を定義したい場合
	//ここでメッセージの種類に応じた
	//処理を行う

	//取りあえず WM_DESTROYが来た時の
	//終了処理のみ定義

	switch (msg)
	{
		case WM_DESTROY:

			PostQuitMessage(0);

			//メッセージキューに
			//新しくWM_QUITメッセージを送る

			//いずれメッセージキューから
			//取り出され
			//メインループが終了する
			//(メインループの終了条件を
			//そのように作る)
			break;
	}

	//独自の処理を行ったら
	//デフォルトのウィンドウプロシージャを実行

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//ウィンドウ設定の名前
static const TCHAR* WC_BASIC = _T("Basic");

//作りたいウィンドウの設定を
//登録する関数
HRESULT RegistClassEx(HINSTANCE hInstance)
{
	//ウィンドウの設定を保存する構造体
	WNDCLASSEX wcex;
	
	//wcexの先頭アドレスから
	//WNDCLASSEXの長さ分のメモリを
	//全て0で埋める
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	//つまりはwcexが使用しているメモリ領域を
	//全て0で初期化する処理

	//ウィンドウの設定

	//構造体のサイズ
	wcex.cbSize = sizeof(WNDCLASSEX);

	//ウィンドウの設定情報に追加する捕捉を付けないので
	//0で固定
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	//Windowのスタイル
	//それぞれがビット単位のフラグであるため
	//オア演算で合成したものがスタイルの最終的な設定
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	//CS_HREDRAW 横サイズが変わったときウィンドウ全体の再描画
	//   VREDRAW 縦サイズが変わったときウィンドウ全体の再描画
	//   DBLCLKS ダブルクリックが発生したことをウィンドウに通知

	//WinMainのインスタンスハンドル
	wcex.hInstance = hInstance;

	//ウィンドウプロシージャのアドレス
	//関数ポインタの設定
	//ウィンドウプロシージャをOSが呼び出せるようにする
	wcex.lpfnWndProc = (WNDPROC)WndPrc;

	//背景色
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//メニュー　なし
	wcex.lpszMenuName = NULL;

	//ウィンドウクラスの名前　このウィンドウ設定の名前
	wcex.lpszClassName = WC_BASIC;

	//アイコン　デフォルトのを使う
	wcex.hIcon = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0, 
		0, 
		LR_DEFAULTSIZE | LR_SHARED);
	wcex.hIconSm = NULL;

	//カーソル デフォルトのものを使う
	wcex.hCursor= (HCURSOR)LoadImage(NULL,
		MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);

	//設定したウィンドウクラスを登録
	//登録したウィンドウ設定でないと
	//ウィンドウを作ることができない
	return RegisterClassEx(&wcex); 
	//HRESULT型の実行結果が戻される
}


//登録した設定を基にウィンドウを作成する
HRESULT MakeWindow
(HINSTANCE hInstance,//WinMainの識別子
	HWND &refHWnd,	//ウィンドウの識別子
				   //正しくウィンドウの作成ができたら
				   //この変数に識別子を代入する
	int width = screenWidth,	//クライアント領域の幅
	int height = screenHeight)	//クライアント領域の高さ
	//クライアント領域はウィンドウ全体から
	//外枠やメニューの部分を除いた物と今は思っておけばOK
{
	//クライアント領域のおおきさを決める
	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.right = width;
	rect.bottom = height;

	//クライアント領域を保持するのに必要な
	//ウィンドウのおおきさを計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE/*TRUE*/);
	//正しく実行されるとrectの値が更新される

	//WS_OVERLAPPEDWINDOWはウィンドウのスタイルの一つ

	//ウィンドウのハンドル
	//ウィンドウの識別に使用する
	HWND hWnd;

	hWnd = CreateWindowEx
	(	0,						//ウィンドウ拡張スタイル
		WC_BASIC,				//作りたいウィンドウクラス
								//あらかじめ登録されたもの
		_T("タイトル"),			//ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW,	//ウィンドウのスタイル
		CW_USEDEFAULT,			//位置x座標 デフォルトの値
		CW_USEDEFAULT,			//位置y座標 デフォルトの値
		rect.right - rect.left,	//ウィンドウ全体の幅
		rect.bottom - rect.top, //ウィンドウ全体の高さ
		NULL,					//親ウィンドウのハンドル
		NULL,					//メニューのハンドル
		hInstance,				//WinMainのハンドル

		NULL);					//ウィンドウ作成データ
								//ウィンドウに好きな32ビットのデータを
								//付属させることができる
								//追加情報構造体へのポインタなど
								//を付けるのが無難な使い方か
								//今回は使わない

	//ウィンドウが正しく作れたかをチェック
	//正しく作れたらhWndにNULL以外が入るはず
	if (hWnd == NULL)
	{
		return S_FALSE;//HRESULT型　失敗を表す識別子の一つ
	}

	//ウィンドウをアクティブにして表示
	//hWndでウィンドウの識別をしていることに注目
	ShowWindow(hWnd, SW_SHOWNORMAL);

	//クライアント領域の更新
	UpdateWindow(hWnd);

	//参照渡しになっている引数に
	//ウィンドウの識別ハンドルをコピーする
	//これによって今作ったウィンドウの識別ハンドルを
	//呼び出し元のプログラムで得ることができる
	refHWnd = hWnd;

	//HRESULT型　成功を表す識別子の一つ
	return S_OK;
}

//スプライトのインスタンスを作成
//パラメータは適当で


//エントリーポイント
//プログラムの開始関数

int _stdcall WinMain
(HINSTANCE hInstance,	//プログラムを識別するハンドル
	HINSTANCE hPrevInstance,//アプリケーションの前のインスタンスハンドル
							//win32だと常にNULL
	LPSTR lpCmdLine,		//コマンドライン引数
	int nCmdShow)		//ウィンドウの表示状態
{
	//変数の宣言-------------------------------------

	srand((unsigned int)time(NULL));//乱数の初期値設定

	enum GameMode { TITLE, RESET, PLAY, OVER };
	GameMode game = TITLE;

	int MaxPuyoColor = 3;

	
	GameManager gMane;
	Puyo puyoData;
	Map map;

	puyoData.SetMaxPuyoColor(MaxPuyoColor);

	if (FAILED(RegistClassEx(hInstance)))
	{
		return 0;
	}
	HWND hWnd = NULL;
	if (FAILED(MakeWindow(hInstance, hWnd)))
	{
		MessageBox(NULL,
			TEXT("ウィンドウ作成失敗"),
			TEXT("テスト-タイトル"),
			MB_OK);
		return 0;
	}

	Direct3D& d3d = Direct3D::GetInstance();

	//Direct3DDeviceの作成を試みる
	if (d3d.TryCreate(hWnd))
	{
	}

	//レンダーステートの設定  αブレンド
	d3d.SetRenderState(RENDERSTATE::RENDER_ALPHABLEND);

	Sprite sprite;
	sprite.SetAlpha(0.1);						//透明度の設定
	sprite.SetSize(Pixel, Pixel);				//画像の大きさ
	sprite.SetAngle(0);							//画像の回転

	Sprite sFullSize;
	sFullSize.SetAlpha(0.1);
	sFullSize.SetSize(screenWidth, screenHeight);
	sFullSize.SetAngle(0);
	sFullSize.SetPos(screenWidth / 2, screenHeight / 2);

	//テクスチャのインスタンスを作成
	Texture texBox;
	texBox.Load(_T("Texture/frame.png"));
	Texture texPuyo;
	texPuyo.Load(_T("Texture/ColorPuyo.png"));

	//テクスチャ　プレイ中以外
	Texture texStart;
	texStart.Load(_T("Texture/start.png"));
	Texture texOver;
	texOver.Load(_T("Texture/over.png"));



	//ここで読み込んだ画像の分割処理
	texPuyo.SetDivide(5, 1);

	DirectInput * pDi = DirectInput::GetInstance();
	pDi->Init(hWnd);

	//メインループ
	//メッセージループ

	MSG msg = {};

	//quitメッセージが出てくるまでループを繰り返す
	//quitメッセージは上記のウィンドウプロシージャから送信
	//送信の条件などはウィンドウプロシージャを確認
	while (msg.message != WM_QUIT)
	{

		//PeekMessage
		//メッセージキューの中にメッセージがあるかを調べて
		//msgの中に書き込みtrueを返す
		//メッセージがなければfalseを返す
		//PM_REMOVEを設定しているとメッセージの書き込みのあとに
		//メッセージキューから元のメッセージを消す

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//仮想キーメッセージを文字メッセージに変換し
			//それをメッセージキューにポストする
			TranslateMessage(&msg);

			//メッセージの割り当て
			//ウィンドウプロシージャでメッセージを処理
			DispatchMessage(&msg);
		}
		else
		{
			//メッセージキューにメッセージが無かったとき
			//こちらの処理
			//ここにゲーム処理を書き込んでいく

			pDi->Update();//キー状態の更新

			if (pDi->MouseButtonJustPressed(MOUSE_BUTTON_LEFT))
				Vector2<int> vec = pDi->MousePosition();
			{
				int breakpoint = 0;
			}

			//sprite.SetAngle(sprite.GetAngle_Rad()+0.0f);//回転ここのfを大きい値にするほど回転速度が上がる

			static int dir = 1;//α
			sprite.SetAlpha(sprite.GetAlpha() + (dir*0.01));
			switch (dir)
			{
				case 1:
					if (sprite.GetAlpha() >= 1)
					{
						dir = -1;
					}
					break;
				case -1:
					if (sprite.GetAlpha() <= 0)
					{
						dir = 1;
					}
					break;
			}

			switch (game)
			{
				case TITLE:
					//エンター押したときPLAYへ
					if (pDi->KeyJustPressed(DIK_RETURN))
					{

						game = RESET;
					}
					break;
				case RESET:
					map.Release();
					puyoData.Release();
					gMane.Release();

					game = PLAY;
					break;
				case PLAY:
					gMane.MovePuyo(&puyoData, &map, &gMane);
					if (gMane.GetContactPuyoLeft() != true || gMane.GetContactPuyoRight() != true)
					{
						//ぷよの左右移動
						if (pDi->KeyJustPressed(DIK_LEFT))//左移動
						{
							puyoData.SideMovePuyo(-1,&map);
						}
						else if (pDi->KeyJustPressed(DIK_RIGHT))//右移動
						{
							puyoData.SideMovePuyo(1,&map);
						}
						else if (pDi->KeyJustPressed(DIK_A))//左回転
						{
							puyoData.RotaPuyo(-1,&map,&gMane);
						}
						else if (pDi->KeyJustPressed(DIK_S))//右回転
						{
							puyoData.RotaPuyo(1,&map, &gMane);
						}
						else if (pDi->KeyJustPressed(DIK_RETURN))
						{
							gMane.SetEnter(true);
						}
					}
					
					//trueを返したときゲームオーバーへ移動
					//これはぷよが上まで募ってしまったことを示す
					if (map.GetOverFlag())
					{
						game = OVER;
					}

					break;
				case OVER:

					//リプレイする
					if (pDi->KeyJustPressed(DIK_RETURN))
					{
						game = RESET;
					}

					break;
			}


			//まず描画 
			d3d.BeginScene();//描画開始
			//描画
			d3d.ClearScreen();

			switch (game)
			{
				case TITLE:
					sFullSize.Draw(texStart);
					break;
				case OVER:
					sFullSize.Draw(texOver);
					break;
				default:
					//スタートとゲームオーバー時以外の描画
					for (int y = 0; y < map.GetMapy(); y++)
					{
						for (int x = 0; x < map.GetMapx(); x++)
						{
							sprite.SetPos(Pixel * 2+ ( x * Pixel), Pixel / 2 + (y * Pixel));
							//枠の描画
							sprite.Draw(texBox);
							//ぷよが存在するなら描画
							if (map.GetPuyoData(x, y) != map.NON)
							{
								//存在していたのでその場所の色データを識別
								switch (map.GetPuyoData(x,y))
								{
									case map.RED:
										texPuyo.SetNum(0, 0);
										break;
									case map.GREEN:
										texPuyo.SetNum(1, 0);
										break;
									case map.BLUE:
										texPuyo.SetNum(2, 0);
										break;
									case map.YELLOW:
										texPuyo.SetNum(3, 0);
										break;
									case map.PURPLE:
										texPuyo.SetNum(4, 0);
										break;
								}
								//ぷよの描画
								sprite.Draw(texPuyo);
							}
						}
					}
					//現在動かしているぷよの描画
					/*if (gMane.GetContactPuyoLeft() != true && gMane.GetContactPuyoRight() != true)
					{*/
						//左
						Puyo::PuyoColor pData = puyoData.GetPuyoInfo(1);
						sprite.SetPos(Pixel + (pData.PuyoLeftx + 1) * Pixel, Pixel / 2 + pData.PuyoLefty * Pixel);
						texPuyo.SetNum(pData.PuyoLeftColor, 0);
						sprite.Draw(texPuyo);

						//右
						sprite.SetPos(Pixel + (pData.PuyoRightx + 1) * Pixel, Pixel / 2 + pData.PuyoRighty * Pixel);
						texPuyo.SetNum(pData.PuyoRightColor, 0);
						sprite.Draw(texPuyo);
					//}
					break;
			}
			//描画終了の合図//--------------------------------------------------------------------------------------------
			
			d3d.EndScene();

			//バックバッファをフロントへ反映
			d3d.Present();
		}
	}
	map.Release();

	return 0;
}
