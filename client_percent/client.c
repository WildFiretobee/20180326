#include "func.h"

int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("./server IP PORT\n");
		return -1;
	}
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));//将端口转换为网络字节序
	ser.sin_addr.s_addr=inet_addr(argv[1]);//将点分十进制的ip地址转为32位的网络字节序
	int ret;
	ret=connect(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(-1==ret)
	{
		perror("connect");
		return -1;
	}
	int len;
	char buf[1000]={0};
	recv(sfd,&len,sizeof(len),0);
	recv(sfd,buf,len,0);
	int fd;
	fd=open(buf,O_RDWR|O_CREAT,0666);
	off_t f_size;
	recv_n(sfd,(char*)&len,sizeof(len));
	recv_n(sfd,(char*)&f_size,len);//接文件长度
	printf("%ld\n",f_size);
	int total=0;
	int i=f_size/100;
	int j=1;
	//以下载大小打印
	while(1)
	{
		recv_n(sfd,(char*)&len,sizeof(len));
		if(len>0)
		{
			total=total+len;
			if(total>i)
			{
				printf("%d%s\r",j,"%");
				fflush(stdout);
				j=j+1;
				i=i+f_size/100;
			}
			recv_n(sfd,buf,len);
			write(fd,buf,len);
		}else{
			printf("\n");
			break;
		}
	}
	close(fd);
	close(sfd);
}
