#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/epoll.h>
typedef struct{
	pid_t pid;
	int fd;//父子进程使用的全双工管道
	short busy;//1代表忙碌，0代表非忙碌
}Data,*pData;
typedef struct{
	int len;//控制数据
	char buf[1000];
}train;
#define FILENAME "file"
void make_child(pData p,int n);
void child_handle(int);
void send_fd(int,int,int);
void recv_fd(int,int*,int*);
void tran_file(int);
int send_n(int,char*,int);
