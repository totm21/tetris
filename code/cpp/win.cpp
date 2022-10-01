
#include"Win.h"

bool g_bNcLButtonDown = false;
POINT g_kLastMousePos;
POINT g_kCurMousePos;
RECT g_kCurWindowRect;

Win* win=new Win();

Win::Win()
{
	this->wndclass = { 0 };
	this->wndclass.lpfnWndProc = WindowProc;
    this->wndclass.hbrBackground = CreateSolidBrush(RGB(255,255,255));						//背景颜色画刷
	this->wndclass.hCursor = LoadCursor(NULL, IDC_HAND);								//鼠标光标类型,手：DC_HAND
	this->wndclass.lpszClassName = TEXT("tetris");										//窗口类型名
	this->wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_OWNDC;				//窗口类的风格
	this->wndclass.cbClsExtra = 0;
	this->wndclass.cbWndExtra = 0;
	this->wndclass.lpszMenuName = nullptr;
}

Win::Win(HINSTANCE hInstance)
{
	this->wndclass = { 0 };
	this->wndclass.hInstance = hInstance;												//句柄
	this->wndclass.lpfnWndProc = WindowProc;							
	this->wndclass.hbrBackground = CreateSolidBrush(RGB(255,255,255));					//背景颜色画刷
	this->wndclass.hCursor = LoadCursor(NULL, IDC_HAND);								//鼠标光标类型,手：DC_HAND
	this->wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IMG_ICON_HUANXIONG));	//图标
	this->wndclass.lpszClassName = TEXT("tetris");										//窗口类型名
	this->wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_OWNDC;				//窗口类的风格
	this->wndclass.cbClsExtra = 0;
	this->wndclass.cbWndExtra = 0;
	this->wndclass.lpszMenuName = nullptr;
}

Win::~Win()
{
}

void Win::set_hInstance(HINSTANCE hInstance,int define_img)
{
	this->wndclass.hInstance = hInstance;												//句柄
	this->wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(define_img));				//图标
}

void Win::register_class()
{
	RegisterClass(&this->wndclass);
	return ;
}

void Win::create_window(LPCTSTR name,int location_x,int location_y,int width,int high)
{
	this->hwnd=CreateWindow(
		TEXT("tetris"),													 				//窗口类型名
		name,																			//窗口标题
		WS_OVERLAPPEDWINDOW, 															//窗口的风格
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

void Win::update_window()
{
	UpdateWindow(this->hwnd);
	return ;
}      

bool Win::loop_message()
{
	if(PeekMessage(&this->msg, NULL, 0, 0, PM_REMOVE))	//非阻塞式获取消息
	{
		if (msg.message == WM_QUIT)
			return false;
		//将虚拟键消息转换为字符消息
		TranslateMessage(&this->msg);
		//将消息分发给窗口处理函数
		DispatchMessage(&this->msg);
	}
	/*
	while (GetMessage(&this->msg, NULL, 0, 0))//GetMessage从调用线程的消息队列中取得一个消息并放于msg
	{
		//将虚拟键消息转换为字符消息
		TranslateMessage(&this->msg);
		//将消息分发给窗口处理函数
		DispatchMessage(&this->msg);
	}
	*/
	/*
	if (!glfwWindowShouldClose(window))
	{
		//刷新颜色缓冲和深度
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	*/
	if (g_bNcLButtonDown)
	{
		//有时候客户端会卡顿，一旦不能收到窗口消息，g_bNcLButtonDown可能会一直为true，导致bug。
		//解决办法是，这里总是判断鼠标左键是否按下。从系统层面获取鼠标左键是否按下。
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			::GetCursorPos(&g_kCurMousePos);
			const int nDeltaX = g_kCurMousePos.x - g_kLastMousePos.x;
			const int nDeltaY = g_kCurMousePos.y - g_kLastMousePos.y;
			if (nDeltaX < -1 || nDeltaX > 1 || nDeltaY < -1 || nDeltaY > 1)
			{
				g_kCurWindowRect.left += nDeltaX;
				g_kCurWindowRect.top += nDeltaY;
				g_kLastMousePos = g_kCurMousePos;
				//执行移动操作的时候不要更改窗口size。
				::SetWindowPos(this->hwnd, HWND_NOTOPMOST, g_kCurWindowRect.left, g_kCurWindowRect.top, g_kCurWindowRect.right, g_kCurWindowRect.bottom, SWP_NOSIZE);
			}
		}
		else
		{
			g_bNcLButtonDown = false;
		}
	}
	return true;
}

void Win::create_console()
{
	AllocConsole();
    freopen("CONOUT$", "w", stdout);
}

void Win::start_win(LPCTSTR name,int location_x,int location_y,int width,int high)
{
	this->register_class();
	this->create_window(name,location_x,location_y,width,high);
	this->show_window();
	this->update_window();
	this->loop_message();
	return ;
}

HWND Win::get_hwnd()
{
	return this->hwnd;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	switch (uMsg)
	{
		case WM_KEYDOWN://按键按下
			handle_key(wParam,lParam);
			break;
		case WM_SYSCOMMAND:
			switch (wParam & 0xfff0)
			{
				case SC_KEYMENU:
				case SC_MOUSEMENU:
					//拦截左侧小菜单,不要通知给默认的消息处理函数
					return 0;
				case SC_MOVE:
					if (g_bNcLButtonDown==false)
					{
						//鼠标开始拖动标题栏，我们的逻辑开始执行
						g_bNcLButtonDown = true;
						::GetCursorPos(&g_kLastMousePos);
						::GetWindowRect(hWnd, &g_kCurWindowRect);
					}
					//拦截用户拖拽操作,不要通知给默认的消息处理函数
					return 0;
					break;
			}
			break;
		case WM_NCRBUTTONDOWN:
			g_bNcLButtonDown = false;
			break;
		case WM_CLOSE://窗口关闭消息
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY://窗口销毁消息
			PostQuitMessage(0);
			break;
		return TRUE;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//默认的窗口处理函数
}

void handle_key(WPARAM wParam,LPARAM lParam)
{
	std::cout<<"当前按下的是: "<<wParam<<std::endl;
	//Sleep(1000*5);
	return;
}


