#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "def.h"

int main(){
    socket_init();
    printf("Waitting for connection from client...\n");
    socket_connect();
    exit(0);
}