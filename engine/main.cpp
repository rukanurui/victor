#include <stdio.h>
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
        if (i%2==0)
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

        sprite5[i]->SetColor({ 1,1,1,1 });

        //sprites[i].isInvisible = true;

        // 頂点バッファに反映
        sprite5[i]->SpriteTransVertexBuffer();
    }

    spriteCommon->SpriteCommonLoadTexture(6, L"Resources/floar.png");



    //Sprite* sprite6 = Sprite::Create(spriteCommon, 6);

  
    //sprite6->SetPosition({ 0,0,0 });
    //sprite6->SetSize({ 90,90 });
    //sprite6->SettexSize({ 90,90 });
    //sprite6->SpriteTransVertexBuffer();

    const int BACK_NUM = 300;

    Sprite* sprite6[BACK_NUM] = { nullptr };

    // スプライトの生成
    for (int i = 0; i < BACK_NUM; i++)
    {
        
        sprite6[i] = Sprite::Create(spriteCommon, 6);
       
        // スプライトの座標変更
        sprite6[i]->SetPosition({ 0 ,0 ,0 });
        sprite6[i]->SetSize({ 90,90 });
        sprite6[i]->SettexSize({ 90,90 });

        //sprites[i].isInvisible = true;

        // 頂点バッファに反映
        sprite6[i]->SpriteTransVertexBuffer();
    }

    //
    Sprite* sprite7 = Sprite::Create(spriteCommon, 7);

    spriteCommon->SpriteCommonLoadTexture(7, L"Resources/HP_3.png");
    sprite7->SetPosition({ 200,70,0 });
    sprite7->SetSize({ 360,82 });
    sprite7->SettexSize({ 360,82 });

    sprite7->SpriteTransVertexBuffer();

    //
    Sprite* sprite8 = Sprite::Create(spriteCommon, 8);

    spriteCommon->SpriteCommonLoadTexture(8, L"Resources/HP_2.png");
    sprite8->SetPosition({ 200,70,0 });
    sprite8->SetSize({ 360,82 });
    sprite8->SettexSize({ 360,82 });

    sprite8->SpriteTransVertexBuffer();

    //
    Sprite* sprite9 = Sprite::Create(spriteCommon, 9);

    spriteCommon->SpriteCommonLoadTexture(9, L"Resources/HP_1.png");
    sprite9->SetPosition({ 200,70,0 });
    sprite9->SetSize({ 360,82 });
    sprite9->SettexSize({ 360,82 });

    sprite9->SpriteTransVertexBuffer();

    //
    Sprite* sprite10 = Sprite::Create(spriteCommon, 10);

    spriteCommon->SpriteCommonLoadTexture(10, L"Resources/HP_0.png");
    sprite10->SetPosition({ 200,70,0 });
    sprite10->SetSize({ 360,82 });
    sprite10->SettexSize({ 360,82 });

    sprite10->SpriteTransVertexBuffer();


    //敵白
    spriteCommon->SpriteCommonLoadTexture(11, L"Resources/SIRO.png");

    Sprite* sprite11[ENEMY1_NUM] = { nullptr };

    // スプライトの生成
    for (int i = 0; i < ENEMY1_NUM; i++)
    {

        sprite11[i] = Sprite::Create(spriteCommon, 11);

        // スプライトの座標変更
        sprite11[i]->SetPosition({ 0 ,0 ,0 });
        sprite11[i]->SetSize({ 60,60 });
        sprite11[i]->SettexSize({ 70,70 });

        //sprites[i].isInvisible = true;

        // 頂点バッファに反映
        sprite11[i]->SpriteTransVertexBuffer();
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
    int debug_y = 20;

    int debug2_x = 300;
    int debug2_y = 24;

    //ゲームシーン処理関連

    int GameScene = 0;
    int GameTime = 300;
    int GameTime_Count = 0;
   
    char moji[64];
    char moji2[64];

    Player* player = nullptr;
    player = new Player();
    Enemy* enemy1=nullptr;
    enemy1 = new Enemy();

    Collision*collision=nullptr;
    collision = new Collision();
    

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


        for (int i = 0; i < BACK_NUM; i++)
        {
            sprite6[i]->Update();
        }
      
        for (int i = 0; i < ENEMY1_NUM; i++)
        {
            sprite5[i]->Update();
            sprite11[i]->Update();
        }

        sprite7->Update();
        sprite8->Update();
        sprite9->Update();
        sprite10->Update();

        sprite->SetPosition({ player->Player_RedX,player->Player_RedY,0 });
        sprite2->SetPosition({ player->Player_BlueX,player->Player_BlueY,0 });
        sprite4->SetPosition({ item->LEG_.X-player->Map_X,item->LEG_.Y - player->Map_Y,0 });



        //背景　描画　座標

        //for(int i=0;i<:i++)
        for (int i = 0; i < BACK_NUM; i++)
        {         
            if(i<30)sprite6[i]->SetPosition({ (-697+(i*90)) - player->Map_X,45 - player->Map_Y,0 });
            else if(i<60)sprite6[i]->SetPosition({ (-697+((i-30)*90)) - player->Map_X,135 - player->Map_Y,0 });
            else if (i < 90)sprite6[i]->SetPosition({ (-697 + ((i-60) * 90)) - player->Map_X,225 - player->Map_Y,0 });
            else if (i < 120)sprite6[i]->SetPosition({ (-697 + ((i-90) * 90)) - player->Map_X,315 - player->Map_Y,0 });
            else if (i < 150)sprite6[i]->SetPosition({ (-697 + ((i-120) * 90)) - player->Map_X,405 - player->Map_Y,0 });
            else if (i < 180)sprite6[i]->SetPosition({ (-697 + ((i-150) * 90)) - player->Map_X,495 - player->Map_Y,0 });
            else if (i < 210)sprite6[i]->SetPosition({ (-697 + ((i - 180) * 90)) - player->Map_X,585 - player->Map_Y,0 });
            else if (i < 240)sprite6[i]->SetPosition({ (-697 + ((i - 210) * 90)) - player->Map_X,675 - player->Map_Y,0 });
            else if (i < 270)sprite6[i]->SetPosition({ (-697 + ((i - 240) * 90)) - player->Map_X,765 - player->Map_Y,0 });
            else if (i < 300)sprite6[i]->SetPosition({ (-697 + ((i - 270) * 90)) - player->Map_X,855 - player->Map_Y,0 });
        }

        sprite2->SetSize({ 50 * player->Blue_Lv,50 * player->Blue_Lv });
        sprite->SetSize({ 50 * player->Red_Lv,50 * player->Red_Lv });

        if (player->invincibleFlag == 1)
        {
            if (player->invincibleTime ==10)
            {
                sprite->SetColor({ 1, 1, 1, 0 });
                sprite2->SetColor({ 1, 1, 1, 0 });
            }
            else if (player->invincibleTime == 20)
            {
                sprite->SetColor({ 1, 1, 1, 1 });
                sprite2->SetColor({ 1, 1, 1, 1 });
            }
            else if (player->invincibleTime == 30)
            {
                sprite->SetColor({ 1, 1, 1, 0 });
                sprite2->SetColor({ 1, 1, 1, 0 });
            }
            else if (player->invincibleTime == 40)
            {
                sprite->SetColor({ 1, 1, 1, 1 });
                sprite2->SetColor({ 1, 1, 1, 1 });
            }
            else if (player->invincibleTime == 50)
            {
                sprite->SetColor({ 1, 1, 1, 0 });
                sprite2->SetColor({ 1, 1, 1, 0 });
            }
            else if (player->invincibleTime == 60)
            {
                sprite->SetColor({ 1, 1, 1, 1 });
                sprite2->SetColor({ 1, 1, 1, 1 });
            }
            else if (player->invincibleTime == 70)
            {
                sprite->SetColor({ 1, 1, 1, 0 });
                sprite2->SetColor({ 1, 1, 1, 0 });
            }
            else if (player->invincibleTime == 80)
            {
                sprite->SetColor({ 1, 1, 1, 1 });
                sprite2->SetColor({ 1, 1, 1, 1 });
            }
            else if (player->invincibleTime == 90)
            {
                sprite->SetColor({ 1, 1, 1, 0 });
                sprite2->SetColor({ 1, 1, 1, 0 });
            }
        }
        else
        {
            sprite->SetColor({ 1, 1, 1, 1 });
            sprite2->SetColor({ 1, 1, 1, 1 });
        }
        

        sprite2->SpriteTransVertexBuffer();
        sprite->SpriteTransVertexBuffer();


        player->setter(item->LEG_.Effect);
        player->setter2(item->ARM_->Effect);
        player->setter3(item->STUDY_->Effect);
        
        enemy1->Getter_X(player->Map_X);
        enemy1->Getter_Y(player->Map_Y);

        enemy1->Central_X_Get(player->Central_x);
        enemy1->Central_Y_Get(player->Central_y);


        GameTime_Count++;
        if (GameTime_Count >= 60)
        {
            GameTime_Count = 0;
            GameTime -= 1;
        }

        sprintf_s(moji, "%d", GameTime);
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
    

        if (collision->CollisionArm(player->Central_x, player->Central_y, 50, item->LEG_.X - player->Map_X, item->LEG_.Y - player->Map_Y, 50))
        {
            item->LEG_.Flag = 1;
        }
          debugtext->Print(moji, debug_x, debug_y);
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

        //背景の描画
        for (int i = 0; i < BACK_NUM; i++)
        {
            sprite6[i]->SpriteDraw();
        }

        if (item->LEG_.Flag == 0) sprite4->SpriteDraw();


        //敵の当たり判定と描画
       for (int i = 0; i < ENEMY1_NUM; i++)
        {

           //中央と敵
           if (collision->CollisionArm(player->Central_x, player->Central_y, 20, enemy1->Enemy1[i].X-player->Map_X, enemy1->Enemy1[i].Y - player->Map_Y, enemy1->Enemy1[i].R) && enemy1->Enemy1[i].Flag == 1&&player->invincibleFlag==0)
           {
               player->invincibleFlag = 1;
               player->HP -= 1;

               enemy1->Enemy1[i].Flag = 0;
               enemy1->Enemy1[i].Die = 1;

           }

           //敵と腕の処理
           if (player->invincibleFlag == 0&&enemy1->Enemy1[i].knock_back==0)
           {

               if (i%2==0)
               {
                   //自機蒼と赤
                   if (collision->CollisionArm(player->Player_BlueX, player->Player_BlueY, player->Blue_R * player->Blue_Lv, enemy1->Enemy1[i].X-player->Map_X, enemy1->Enemy1[i].Y - player->Map_Y, enemy1->Enemy1[i].R) && enemy1->Enemy1[i].Flag == 1)
                   {

                       if (player->Blue_Lv >= 2)
                       {
                           player->Blue_Lv -= 1;
                       }
                       //振動
                       player->Shake();
                   }               //自機赤と赤
                   else if (collision->CollisionArm(player->Player_RedX, player->Player_RedY, player->Red_R * player->Red_Lv, enemy1->Enemy1[i].X- player->Map_X, enemy1->Enemy1[i].Y - player->Map_Y, enemy1->Enemy1[i].R) && enemy1->Enemy1[i].Flag == 1)
                   {
                       if (enemy1->Enemy1[i].HP > 1)
                       {
                           enemy1->Enemy1[i].knock_back = 1;
                       }

                       if (player->Red_Lv < 3&&enemy1->Enemy1[i].HP==1)
                       {
                           player->Red_Lv += 1;
                       }
                       enemy1->Enemy1[i].HP -= 1;
                      // enemy1->Enemy1[i].Flag = 0;
                     //  enemy1->Enemy1[i].Die = 1;
                       
                      
                   }


               }
               else
               {
                   if (collision->CollisionArm(player->Player_RedX, player->Player_RedY, player->Red_R * player->Red_Lv, enemy1->Enemy1[i].X- player->Map_X, enemy1->Enemy1[i].Y - player->Map_Y, enemy1->Enemy1[i].R) && enemy1->Enemy1[i].Flag == 1)
                   {

                       if (player->Red_Lv >= 2)
                       {
                           player->Red_Lv -= 1;
                       }
                       //振動
                       player->Shake();
                   }         //自機蒼と蒼
                   else if (collision->CollisionArm(player->Player_BlueX, player->Player_BlueY, player->Blue_R * player->Blue_Lv, enemy1->Enemy1[i].X- player->Map_X, enemy1->Enemy1[i].Y - player->Map_Y, enemy1->Enemy1[i].R) && enemy1->Enemy1[i].Flag == 1)
                   {
                       if (enemy1->Enemy1[i].HP > 1)
                       {
                           enemy1->Enemy1[i].knock_back = 1;
                       }

                       if (player->Blue_Lv < 3 && enemy1->Enemy1[i].HP == 1)
                       {
                           player->Blue_Lv += 1;
                       }

                       enemy1->Enemy1[i].HP -= 1;
                       //enemy1->Enemy1[i].Flag = 0;
                       //enemy1->Enemy1[i].Die = 1;

                      
                   }
               }
           }

           if (enemy1->Enemy1[i].HP <= 0)
           {
               enemy1->Enemy1[i].Flag = 0;
               enemy1->Enemy1[i].Die = 1;
           }

            sprite5[i]->SetPosition({ enemy1->Enemy1[i].X - player->Map_X,enemy1->Enemy1[i].Y - player->Map_Y,0 });
            sprite11[i]->SetPosition({ enemy1->Enemy1[i].X - player->Map_X,enemy1->Enemy1[i].Y - player->Map_Y,0 });

            //通常時の描画
            if(enemy1->Enemy1[i].Flag==1&& enemy1->Enemy1[i].knock_back == 0)sprite5[i]->SpriteDraw();
            //ノックバック時の描画
            if (enemy1->Enemy1[i].knock_back == 1)sprite11[i]->SpriteDraw();
        }

        //自キャラの描画
        sprite->SpriteDraw();
        sprite2->SpriteDraw();

        //UI
        //体力の可視化
        if (player->HP == 3)
        {
            sprite7->SpriteDraw();
        }
        else  if (player->HP == 2)
        {
            sprite8->SpriteDraw();
        }
        else  if (player->HP == 1)
        {
            sprite9->SpriteDraw();
        }
        else  if (player->HP == 0)
        {
            sprite10->SpriteDraw();
        }

        debugtext->DrawAll();//的カウント
        //メイン
        if (player->invincibleFlag == 1)
        {
          
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

    for (int i = 0; i < ENEMY1_NUM; i++)
    {
        delete sprite5[i];
    }

    //テキスト解放
    delete debugtext;

    audio->Finalize();
    delete audio;

    return 0;
}
