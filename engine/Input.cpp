#include "Input.h"


//#include<wrl.h>
//#include<dinput.h>
//using namespace Microsoft::WRL;

//#define DIRECTINPUT_VERSION 0x0800//DirectInput�̃o�[�W�����w��

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")


void Input::Intialize(WinApp* winApp)
{
    HRESULT result;


    //DirectInput�̃C���X�^���X����
    //ComPtr<IDirectInput8> dinput = nullptr;
    //�؂�Ă���App�̃C���X�^���X���L�^
    this->winApp = winApp;

    result = DirectInput8Create(
        winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
    //�L�[�{�[�h����
    result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
    //���̓f�[�^�̌`���Z�b�g
    result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);
    //�r�����䃌�x���̃Z�b�g
    result = devkeyboard->SetCooperativeLevel(
        winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);



    //�Q�[���p�b�h
    //result=dinput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback,
    //   NULL, DIEDFL_ATTACHEDONLY);


}

/*
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
    HRESULT hr;

    hr =dinput->CreateDevice(pdidInstance->guidInstance, &Input::gamepad, NULL);

    if (FAILED(hr)) return DIENUM_CONTINUE;

    return DIENUM_STOP;
}
*/
void Input::Update()
{
    HRESULT result;

    //�O��̃L�[���͂�ۑ�
   // memcpy(oldkey, key, sizeof(key));

    //�L�[�{�[�h���̎擾
    result = devkeyboard->Acquire();
    //�S�L�[�̓��͏����擾
   // BYTE key[256] = {};
    memcpy(oldkey, key, sizeof(key));

    result = devkeyboard->GetDeviceState(sizeof(key), key);

}

bool Input::PushKey(BYTE keyNumber)
{
    //�w��L�[�������Ă����true��Ԃ�
    if (key[keyNumber])
    {
        return true;
    }

    //�����łȂ����false��Ԃ�
    return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
    //�O�񉟂��Ă��Ȃ��A���񉟂��Ă����true��Ԃ�
    if (key[keyNumber] && !oldkey[keyNumber])
    {
        return true;
    }

    //�����łȂ��ꍇ�Afalse��Ԃ�
    return false;
}

void Input::PadUpdate()
{
    XINPUT_STATE state;
    XInputGetState(0, &state);


    int iPad_left = 0, iPad_right = 0, iPad_up = 0, iPad_down = 0;
    int iPad_leftshoulder = 0, iPad_rightshoulder = 0;
    int iPad_A = 0, iPad_B = 0, iPad_X = 0, iPad_Y = 0;

    XINPUT_VIBRATION vibration;

    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) iPad_left = 1;//�Q�[���p�b�h�\���L�[��
    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) iPad_right = 1;//�Q�[���p�b�h�\���L�[�E
    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) iPad_up = 1;//�Q�[���p�b�h�\���L�[��
    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) iPad_down = 1;//�Q�[���p�b�h�\���L�[��
    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) iPad_leftshoulder = 1;//�Q�[���p�b�hL
    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) iPad_rightshoulder = 1;//�Q�[���p�b�hR
    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) iPad_A = 1;//�Q�[���p�b�hA
    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) iPad_B = 1;//�Q�[���p�b�hB
    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) iPad_X = 1;//�Q�[���p�b�hX
    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) iPad_Y = 1;//�Q�[���p�b�hY
    //�Q�[���p�b�h�A�i���O�X�e�B�b�N�̃f�b�h�]�[������
    if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
        (state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
    {
        state.Gamepad.sThumbLX = 0;
        state.Gamepad.sThumbLY = 0;
    }


    vibration.wLeftMotorSpeed = 0;
    vibration.wRightMotorSpeed = 0;
    XInputSetState(0, &vibration);


}
