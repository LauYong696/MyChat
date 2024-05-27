#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <ncurses.h>
#include"def.h"

pthread_mutex_t read_lock;
pthread_mutex_t write_lock;
pthread_mutex_t print_lock;

extern int new_read_socket;
extern int server_read_fd, new_read_socket;
extern int server_write_fd, new_write_socket;
void quit();

extern int row, col;
int print_line_count = 0;


void* read_thread(void *arg){
    int n;
    char recvline[1000 + 1];

    while(( n = read(new_read_socket,recvline,1000)) > 0){
        recvline[n] = 0;
        if(strcmp(recvline, "quit") == 0){
            printf("客户端终止了对话\n");
            quit();
            return 0;
        }
        pthread_mutex_lock(&print_lock);
        mvprintw(print_line_count, 0, "client: %s", recvline);
        pthread_mutex_unlock(&print_lock);
        move(row - 1, 8);
        refresh();
        print_line_count++;
    }

}

void* write_thread(void *arg){
    while (1) {
        char sendline[1024];
        move(row - 1, 8);                          // 将光标移动到提示信息后
        clrtoeol();                                // 清除从光标到行尾的内容
        getnstr(sendline, sizeof(sendline) - 1);   // 获取用户输入

        send(new_write_socket, sendline, strlen(sendline), 0);

        if(strcmp(sendline,"quit") == 0){
            printf("你终止了对话\n");
            quit();
            return 0;
        }

        //clear();                              // 清屏
        pthread_mutex_lock(&print_lock);
        mvprintw(print_line_count, 0, "server: %s", sendline);            // 在顶端打印用户输入的内容
        pthread_mutex_unlock(&print_lock);
        mvprintw(row - 1, 0, "server: ");       // 恢复提示信息
        refresh();
	    print_line_count++ ;
    }
}

int create_thread(void){
    pthread_t pthread1;
    pthread_t pthread2;

    ncurese_init();

    pthread_mutex_init(&read_lock,NULL);
    pthread_mutex_init(&write_lock,NULL);
    pthread_mutex_init(&print_lock,NULL);

    pthread_create(&pthread1, NULL, read_thread, NULL);
    pthread_create(&pthread2, NULL, write_thread, NULL);

    pthread_join(pthread1, NULL);
    pthread_join(pthread2,NULL);

    return 0;
}

void quit(){
    close(new_read_socket);
    close(new_write_socket);
    // closing the listening socket
    close(server_read_fd);
    close(server_write_fd);
}