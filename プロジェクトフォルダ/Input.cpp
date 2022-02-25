#include "Input.h"



#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
using namespace Microsoft::WRL;


void Input::Initialize(WinApp* winApp)
{

    HRESULT result;

    this->winApp = winApp;

    result = DirectInput8Create(
        winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);

    //ComPtr<IDirectInputDevice8> devkeyboard = nullptr;
    result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
    //���̓f�[�^�`���̃Z�b�g
    result = devkeyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��
    //�r�����䃌�x���̃Z�b�g
    result = devkeyboard->SetCooperativeLevel(
        winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Input::Update()
{

    HRESULT result;

    //�O��̃L�[���͂�ۑ�
    memcpy(oldkey, key, sizeof(key));

    //�L�[�{�[�h���̎擾�J�n
    result = devkeyboard->Acquire();
    
    result = devkeyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNumber)
{
    //�w��L�[�������Ă����true��Ԃ�
    if (key[keyNumber]) {
        return true;
    }
    //�����łȂ����false
    return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
    //�O������ĂȂ��A���񉟂��Ă���
    if (oldkey[keyNumber]==0&&key[keyNumber]==1) {
        return true;
    }
    //�����łȂ����false
    return false;
}

