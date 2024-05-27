#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "def.h"

int main(){
    read_socket_init();
    write_socket_init();
    printf("正在等待来自客户端的连接:\n");
    read_socket_connect();
    printf("read connected\n");
    write_socket_connect();
    printf("已经与客户端建立连接\n");
    create_thread();
    exit(0);
}