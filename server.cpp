#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include<cstring>


int main() {
    int lserverFd;
    int lnewSocket;
    struct sockaddr_in laddress;
    memset(&laddress, 0, sizeof(laddress));  
    int loption=1;
    int laddLength=sizeof(laddress);
    char lbuffer[1024]={0};

    const char *hello="Greeting from server";
    lserverFd=socket(AF_INET,SOCK_STREAM,0);
    setsockopt(lserverFd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&loption,sizeof(loption));
    if(lserverFd<0){ perror("socket failed"); return 1; }
    laddress.sin_family=AF_INET;
    laddress.sin_addr.s_addr=INADDR_ANY;
    laddress.sin_port=htons(8080);

    if (bind(lserverFd, (struct sockaddr *)&laddress, sizeof(laddress)) < 0) {
        perror("bind failed");
        return 1;
    }


    listen(lserverFd,2);
    std::cout<<"Server is listening on"<<std::endl;
    lnewSocket=accept(lserverFd,(struct sockaddr*)&laddress,(socklen_t*)&laddLength);

    read(lnewSocket,lbuffer,1024);
    std::cout<<"buffer data"<<lbuffer<<std::endl;

    send(lnewSocket,hello,strlen(hello),0);
    std::cout<<"sent hello to client"<<std::endl;

    close(lnewSocket);
    close(lserverFd);
}
