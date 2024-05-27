#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<arpa/inet.h>
#include"def.h"

int server_read_fd, new_read_socket;
int server_write_fd, new_write_socket;
struct sockaddr_in server_read_addr;
struct sockaddr_in server_write_addr;
int read_opt = 1;
int write_opt = 1;
socklen_t server_read_addrlen = sizeof(server_read_addr);
socklen_t server_write_addrlen = sizeof(server_write_addr);


int read_socket_init(int argc, char const* argv[]){
    if((server_read_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket failed\n");
        exit(EXIT_FAILURE);
    }

    if(setsockopt(server_read_fd, SOL_SOCKET, 
                SO_REUSEADDR | SO_REUSEPORT, &read_opt, 
                sizeof(read_opt))){
        perror("setsockopt\n");
        exit(EXIT_FAILURE);
    }

    server_read_addr.sin_family = AF_INET;
    server_read_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_read_addr.sin_port = htons(READ_PORT);

    if(bind(server_read_fd, (struct sockaddr*)&server_read_addr,
        sizeof(server_read_addr))){
        perror("bind failed\n");
        exit(EXIT_FAILURE);            
    }
}

int read_socket_connect(){
    if(listen(server_read_fd, 3) < 0) {
		perror("listen\n");
		exit(EXIT_FAILURE);
	}

    if((new_read_socket = accept(server_read_fd, 
       (struct sockaddr*)&server_read_addr, &server_read_addrlen))< 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
}

int write_socket_init(){
    if((server_write_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket failed\n");
        exit(EXIT_FAILURE);
    }

    if(setsockopt(server_write_fd, SOL_SOCKET, 
                SO_REUSEADDR | SO_REUSEPORT, &write_opt, 
                sizeof(read_opt))){
        perror("setsockopt\n");
        exit(EXIT_FAILURE);
    }

    server_write_addr.sin_family = AF_INET;
    server_write_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_write_addr.sin_port = htons(WRITE_PORT);

    if(bind(server_write_fd, (struct sockaddr*)&server_write_addr,
        sizeof(server_write_addr))){
        perror("write_socket bind failed\n");
        exit(EXIT_FAILURE);            
    }
}

int write_socket_connect(){
    if(listen(server_write_fd, 3) < 0) {
		perror("listen\n");
		exit(EXIT_FAILURE);
	}

    if((new_write_socket = accept(server_write_fd, 
       (struct sockaddr*)&server_write_addr, &server_write_addrlen))< 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
}

