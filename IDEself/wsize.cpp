#ifndef __WSIZE_TEST
#define __WSIZE_TEST
#include<windows.h>
#include<process.h>
#include<cstdio>
int TITL_H=63,CHAR_H=23,CHAR_W=15;
struct __gmyhwnd__arg{
	HWND hwnd;
	DWORD pid;
};
int __stdcall __gmyhwnd__Enum(HWND hwnd, LPARAM lParam)
{
	__gmyhwnd__arg *arg = (__gmyhwnd__arg*)lParam;
	DWORD pid = 0;
	GetWindowThreadProcessId(hwnd, &pid);
	if (pid == arg->pid){
		arg->hwnd = hwnd;
		return 0;
	}
	return 1;
}
HWND gmyhwnd(){
	__gmyhwnd__arg ewa;
	ewa.pid=getpid();
	ewa.hwnd=0;
	EnumWindows(__gmyhwnd__Enum,(LPARAM)&ewa);
	return ewa.hwnd;
}
HWND hwnd=GetForegroundWindow();
int getheight(HWND hwnd){
	RECT rect;GetWindowRect(hwnd,&rect);
	return (rect.bottom-rect.top-TITL_H)/CHAR_H;
}
int getweight(HWND hwnd){
	RECT rect;GetWindowRect(hwnd,&rect);
	return (rect.right-rect.left)/CHAR_W;
}
int getmousex(HWND hwnd){
	RECT rect;GetWindowRect(hwnd,&rect);
	POINT p;GetCursorPos(&p);
	return (p.x-rect.left)/CHAR_W;
}
int getmousey(HWND hwnd){
	RECT rect;GetWindowRect(hwnd,&rect);
	POINT p;GetCursorPos(&p);
	return (p.y-rect.top-TITL_H)/CHAR_H;
}
int getheight(){return	getheight(hwnd);}
int getweight(){return	getweight(hwnd);}
int getmousex(){return	getmousex(hwnd);}
int getmousey(){return	getmousey(hwnd);}
#define keydn(x) (GetAsyncKeyState(x)&0X8000)
bool key(int x){
	if(keydn(x))
	{
		while(keydn(x));
		return	true;
	}
	return false;
}
bool issel(HWND hwnd){
	POINT p;GetCursorPos(&p);
	RECT rect;GetWindowRect(hwnd,&rect);
	return GetForegroundWindow()==hwnd
			&&rect.top<p.y&&p.y<rect.bottom
			&&rect.left<p.x&&p.x<rect.right;
}
void chkconf(){
	RECT rect;GetWindowRect(hwnd,&rect);
	printf("A\nA\nA\nA\nA\nA\nAAAAAAA");
	POINT p;	while(!key(VK_LBUTTON))	GetCursorPos(&p);
	printf("%d",TITL_H=p.y-rect.top);
	POINT p1;	while(!key(VK_LBUTTON))	GetCursorPos(&p1);
	printf("%d %d",CHAR_H=(p1.y-p.y)/6,CHAR_W=(p1.x-p.x)/6);
}
#endif
