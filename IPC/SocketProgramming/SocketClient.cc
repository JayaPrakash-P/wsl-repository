#include "SocketClient.h"

#include <iostream>
#include <chrono>



SocketClient::SocketClient(SocketData& socketData)
    :socketData(socketData),
     socketConnected(false)
{
    
};

void SocketClient::Open()
{
    socketData.sdSocketFd = socket(socketData.sdDomain, socketData.sdType, socketData.sdProtocol);
    if(socketData.sdSocketFd < 0)
    {
        std::cout << "SocketClient::Open - Failed... : " << std::strerror(errno) << std::endl;
        exit(-1);
    }
    else
        std::cout << "SocketClient::Open - Succeeded...sdSocketFd : " << socketData.sdSocketFd << std::endl;
    
}

void SocketClient::Connect()
{
    if(socketData.sdSocketFd < 0)
    {
        std::cout << "SocketClient::Connect - Failed... Invalid  sdSocketFd : " << socketData.sdSocketFd << std::endl;
        exit(-1);
    }
    else
    {
        socklen_t  sdSockAddrLen = sizeof(socketData.sdSockAddrIn);
        int retVal = connect(socketData.sdSocketFd, (struct sockaddr*)&(socketData.sdSockAddrIn), sdSockAddrLen);
        if(retVal != 0)
        {
            std::cout << "SocketClient::Connect - Failed... : " << std::strerror(errno) << std::endl;
            exit(-1);
        }
        else
        {
            socketConnected = true;
            std::cout << "SocketClient::Connect - Succeeded... retVal : " << retVal << std::endl;
            readerThread = std::thread(&SocketClient::ReaderThread, this);
        }
    }
}

void SocketClient::Close()
{
    std::cout << "SocketClient::Close" << std::endl;
    shutdown(socketData.sdSocketFd, SHUT_RDWR);
    close(socketData.sdSocketFd);
    socketData.sdSocketFd = 0;
    socketConnected = false;
    if(readerThread.joinable())
    {
        readerThread.join();
        std::cout << "SocketClient::Close - readerThread joined..." << std::endl;
    }
    else
        std::cout << "SocketClient::Close - readerThread NOT joinable..." << std::endl;
}

void SocketClient::SendData()
{
    char sendData[] = "Hello from SocketClient...";

    int dataLen = write(socketData.sdSocketFd, sendData, strlen(sendData));
    
    if(dataLen == strlen(sendData))
        std::cout << "SocketClient::SendData - Succeeded..." << std::endl;
}

void SocketClient::ReaderThread()
{
    char readData[255];
    memset(readData, 0, sizeof(readData));
    while(true)
    {        
        std::cout << "SocketClient::ReaderThread - waiting on read...\n";
        int dataLen = read(socketData.sdSocketFd, readData, sizeof(readData));
        if(dataLen == 0) break;
        std::cout << "SocketClient::ReaderThread - Server Data : " << readData << std::endl;
    }
    std::cout << "SocketClient::ReaderThread - Exiting..." << std::endl;
}

SocketClient::~SocketClient()
{
    
}


int main()
{
    SocketData socketData("127.0.0.1", 5555);
    SocketClient socketClient(socketData);
    socketClient.Open();
    socketClient.Connect();
    socketClient.SendData();
    std::this_thread::sleep_for(std::chrono::seconds(100));
    socketClient.Close();
 
}