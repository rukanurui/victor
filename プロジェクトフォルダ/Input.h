#include <Windows.h>
#include <wrl.h>
#include "WinApp.h"

#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��
#include <dinput.h>
#pragma once
class Input
{
public:
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
public: //�����o�֐�
	//������
	void Initialize(WinApp* winApp);
	//�X�V
	void Update();

/// <summary>
/// �L�[�̉������`�F�b�N
/// </summary>
/// <param name = "keyNumber">�L�[�ԍ�(DIK_0�Ȃ�)</param>
/// <returns>������Ă��邩</returns>
	bool PushKey(BYTE keyNumber);

/// <summary>
/// �L�[�̃g���K�[���`�F�b�N
/// </summary>
/// <param name = "keyNumber">�L�[�ԍ�(DIK_0�Ȃ�)</param>
/// <returns>�g���K�[��</returns>
	bool TriggerKey(BYTE keyNumber);

private: //�����o�ϐ�
	//�L�[�{�[�h�̃f�o�C�X
	ComPtr<IDirectInputDevice8> devkeyboard;
	//�S�L�[�̓��͏����擾����
	BYTE key[256] = {};
	//�O��̑S�L�[�̓��͏����擾����
	BYTE oldkey[256] = {};
	//�C���X�^���X����
	ComPtr<IDirectInput8> dinput = nullptr;
	//WindowsAPI
	WinApp* winApp = nullptr;
};

