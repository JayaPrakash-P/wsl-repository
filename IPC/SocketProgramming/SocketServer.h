#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <thread>
#include <cstring>

class SocketData
{
public:

    int         sdDomain;
    int         sdType;
    int         sdProtocol;
    int         sdSocketFdServer, sdSocketFdClient;
    struct sockaddr_in sdSockAddrInServer, sdSockAddrInClient;
    
    explicit SocketData(std::string ipAddress, int portNumber)
    {
        sdDomain                      = AF_INET;
        sdType                        = SOCK_STREAM;
        sdProtocol                    = 0;
        sdSocketFdServer              = 0;
        sdSocketFdClient              = 0;
        
        sdSockAddrInServer.sin_family       = sdDomain;
        sdSockAddrInServer.sin_port         = htons(portNumber);
        sdSockAddrInServer.sin_addr.s_addr  = inet_addr(ipAddress.c_str());
    }
};

class SocketServer
{
public:
    explicit SocketServer(SocketData& socketData);
    void Open();
    void Bind();
    void Listen();
    void Accept();
    void SendData();
    void Close();
    ~SocketServer();
private:
    bool serverRunning;
    bool clientRunning;
    SocketData socketData;
    std::thread readerThread;
    void ReaderThread();
};