// WinCreate.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "resource.h"
HINSTANCE g_hInstance=0;//���ܵ�ǰ����ʵ�����
void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch(LOWORD(wParam) )
	{
	case ID_NEW:
		MessageBox(NULL, "�½������", "Infor", MB_OK);
		break;
	case ID_EXIT:
		MessageBox(NULL, "�˳������", "Infor", MB_OK);
		break;
	case ID_ABOUT:
		MessageBox(NULL, "���ڱ����", "Infor", MB_OK);
		break;
	}
}
void OnPaint(HWND hWnd) //OnPaint���ܻ�Ƶ���ĵ����ڴ� ����ֻ�����һ��
{
	PAINTSTRUCT ps = {0};
	HDC hdc = BeginPaint(hWnd, &ps);
	HICON hIcon = LoadIcon(g_hInstance,
		MAKEINTRESOURCE(IDI_ICON1));
	DrawIcon(hdc, 100, 100, hIcon);
	EndPaint(hWnd, &ps);
}
//���ڴ�������
LRESULT CALLBACK WndProc(HWND hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam)
{
	switch(nMsg)
	{
	case WM_PAINT:
		OnPaint(hWnd);
		break;
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd,nMsg,wParam,lParam);
}
//ע�ᴰ����
BOOL Register(LPSTR lpClassName,WNDPROC wndproc)
{
	WNDCLASSEX wce={0};
	wce.cbSize=sizeof(wce);
	wce.cbClsExtra=0;
	wce.cbWndExtra=0;
	wce.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	wce.hCursor=NULL;
	wce.hIcon = LoadIcon(g_hInstance,
		MAKEINTRESOURCE(IDI_ICON1));
	wce.hIconSm=LoadIcon(g_hInstance,
		MAKEINTRESOURCE(IDI_ICON2));
	wce.hInstance=g_hInstance;
	wce.lpfnWndProc=wndproc;
	wce.lpszClassName=lpClassName;
	wce.lpszMenuName = NULL;	 // MAKEINTRESOURCE(IDR_MENU1);
	wce.style=CS_HREDRAW | CS_VREDRAW;
	ATOM nAtom=RegisterClassEx(&wce);
	if(nAtom==0)
		return FALSE;
	return TRUE;
}
//����������
HWND CreateMain(LPSTR lpClassName,LPSTR lpWndName)
{
	HMENU hMenu = LoadMenu(g_hInstance, 
		MAKEINTRESOURCE(IDR_MENU1));
	HWND hWnd=CreateWindowEx(0, lpClassName, lpWndName,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, hMenu, g_hInstance, NULL);
	HICON hIcon = LoadIcon(g_hInstance,
		MAKEINTRESOURCE(IDI_ICON1));
	SendMessage(hWnd, WM_SETICON, ICON_SMALL,
		(LPARAM)hIcon);
	return hWnd;
}
//��ʾ����
void Display(HWND hWnd)
{
	ShowWindow(hWnd,SW_SHOW);
	UpdateWindow(hWnd);
}
//��Ϣѭ��
void Message()
{
	MSG nMsg={0};
	while(GetMessage(&nMsg,NULL,0,0))
	{
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);
	}
}
//������
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.

	g_hInstance=hInstance;
	if(!Register("Main",WndProc))
	{
		MessageBox(NULL,"ע��ʧ��","Error",MB_OK);
		return 0;
	}
	HWND hWnd=CreateMain("Main","window");
	Display(hWnd);
	Message();
	return 0;	
}


