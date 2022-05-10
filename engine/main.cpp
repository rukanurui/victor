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
#include "particle.h"
#include "Boss.h"



#include "PostEffect.h"

Sphere sphere;

Plane plane;

Triangle triangle;

Ray ray;

//
DirectXCommon* dxCommon = nullptr;
SpriteCommon* spriteCommon = new SpriteCommon();
SpriteCommon* spriteCommon2= new SpriteCommon();


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
    PostEffect* postEffect = nullptr;

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

    //ポストエフェクト用
    //Sprite*sprite=Sprite::Create(100, "Resources/Red.png");
    Sprite* sprite100 = Sprite::Create(spriteCommon, 100);
    spriteCommon->SpriteCommonLoadTexture(100, L"Resources/Red.png");

    //ポストエフェクト初期化
    postEffect = new PostEffect();
   // postEffect->Initialize();

    //スプライト
    Sprite* sprite = Sprite::Create(spriteCommon, 0);

    spriteCommon->SpriteCommonLoadTexture(0, L"Resources/Kobusi_aka.png");
    //sprite->SetPosition({ Central_x,Central_y,0 });
    sprite->SetSize({ 70,70 });
    sprite->SettexSize({ 104,114 });

    sprite->SpriteTransVertexBuffer();

    //
    Sprite* sprite2 = Sprite::Create(spriteCommon, 1);

    spriteCommon->SpriteCommonLoadTexture(1, L"Resources/Kobusi_ao.png");
    sprite2->SetPosition({ 0,360,0 });
    sprite2->SetSize({ 70,70 });
    sprite2->SettexSize({ 104,114 });

    sprite2->SpriteTransVertexBuffer();

    //
    Sprite* sprite3 = Sprite::Create(spriteCommon, 3);

    spriteCommon->SpriteCommonLoadTexture(3, L"Resources/Enemy1.png");
    sprite3->SetPosition({ 0,360,0 });
    sprite3->SetSize({ 60,60 });
    sprite3->SettexSize({ 60,60 });
    //
    Sprite* sprite4 = Sprite::Create(spriteCommon, 4);

    spriteCommon->SpriteCommonLoadTexture(4, L"Resources/barri.png");
    sprite4->SetPosition({ 0,360,0 });
    sprite4->SetSize({ 60,60 });
    sprite4->SettexSize({ 60,60 });

    sprite4->SpriteTransVertexBuffer();

    const int ENEMY1_NUM = 300;

    Sprite* sprite5[ENEMY1_NUM] = { nullptr };
   
    // スプライトの生成
    spriteCommon->SpriteCommonLoadTexture(104, L"Resources/zako_aka.png");
    spriteCommon->SpriteCommonLoadTexture(105, L"Resources/zako_ao.png");
    for (int i = 0; i < ENEMY1_NUM; i++)
    {
        //ほんとは５０で区切る（デモは５区切り）
        if (i%2==0)
        {
            sprite5[i] = Sprite::Create(spriteCommon, 104);
        }
        else
        {
            sprite5[i] = Sprite::Create(spriteCommon, 105);
        }
        // スプライトの座標変更
        sprite5[i]->SetPosition({ 30 ,100 ,0 });
        sprite5[i]->SetSize({ 30,30 });
        sprite5[i]->SettexSize({ 90,90 });

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

    const int BACK_NUM = 720;

    Sprite* sprite6[BACK_NUM] = { nullptr };

    // スプライトの生成
    for (int i = 0; i < BACK_NUM; i++)
    {
        
        sprite6[i] = Sprite::Create(spriteCommon, 6);
       
        // スプライトの座標変更
        sprite6[i]->SetPosition({ 0 ,0 ,0 });
        sprite6[i]->SetSize({ 90,90 });
        sprite6[i]->SettexSize({ 90,90 });
        sprite6[i]->SetRotation({ 0,0,0 });

        //sprites[i].isInvisible = true;

        // 頂点バッファに反映
        sprite6[i]->SpriteTransVertexBuffer();
    }

    //Hp  UI変数
    float Hp_X = 0;
    float Hp_Y = 0;

    float Hp_Size_X = 72;
    float Hp_Size_Y = 16.4;
    //
    Sprite* sprite7 = Sprite::Create(spriteCommon, 7);

    spriteCommon->SpriteCommonLoadTexture(7, L"Resources/HP_3.png");
    sprite7->SetPosition({ 200,70,0 });
    sprite7->SetSize({ Hp_Size_X,Hp_Size_Y });
    sprite7->SettexSize({ 360,82 });

    sprite7->SpriteTransVertexBuffer();

    //
    Sprite* sprite8 = Sprite::Create(spriteCommon, 8);

    spriteCommon->SpriteCommonLoadTexture(8, L"Resources/HP_2.png");
    sprite8->SetPosition({ 200,70,0 });
    sprite8->SetSize({ Hp_Size_X,Hp_Size_Y });
    sprite8->SettexSize({ 360,82 });

    sprite8->SpriteTransVertexBuffer();

    //
    Sprite* sprite9 = Sprite::Create(spriteCommon, 9);

    spriteCommon->SpriteCommonLoadTexture(9, L"Resources/HP_1.png");
    sprite9->SetPosition({ 200,70,0 });
    sprite9->SetSize({ Hp_Size_X,Hp_Size_Y });
    sprite9->SettexSize({ 360,82 });

    sprite9->SpriteTransVertexBuffer();

    //
    Sprite* sprite10 = Sprite::Create(spriteCommon, 10);

    spriteCommon->SpriteCommonLoadTexture(10, L"Resources/HP_0.png");
    sprite10->SetPosition({ 200,70,0 });
    sprite10->SetSize({ Hp_Size_X,Hp_Size_Y });
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
        sprite11[i]->SetSize({ 30,30 });
        sprite11[i]->SettexSize({ 70,70 });

        //sprites[i].isInvisible = true;

        // 頂点バッファに反映
        sprite11[i]->SpriteTransVertexBuffer();
    }

    //
    Sprite* sprite12 = Sprite::Create(spriteCommon, 12);

    spriteCommon->SpriteCommonLoadTexture(12, L"Resources/Exp_Bar.png");
    sprite12->SetPosition({ 30,30,0 });
    sprite12->SetSize({ 316,24});
    sprite12->SettexSize({ 316,58});
    sprite12->SetAnchor({ 0,0.5 });


    sprite12->SpriteTransVertexBuffer();

    //
    Sprite* sprite13 = Sprite::Create(spriteCommon, 13);

    spriteCommon->SpriteCommonLoadTexture(13, L"Resources/Exp_Bar2.png");
    sprite13->SetPosition({ 30,30,0 });
    sprite13->SetSize({ 316,24 });
    sprite13->SettexSize({ 316,58 });
    sprite13->SetAnchor({ 0,0.5 });

    sprite13->SpriteTransVertexBuffer();


    //
    spriteCommon->SpriteCommonLoadTexture(14, L"Resources/Exp.png");


    const int EXP_NUM = 300;

    Sprite* sprite14[EXP_NUM] = { nullptr };

    // スプライトの生成
    for (int i = 0; i < EXP_NUM; i++)
    {

        sprite14[i] = Sprite::Create(spriteCommon,14);

        // スプライトの座標変更
        sprite14[i]->SetPosition({ 0 ,0 ,0 });
        sprite14[i]->SetSize({ 10,10 });
        sprite14[i]->SettexSize({ 60,60 });

        //sprites[i].isInvisible = true;

        // 頂点バッファに反映
        sprite14[i]->SpriteTransVertexBuffer();
    }

    //
    spriteCommon->SpriteCommonLoadTexture(15, L"Resources/HEAL.png");


    const int HEAL_NUM = 10;

    Sprite* sprite15[HEAL_NUM] = { nullptr };

    // スプライトの生成
    for (int i = 0; i < HEAL_NUM; i++)
    {

        sprite15[i] = Sprite::Create(spriteCommon, 15);

        // スプライトの座標変更
        sprite15[i]->SetPosition({ 0 ,0 ,0 });
        sprite15[i]->SetSize({ 20,20 });
        sprite15[i]->SettexSize({ 66,60 });

        //sprites[i].isInvisible = true;

        // 頂点バッファに反映
        sprite15[i]->SpriteTransVertexBuffer();
    }

    //
    spriteCommon->SpriteCommonLoadTexture(16, L"Resources/BOX.png");


    const int BOX_NUM = 10;

    Sprite* sprite16[BOX_NUM] = { nullptr };

    // スプライトの生成
    for (int i = 0; i < BOX_NUM; i++)
    {

        sprite16[i] = Sprite::Create(spriteCommon, 16);

        // スプライトの座標変更
        sprite16[i]->SetPosition({ 0 ,0 ,0 });
        sprite16[i]->SetSize({ 33,30 });
        sprite16[i]->SettexSize({ 66,60 });

        //sprites[i].isInvisible = true;

        // 頂点バッファに反映
        sprite16[i]->SpriteTransVertexBuffer();
    }

    //
    Sprite* sprite17 = Sprite::Create(spriteCommon, 17);

    spriteCommon->SpriteCommonLoadTexture(17, L"Resources/title2.png");
    sprite17->SetPosition({ 640,360,0 });
    sprite17->SetSize({ 1280,720 });
    sprite17->SettexSize({ 1280,720 });
   // sprite17->SetAnchor({ 0,0.5 });
    sprite17->SpriteTransVertexBuffer();


    //
    Sprite* sprite18 = Sprite::Create(spriteCommon, 18);

    spriteCommon->SpriteCommonLoadTexture(18, L"Resources/GAMEOVER.png");
    sprite18->SetPosition({ 680,360,0 });
    sprite18->SetSize({ 1280,720 });
    sprite18->SettexSize({ 1280,720 });
    // sprite17->SetAnchor({ 0,0.5 });
    sprite18->SpriteTransVertexBuffer();

    //
    Sprite* sprite22 = Sprite::Create(spriteCommon, 22);

    spriteCommon->SpriteCommonLoadTexture(22, L"Resources/RULE1.png");
    sprite22->SetPosition({ 680,360,0 });
    sprite22->SetSize({ 1280,720 });
    sprite22->SettexSize({ 1280,720 });
    // sprite17->SetAnchor({ 0,0.5 });
    sprite22->SpriteTransVertexBuffer();

    //
    Sprite* sprite23 = Sprite::Create(spriteCommon, 23);

    spriteCommon->SpriteCommonLoadTexture(23, L"Resources/RULE2.png");
    sprite23->SetPosition({ 680,360,0 });
    sprite23->SetSize({ 1280,720 });
    sprite23->SettexSize({ 1280,720 });
    // sprite17->SetAnchor({ 0,0.5 });
    sprite23->SpriteTransVertexBuffer();

    //
    Sprite* sprite24 = Sprite::Create(spriteCommon, 24);

    spriteCommon->SpriteCommonLoadTexture(24, L"Resources/gameClear.png");
    sprite24->SetPosition({ 680,360,0 });
    sprite24->SetSize({ 1280,720 });
    sprite24->SettexSize({ 1280,720 });
    // sprite17->SetAnchor({ 0,0.5 });
    sprite24->SpriteTransVertexBuffer();

    //
    Sprite* sprite25 = Sprite::Create(spriteCommon, 25);

    spriteCommon->SpriteCommonLoadTexture(25, L"Resources/ziki.png");
    sprite25->SetPosition({ 680,360,0 });
    sprite25->SetSize({ 20,20 });
    sprite25->SettexSize({ 70,70 });
    // sprite17->SetAnchor({ 0,0.5 });
    sprite25->SpriteTransVertexBuffer();


    spriteCommon->SpriteCommonLoadTexture(26, L"Resources/bluepart.png");
    spriteCommon->SpriteCommonLoadTexture(27, L"Resources/redpart.png");

    //青particle
    const int BLUEP_NUM = 300;
    Sprite* bluepart[BLUEP_NUM] = { nullptr };
    // スプライトの生成
    for (int i = 0; i < BLUEP_NUM; i++)
    {

        bluepart[i] = Sprite::Create(spriteCommon, 26);

        // スプライトの座標変更
        bluepart[i]->SetPosition({ 30 ,100 ,0 });
        bluepart[i]->SetSize({ 10,10 });

        //sprites[i].isInvisible = true;

        // 頂点バッファに反映
        bluepart[i]->SpriteTransVertexBuffer();
    }

    //赤particle
    const int REDP_NUM = 300;
    Sprite* redpart[REDP_NUM] = { nullptr };
    // スプライトの生成
    for (int i = 0; i < REDP_NUM; i++)
    {

        redpart[i] = Sprite::Create(spriteCommon, 27);

        // スプライトの座標変更
        redpart[i]->SetPosition({ 30 ,100 ,0 });
        redpart[i]->SetSize({ 10,10 });

        //sprites[i].isInvisible = true;

        // 頂点バッファに反映
        redpart[i]->SpriteTransVertexBuffer();
    }

    //
    Sprite* sprite28 = Sprite::Create(spriteCommon, 28);

    spriteCommon->SpriteCommonLoadTexture(28, L"Resources/Red_Bar.png");
    sprite28->SetPosition({ 30,60,0 });
    sprite28->SetSize({ 316,24 });
    sprite28->SettexSize({ 316,58 });
    sprite28->SetAnchor({ 0,0.5 });
    sprite28->SpriteTransVertexBuffer();

    //
    Sprite* sprite29 = Sprite::Create(spriteCommon, 29);

    spriteCommon->SpriteCommonLoadTexture(29, L"Resources/Red_Bar2.png");
    sprite29->SetPosition({ 30,60,0 });
    sprite29->SetSize({ 316,24 });
    sprite29->SettexSize({ 316,58 });
    sprite29->SetAnchor({ 0,0.5 });
    sprite29->SpriteTransVertexBuffer();

    //
    Sprite* sprite30 = Sprite::Create(spriteCommon, 30);

    spriteCommon->SpriteCommonLoadTexture(30, L"Resources/Controll.png");
    sprite30->SetPosition({ 0,0,0 });
    sprite30->SetSize({ 60,60 });
    sprite30->SettexSize({ 60,60 });
    sprite30->SetAnchor({ 0.5,0.5 });
    sprite30->SpriteTransVertexBuffer();

    //
    Sprite* sprite31 = Sprite::Create(spriteCommon, 31);

    spriteCommon->SpriteCommonLoadTexture(31, L"Resources/FOUND.png");
    sprite31->SetPosition({ 640,360,0 });
    sprite31->SetSize({ 1280,720 });
    sprite31->SettexSize({ 1280,720 });
    sprite31->SetAnchor({ 0.5,0.5 });
    sprite31->SpriteTransVertexBuffer();

    //
    Sprite* sprite32 = Sprite::Create(spriteCommon, 32);

    spriteCommon->SpriteCommonLoadTexture(32, L"Resources/attackSpeedUp.png");
    sprite32->SetPosition({ 640,360,0 });
    sprite32->SetSize({200,200 });
    sprite32->SettexSize({ 108,108 });
    sprite32->SetAnchor({ 0.5,0.5 });
    sprite32->SpriteTransVertexBuffer();

    //
    Sprite* sprite33 = Sprite::Create(spriteCommon, 33);

    spriteCommon->SpriteCommonLoadTexture(33, L"Resources/speedUp.png");
    sprite33->SetPosition({ 640,360,0 });
    sprite33->SetSize({ 200,200 });
    sprite33->SettexSize({ 108,108 });
    sprite33->SetAnchor({ 0.5,0.5 });
    sprite33->SpriteTransVertexBuffer();

    //
    Sprite* sprite34 = Sprite::Create(spriteCommon, 34);

    spriteCommon->SpriteCommonLoadTexture(34, L"Resources/expUp.png");
    sprite34->SetPosition({ 640,360,0 });
    sprite34->SetSize({ 200,200 });
    sprite34->SettexSize({ 108,108 });
    sprite34->SetAnchor({ 0.5,0.5 });
    sprite34->SpriteTransVertexBuffer();


    //
    Sprite* sprite35 = Sprite::Create(spriteCommon, 35);

    spriteCommon->SpriteCommonLoadTexture(35, L"Resources/BARRIERt.png");
    sprite35->SetPosition({ 640,360,0 });
    sprite35->SetSize({ 200,200 });
    sprite35->SettexSize({ 200,200 });
    sprite35->SetAnchor({ 0.5,0.5 });
    sprite35->SpriteTransVertexBuffer();

    //
    Sprite* sprite36 = Sprite::Create(spriteCommon, 36);

    spriteCommon->SpriteCommonLoadTexture(36, L"Resources/STOP.png");
    sprite36->SetPosition({ 640,360,0 });
    sprite36->SetSize({ 200,200 });
    sprite36->SettexSize({ 200,200 });
    sprite36->SetAnchor({ 0.5,0.5 });
    sprite36->SpriteTransVertexBuffer();

    //
    Sprite* sprite37 = Sprite::Create(spriteCommon, 37);

    spriteCommon->SpriteCommonLoadTexture(37, L"Resources/powerUp.png");
    sprite37->SetPosition({ 640,360,0 });
    sprite37->SetSize({ 200,200 });
    sprite37->SettexSize({ 108,108 });
    sprite37->SetAnchor({ 0.5,0.5 });
    sprite37->SpriteTransVertexBuffer();

    //
    Sprite* sprite38 = Sprite::Create(spriteCommon, 38);

    spriteCommon->SpriteCommonLoadTexture(38, L"Resources/ROLL_UP2.png");
    sprite38->SetPosition({ 640,360,0 });
    sprite38->SetSize({ 200,200 });
    sprite38->SettexSize({ 200,200 });
    sprite38->SetAnchor({ 0.5,0.5 });
    sprite38->SpriteTransVertexBuffer();

    //
    Sprite* sprite39 = Sprite::Create(spriteCommon, 39);

    spriteCommon->SpriteCommonLoadTexture(39, L"Resources/bomb.png");
    sprite39->SetPosition({ 640,360,0 });
    sprite39->SetSize({ 200,200 });
    sprite39->SettexSize({ 108,108 });
    sprite39->SetAnchor({ 0.5,0.5 });
    sprite39->SpriteTransVertexBuffer();

    //
    Sprite* sprite40 = Sprite::Create(spriteCommon, 40);

    spriteCommon->SpriteCommonLoadTexture(40, L"Resources/Red.png");
    sprite40->SetPosition({ 640,360,0 });
    sprite40->SetSize({ 70,70 });
    sprite40->SettexSize({ 70,70 });
    sprite40->SpriteTransVertexBuffer();

    //
    Sprite* sprite41 = Sprite::Create(spriteCommon, 41);

    spriteCommon->SpriteCommonLoadTexture(41, L"Resources/Blue.png");
    sprite41->SetPosition({ 640,360,0 });
    sprite41->SetSize({ 70,70 });
    sprite41->SettexSize({ 70,70 });
    sprite41->SpriteTransVertexBuffer();

    //
    Sprite* sprite42 = Sprite::Create(spriteCommon, 42);

    spriteCommon->SpriteCommonLoadTexture(42, L"Resources/Boss.png");
    sprite42->SetPosition({ 640,360,0 });
    sprite42->SetSize({ 70,70 });
    sprite42->SettexSize({ 70,70 });
    sprite42->SpriteTransVertexBuffer();

  

    //
    Sprite* sprite44 = Sprite::Create(spriteCommon, 44);

    spriteCommon->SpriteCommonLoadTexture(44, L"Resources/ARM_R.png");
    sprite44->SetPosition({ 640,460,0 });
    sprite44->SetSize({ 1200,200 });
    sprite44->SettexSize({ 1200,200 });
    sprite44->SpriteTransVertexBuffer();

    //
    Sprite* sprite45 = Sprite::Create(spriteCommon, 45);

    spriteCommon->SpriteCommonLoadTexture(45, L"Resources/LEG_R.png");
    sprite45->SetPosition({ 640,460,0 });
    sprite45->SetSize({ 1200,200 });
    sprite45->SettexSize({ 1200,200 });
    sprite45->SpriteTransVertexBuffer();

    //
    Sprite* sprite46 = Sprite::Create(spriteCommon, 46);

    spriteCommon->SpriteCommonLoadTexture(46, L"Resources/STU_R.png");
    sprite46->SetPosition({ 640,460,0 });
    sprite46->SetSize({ 1200,200 });
    sprite46->SettexSize({ 1200,200 });
    sprite46->SpriteTransVertexBuffer();

    //
    Sprite* sprite47 = Sprite::Create(spriteCommon, 47);

    spriteCommon->SpriteCommonLoadTexture(47, L"Resources/BAR_R.png");
    sprite47->SetPosition({ 640,460,0 });
    sprite47->SetSize({ 1200,200 });
    sprite47->SettexSize({ 1200,200 });
    sprite47->SpriteTransVertexBuffer();

    //
    Sprite* sprite48 = Sprite::Create(spriteCommon, 48);

    spriteCommon->SpriteCommonLoadTexture(48, L"Resources/ATT_R.png");
    sprite48->SetPosition({ 640,460,0 });
    sprite48->SetSize({ 1200,200 });
    sprite48->SettexSize({ 1200,200 });
    sprite48->SpriteTransVertexBuffer();

    //
    Sprite* sprite49 = Sprite::Create(spriteCommon, 49);

    spriteCommon->SpriteCommonLoadTexture(49, L"Resources/STO_R.png");
    sprite49->SetPosition({ 640,460,0 });
    sprite49->SetSize({ 1200,200 });
    sprite49->SettexSize({ 1200,200 });
    sprite49->SpriteTransVertexBuffer();

    //
    Sprite* sprite50 = Sprite::Create(spriteCommon, 50);

    spriteCommon->SpriteCommonLoadTexture(50, L"Resources/ROLL_R.png");
    sprite50->SetPosition({ 640,460,0 });
    sprite50->SetSize({ 1200,200 });
    sprite50->SettexSize({ 1200,200 });
    sprite50->SpriteTransVertexBuffer();


    //
    Sprite* sprite51 = Sprite::Create(spriteCommon, 51);

    spriteCommon->SpriteCommonLoadTexture(51, L"Resources/DES_R.png");
    sprite51->SetPosition({ 640,460,0 });
    sprite51->SetSize({ 1200,200 });
    sprite51->SettexSize({ 1200,200 });
    sprite51->SpriteTransVertexBuffer();

    //
    Sprite* sprite52 = Sprite::Create(spriteCommon, 52);

    spriteCommon->SpriteCommonLoadTexture(52, L"Resources/PUSH.png");
    sprite52->SetPosition({ 660,360,0 });
    sprite52->SetSize({ 1280,720 });
    sprite52->SettexSize({ 1280,720 });
    sprite52->SpriteTransVertexBuffer();

    //デバックテキスト
    DebugText* debugtext = nullptr;
    debugtext = new DebugText();


    const int debugTextTexNumber = 19;

    spriteCommon->SpriteCommonLoadTexture(debugTextTexNumber, L"Resources/ASC_white1280.png");
    //SpriteCommonLoadTexture(spriteCommon, debugTextTexNumber, L"Resources/ASC_white1280.png", dxCommon->GetDev());

    debugtext->debugTextInit(spriteCommon, debugTextTexNumber);

    //
    DebugText* debugtext2 = nullptr;
    debugtext2 = new DebugText();


    const int debugTextTexNumber2 = 20;

    spriteCommon->SpriteCommonLoadTexture(debugTextTexNumber2, L"Resources/ASC_white1280.png");
    //SpriteCommonLoadTexture(spriteCommon, debugTextTexNumber, L"Resources/ASC_white1280.png", dxCommon->GetDev());

    debugtext2->debugTextInit(spriteCommon, debugTextTexNumber2);


    //
    DebugText* debugtext3 = nullptr;
    debugtext3 = new DebugText();


    const int debugTextTexNumber3 = 21;

    spriteCommon->SpriteCommonLoadTexture(debugTextTexNumber3, L"Resources/ASC_white1280.png");
    //SpriteCommonLoadTexture(spriteCommon, debugTextTexNumber, L"Resources/ASC_white1280.png", dxCommon->GetDev());

    debugtext3->debugTextInit(spriteCommon, debugTextTexNumber3);




    //
   // spriteCommon->Initialize_Post(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->window_width, winApp->window_height);
    Sprite* sprite43 = Sprite::Create(spriteCommon, 43);

    spriteCommon->SpriteCommonLoadTexture(43, L"Resources/Pera.png");
    sprite43->SetPosition({ 640,360,0 });
    sprite43->SetSize({ 1280,720 });
    sprite43->SettexSize({ 1280,720 });
    sprite43->SpriteTransVertexBuffer();

    
       // DirectX初期化処理　ここまで

       //3D初期値設定

       //的のフラグ
    int TargetFlag = 1;
    //int RuleFlag = 0;

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

    int BossScene = 0;
    int EnemyBreak = 0;

    int KillCount = 0;

    int bluecolflag = 0;
    int redcolflag = 0;

   
    char moji[64];
    char moji2[64];
    char moji3[64];

    Player* player = nullptr;
    player = new Player();
    Enemy* enemy1=nullptr;
    enemy1 = new Enemy();

    Boss* boss = nullptr;
    boss = new Boss();

    Collision*collision=nullptr;
    collision = new Collision();
    

    Item* item = nullptr;
    item = new Item();

    particle* partb = nullptr;
    partb = new particle();
    particle* partr = nullptr;
    partr = new particle();

    partb->Initialize();
    partr->Initialize();
  
    enemy1->Intialize();
    item->Intialize();
    player->Initialize();
    boss->Initialize();

    float E_R = 0;

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

           // E_R = enemy1->Enemy1[i].R;
            sprite5[i]->SetSize({enemy1->Enemy1[i].R,enemy1->Enemy1[i].R});
            sprite5[i]->SpriteTransVertexBuffer();

        }

        for (int i = 0; i < EXP_NUM; i++)
        {
            sprite14[i]->Update();
        }

        for (int i = 0; i < HEAL_NUM; i++)
        {
            sprite15[i]->Update();
        }

        for (int i = 0; i < BOX_NUM; i++)
        {
            sprite16[i]->Update();
        }

        for (int i = 0; i < BLUEP_NUM; i++)
        {
            bluepart[i]->Update();
        }

        for (int i = 0; i < REDP_NUM; i++)
        {
            redpart[i]->Update();
        }

        sprite7->Update();
        sprite8->Update();
        sprite9->Update();
        sprite10->Update();

        sprite12->Update();
        sprite13->Update();
        sprite17->Update();
        sprite18->Update();

        sprite22->Update();
        sprite23->Update();
        sprite24->Update();
        sprite25->Update();

        sprite28->Update();
        sprite29->Update();
        sprite30->Update();
        sprite31->Update();

        sprite32->Update();
        sprite33->Update();
        sprite34->Update();
        sprite35->Update();
        sprite36->Update();
        sprite37->Update();
        sprite38->Update();
        sprite39->Update();
        sprite40->Update();
        sprite41->Update();
        sprite42->Update();
        sprite43->Update();

        sprite44->Update();
        sprite45->Update();
        sprite46->Update();
        sprite47->Update();
        sprite48->Update();
        sprite49->Update();
        sprite50->Update();
        sprite51->Update();
        sprite52->Update();




        Hp_X = player->Central_x;
        Hp_Y = player->Central_y +30;

        sprite->SetPosition({ player->Player_RedX,player->Player_RedY,0 });
        sprite4->SetPosition({ player->Central_x,player->Central_y,0 });
        sprite2->SetPosition({ player->Player_BlueX,player->Player_BlueY,0 });
        sprite7->SetPosition({ Hp_X,Hp_Y,0 });
        sprite8->SetPosition({ Hp_X,Hp_Y,0 });
        sprite9->SetPosition({ Hp_X,Hp_Y,0 });
        sprite10->SetPosition({ Hp_X,Hp_Y,0 });
        sprite25->SetPosition({ player->Central_x,player->Central_y,0 });




        //背景　描画　座標

        //for(int i=0;i<:i++)
        for (int i = 0; i < BACK_NUM; i++)
        {         
            if(i<30)sprite6[i]->SetPosition({ (-697+(i*90)) - player->Back_X,45 - player->Back_Y,0 });
            else if(i<60)sprite6[i]->SetPosition({ (-697+((i-30)*90)) - player->Back_X,135 - player->Back_Y,0 });
            else if (i < 90)sprite6[i]->SetPosition({ (-697 + ((i-60) * 90)) - player->Back_X,225 - player->Back_Y,0 });
            else if (i < 120)sprite6[i]->SetPosition({ (-697 + ((i-90) * 90)) - player->Back_X,315 - player->Back_Y,0 });
            else if (i < 150)sprite6[i]->SetPosition({ (-697 + ((i-120) * 90)) - player->Back_X,405 - player->Back_Y,0 });
            else if (i < 180)sprite6[i]->SetPosition({ (-697 + ((i-150) * 90)) - player->Back_X,495 - player->Back_Y,0 });
            else if (i < 210)sprite6[i]->SetPosition({ (-697 + ((i - 180) * 90)) - player->Back_X,585 - player->Back_Y,0 });
            else if (i < 240)sprite6[i]->SetPosition({ (-697 + ((i - 210) * 90)) - player->Back_X,675 - player->Back_Y,0 });
            else if (i < 270)sprite6[i]->SetPosition({ (-697 + ((i - 240) * 90)) - player->Back_X,765 - player->Back_Y,0 });
            else if (i < 300)sprite6[i]->SetPosition({ (-697 + ((i - 270) * 90)) - player->Back_X,855 - player->Back_Y,0 });
            else if (i < 330)sprite6[i]->SetPosition({ (-697 + ((i - 300) * 90)) - player->Back_X,945 - player->Back_Y,0 });
            else if (i < 360)sprite6[i]->SetPosition({ (-697 + ((i - 330) * 90)) - player->Back_X,1035 - player->Back_Y,0 });
            else if (i < 390)sprite6[i]->SetPosition({ (-697 + ((i - 360) * 90)) - player->Back_X,1125 - player->Back_Y,0 });
            else if (i < 420)sprite6[i]->SetPosition({ (-697 + ((i - 390) * 90)) - player->Back_X,1215 - player->Back_Y,0 });
            else if (i < 450)sprite6[i]->SetPosition({ (-697 + ((i - 420) * 90)) - player->Back_X,1305 - player->Back_Y,0 });
            else if (i < 480)sprite6[i]->SetPosition({ (-697 + ((i - 450) * 90)) - player->Back_X,1395 - player->Back_Y,0 });
            else if (i < 510)sprite6[i]->SetPosition({ (-697 + ((i - 480) * 90)) - player->Back_X,-45 - player->Back_Y,0 });
            else if (i < 540)sprite6[i]->SetPosition({ (-697 + ((i - 510) * 90)) - player->Back_X,-135 - player->Back_Y,0 });
            else if (i < 570)sprite6[i]->SetPosition({ (-697 + ((i - 540) * 90)) - player->Back_X,-225 - player->Back_Y,0 });
            else if (i < 600)sprite6[i]->SetPosition({ (-697 + ((i - 570) * 90)) - player->Back_X,-315 - player->Back_Y,0 });
            else if (i < 630)sprite6[i]->SetPosition({ (-697 + ((i - 600) * 90)) - player->Back_X,-405 - player->Back_Y,0 });
            else if (i < 660)sprite6[i]->SetPosition({ (-697 + ((i - 630) * 90)) - player->Back_X,-495 - player->Back_Y,0 });
            else if (i < 690)sprite6[i]->SetPosition({ (-697 + ((i - 660) * 90)) - player->Back_X,-585 - player->Back_Y,0 });
            else if (i < 720)sprite6[i]->SetPosition({ (-697 + ((i - 690) * 90)) - player->Back_X,-675 - player->Back_Y,0 });
        }

        sprite2->SetSize({ player->Blue_R * player->Blue_Lv,player->Blue_R * player->Blue_Lv });
        sprite->SetSize({ player->Red_R * player->Red_Lv,player->Red_R * player->Red_Lv });

        //本体無敵時間
        if (player->invincibleFlag == 1)
        {
            if (player->invincibleTime ==10)
            {
                sprite->SetColor({ 1, 1, 1, 0 });
                sprite2->SetColor({ 1, 1, 1, 0 });
                sprite25->SetColor({ 1, 1, 1, 0 });
            }
            else if (player->invincibleTime == 20)
            {
                sprite->SetColor({ 1, 1, 1, 1 });
                sprite2->SetColor({ 1, 1, 1, 1 });
                sprite25->SetColor({ 1, 1, 1, 1 });
            }
            else if (player->invincibleTime == 30)
            {
                sprite->SetColor({ 1, 1, 1, 0 });
                sprite2->SetColor({ 1, 1, 1, 0 });
                sprite25->SetColor({ 1, 1, 1, 0 });
            }
            else if (player->invincibleTime == 40)
            {
                sprite->SetColor({ 1, 1, 1, 1 });
                sprite2->SetColor({ 1, 1, 1, 1 });
                sprite25->SetColor({ 1, 1, 1, 1 });
            }
            else if (player->invincibleTime == 50)
            {
                sprite->SetColor({ 1, 1, 1, 0 });
                sprite2->SetColor({ 1, 1, 1, 0 });
                sprite25->SetColor({ 1, 1, 1, 0 });
            }
            else if (player->invincibleTime == 60)
            {
                sprite->SetColor({ 1, 1, 1, 1 });
                sprite2->SetColor({ 1, 1, 1, 1 });
                sprite25->SetColor({ 1, 1, 1, 1 });
            }
            else if (player->invincibleTime == 70)
            {
                sprite->SetColor({ 1, 1, 1, 0 });
                sprite2->SetColor({ 1, 1, 1, 0 });
                sprite25->SetColor({ 1, 1, 1, 0 });
            }
            else if (player->invincibleTime == 80)
            {
                sprite->SetColor({ 1, 1, 1, 1 });
                sprite2->SetColor({ 1, 1, 1, 1 });
                sprite25->SetColor({ 1, 1, 1, 1 });
            }
            else if (player->invincibleTime == 90)
            {
                sprite->SetColor({ 1, 1, 1, 0 });
                sprite2->SetColor({ 1, 1, 1, 0 });
                sprite25->SetColor({ 1, 1, 1, 0 });
            }
        }
        else if(player->invincible_armFlag == 0&&player->invincibleFlag==0)
        {
            sprite->SetColor({ 1, 1, 1, 1 });
            sprite2->SetColor({ 1, 1, 1, 1 });
            sprite25->SetColor({ 1, 1, 1, 1 });
        }
        
        //arm無敵時間
        if (player->invincible_armFlag == 1)
        {
            if (player->invincible_armTime == 10)
            {
                sprite->SetColor({ 1, 1, 1, 0 });
                sprite2->SetColor({ 1, 1, 1, 0 });
            }
            else if (player->invincible_armTime == 20)
            {
                sprite->SetColor({ 1, 1, 1, 1 });
                sprite2->SetColor({ 1, 1, 1, 1 });
            }
            else if (player->invincible_armTime == 30)
            {
                sprite->SetColor({ 1, 1, 1, 0 });
                sprite2->SetColor({ 1, 1, 1, 0 });
            }
            else if (player->invincible_armTime == 40)
            {
                sprite->SetColor({ 1, 1, 1, 1 });
                sprite2->SetColor({ 1, 1, 1, 1 });
            }
            else if (player->invincible_armTime == 50)
            {
                sprite->SetColor({ 1, 1, 1, 0 });
                sprite2->SetColor({ 1, 1, 1, 0 });
            }
            else if (player->invincible_armTime == 60)
            {
                sprite->SetColor({ 1, 1, 1, 1 });
                sprite2->SetColor({ 1, 1, 1, 1 });
            }
            else if (player->invincible_armTime == 70)
            {
                sprite->SetColor({ 1, 1, 1, 0 });
                sprite2->SetColor({ 1, 1, 1, 0 });
            }
            else if (player->invincible_armTime == 80)
            {
                sprite->SetColor({ 1, 1, 1, 1 });
                sprite2->SetColor({ 1, 1, 1, 1 });
            }
            else if (player->invincible_armTime == 90)
            {
                sprite->SetColor({ 1, 1, 1, 0 });
                sprite2->SetColor({ 1, 1, 1, 0 });
            }
        }
        else if(player->invincible_armFlag == 0 && player->invincibleFlag == 0)
        {
            sprite->SetColor({ 1, 1, 1, 1 });
            sprite2->SetColor({ 1, 1, 1, 1 });
        }


        //スプライトサイズ変更
        sprite2->SpriteTransVertexBuffer();
        sprite->SpriteTransVertexBuffer();
        sprite13->SpriteTransVertexBuffer();



        //ゲッター関連
        player->setter(item->LEG1.Effect2);
        player->setter2(item->ARM1.Effect2);
        player->setter3(item->STU1.Effect2);
        player->setter4(item->ROLL1.Effect2);
        player->setter_scene(GameScene);
        player->setter_select(item->SelectTime);
        player->setter_deci(item->Decision);
        
        enemy1->Getter_X(player->Map_X);
        enemy1->Getter_Y(player->Map_Y);

        enemy1->Central_X_Get(player->Central_x);
        enemy1->Central_Y_Get(player->Central_y);
        enemy1->Getter_Stop(item->ATT1.Effect);



        boss->Getter_X(player->Map_X);
        boss->Getter_Y(player->Map_Y);

        boss->Central_X_Get(player->Central_x);
        boss->Central_Y_Get(player->Central_y);

        item->Get_deci(player->Decision);


        
        sprintf_s(moji, "%d", GameTime);
        sprintf_s(moji2, "%d", 300-GameTime);
        sprintf_s(moji3, "%d", KillCount);

        //スプライト設定関連ここまで

        if (winApp->ProcessMessage())
        {
            //ゲームループを抜ける
            break;
        }
        input->Update();
        // DirectX毎フレーム処理　ここから
        player->Controll();//ゲームパッドによるPlayerの操作
        GameScene = player->scene_;
        
        if(GameScene==1&&item->SelectTime==0) debugtext->Print(moji, debug_x, debug_y);
        if(GameScene == 2) debugtext2->Print(moji2, 572, 332);
        if (GameScene == 2||GameScene==3) debugtext3->Print(moji3, 572, 464);

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

       // spriteCommon2->PreDraw();

        //スプライト表示

        //アイテム

        //背景の描画
        for (int i = 0; i < BACK_NUM; i++)
        {
            sprite6[i]->SpriteDraw();
        }


        //初期化処理
        if (GameScene == 0)
        {
            player->Initialize();
            enemy1->Intialize();
            item->Intialize();
            boss->Initialize();

            GameScene = 0;
            GameTime = 300;
            GameTime_Count = 0;

            KillCount = 0;

           
            BossScene = 0;
            EnemyBreak = 0;

        }


        //ゲーム本編
        if (GameScene == 1)
        {
            if(item->SelectTime==0)GameTime_Count++;
            if (GameTime_Count >= 60&&BossScene==0)
            {
                GameTime_Count = 0;
                GameTime -= 1;

                if (GameTime == 270)
                {
                    enemy1->TimeLost = 20;
                    enemy1->TypeKinds += 1;
                }
                else if (GameTime == 250)
                {
                    enemy1->TimeLost = 70;
                    enemy1->Appearance += 1;
                    
                }
                else if (GameTime == 200)
                {
                    enemy1->TimeLost = 120;
                    enemy1->Appearance += 1;
                    enemy1->TypeKinds += 1;
                    enemy1-> Enemy_Ge = 130;
                }
                else if (GameTime == 160)
                {

                    enemy1->TimeLost = 160;
                    enemy1->Appearance += 1;
                    enemy1->TypeKinds += 1;
                }
                else if (GameTime == 120)
                {
                    enemy1->TimeLost = 180;
                  //  enemy1->Appearance += 1;
                    enemy1->Enemy_Ge = 120;
                }
                else if (GameTime == 100)
                {
                    enemy1->TimeLost = 200;
                    enemy1->Enemy_Ge = 100;
                }
            }

            if (GameTime <= 0)
            {
                //GameScene = 3;
                BossScene = 1;
                EnemyBreak = 1;
                boss->Flag = 1;
            }

            //毎フレーム動作関数
          
            item->Update();//アイテム

            if(item->SelectTime==0&&BossScene==0)
            enemy1->Update();//敵


        //経験値
            for (int i = 0; i < EXP_NUM; i++)
            {
                sprite14[i]->SetPosition({ player->Exp1[i].X - player->Map_X,player->Exp1[i].Y - player->Map_Y,0 });
                if (collision->CollisionArm(player->Central_x, player->Central_y, 20, player->Exp1[i].X - player->Map_X, player->Exp1[i].Y - player->Map_Y, player->Exp1[i].R) && player->Exp1[i].Flag == 1&&BossScene==0)
                {
                    player->Exp1[i].Flag = 0;
                    player->Exp += 1;
                    player->Exp_2 += 1;
                }


                if (player->Exp1[i].Flag == 1 && BossScene == 0)sprite14[i]->SpriteDraw();
            }

            //回復
            for (int i = 0; i < HEAL_NUM; i++)
            {
                sprite15[i]->SetPosition({ item->Heart_[i].X - player->Map_X,item->Heart_[i].Y - player->Map_Y,0 });
                if (collision->CollisionArm(player->Central_x, player->Central_y, 20, item->Heart_[i].X - player->Map_X, item->Heart_[i].Y - player->Map_Y, item->Heart_[i].R) && item->Heart_[i].Flag == 1 && BossScene == 0)
                {
                    item->Heart_[i].Flag = 0;

                    if (player->HP < 3)
                        player->HP += 1;
                }


                if (item->Heart_[i].Flag == 1 && BossScene == 0)sprite15[i]->SpriteDraw();
            }

            //BOX
            for (int i = 0; i < BOX_NUM; i++)
            {
                sprite16[i]->SetPosition({ item->Box_[i].X - player->Map_X,item->Box_[i].Y - player->Map_Y,0 });
                if (collision->CollisionArm(player->Central_x, player->Central_y, 20, item->Box_[i].X - player->Map_X, item->Box_[i].Y - player->Map_Y, 20) && item->Box_[i].Flag == 1 && BossScene == 0)
                {
                    item->Box_[i].Flag = 0;
                    item->Box_[i].HitFlag = 1;
                    item->SelectTime = 1;
                    //能力ランダム選択α版のみ
                    item->Box_[i].Select = rand() % 8 + 1;
                    //item->Box_[i].Select = 2;
                    item->Add = 1;
              //      item->Box_[i].Select = item->NowAbility;
                }


                if (item->Box_[i].Flag == 1 && BossScene == 0)sprite16[i]->SpriteDraw();
            }

            //敵の当たり判定と描画
            for (int i = 0; i < ENEMY1_NUM; i++)
            {

                //中央と敵
                if (collision->CollisionArm(player->Central_x, player->Central_y, 20, enemy1->Enemy1[i].X - player->Map_X, enemy1->Enemy1[i].Y - player->Map_Y, enemy1->Enemy1[i].R) && enemy1->Enemy1[i].Flag == 1 && player->invincibleFlag == 0)
                {
                    //バリアの時はダメージを受けない
                    if (item->BAR1.Flag == 0)
                    {
                        player->invincibleFlag = 1;
                        player->HP -= 1;
                    }

                    enemy1->Enemy1[i].Flag = 0;
                    enemy1->Enemy1[i].Die = 1;

                }

                //敵と腕の処理
                if (player->invincibleFlag == 0 && enemy1->Enemy1[i].knock_back == 0)
                {

                    if (i % 2 == 0)
                    {
                        //自機蒼と赤
                        if (collision->CollisionArm(player->Player_BlueX, player->Player_BlueY, player->Blue_R * player->Blue_Lv, enemy1->Enemy1[i].X - player->Map_X, enemy1->Enemy1[i].Y - player->Map_Y, enemy1->Enemy1[i].R) && enemy1->Enemy1[i].Flag == 1)
                        {

                            if (player->Blue_Lv >= 2)
                            {
                                //player->Blue_Lv -= 1;
                            }
                            //振動
                            if(player->invincible_armFlag==0&&player->WrongFlag==0)player->Shake();
                        }               //自機赤と赤
                        else if (collision->CollisionArm(player->Player_RedX, player->Player_RedY, player->Red_R * player->Red_Lv, enemy1->Enemy1[i].X - player->Map_X, enemy1->Enemy1[i].Y - player->Map_Y, enemy1->Enemy1[i].R) && enemy1->Enemy1[i].Flag == 1)
                        {
                            //arm無敵時間なら即座に終了させる
                            if (player->invincible_armFlag == 1)
                            {
                                player->invincible_armFlag = 0;
                            }


                            if (enemy1->Enemy1[i].HP > 1)
                            {
                                enemy1->Enemy1[i].knock_back = 1;
                               // redcolflag = 1;
                            }
                            else
                            {
                                player->Exp_2 += 2 + item->STU1.Effect2;
                                KillCount += 1;
                                redcolflag = 1;
                            }

                           // if (item->STR1.Flag == 1)
                           // {
                           //     player->Exp += 2 + item->STU1.Effect2;
                           //     KillCount += 1;
                           //     redcolflag = 1;
                           // }

                            if (player->Red_Lv < 3 && enemy1->Enemy1[i].HP == 1)
                            {
                                // player->Red_Lv += 1;
                            }
                            enemy1->Enemy1[i].HP -= 1+item->STR1.Effect2;


                        }


                    }
                    else
                    {
                        if (collision->CollisionArm(player->Player_RedX, player->Player_RedY, player->Red_R * player->Red_Lv, enemy1->Enemy1[i].X - player->Map_X, enemy1->Enemy1[i].Y - player->Map_Y, enemy1->Enemy1[i].R) && enemy1->Enemy1[i].Flag == 1)
                        {

                            if (player->Red_Lv >= 2)
                            {
                               // player->Red_Lv -= 1;
                            }
                            //振動
                            if (player->invincible_armFlag == 0 && player->WrongFlag == 0)player->Shake();
                        }         //自機蒼と蒼
                        else if (collision->CollisionArm(player->Player_BlueX, player->Player_BlueY, player->Blue_R * player->Blue_Lv, enemy1->Enemy1[i].X - player->Map_X, enemy1->Enemy1[i].Y - player->Map_Y, enemy1->Enemy1[i].R) && enemy1->Enemy1[i].Flag == 1)
                        {

                            //arm無敵時間なら即座に終了させる
                            if (player->invincible_armFlag == 1)
                            {
                                player->invincible_armFlag = 0;
                            }

                            if (enemy1->Enemy1[i].HP > 1)
                            {
                                enemy1->Enemy1[i].knock_back = 1;
                                //bluecolflag = 1;
                            }
                            else
                            {
                                player->Exp += 2 + item->STU1.Effect2;
                                KillCount += 1;
                                bluecolflag = 1;
                            }

                           // if (item->STR1.Flag == 1)
                           // {
                           //     player->Exp += 2 + item->STU1.Effect2;
                           //     KillCount += 1;
                           //     bluecolflag = 1;
                           // }

                            if (player->Blue_Lv < 3 && enemy1->Enemy1[i].HP == 1)
                            {
                                //player->Blue_Lv += 1;
                            }

                            enemy1->Enemy1[i].HP -= 1+item->STR1.Effect2;


                        }
                    }
                }

                //画面内敵一斉排除
                if (item->DESTROY_.Flag == 1)
                {
                    if (enemy1->Enemy1[i].X - player->Map_X > 0 && enemy1->Enemy1[i].X - player->Map_X < 1280)
                    {
                        if (enemy1->Enemy1[i].Y - player->Map_Y > 0 && enemy1->Enemy1[i].Y - player->Map_Y < 720)
                        {

                            enemy1->Enemy1[i].Flag = 0;
                            enemy1->Enemy1[i].Die = 1;
                            KillCount += 1;
                            if (i % 2 == 0)
                            {
                                redcolflag = 1;
                            }
                            else
                            {
                                bluecolflag = 1;
                            }

                           

                        }
                    }
                }
                //Boss時間になったら敵全て自壊
                if (EnemyBreak == 1)
                {
                    enemy1->Enemy1[i].Flag = 0;
                    enemy1->Enemy1[i].Die = 1;
                   // KillCount += 1;
                    if (i % 2 == 0)
                    {
                        redcolflag = 1;
                    }
                    else
                    {
                        bluecolflag = 1;
                    }
                }

                if (enemy1->Enemy1[i].HP <= 0)
                {
                    enemy1->Enemy1[i].Flag = 0;
                    enemy1->Enemy1[i].Die = 1;
                   
                }

                sprite5[i]->SetPosition({ enemy1->Enemy1[i].X - player->Map_X,enemy1->Enemy1[i].Y - player->Map_Y,0 });
                sprite11[i]->SetPosition({ enemy1->Enemy1[i].X - player->Map_X,enemy1->Enemy1[i].Y - player->Map_Y,0 });

                if (redcolflag == 1)
                {
                    partr->createred(enemy1->Enemy1[i].X - player->Map_X, enemy1->Enemy1[i].Y - player->Map_Y, 0, 0);
                }

                redpart[i]->SetPosition({ partr->PARTr[i].x,partr->PARTr[i].y,0 });

                partr->movered(enemy1->Enemy1[i].X - player->Map_X, enemy1->Enemy1[i].Y - player->Map_Y, 0, 0);

                partr->Finalizered(redcolflag);

                if (bluecolflag == 1)
                {
                    partb->createblue(enemy1->Enemy1[i].X - player->Map_X, enemy1->Enemy1[i].Y - player->Map_Y, 0, 0);
                }

                bluepart[i]->SetPosition({ partb->PARTb[i].x,partb->PARTb[i].y,0 });

                partb->moveblue(enemy1->Enemy1[i].X - player->Map_X, enemy1->Enemy1[i].Y - player->Map_Y, 0, 0);

                partb->Finalizeblue(bluecolflag);

                //通常時の描画
                if (enemy1->Enemy1[i].Flag == 1 && enemy1->Enemy1[i].knock_back == 0)sprite5[i]->SpriteDraw();
                //ノックバック時の描画
                if (enemy1->Enemy1[i].knock_back == 1)sprite11[i]->SpriteDraw();
            }

        }
        if (EnemyBreak == 1)
        {
            EnemyBreak = 0;
        }


        if (item->DESTROY_.Flag == 1)
        {
            item->DESTROY_.Flag = 0;
           
            //効果消えたら一個左に詰める
            if (item->UI_Flag != item->DESTROY_.UI)
            {
                if (item->DESTROY_.UI == 1)
                {
                    if (item->ARM1.UI > 3)
                    {
                        item->ARM1.UI -= 1;
                    }
                    else if (item->LEG1.UI > 3)
                    {
                        item->LEG1.UI -= 1;
                    }
                    else if (item->STU1.UI > 3)
                    {
                        item->STU1.UI -= 1;
                    }
                    else if (item->ATT1.UI > 3)
                    {
                        item->ATT1.UI -= 1;
                    }
                    else if (item->STR1.UI > 3)
                    {
                        item->STR1.UI -= 1;
                    }
                    else if (item->ROLL1.UI > 3)
                    {
                        item->ROLL1.UI -= 1;
                    }
                }
                else
                {
                    if (item->ARM1.UI > 2 && item->ARM1.UI != 1)
                    {
                        item->ARM1.UI -= 1;
                    }
                    else if (item->LEG1.UI > 2 && item->LEG1.UI != 1)
                    {
                        item->LEG1.UI -= 1;
                    }
                    else if (item->STU1.UI > 2 && item->STU1.UI != 1)
                    {
                        item->STU1.UI -= 1;
                    }
                    else if (item->ATT1.UI > 2 && item->ATT1.UI != 1)
                    {
                        item->ATT1.UI -= 1;
                    }
                    else if (item->STR1.UI > 2 && item->STR1.UI != 1)
                    {
                        item->STR1.UI -= 1;
                    }
                    else if (item->ROLL1.UI > 2 && item->ROLL1.UI != 1)
                    {
                        item->ROLL1.UI -= 1;
                    }
                }
            }

            item->DESTROY_.UI = 0;

            if (item->UI_Flag != 0)item->UI_Flag -= 1;
            

        }

        //ボス
        if (BossScene == 1)
        {
           
            if (collision->CollisionArm(player->Player_RedX, player->Player_RedY, player->Red_R * player->Red_Lv, boss->x-player->Map_X, boss->y-player->Map_Y, boss->R) && boss->Flag == 1)
            {
                boss->HP -= 1;
                boss->knock_back = 1;
            }
            else if (collision->CollisionArm(player->Player_BlueX, player->Player_BlueY, player->Red_R * player->Red_Lv, boss->x - player->Map_X, boss->y - player->Map_Y, boss->R) && boss->Flag == 1)
            {
                boss->HP -= 1;
                boss->knock_back = 1;
            }


            if (collision->CollisionArm(player->Central_x, player->Central_y, 20, boss->RedX - player->Map_X, boss->RedY - player->Map_Y, boss->Red_R) && boss->Flag == 1 && player->invincibleFlag == 0)
            {
                //バリアの時はダメージを受けない
                if (item->BAR1.Flag == 0)
                {
                    player->invincibleFlag = 1;
                    player->HP -= 1;
                }

            }
            else  if (collision->CollisionArm(player->Central_x, player->Central_y, 20, boss->BlueX - player->Map_X, boss->BlueY - player->Map_Y, boss->Blue_R) && boss->Flag == 1 && player->invincibleFlag == 0)
            {
                //バリアの時はダメージを受けない
                if (item->BAR1.Flag == 0)
                {
                    player->invincibleFlag = 1;
                    player->HP -= 1;
                }

            }


            if (boss->HP <= 0)
            {
                boss->Flag = 0;
                GameScene = 3;
            }


            sprite40->SetPosition({ boss->RedX - player->Map_X,boss->RedY - player->Map_Y,0 });
            sprite41->SetPosition({ boss->BlueX - player->Map_X,boss->BlueY - player->Map_Y,0 });
            sprite42->SetPosition({ boss->x- player->Map_X,boss->y - player->Map_Y,0 });

            if (boss->Flag == 1)
            {
                boss->Update();
                sprite40->SpriteDraw();
                sprite41->SpriteDraw();
                sprite42->SpriteDraw();
            }
        }


        //自キャラの描画
        sprite->SpriteDraw();
        sprite2->SpriteDraw();
        sprite25->SpriteDraw();

        if (GameScene == 1)
        {
            //UI
            if (item->BAR1.Flag == 1)sprite4->SpriteDraw();

            if (redcolflag == 1)
            {
                for (int i = 0; i < REDP_NUM; i++)
                {
                    redpart[i]->SpriteDraw();
                }
            }

            if (bluecolflag == 1)
            {
                for (int i = 0; i < BLUEP_NUM; i++)
                {
                    bluepart[i]->SpriteDraw();
                }
            }

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
                GameScene = 2;
            }

            //ExpBar蒼
            sprite12->SpriteDraw();
            sprite13->SpriteDraw();


            //ExpBar赤
            sprite28->SpriteDraw();
            sprite29->SpriteDraw();

        }
        else if(GameScene==0&&player->RuleFlag==0)
        {
            sprite17->SpriteDraw();
            sprite52->SpriteDraw();
        }
        else if (GameScene == 2)
        {
            sprite18->SpriteDraw();
        }
        else if (GameScene == 3)
        {
            sprite24->SpriteDraw();
        }

        if (player->RuleFlag == 1)
        {
            sprite22->SpriteDraw();
        }
        else if(player->RuleFlag == 2)
        {
            sprite23->SpriteDraw();
        }


        if (player->Level == 1)
        {
            sprite13->SetSize({ player->Exp * 26,24 });
        }
        else if (player->Level == 2)
        {
            sprite13->SetSize({ player->Exp * 13,24 });
        }
        else if (player->Level == 3)
        {
            sprite13->SetSize({ player->Exp * 9,24 });
        }
        else if (player->Level == 4)
        {
            sprite13->SetSize({ player->Exp * 6,24 });
        }
        else
        {
            sprite13->SetSize({ player->Exp * 5,24 });
        }

        //レベルバー赤
        if (player->Level2 == 1)
        {
            sprite29->SetSize({ player->Exp_2 * 26,24 });
        }
        else if (player->Level2 == 2)
        {
            sprite29->SetSize({ player->Exp_2 * 13,24 });
        }
        else if (player->Level2 == 3)
        {
            sprite29->SetSize({ player->Exp_2 * 9,24 });
        }
        else if (player->Level2 == 4)
        {
            sprite29->SetSize({ player->Exp_2 * 6,24 });
        }
        else
        {
            sprite29->SetSize({ player->Exp_2 * 5,24 });
        }

      
     


        sprite13->SpriteTransVertexBuffer();
        sprite29->SpriteTransVertexBuffer();



        sprite32->SpriteTransVertexBuffer();
        sprite33->SpriteTransVertexBuffer();
        sprite34->SpriteTransVertexBuffer();
        sprite35->SpriteTransVertexBuffer();
        sprite36->SpriteTransVertexBuffer();
        sprite37->SpriteTransVertexBuffer();
        sprite38->SpriteTransVertexBuffer();
        sprite39->SpriteTransVertexBuffer();





        if (item->ARM1.Effect2 != 0&&item->SelectTime!=1)
        {
            sprite32->SpriteDraw();
            sprite32->SetPosition({ 380+(50*(item->ARM1.UI-1)),45,0});
            sprite32->SetSize({ 45,45 });
        }
        else
        {
            sprite32->SetPosition({ 640,260,0 });
            sprite32->SetSize({ 200,200 });
        }

        if (item->LEG1.Effect2 != 0 && item->SelectTime != 1)
        {
            sprite33->SpriteDraw();
            sprite33->SetPosition({ 380+(50*(item->LEG1.UI-1)),45,0});
            sprite33->SetSize({ 45,45 });
        }
        else
        {
            sprite33->SetPosition({ 640,260,0 });
            sprite33->SetSize({ 200,200 });
        }

        if(item->STU1.Effect2 != 0 && item->SelectTime != 1)
        {
            sprite34->SpriteDraw();
            sprite34->SetPosition({ 380+(50*(item->STU1.UI-1)),45,0});
            sprite34->SetSize({ 45,45 });
        }
        else
        {
            sprite34->SetPosition({ 640,260,0 });
            sprite34->SetSize({ 200,200 });
        }

        if (item->BAR1.Flag == 1 && item->SelectTime != 1)
        {
            sprite35->SpriteDraw();
            sprite35->SetPosition({ 380+(50*(item->BAR1.UI-1)),45,0});
            sprite35->SetSize({ 45,45 });
        }
        else
        {
            sprite35->SetPosition({ 640,260,0 });
            sprite35->SetSize({ 200,200 });
        }

        if (item->ATT1.Flag == 1 && item->SelectTime != 1)
        {
            sprite36->SpriteDraw();
            sprite36->SetPosition({ 380 + (50 * (item->ATT1.UI - 1)),45,0 });
            sprite36->SetSize({ 45,45 });
        }
        else
        {
            sprite36->SetPosition({ 640,260,0 });
            sprite36->SetSize({ 200,200 });
        }

        if (item->STR1.Flag == 1 && item->SelectTime != 1)
        {
            sprite37->SpriteDraw();
            sprite37->SetPosition({ 380 + (50 * (item->STR1.UI - 1)),45,0 });
            sprite37->SetSize({ 45,45 });
        }
        else
        {
            sprite37->SetPosition({ 640,260,0 });
            sprite37->SetSize({ 200,200 });
        }

        if (item->ROLL1.Flag == 1 && item->SelectTime != 1)
        {
            sprite38->SpriteDraw();
            sprite38->SetPosition({ 380 + (50 * (item->ROLL1.UI - 1)),45,0 });
            sprite38->SetSize({ 45,45 });
        }
        else
        {
            sprite38->SetPosition({ 640,260,0 });
            sprite38->SetSize({ 200,200 });
        }

        if (item->DESTROY_.Flag == 1 && item->SelectTime != 1)
        {
            sprite39->SpriteDraw();
            sprite39->SetPosition({ 380 + (50 * (item->DESTROY_.UI - 1)),45,0 });
            sprite39->SetSize({ 45,45 });
        }
        else
        {
            sprite39->SetPosition({ 640,260,0 });
            sprite39->SetSize({ 200,200 });
        }

        //ABIllity選択時UI
       


        sprite30->SetPosition({ player->cursor_x,player->cursor_y,0 });
        if (item->SelectTime == 1) 
        {
            sprite31->SpriteDraw();
            sprite30->SpriteDraw();

           
            if (item->NowAbility == 1)
            {
                sprite32->SpriteDraw();
                sprite44->SpriteDraw();

            }
            else  if (item->NowAbility == 2)
            {
                sprite33->SpriteDraw();
                sprite45->SpriteDraw();

            }
            else  if (item->NowAbility == 3)
            {
                sprite34->SpriteDraw();
                sprite46->SpriteDraw();

            }
            else  if (item->NowAbility == 4)
            {
                sprite35->SpriteDraw();
                sprite47->SpriteDraw();

            }
            else  if (item->NowAbility == 5)
            {
                sprite36->SpriteDraw();
                sprite48->SpriteDraw();

            }
            else  if (item->NowAbility == 6)
            {
                sprite37->SpriteDraw();
                sprite49->SpriteDraw();

            }
            else  if (item->NowAbility == 7)
            {
                sprite38->SpriteDraw();
                sprite50->SpriteDraw();

            }
            else  if (item->NowAbility == 8)
            {
                sprite39->SpriteDraw();
                sprite51->SpriteDraw();

            }
        }

        if (item->ARM1.Effect2 != 0)
        {
          //  sprite32->SpriteDraw();
        }

        //一番前
        sprite43->SpriteDraw();
     
        debugtext->DrawAll();//的カウント

        debugtext2->DrawAll();//的カウント

        debugtext3->DrawAll();//的カウント



        //postEffect->Draw(dxCommon->GetCmdList());
        //メイン
      
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
    //delete spriteCommon2;
    delete postEffect;

    delete sprite;

    for (int i = 0; i < ENEMY1_NUM; i++)
    {
        delete sprite5[i];
    }

    for (int i = 0; i < REDP_NUM; i++)
    {
        delete redpart[i];
    }

    for (int i = 0; i < BLUEP_NUM; i++)
    {
        delete bluepart[i];
    }


    //テキスト解放
    delete debugtext;

    audio->Finalize();
    delete audio;

    return 0;
}
