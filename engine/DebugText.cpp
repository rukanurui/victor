#include "DebugText.h"


void DebugText::Initialize(SpriteCommon* spriteCommon, UINT texnumber)
{
    assert(spriteCommon);
    spriteCommona = spriteCommon;

    // �S�ẴX�v���C�g�f�[�^�ɂ���
    for (int i = 0; i < _countof(spritesa); i++)
    {
        // �X�v���C�g�𐶐�����
        spritesa[i] = Sprite::Create(spriteCommona, texnumber, { 0,0 });
    }
}

void DebugText::Print(const std::string& text, float x, float y, float scale)
{
    // �S�Ă̕����ɂ���
    for (int i = 0; i < text.size(); i++)
    {
        // �ő啶��������
        if (spriteIndexa >= maxCharCount) {
            break;
        }

        // 1�������o��(��ASCII�R�[�h�ł������藧���Ȃ�)
        const unsigned char& character = text[i];

        // ASCII�R�[�h��2�i����΂����ԍ����v�Z
        int fontIndex = character - 32;
        if (character >= 0x7f) {
            fontIndex = 0;
        }

        int fontIndexY = fontIndex / fontLineCount;
        int fontIndexX = fontIndex % fontLineCount;

        // ���W�v�Z

        spritesa[spriteIndexa]->SetPosition({ x + fontWidth * scale * i, y, 0 });
        spritesa[spriteIndexa]->SetTexLeftTop({ (float)fontIndexX * fontWidth, (float)fontIndexY * fontHeight });
        spritesa[spriteIndexa]->SetTexSize({ fontWidth, fontHeight });
        spritesa[spriteIndexa]->SetSize({ fontWidth * scale, fontHeight * scale });
        // ���_�o�b�t�@�]��
        spritesa[spriteIndexa]->TransferVertexBuffer();
        // �X�V
        spritesa[spriteIndexa]->Update();

        // �������P�i�߂�
        spriteIndexa++;
    }
}

// �܂Ƃ߂ĕ`��
void DebugText::DrawAll()
{
    // �S�Ă̕����̃X�v���C�g�ɂ���
    for (int i = 0; i < spriteIndexa; i++)
    {
        // �X�v���C�g�`��
        spritesa[spriteIndexa]->Draw();
    }

    spriteIndexa = 0;
}