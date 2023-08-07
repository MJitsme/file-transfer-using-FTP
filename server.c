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

//function for file sending
void recv_file(int connfd)
{
  FILE* fp;
  char buff[MAX];
  char* filename="recv.txt";
  int n;
  fp=fopen(filename,"w");
  while(1)
  {
    n=recv(connfd,buff,MAX,0);
    if(n<=0)
    {
      break;
      return;
    }
    fprintf(fp,"%s",buff);
    bzero(buff,MAX);
  }
}

//main function
int main()
{
  int sockfd,connfd,len;
  SAI server,client;
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  printf("socket created successfully..\n");
  server.sin_family=AF_INET;
  server.sin_addr.s_addr=htonl(INADDR_ANY);
  server.sin_port=htons(PORT);

  if(bind(sockfd,(SA*)&server,sizeof(server))==0)
    printf("binding successful..\n");
  else
  {
    printf("binding failed");
    return 1;
  }

  if(listen(sockfd,5)==0)
    printf("server listening on port 9014\n");
  else
  {
    printf("server listening failed");
    return 1;
  }
  len=sizeof(client);
  connfd=accept(sockfd,(SA*)&client,(socklen_t*)&len);
  printf("Server accept the client..\n");
  recv_file(connfd);
  close(sockfd);
  return 0;
}
