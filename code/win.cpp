
#include"Win.h"

LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}


Win::Win()
{
    this->wndclass.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));					//������ɫ��ˢ
	this->wndclass.hCursor = LoadCursor(NULL, IDC_HAND);								//���������,�֣�DC_HAND
	this->wndclass.hIcon = LoadIcon(NULL, IDI_ERROR);									//ͼ��
	this->wndclass.lpszClassName = TEXT("tetris");										//����������
	this->wndclass.style = CS_HREDRAW | CS_VREDRAW;										//������ķ��
}

Win::Win(HINSTANCE hInstance)
{
	this->wndclass = { 0 };
	this->wndclass.hInstance = hInstance;												//���
	this->wndclass.lpfnWndProc = WindowProc;							
	this->wndclass.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));					//������ɫ��ˢ
	this->wndclass.hCursor = LoadCursor(NULL, IDC_HAND);								//���������,�֣�DC_HAND
	this->wndclass.hIcon = LoadIcon(NULL, IDI_ERROR);									//ͼ��
	this->wndclass.lpszClassName = TEXT("tetris");										//����������
	this->wndclass.style = CS_HREDRAW | CS_VREDRAW;										//������ķ��
}

void Win::register_class()
{
	RegisterClass(&this->wndclass);
	return ;
}

void Win::create_window(std::string name,int location_x,int location_y,int width,int high)
{
	this->hwnd=CreateWindow(
		TEXT("tetris"),													 				//����������
		//stringToLPCWSTR(name),					                            		//���ڱ���
		TEXT("����˹����"),
		WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,                  			//���ڵķ��
		location_x, location_y,                                                         //�������Ͻ����꣨���أ�
		width, high,                                                               		//���ڵĿ�͸�
		NULL,                                                                   		//�����ھ��
		NULL,                                                                   		//�˵����
		this->wndclass.hInstance,						                                //Ӧ�ó���ʵ�����
		NULL 
	);
	return ;
}

void Win::show_window()
{
	ShowWindow(this->hwnd, SW_SHOW);
	return ;
}      

void Win::updata_window()
{
	UpdateWindow(this->hwnd);
	return ;
}      

void Win::loop_message()
{
	while (GetMessage(&this->msg, NULL, 0, 0))//GetMessage�ӵ����̵߳���Ϣ������ȡ��һ����Ϣ������msg
	{
		//���������Ϣת��Ϊ�ַ���Ϣ
		TranslateMessage(&this->msg);
		//����Ϣ�ַ������ڴ�����
		DispatchMessage(&this->msg);
	}
	return ;
}

void Win::start_win(std::string name,int location_x,int location_y,int width,int high)
{
	this->register_class();
	this->create_window(name,location_x,location_y,width,high);
	this->show_window();
	this->updata_window();
	this->loop_message();
	return ;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	switch (uMsg)
	{
		case WM_CLOSE://���ڹر���Ϣ
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY://����������Ϣ
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//Ĭ�ϵĴ��ڴ�����
}