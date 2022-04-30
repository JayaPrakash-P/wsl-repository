// Example program
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <cstring>
#include <chrono>
#include <thread>

#define IP_ADDRESS "127.0.0.1"
#define PORT_NUM   5555

void SocketServer()
{
    std::cout << "SocketServer - Enter\n";
    int serverFD = 0;
    int clientFD = 0;
    struct sockaddr_in serverAddr, clientAddr;
    serverFD = socket(AF_INET, SOCK_STREAM,0);
    if(serverFD < 0)
    {
        std::cout << "socket() failed : " << std::strerror(errno) << std::endl;
        exit(-1);
    }
    
    serverAddr.sin_family       = AF_INET;
    serverAddr.sin_port         = htons(PORT_NUM);
    serverAddr.sin_addr.s_addr  = inet_addr(IP_ADDRESS);
    
    int res = bind(serverFD, (struct sockaddr *)&serverAddr, (socklen_t)sizeof(serverAddr));
    if(res !=0 )
    {
        std::cout << "bind() failed : " << std::strerror(errno) << std::endl;
        exit(-1);
    }
    
    res = listen(serverFD, 1);
    if(res !=0 )
    {
        std::cout << "listen() failed : " << std::strerror(errno) << std::endl;
        exit(-1);
    }
    
    socklen_t addrLen = sizeof(clientAddr);
    clientFD = accept(serverFD, (struct sockaddr *)&clientAddr, &addrLen);
    if(clientFD < 0)
    {
        std::cout << "accept() failed : " << std::strerror(errno) << std::endl;
        exit(-1);
    }
    else
        std::cout << "accept()  : [" << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << "]\n";

    char clientData[255];
    memset(clientData, 0 , sizeof(clientData));
    read(clientFD, clientData, sizeof(clientData));
    std::cout << "clientData : " << clientData << std::endl;
    
    char serverData[]="Hello from server!";
    write(clientFD, serverData, strlen(serverData));
    
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    close(clientFD);
    close(serverFD);
    
    std::cout << "SocketServer - Exit\n";
}

void SocketClient()
{
    std::cout << "SocketClient - Enter\n";
    int clientFD = 0;
    struct sockaddr_in clientAddr;
    
    clientFD = socket(AF_INET, SOCK_STREAM,0);
    if(clientFD < 0)
    {
        std::cout << "socket() failed : " << std::strerror(errno) << std::endl;
        exit(-1);
    }
    
    clientAddr.sin_family       = AF_INET;
    clientAddr.sin_port         = htons(PORT_NUM);
    clientAddr.sin_addr.s_addr  = inet_addr(IP_ADDRESS);
    
    int res = connect(clientFD, (struct sockaddr *)&clientAddr, (socklen_t)sizeof(clientAddr));
    if(res !=0 )
    {
        std::cout << "connect() failed : " << std::strerror(errno) << std::endl;
        exit(-1);
    }
    
    char clientData[]="Hello from client!";
    write(clientFD, clientData, strlen(clientData));
        
    char serverData[255];
    memset(serverData, 0 , sizeof(serverData));
    read(clientFD, serverData, sizeof(serverData));
    std::cout << "serverData : " << serverData << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    close(clientFD);
    
    std::cout << "SocketClient - Exit\n";
}

int main()
{
  std::cout << "main - Enter\n";
  std::thread server(SocketServer);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::thread client(SocketClient);
  
  server.join();
  client.join();
  
  std::cout << "main - Exit\n";

}
