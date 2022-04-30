#include "SocketServer.h"

#include <iostream>
#include <chrono>



SocketServer::SocketServer(SocketData& socketData)
    :socketData(socketData),
     serverRunning(false),
     clientRunning(false)
{
    
}

void SocketServer::Open()
{
    socketData.sdSocketFdServer = socket(socketData.sdDomain, socketData.sdType, socketData.sdProtocol);
    if(socketData.sdSocketFdServer < 0)
    {
        std::cout << "SocketServer::Open - Failed... : " << std::strerror(errno) << std::endl;
        exit(-1);
    }
    else
        std::cout << "SocketServer::Open - Succeeded...sdSocketFdServer : " << socketData.sdSocketFdServer << std::endl;
    
}

void SocketServer::Bind()
{
    if(socketData.sdSocketFdServer < 0)
    {
        std::cout << "SocketServer::Bind - Invalid  sdSocketFdServer : " << socketData.sdSocketFdServer << std::endl;
        exit(-1);
    }
    else
    {
        socklen_t  sdSockAddrLen = sizeof(socketData.sdSockAddrInServer);
        int retVal = bind(socketData.sdSocketFdServer, (struct sockaddr*)&(socketData.sdSockAddrInServer), sdSockAddrLen);
        if(retVal != 0)
        {
            std::cout << "SocketServer::Bind - Failed... : " << std::strerror(errno) << std::endl;
            exit(-1);
        }
        else
        {
            serverRunning = true;
            std::cout << "SocketServer::Bind - Succeeded... retVal : " << retVal << std::endl;
        }
    }
}

void SocketServer::Listen()
{
    if(socketData.sdSocketFdServer < 0)
    {
        std::cout << "SocketServer::Listen - Invalid  sdSocketFdServer : " << socketData.sdSocketFdServer << std::endl;
        exit(-1);
    }
    else
    {
        int retVal = listen(socketData.sdSocketFdServer, 5);
        if(retVal != 0)
        {
            std::cout << "SocketServer::Listen - Failed... : " << std::strerror(errno) << std::endl;
            exit(-1);
        }
        else
        {
            serverRunning = true;
            std::cout << "SocketServer::Listen - Succeeded... retVal : " << retVal << std::endl;
        }
    }
}

void SocketServer::Accept()
{
    if(socketData.sdSocketFdServer < 0)
    {
        std::cout << "SocketServer::Accept - Invalid  sdSocketFdServer : " << socketData.sdSocketFdServer << std::endl;
        exit(-1);
    }
    else
    {
        socklen_t sdSockAddrLen = sizeof(socketData.sdSockAddrInClient);
        std::cout << "SocketServer::Accept - Waiting on accept...\n";
        socketData.sdSocketFdClient = accept(socketData.sdSocketFdServer, (struct sockaddr*)&socketData.sdSockAddrInClient, &sdSockAddrLen);
        if(socketData.sdSocketFdClient < 0)
        {
            std::cout << "SocketClient::Accept - Failed... : " << std::strerror(errno) << std::endl;
            exit(-1);
        }
        else
        {
            std::cout << "SocketClient::Accept - Succeeded...sdSocketFdClient : " << socketData.sdSocketFdClient << std::endl;
            std::cout << "SocketClient::Accept - [" << inet_ntoa(socketData.sdSockAddrInClient.sin_addr) << ":"
                      << ntohs(socketData.sdSockAddrInClient.sin_port) << "]\n";
            clientRunning = true;
            readerThread = std::thread(&SocketServer::ReaderThread, this);
        }
    }
}

void SocketServer::ReaderThread()
{
    char readData[255];
    memset(readData, 0, sizeof(readData));
    while(true)
    {        
        std::cout << "SocketServer::ReaderThread - waiting on read...\n";
        int dataLen = read(socketData.sdSocketFdClient, readData, sizeof(readData));
        if(dataLen == 0) break;
        std::cout << "SocketServer::ReaderThread - Client Data : " << readData << std::endl;
    }
    std::cout << "SocketServer::ReaderThread - Exiting..." << std::endl;
}

void SocketServer::Close()
{
    std::cout << "SocketServer::Close" << std::endl;
    shutdown(socketData.sdSocketFdClient, SHUT_RDWR);
    shutdown(socketData.sdSocketFdServer, SHUT_RDWR);
    close(socketData.sdSocketFdClient);
    close(socketData.sdSocketFdServer);
    socketData.sdSocketFdClient = 0;
    socketData.sdSocketFdServer = 0;
    serverRunning = false;
    clientRunning = false;
    if(readerThread.joinable())
    {
        readerThread.join();
        std::cout << "SocketServer::Close - readerThread joined..." << std::endl;
    }
    else
        std::cout << "SocketServer::Close - readerThread NOT joinable..." << std::endl;
}

void SocketServer::SendData()
{
    char sendData[] = "Hello from SocketServer...";

    int dataLen = write(socketData.sdSocketFdClient, sendData, strlen(sendData));
    
    if(dataLen == strlen(sendData))
        std::cout << "SocketServer::SendData - Succeeded..." << std::endl;
}

SocketServer::~SocketServer()
{
    
}


int main()
{
    SocketData socketData("127.0.0.1", 5555);
    SocketServer socketServer(socketData);
    socketServer.Open();
    socketServer.Bind();
    socketServer.Listen();
    socketServer.Accept();
    socketServer.SendData();
    std::this_thread::sleep_for(std::chrono::seconds(100));
    socketServer.Close();
 
}