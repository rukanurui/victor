#include "GamePad.h"

void GamePad::Update()
{
    XInputGetState(0, &state);

    iPad_left = 0, iPad_right = 0, iPad_up = 0, iPad_down = 0;
    iPad_leftshoulder = 0, iPad_rightshoulder = 0;
    iPad_A = 0, iPad_B = 0, iPad_X = 0, iPad_Y = 0;

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



 //   XInputSetState(0, &vibration);
}

void GamePad::PreUpdate()
{
    Old_iPad_left = iPad_left, Old_iPad_right = iPad_right, iOld_Pad_up = iPad_up, Old_iPad_down = iPad_down;
    Old_iPad_leftshoulder = iPad_leftshoulder, Old_iPad_rightshoulder = iPad_rightshoulder;
    Old_iPad_A = iPad_A, Old_iPad_B = iPad_B, Old_iPad_X = iPad_X, Old_iPad_Y = iPad_Y;
}
