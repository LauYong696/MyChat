#define READ_PORT  9090
#define WRITE_PORT 9091
#define BUFFERSIZE 1024

int read_socket_init();
int write_socket_init();
int read_socket_connect();
int write_socket_connect();
int create_thread();
void ncurese_init();