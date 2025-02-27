﻿#include "Audio.h"
#include "DirectXCommon.h"
#include "GameScene.h"
#include "TextureManager.h"
#include "WinApp.h"
//#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include "Player.h"
#include "Boss.h"
#include "FPS.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText* debugText = nullptr;
	/*AxisIndicator* axisIndicator = nullptr;*/
	PrimitiveDrawer* primitiveDrawer = nullptr;
	GameScene* gameScene = nullptr;
	FPS* fps = new FPS;

	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow("TD2");

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// デバッグテキスト初期化
	debugText = DebugText::GetInstance();
	debugText->Initialize();

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	/*axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();*/

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();
#pragma endregion

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize();

	//FPS変えたいとき
	fps->SetFrameRate(60);


	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		fps->FpsControlBegin();

		//--------------------更新処理---------------------//

		// 入力関連の毎フレーム処理
		input->Update();
		// ゲームシーンの毎フレーム処理
		gameScene->Update();
		// 軸表示の更新
		/*axisIndicator->Update();*/

		//----------------------------------------------//

		//--------------------描画処理---------------------//

		// 描画開始
		dxCommon->PreDraw();
		// ゲームシーンの描画
		gameScene->Draw();
		// 軸表示の描画
		/*axisIndicator->Draw();*/
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// 描画終了
		dxCommon->PostDraw();

		//----------------------------------------------//
		fps->FpsControlEnd();
	}

	// 各種解放
	SafeDelete(gameScene);
	audio->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	delete fps;

	return 0;
}