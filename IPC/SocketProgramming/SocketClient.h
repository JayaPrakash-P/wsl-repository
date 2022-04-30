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
    int         sdSocketFd;
    struct sockaddr_in sdSockAddrIn;
    
    explicit SocketData(std::string ipAddress, int portNumber)
    {
        sdDomain                      = AF_INET;
        sdType                        = SOCK_STREAM;
        sdProtocol                    = 0;
        sdSocketFd                    = 0;
        
        sdSockAddrIn.sin_family       = sdDomain;
        sdSockAddrIn.sin_port         = htons(portNumber);
        sdSockAddrIn.sin_addr.s_addr  = inet_addr(ipAddress.c_str());
    }
};

class SocketClient
{
public:
    explicit SocketClient(SocketData& socketData);
    void Open();
    void Connect();
    void SendData();
    void Close();
    ~SocketClient();
private:
    bool socketConnected;
    SocketData socketData;
    std::thread  readerThread;
    void ReaderThread();
};