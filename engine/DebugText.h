#pragma once
#include "DebugText.h"
#include "Sprite.h"
#include <string>
#include <Windows.h>

class DebugText
{
public: // �萔�̐錾    
    static const int maxCharCount = 256;    // �ő啶����
    static const int fontWidth = 9;         // �t�H���g�摜��1�������̉���
    static const int fontHeight = 18;       // �t�H���g�摜��1�������̏c��
    static const int fontLineCount = 14;    // �t�H���g�摜��1�s���̕�����

public: // �����o�֐�
    void Initialize(SpriteCommon* spriteCommon, UINT texnumber);

    void Print(const std::string& text, float x, float y, float scale = 1.0f);

    void DrawAll();

private: // �����o�ϐ�   
    SpriteCommon* spriteCommona = nullptr;
    // �X�v���C�g�f�[�^�̔z��
    Sprite* spritesa[maxCharCount];
    // �X�v���C�g�f�[�^�z��̓Y�����ԍ�
    int spriteIndexa = 0;
};