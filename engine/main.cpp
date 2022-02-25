
#include <vector>
#include <string>
#include <fstream>

#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定

#include "Input.h"

#include "WinApp.h"
#include "DirectXCommon.h"
#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")

#include "Object3d.h"
#include "model.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "DebugText.h"



using namespace DirectX;
using namespace Microsoft::WRL;







// チャンクヘッダ
struct ChunkHeader
{
    char id[4]; // チャンク毎のID
    int32_t size;  // チャンクサイズ
};

// RIFFヘッダチャンク
struct RiffHeader
{
    ChunkHeader chunk;   // "RIFF"
    char type[4]; // "WAVE"
};

// FMTチャンク
struct FormatChunk
{
    ChunkHeader chunk; // "fmt "
    WAVEFORMATEX fmt; // 波形フォーマット
};

class XAudio2VoiceCallback : public IXAudio2VoiceCallback
{
public:
    // ボイス処理パスの開始時
    STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired) {};
    // ボイス処理パスの終了時
    STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {};
    // バッファストリームの再生が終了した時
    STDMETHOD_(void, OnStreamEnd) (THIS) {};
    // バッファの使用開始時
    STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) {};
    // バッファの末尾に達した時
    STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext) {};
    // 再生がループ位置に達した時
    STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {};
    // ボイスの実行エラー時
    STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {};
};

// 音声データ
struct SoundData
{
    // 波形フォーマット
    WAVEFORMATEX wfex;
    // バッファの先頭アドレス
    BYTE* pBuffer;
    // バッファのサイズ
    unsigned int bufferSize;
};

// 音声読み込み
SoundData SoundLoadWave(const char* filename)
{
    // ファイル入力ストリームのインスタンス
    std::ifstream file;
    // .wavファイルをバイナリモードで開く
    file.open(filename, std::ios_base::binary);
    // ファイルオープン失敗を検出する
    assert(file.is_open());

    // RIFFヘッダーの読み込み
    RiffHeader riff;
    file.read((char*)&riff, sizeof(riff));
    // ファイルがRIFFかチェック
    if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
        assert(0);
    }
    // タイプがWAVEかチェック
    if (strncmp(riff.type, "WAVE", 4) != 0) {
        assert(0);
    }

    // Formatチャンクの読み込み
    FormatChunk format = {};
    // チャンクヘッダーの確認
    file.read((char*)&format, sizeof(ChunkHeader));
    if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
        assert(0);
    }
    // チャンク本体の読み込み
    assert(format.chunk.size <= sizeof(format.fmt));
    file.read((char*)&format.fmt, format.chunk.size);

    // Dataチャンクの読み込み
    ChunkHeader data;
    file.read((char*)&data, sizeof(data));
    // JUNKチャンクを検出した場合
    if (strncmp(data.id, "JUNK ", 4) == 0) {
        // 読み取り位置をJUNKチャンクの終わりまで進める
        file.seekg(data.size, std::ios_base::cur);
        // 再読み込み
        file.read((char*)&data, sizeof(data));
    }

    if (strncmp(data.id, "data ", 4) != 0) {
        assert(0);
    }

    // Dataチャンクのデータ部（波形データ）の読み込み
    char* pBuffer = new char[data.size];
    file.read(pBuffer, data.size);

    // Waveファイルを閉じる
    file.close();

    // returnする為の音声データ
    SoundData soundData = {};

    soundData.wfex = format.fmt;
    soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
    soundData.bufferSize = data.size;

    return soundData;
}

// 音声データ解放
void SoundUnload(SoundData* soundData)
{
    // バッファのメモリを解放
    delete[] soundData->pBuffer;

    soundData->pBuffer = 0;
    soundData->bufferSize = 0;
    soundData->wfex = {};
}

// 音声再生
void SoundPlayWave(IXAudio2* xAudio2, const SoundData& soundData) {

    HRESULT result;

    // 波形フォーマットを元にSourceVoiceの生成
    IXAudio2SourceVoice* pSourceVoice = nullptr;
    result = xAudio2->CreateSourceVoice(&pSourceVoice, &soundData.wfex);
    assert(SUCCEEDED(result));

    // 再生する波形データの設定
    XAUDIO2_BUFFER buf{};
    buf.pAudioData = soundData.pBuffer;
    buf.AudioBytes = soundData.bufferSize;
    buf.Flags = XAUDIO2_END_OF_STREAM;

    // 波形データの再生
    result = pSourceVoice->SubmitSourceBuffer(&buf);
    result = pSourceVoice->Start();
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

    //ポインタ置き場
    Input* input = nullptr;
    WinApp* winApp = nullptr;
    DirectXCommon* dxCommon = nullptr;

    HRESULT result;

#pragma region WindowsAPI初期化
    winApp = new WinApp();
    winApp->Initialize();
#pragma endregion WindowsAPI初期化

#pragma region DirectX初期化処理
    // DirectX初期化処理　ここから
    dxCommon = new DirectXCommon();
    dxCommon->Initialize(winApp);


    //Object3d静的初期化
    Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
    //OBJからモデルデータを読み込む
    model* Model = model::LoadFromOBJ("triangle_mat");
    //3dオブジェクト生成
    Object3d* object3d = Object3d::Create();
    //モデル紐づけ
    object3d->SetModel(Model);

    // スプライト共通部分の初期化
    SpriteCommon* spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->GetDevice(),dxCommon->GetCommandList(),winApp->window_width,winApp->window_height);



    //入力の初期化
    input = new Input();
    input->Initialize(winApp);

    ComPtr<IXAudio2> xAudio2;
    IXAudio2MasteringVoice* masterVoice;
    XAudio2VoiceCallback voiceCallback;

    // XAudioエンジンのインスタンスを生成
    result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
    assert(SUCCEEDED(result));

    // マスターボイスを生成
    result = xAudio2->CreateMasteringVoice(&masterVoice);
    assert(SUCCEEDED(result));

    // 音声読み込み
    SoundData soundData1 = SoundLoadWave("Resources/Alarm01.wav");

    // 音声再生
    //SoundPlayWave(xAudio2.Get(), soundData1);

    // DirectX初期化処理　ここまで
#pragma endregion DirectX初期化処理

#pragma region 描画初期化処理
  

    //// スプライト共通データ生成
    //spriteCommon = SpriteCommonCreate(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
    // スプライト共通テクスチャ読み込み
    spriteCommon->LoadTexture(0, L"Resources/texture.png");
    spriteCommon->LoadTexture(1, L"Resources/house.png");

    std::vector<Sprite*> sprites;

   /* Sprite* sprite = Sprite::Create(spriteCommon, 0);*/
   

    // スプライトの生成
    for (int i = 0; i < 20; i++)
    {
        int texNumber = 0;
        Sprite* sprite = Sprite::Create(spriteCommon,texNumber, { 0,0 }, false, false);

        // スプライトの座標変更
        sprite->SetPosition({ (float)(rand() % 1280) ,(float)(rand() % 720) ,0 });
        sprite->SetRotation({ (float)(rand() % 360) });
        sprite->SetSize({ (float)(rand() % 400), (float)(rand() % 100) });
        //sprites[i].isInvisible = true;
  
        // 頂点バッファに反映
        sprite->TransferVertexBuffer();

        sprites.push_back(sprite);
        sprite->SetPosition({ 500,300,0 });
    }

    // デバッグテキスト
    DebugText* debugText = nullptr;
    debugText = new DebugText();

    // デバッグテキスト用のテクスチャ番号を指定
    const int debugTextTexNumber = 2;
    // デバッグテキスト用のテクスチャ読み込み
    spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
    // デバッグテキスト初期化
    debugText->Initialize(spriteCommon, debugTextTexNumber);

  
#pragma endregion 描画初期化処理

    int counter = 0; // アニメーションの経過時間カウンター

    while (true)  // ゲームループ
    {
#pragma region ウィンドウメッセージ処理
        if (winApp->ProcessMessage())
        {
            break;
        }

#pragma endregion ウィンドウメッセージ処理

#pragma region DirectX毎フレーム処理
        // DirectX毎フレーム処理　ここから

        //入力の更新
        input->Update();

        //object3d更新
        object3d->Update();

        //スプライト更新
        for (auto& sprite : sprites) {
            sprite->Update();
        }

        const int cycle = 540; // 繰り返しの周期
        counter++;
        counter %= cycle; // 周期を超えたら0に戻る
        float scale = (float)counter / cycle; // [0,1]の数値

        scale *= 360.0f;


        if (input->TriggerKey(DIK_0)) // 数字の0キーが押されていたら
        {
            OutputDebugStringA("Hit 0\n");  // 出力ウィンドウに「Hit 0」と表示
        }

        float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

        if (input->TriggerKey(DIK_SPACE))     // スペースキーが押されていたら
        {
            // 画面クリアカラーの数値を書き換える
            clearColor[1] = 1.0f;
        }

        
        // 各オブジェクトの半径
        const float radius1 = 3.0f;
        const float radisu2 = 3.0f;
        // X座標,Y座標を指定して表示
        debugText->Print("Hello,DirectX!!", 200, 100);
        // X座標,Y座標,縮尺を指定して表示
        debugText->Print("Nihon Kogakuin", 200, 200, 2.0f);

        //sprite.rotation = 45;
        //sprite.position = {1280/2, 720/2, 0};
        //sprite.color = {0, 0, 1, 1};


        // DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理

#pragma region グラフィックスコマンド

        //描画前処理
        dxCommon->PreDraw();

        //3dオブジェクト描画前処理
        Object3d::PreDraw(dxCommon->GetCommandList());

        //3dオブジェクトの描画
        object3d->Draw();

        ///<summary>
        ///ここに3dオブジェクトの描画処理を追加できる
        /// </summary>

        //3dオブジェクトの描画後処理
        Object3d::PostDraw();

        // ４．描画コマンドここから
       

        // スプライト共通コマンド
        spriteCommon->PreDraw();

        // スプライト描画

        for (auto& sprite : sprites) {
            sprite->Draw();
        }

        // デバッグテキスト描画
        debugText->DrawAll();

        // ４．描画コマンドここまで
         //描画後処理
        dxCommon->PostDraw();

    }
        //解放処理
        delete input;
        delete dxCommon;

        //3dオブジェクト解放
        delete object3d;
        //3dモデル解放
        delete Model;

        //スプライト解放
        for (auto& sprite : sprites) {
            delete sprite;
        }
        sprites.clear();
        delete spriteCommon;

        //デバッグテキスト解放
        delete debugText;

        // XAudio2解放
        xAudio2.Reset();
        // 音声データ解放
        SoundUnload(&soundData1);

        winApp->Finalize();
        delete winApp;
        winApp = nullptr;
#pragma endregion WindowsAPI後始末

        return 0;
 }