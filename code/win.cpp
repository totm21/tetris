
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
    this->wndclass.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));					//背景颜色画刷
	this->wndclass.hCursor = LoadCursor(NULL, IDC_HAND);								//鼠标光标类型,手：DC_HAND
	this->wndclass.hIcon = LoadIcon(NULL, IDI_ERROR);									//图标
	this->wndclass.lpszClassName = TEXT("tetris");										//窗口类型名
	this->wndclass.style = CS_HREDRAW | CS_VREDRAW;										//窗口类的风格
}

Win::Win(HINSTANCE hInstance)
{
	this->wndclass = { 0 };
	this->wndclass.hInstance = hInstance;												//句柄
	this->wndclass.lpfnWndProc = WindowProc;							
	this->wndclass.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));					//背景颜色画刷
	this->wndclass.hCursor = LoadCursor(NULL, IDC_HAND);								//鼠标光标类型,手：DC_HAND
	this->wndclass.hIcon = LoadIcon(NULL, IDI_ERROR);									//图标
	this->wndclass.lpszClassName = TEXT("tetris");										//窗口类型名
	this->wndclass.style = CS_HREDRAW | CS_VREDRAW;										//窗口类的风格
}

void Win::register_class()
{
	RegisterClass(&this->wndclass);
	return ;
}

void Win::create_window(std::string name,int location_x,int location_y,int width,int high)
{
	this->hwnd=CreateWindow(
		TEXT("tetris"),													 				//窗口类型名
		//stringToLPCWSTR(name),					                            		//窗口标题
		TEXT("俄罗斯方块"),
		WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,                  			//窗口的风格
		location_x, location_y,                                                         //窗口左上角坐标（像素）
		width, high,                                                               		//窗口的宽和高
		NULL,                                                                   		//父窗口句柄
		NULL,                                                                   		//菜单句柄
		this->wndclass.hInstance,						                                //应用程序实例句柄
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
	while (GetMessage(&this->msg, NULL, 0, 0))//GetMessage从调用线程的消息队列中取得一个消息并放于msg
	{
		//将虚拟键消息转换为字符消息
		TranslateMessage(&this->msg);
		//将消息分发给窗口处理函数
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
		case WM_CLOSE://窗口关闭消息
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY://窗口销毁消息
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//默认的窗口处理函数
}