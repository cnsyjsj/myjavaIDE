#ifndef __WSIZE_TEST
#define __WSIZE_TEST
#include<windows.h>
#define TITL_H 50
#define CHAR_H 19
#define CHAR_W 10
HWND hwnd=GetForegroundWindow();
//int getheight(HWND hwnd){
//	RECT rect;GetWindowRect(hwnd,&rect);
//	return (rect.bottom-rect.top-TITL_H)/CHAR_H;
//}
//int getweight(HWND hwnd){
//	RECT rect;GetWindowRect(hwnd,&rect);
//	return (rect.right-rect.left)/CHAR_W;
//}
//int getmousex(HWND hwnd){
//	RECT rect;GetWindowRect(hwnd,&rect);
//	POINT p;GetCursorPos(&p);
//	return (p.x-rect.left)/CHAR_W;
//}
//int getmousey(HWND hwnd){
//	RECT rect;GetWindowRect(hwnd,&rect);
//	POINT p;GetCursorPos(&p);
//	return (p.y-rect.top-TITL_H)/CHAR_H;
//}
int getheight(){
	RECT rect;GetWindowRect(hwnd,&rect);
	return (rect.bottom-rect.top-TITL_H)/CHAR_H;
}
int getweight(){
	RECT rect;GetWindowRect(hwnd,&rect);
	return (rect.right-rect.left)/CHAR_W;
}
int getmousex(){
	RECT rect;GetWindowRect(hwnd,&rect);
	POINT p;GetCursorPos(&p);
	return (p.x-rect.left)/CHAR_W;
}
int getmousey(){
	RECT rect;GetWindowRect(hwnd,&rect);
	POINT p;GetCursorPos(&p);
	return (p.y-rect.top-TITL_H)/CHAR_H;
}
bool key(int x)
{
	if(GetAsyncKeyState(x)&0X8000)
	{
		while(GetAsyncKeyState(x)&0X8000);
		return	true;
	}
	return false;
}
bool issel(HWND hwnd)
{
	POINT p;GetCursorPos(&p);
	RECT rect;GetWindowRect(hwnd,&rect);
	return GetForegroundWindow()==hwnd
			&&rect.top<p.y&&p.y<rect.bottom
			&&rect.left<p.x&&p.x<rect.right;
}
#endif
