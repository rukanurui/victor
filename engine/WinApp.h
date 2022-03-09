#pragma once

#include <windows.h>



//WindowsAPI
class WinApp
{
public://�ÓI�����o�֐�
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: //�����o�֐�
	//������
	void Initialize();
	//�X�V
	void Update();
	//�I��
	void Finalize();
	//getter
	HWND GetHwnd() { return hwnd; }
	//
	HINSTANCE GetHInstance() { return w.hInstance; }
	//���b�Z�[�W�̏���
	bool ProcessMessage();
private:
	//�E�B���h�E�n���h��
	HWND hwnd = nullptr;

	//�E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX w{};
public://�萔
	//����
	static const int window_width = 1280;
	//�c��
	static const int window_height = 720;
};

