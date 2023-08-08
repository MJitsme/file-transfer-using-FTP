//importing libraries
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

//defining global variables
#define MAX 100
#define PORT 9014
#define SA struct sockaddr
#define SAI struct sockaddr_in

//function to send file
void send_file(int sockfd)
{
  char buff[MAX]={0};
  fp=fopen("send.txt","r");
  while(fgets(buff,MAX,fp)!=NULL)
  {
    send(sockfd,buff,sizeof(buff),0);
    bzero(buff,MAX);
  }
}

//main function
int main()
{
  int sockfd;
  SAI server;
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  printf("socket created successfully\n");
  server.sin_family=AF_INET;
  server.sin_addr.s_addr=htonl(INADDR_ANY);
  server.sin_port=htons(PORT);

  if(connect(sockfd,(SA*)&server,sizeof(server))==0);
  {
    printf("Connection successful..\n");
  }
  else
  {
    printf("Connection failed..");
    return 1;
  }

  send_file(sockfd);
  close(sockfd);
  return 0;
}
