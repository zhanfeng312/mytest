// WinCreate.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "resource.h"
HINSTANCE g_hInstance = 0;//���ܵ�ǰ����ʵ�����
int g_kind = 0;  //��־�� (��������ͼ��)  ��֤Ψһ����
void OnCommand(HWND hWnd, WPARAM wParam)
{
	g_kind = LOWORD(wParam); //����־�����˸�ֵ

	switch (g_kind)
	{
		
	case ID_PIT:
	case ID_LINE:  //����⼸����ִ��������δ���
	case ID_REC:
	case ID_ELL:
	case ID_ARC:
	case ID_PIE:
	case ID_BMP:
		InvalidateRect(hWnd, NULL, TRUE); //����Ϊ��Ч����
		break;
	}
}
void DrawPit(HDC hdc)
{
	//SetPixel(hdc, 100, 100, RGB(255, 0, 0)); //����
	for(int i = 0; i < 256; i++)
	{
		for(int j = 0; j < 256; j++)
		{
			SetPixel(hdc, i, j, RGB(i, j, 0));
		}
	}
}
void DrawLine(HDC hdc)
{
	MoveToEx(hdc, 100, 100, NULL);  //���ô��ڵ�ǰ��Ϊ100, 100
	LineTo(hdc, 300, 300);   //ֱ�߻����,�ѵ�ǰ��
	LineTo(hdc, 0, 300);
	LineTo(hdc, 100, 100);
}
void DrawRec(HDC hdc)
{
	Rectangle(hdc, 100, -100, 300, -300);
	RoundRect(hdc, 300, 100, 500, 300, 1000, 1000); //�Բ����������ж�
}
void DrawEll(HDC hdc)
{
	Ellipse(hdc, 100, 100, 300, 300); //��Բ
	Ellipse(hdc, 300, 100, 600, 300); //��Բ
}
void DrawArc(HDC hdc)
{
	Arc(hdc, 100, 100, 300, 300 ,100, 100, 300, 300);
}
void DrawPie(HDC hdc)
{
	Pie(hdc, 100, 100, 300, 300, 300, 100, 100, 100);
}
void DrawBmp(HDC hdc)
{
	HBITMAP hBmp = LoadBitmap(g_hInstance,
		MAKEINTRESOURCE(IDB_BITMAP2));
	BITMAP bmpInfo = {0};
	GetObject(hBmp, sizeof(bmpInfo), &bmpInfo); 
	//���λͼ�Ŀ��͸�

	HDC hMemdc = CreateCompatibleDC(hdc);
	//������һ���ڴ�DC,ͬʱ��������һ����������

	HGDIOBJ nOldBmp = SelectObject(hMemdc, hBmp);
	//�ڴ潫�����ͼƬ ������ ���������� (0,0)

//	BitBlt(hdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, 
	//	hMemdc, 0, 0, SRCCOPY); 
	//һ��һ����

	StretchBlt(hdc, 150, 100, 96, 96,
		hMemdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, NOTSRCCOPY);
	//���ų���

	SelectObject(hMemdc, nOldBmp);
	DeleteObject(hBmp);
	DeleteDC(hMemdc);
}
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps = {0};
	HDC hdc = BeginPaint(hWnd, &ps); //��OS��ץ��������������������л�
	HPEN hPen = CreatePen(PS_DASH, 1, RGB(255, 0, 0)); //����һ������ �������PS_SOLID,�ڶ���������д�Ĳ���1,�ǻ��ʾ�ʧЧ��
	HGDIOBJ nOldPen = SelectObject(hdc, hPen);  //�͸���
//	HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0)); //��ԭ���İ�ɫ��ˢ������
//	HBRUSH hBrush = CreateHatchBrush(
		//HS_CROSS, RGB(0, 255, 0));
//	HGDIOBJ hBrush = GetStockObject(NULL_BRUSH);
	HBITMAP hBmp = LoadBitmap(g_hInstance,
		MAKEINTRESOURCE(IDB_BITMAP1));
	HBRUSH hBrush = CreatePatternBrush(hBmp);
	HGDIOBJ nOldBrush = SelectObject(hdc, hBrush);

	int nOldMode = SetMapMode(hdc, MM_ANISOTROPIC);
	SetWindowExtEx(hdc, 1, 1, NULL);
	SetViewportExtEx(hdc, 2, -2, NULL);

	switch (g_kind)
	{
	case ID_BMP:
		DrawBmp(hdc); //����λͼ
		break;
	case ID_PIE:
		DrawPie(hdc);   //��������
		break;  
	case ID_ARC:
		DrawArc(hdc) ; //���ƻ���
		break;
	case ID_ELL:
		DrawEll(hdc) ;  //����Բ��
		break;
	case ID_REC:
		DrawRec(hdc); //���ƾ���
		break;
	case ID_PIT:
		DrawPit(hdc); //���Ƶ�
		break;
	case ID_LINE:
		DrawLine(hdc); //����ֱ��
		break;
	}
	SetMapMode(hdc, nOldMode);

	SelectObject(hdc, nOldBrush);
	DeleteObject(hBrush);
	SelectObject(hdc, nOldPen); //������ ����Ҫ����
	DeleteObject(hPen);  //�ѱ����ٵ�
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
	wce.hbrBackground = CreateSolidBrush(RGB(0, 255, 0)); //���ڵı���ɫ
	wce.hCursor=NULL;
	wce.hIcon=NULL;
	wce.hIconSm=NULL;
	wce.hInstance=g_hInstance;
	wce.lpfnWndProc=wndproc;
	wce.lpszClassName=lpClassName;
	wce.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //���ز˵�
	wce.style=CS_HREDRAW | CS_VREDRAW;
	ATOM nAtom=RegisterClassEx(&wce);
	if(nAtom==0)
		return FALSE;
	return TRUE;
}
//����������
HWND CreateMain(LPSTR lpClassName,LPSTR lpWndName)
{
	HWND hWnd=CreateWindowEx(0,lpClassName,lpWndName,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,g_hInstance,NULL);
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


