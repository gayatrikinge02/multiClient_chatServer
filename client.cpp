#include <iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>

int main() {
   int lsocket=0;
   struct sockaddr_in  l_serverAddress;
   char lbuffer[1024]={0};

   lsocket=socket(AF_INET,SOCK_STREAM,0);
   if(lsocket<0){
    std::cerr<<"couldnt create socket at client side";
    return -1;
}
    l_serverAddress.sin_family=AF_INET;
    l_serverAddress.sin_port=htons(8080);

    if(inet_pton(AF_INET,"127.0.0.1",&l_serverAddress.sin_addr)<=0){
        std::cerr<<"Invalid address"<<std::endl;
        return -1;
    }

    if(connect(lsocket,(struct sockaddr*) &l_serverAddress,sizeof(l_serverAddress))<0){
        std::cerr<<"Connection failed"<<std::endl;
        return -1;
    }

    const char *hello = "Hello from client";
    send(lsocket, hello, strlen(hello), 0);
    std::cout << "Hello message sent" << std::endl;
    read(lsocket, lbuffer, 1024);
    std::cout<<"server msg:"<<lbuffer<<std::endl;

    close(lsocket);
    return 0;
}
