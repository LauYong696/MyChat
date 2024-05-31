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

pthread_mutex_t print_lock;

void quit();

int lock_init(void){
    pthread_mutex_init(&print_lock,NULL);
    return 0;
}

void quit(){
    //todo
}