#include<ncurses.h>
#include <string.h>
#include "def.h"

int row, col;
WINDOW *win;


void ncurese_init(){
    initscr();              // 初始化ncurses模式
    echo();                 // 开启字符回显
    cbreak();               // 禁用行缓冲，使得输入字符可以立即被程序读取
    curs_set(TRUE);         // 显示光标
    newwin(LINES, COLS, 0, 0);
    scrollok(win, TRUE);

    getmaxyx(stdscr, row, col);  // 获取终端尺寸

    // 输出提示信息
    mvprintw(row - 1, 0, "server: ");
    refresh();
}

