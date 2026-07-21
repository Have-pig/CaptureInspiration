#include <graphics.h>
#include <conio.h>
#include <iostream>

int main()
{
	// 初始化窗口，宽800，高600
	initgraph(800, 600);

	// 清屏并设置背景色与文字
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(BLACK);

	outtextxy(350, 280, "Hello, EasyX! 出现窗口说明初始化成功。");

	// 等待按键后关闭窗口
	_getch();
	closegraph();
	return 0;
}

