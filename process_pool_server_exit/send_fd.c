#include "func.h"
//内核控制信息传递
void send_fd(int pfd,int fd,int exit_flag)
{
	struct msghdr msg;
	bzero(&msg,sizeof(msg));
	struct cmsghdr *cmsg;
	int len=CMSG_LEN(sizeof(int));
	cmsg=(struct cmsghdr *)malloc(len);
	cmsg->cmsg_len=len;
	cmsg->cmsg_level=SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	*(int*)CMSG_DATA(cmsg)=fd;
	msg.msg_control=cmsg;
	msg.msg_controllen=len;
	char buf1[10]="world";
	struct iovec iov[2];
	iov[0].iov_base=&exit_flag;
	iov[0].iov_len=4;
	iov[1].iov_base=buf1;
	iov[1].iov_len=5;
	msg.msg_iov=iov;
	msg.msg_iovlen=2;
	int ret=sendmsg(pfd,&msg,0);
	if(-1==ret)
	{
		perror("sendmsg");
		return;
	}
}

void recv_fd(int pfd,int *fd,int *exit_flag)
{
	struct msghdr msg;
	bzero(&msg,sizeof(msg));
	struct cmsghdr *cmsg;
	int len=CMSG_LEN(sizeof(int));
	cmsg=(struct cmsghdr *)malloc(len);
	cmsg->cmsg_len=len;
	cmsg->cmsg_level=SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	msg.msg_control=cmsg;
	msg.msg_controllen=len;
	char buf1[10]="world";
	struct iovec iov[2];
	iov[0].iov_base=exit_flag;
	iov[0].iov_len=4;
	iov[1].iov_base=buf1;
	iov[1].iov_len=5;
	msg.msg_iov=iov;
	msg.msg_iovlen=2;
	int ret=recvmsg(pfd,&msg,0);
	if(-1==ret)
	{
		perror("recvmsg");
		return;
	}
	*fd=*(int*)CMSG_DATA(cmsg);
}
