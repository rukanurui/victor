#include <Windows.h>

#pragma once
class WinApp
{
public://�����o�ϐ�
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	//getter
	HWND GetHwnd() { return hwnd; }
	//getter
	HINSTANCE GetHInstance() { return w.hInstance;}
	
private:
	//�E�C���h�E�n���h��
	HWND hwnd = nullptr;
	//�E�C���h�E�N���X�̐ݒ�
	WNDCLASSEX w{};
public: //�����o�֐�
//������
	void Initialize();
	//�X�V
	void Update();
	//�I��
	void Finalize();
	//���b�Z�[�W�̏���
	bool ProcessMessage();
public://�萔
	// �E�B���h�E�T�C�Y
	static const int window_width = 1280;  // ����
	static const int window_height = 720;  // �c��
};

