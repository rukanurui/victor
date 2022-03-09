#pragma once

#include <Windows.h>
#include <xaudio2.h>
#include <wrl.h>
#include <cstdint>
#include <map>
#include<string>

class Audio
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
    template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
    struct ChunkHeader
    {
        char id[4];
        int32_t  size;
    };

    struct RiffHeader
    {
        ChunkHeader chunk;
        char type[4];

    };

    struct FormatChunk
    {
        ChunkHeader chunk;
        WAVEFORMATEX fmt;
    };

    struct SoundData
    {
        WAVEFORMATEX wfex;

        BYTE* pBuffer;

        unsigned int bufferSize;


    };

public : //�����o�֐�

    void SoundLoadWave(const char* filename);

    void SoundUnload(SoundData* soundData);

    void SoundPlayWave(std::string filename);
    void SoundPlayWaveLoop(std::string filename);

    //������
    void Initialize();

    void Finalize();
private://�����o�ϐ�

    ComPtr<IXAudio2> xAudio2_;
    IXAudio2MasteringVoice* masterVoice;

    std::map<std::string, SoundData> soudDatas_;
};

