
#include"win.h"

win::win()
{
    this->wndclass.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));					//������ɫ��ˢ
	this->wndclass.hCursor = LoadCursor(NULL, IDC_HAND);								//���������,�֣�DC_HAND
	this->wndclass.hIcon = LoadIcon(NULL, IDI_ERROR);									//ͼ��
	this->wndclass.lpszClassName = TEXT("tetris");										//����������
	this->wndclass.style = CS_HREDRAW | CS_VREDRAW;										//������ķ��
}