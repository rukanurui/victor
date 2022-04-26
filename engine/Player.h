#pragma once
//#pragma comment (lib, "xinput.lib")
//#include <xinput.h>
#include <DirectXMath.h>
#include "GamePad.h"
#include"Item.h"
#include"Input.h"


class Player
{
private:

public:
    //変数

   //センター座標
    float Central_x = 640;
    float Central_y = 360;

    //回転する円の大きさ
    float Player_radius = 100;
    //回転するための値
    float timer = 0;
    //切り替え変数
    int Switch = 0;

    //赤球座標
    float Player_RedX = 0;
    float Player_RedY = 0;

    float Red_R = 20;
    float Blue_R = 20;

    //蒼球座標
    float Player_BlueX = 0;
    float Player_BlueY = 0;

    //球のフラグ関連
    float Red_Lv = 1;
    float Blue_Lv = 1;

    int Radius = 100;

    int HP = 3;
    int invincibleTime = 0;
    int invincibleFlag = 0;

    float Map_X = 0;
    float Map_Y = 0;

    float Back_X = 0;
    float Back_Y = 0;


    float Effect_;
    float Effect_2;
    float Effect_3;
    float Effect_4;


    int scene_=0;

    int WrongFlag = 0;//間違えフラッグ
    int WrongTimer = 0;//間違え拘束時間

    int invincible_armFlag = 0;
    int invincible_armTime = 0;

    int RuleFlag = 0;

    int Switch_cool = 0;
    float cool_time = 0;

    //経験値
    float Exp = 0;
    int Level = 1;
    int Level_demo = 1;

    float Exp_2 = 0;
    int Level2 = 1;
    int Level_demo2 = 1;


    //選択成長要素


    const int EXP_NUM = 300;

    typedef struct Exp
    {
        float X = 0;//ｘ座標
        float Y = 0;//ｙ座標

        float R = 0;//半径
        int Flag = 0;//フラグ
        int Time = 0;
        int X_rand = 0;
        int Y_rand = 0;
       
    }EXP;

    EXP Exp1[300];

    //特殊能力変数


  //  Item* item= nullptr;

    //トリガー処理のための変数
    int Old_iPad_left = 0, Old_iPad_right = 0, iOld_Pad_up = 0, Old_iPad_down = 0;
    int Old_iPad_leftshoulder = 0, Old_iPad_rightshoulder = 0;
    int Old_iPad_A = 0, Old_iPad_B = 0, Old_iPad_X = 0, Old_iPad_Y = 0;

    int select_;
    int deci_;

    int Decision;

    //選択時カーソル座標
    float cursor_x = 640;
    float cursor_y = 390;

    int UI_Flag = 0;

    int TitleRoll = 0;

    //関数
    void Controll();//位置反転
    void Initialize();//初期化
    void Shake();//間違えたときの管理
    void Wrong();//間違えたときの内容処理
    void invincible();//無敵中処理
    void Exp2();//Exp処理
    void LevelUp();//レベルアップ能力


    void setter(float Effect) { Effect_ = Effect; }

    void setter2(float Effect2) { Effect_2 = Effect2; }

    void setter3(float Effect3) { Effect_3= Effect3; }
    void setter4(float Effect4) { Effect_4 = Effect4; }

    void setter_scene(int scene) { scene_ = scene; }
    void setter_select(int select) { select_ =select ; }
    void setter_deci(int deci) { deci_ = deci; }

    void Map_Setter(float X, float Y) { Map_X = X; Map_Y = Y; }
};

