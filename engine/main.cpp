﻿#include <stdio.h>
#include <stdlib.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <vector>
#include <string>
#include <DirectXMath.h>
#include <cstdlib>      // srand,rand
#include <time.h>
using namespace DirectX;

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#include<DirectXTex.h>
#include <wrl.h>

using namespace Microsoft::WRL;

#include<d3dx12.h>

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"

#include "3d/Object3d.h"
#include"Model.h"


#include "Collision.h"
#include "CollisionPrimitive.h"


#include<xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#include<fstream>

#include "WinApp.h"
#include "Audio.h"
#include"SpriteCommon.h"
#include "Sprite.h"
#include "DebugText.h"

#include "Player.h"
#include "Enemy.h"
#include "Item.h"

Sphere sphere;

Plane plane;

Triangle triangle;

Ray ray;

//
DirectXCommon* dxCommon = nullptr;
SpriteCommon* spriteCommon = new SpriteCommon();

//ComPtr<ID3D12Device> dev;

LRESULT CALLBACK WindowProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


#ifdef _DEBUG
#   define MyOutputDebugString( str, ... ) \
      { \
        TCHAR c[256]; \
        _stprintf( c, str, __VA_ARGS__ ); \
        OutputDebugString( c ); \
      }
#else
#    define MyOutputDebugString( str, ... ) // 空実装
#endif

//# Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    //ポインタ置き場
    Input* input = nullptr;
    WinApp* winApp = nullptr;
    Audio* audio = nullptr;

    //WindowsAPIの初期化
    winApp = new WinApp();
    winApp->Initialize();

    // DirectX初期化処理　ここから

    ComPtr<IXAudio2> xAudio2;
    IXAudio2MasteringVoice* masterVoice;

    //DirectXの初期化
    dxCommon = new DirectXCommon();
    dxCommon->Initialize(winApp);
    HRESULT result;

    //入力の初期化
    input = new Input();
    input->Intialize(winApp);

    //3D初期化
    Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);
    //読み込み

    //生成

    //ひもづけ

    //位置指定

    result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);

    //マスターボイスを作成 
    result = xAudio2->CreateMasteringVoice(&masterVoice);

    //スプライト初期化

    spriteCommon->Initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->window_width, winApp->window_height);

    //スプライト
    Sprite* sprite = Sprite::Create(spriteCommon, 0);

    spriteCommon->SpriteCommonLoadTexture(0, L"Resources/Red.png");
    //sprite->SetPosition({ Central_x,Central_y,0 });
    sprite->SetSize({ 70,70 });
    sprite->SettexSize({ 70,70 });

    sprite->SpriteTransVertexBuffer();

    //
    Sprite* sprite2 = Sprite::Create(spriteCommon, 1);

    spriteCommon->SpriteCommonLoadTexture(1, L"Resources/Blue.png");
    sprite2->SetPosition({ 0,360,0 });
    sprite2->SetSize({ 70,70 });
    sprite2->SettexSize({ 70,70 });

    sprite2->SpriteTransVertexBuffer();

    //
    Sprite* sprite3 = Sprite::Create(spriteCommon, 3);

    spriteCommon->SpriteCommonLoadTexture(3, L"Resources/Enemy1.png");
    sprite3->SetPosition({ 0,360,0 });
    sprite3->SetSize({ 60,60 });
    sprite3->SettexSize({ 60,60 });
    //
    Sprite* sprite4 = Sprite::Create(spriteCommon, 4);

    spriteCommon->SpriteCommonLoadTexture(4, L"Resources/LEG.png");
    sprite4->SetPosition({ 0,360,0 });
    sprite4->SetSize({ 60,60 });
    sprite4->SettexSize({ 60,60 });


    const int ENEMY1_NUM = 100;

    Sprite* sprite5[ENEMY1_NUM] = { nullptr };
   
    // スプライトの生成
    for (int i = 0; i < ENEMY1_NUM; i++)
    {
        //ほんとは５０で区切る（デモは５区切り）
        if (i < 5)
        {
            sprite5[i] = Sprite::Create(spriteCommon, 0);
        }
        else
        {
            sprite5[i] = Sprite::Create(spriteCommon, 1);
        }
        // スプライトの座標変更
        sprite5[i]->SetPosition({ 30 ,100 ,0 });
        sprite5[i]->SetSize({ 60,60 });
        sprite5[i]->SettexSize({ 70,70 });

        //sprites[i].isInvisible = true;

        // 頂点バッファに反映
        sprite5[i]->SpriteTransVertexBuffer();
    }



    //デバックテキスト
    DebugText* debugtext = nullptr;
    debugtext = new DebugText();


    const int debugTextTexNumber = 2;

    spriteCommon->SpriteCommonLoadTexture(debugTextTexNumber, L"Resources/ASC_white1280.png");
    //SpriteCommonLoadTexture(spriteCommon, debugTextTexNumber, L"Resources/ASC_white1280.png", dxCommon->GetDev());

    debugtext->debugTextInit(spriteCommon, debugTextTexNumber);

    //   DebugText debugtext2;

    //   const int debugTextTexNumber2 = 3;

    //   SpriteCommonLoadTexture(spriteCommon, debugTextTexNumber2, L"Resources/ASC_white1280.png", dxCommon->GetDev());

    //   debugtext2.debugTextInit(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height, debugTextTexNumber2, spriteCommon);

       // DirectX初期化処理　ここまで

       //3D初期値設定

       //的のフラグ
    int TargetFlag = 1;

    //オーディオ初期化
    audio = new Audio();
    audio->Initialize();

    audio->SoundLoadWave("Resources/Shot.wav");//正解の音
    audio->SoundLoadWave("Resources/Push.wav");

    //パイプライン生成

    BYTE key[256] = {};
    BYTE olds[256] = {};

    int debug_x = 600;
    int debug_y = 80;

    int debug2_x = 300;
    int debug2_y = 24;

    //ゲームシーン処理関連

    int GameScene = 0;
   
    char moji[64];
    char moji2[64];

    Player* player = nullptr;
    player = new Player();
    Enemy* enemy1;
    enemy1 = new Enemy();
    Collision collision;

    Item* item = nullptr;
    item = new Item();


    enemy1->Intialize();
    item->Intialize();
    player->Initialize();

    while (true)  // ゲームループ
    {

        //3d更新

        //スプライト
        sprite->Update();
        sprite2->Update();
        sprite3->Update();
        sprite4->Update();
        for (int i = 0; i < ENEMY1_NUM; i++)
        {
            sprite5[i]->Update();
        }

        sprite->SetPosition({ player->Player_RedX,player->Player_RedY,0 });
        sprite2->SetPosition({ player->Player_BlueX,player->Player_BlueY,0 });
        sprite4->SetPosition({ item->LEG_.X-player->Map_X,item->LEG_.Y - player->Map_Y,0 });

        sprite2->SetSize({ 50 * player->Blue_Lv,50 * player->Blue_Lv });
        sprite->SetSize({ 50 * player->Red_Lv,50 * player->Red_Lv });

        sprite2->SpriteTransVertexBuffer();
        sprite->SpriteTransVertexBuffer();


        player->setter(item->LEG_.Effect);
        player->setter2(item->ARM_->Effect);
        player->setter3(item->STUDY_->Effect);

        //sprintf_s(moji, "%d", Target_Hit);
        //sprintf_s(moji2, "%d", TimeRimit);

        if (winApp->ProcessMessage())
        {
            //ゲームループを抜ける
            break;
        }

        // DirectX毎フレーム処理　ここから

        input->Update();

        //初期化処理

        //ゲーム内の動作  

        //更新
     
        player->Controll();//ゲームパッドによるPlayerの操作
        item->Update();
        enemy1->Update();
    
    

        if (collision.CollisionArm(player->Central_x, player->Central_y, 50, item->LEG_.X, item->LEG_.Y, 50))
        {
            item->LEG_.Flag = 1;
        }
        //  debugtext->Print(moji, debug_x, debug_y);
         // debugtext2.Print(spriteCommon, moji2, debug2_x, debug2_y,1.0f);

          // バックバッファの番号を取得（2つなので0番か1番）
        dxCommon->PreDraw();

        //3D描画前処理
        Object3d::PreDraw(dxCommon->GetCmdList());

        //3D描画
        //ここに処理追加できる

        //3D描画後処理
        Object3d::PostDraw();

        ////スプライト共通コマンド
        spriteCommon->PreDraw();

        //スプライト表示

        //アイテム
        if (item->LEG_.Flag == 0) sprite4->SpriteDraw();


        //敵
       for (int i = 0; i < ENEMY1_NUM; i++)
        {
           //
           if (i < 5)
           {
               //自機蒼と赤
               if (collision.CollisionArm(player->Player_BlueX, player->Player_BlueY, player->Blue_R * player->Blue_Lv, enemy1->Enemy1[i].X, enemy1->Enemy1[i].Y, enemy1->Enemy1[i].R) && enemy1->Enemy1[i].Flag == 1)
               {
                  // enemy1->Enemy1[i].Flag = 0;
                 //  enemy1->Enemy1[i].Die = 1;

                   if (player->Blue_Lv >= 2)
                   {
                       player->Blue_Lv -= 1;
                   }
               }               //自機赤と赤
               else if (collision.CollisionArm(player->Player_RedX, player->Player_RedY, player->Red_R * player->Red_Lv, enemy1->Enemy1[i].X, enemy1->Enemy1[i].Y, enemy1->Enemy1[i].R) && enemy1->Enemy1[i].Flag == 1)
               {
                   enemy1->Enemy1[i].Flag = 0;
                   enemy1->Enemy1[i].Die = 1;

                   if (player->Red_Lv <3)
                   {
                       player->Red_Lv += 1;
                   }
               }


           }
           else
           {
               if (collision.CollisionArm(player->Player_RedX, player->Player_RedY, player->Red_R * player->Red_Lv, enemy1->Enemy1[i].X, enemy1->Enemy1[i].Y, enemy1->Enemy1[i].R) && enemy1->Enemy1[i].Flag == 1)
               {
                   //enemy1->Enemy1[i].Flag = 0;
                  // enemy1->Enemy1[i].Die = 1;


                   if (player->Red_Lv >=2)
                   {
                       player->Red_Lv -= 1;
                   }
               }         //自機蒼と蒼
               else if (collision.CollisionArm(player->Player_BlueX, player->Player_BlueY, player->Blue_R * player->Blue_Lv, enemy1->Enemy1[i].X, enemy1->Enemy1[i].Y, enemy1->Enemy1[i].R) && enemy1->Enemy1[i].Flag == 1)
               {
                   enemy1->Enemy1[i].Flag = 0;
                   enemy1->Enemy1[i].Die = 1;

                   if (player->Blue_Lv <3)
                   {
                       player->Blue_Lv += 1;
                   }
               }
           }


            sprite5[i]->SetPosition({ enemy1->Enemy1[i].X - player->Map_X,enemy1->Enemy1[i].Y - player->Map_Y,0 });

            if(enemy1->Enemy1[i].Flag==1)sprite5[i]->SpriteDraw();
        }

        //自キャラ
        sprite->SpriteDraw();
        sprite2->SpriteDraw();

        //メイン
        if (GameScene == 1)
        {
            debugtext->DrawAll();//的カウント
            // debugtext2.DrawAll(dxCommon->GetCmdList(), spriteCommon, dxCommon->GetDev());//時間カウント
        }
        // ４．描画コマンドここまで

        // DirectX毎フレーム処理　ここまで
        dxCommon->PostDraw();
    }
    //3D解放

    //入力開放
    delete input;

    //DirectX解放
    delete dxCommon;


    winApp->Finalize();

    //WindowsAPI解放
    delete winApp;
    winApp = nullptr;

    //3Dモデル解放

     //スプライト
    delete spriteCommon;

    delete sprite;

    for (int i = 0; i < 100; i++)
    {
        delete sprite5[i];
    }

    //テキスト解放
    delete debugtext;

    audio->Finalize();
    delete audio;

    return 0;
}
