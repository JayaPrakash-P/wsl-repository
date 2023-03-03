#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <map>
#include <thread>
#include <cstring>
#include <csignal>
#include <memory>

using namespace std;

class SocketServer
{
    unsigned int portNum;
    int serverSocketFd;
    struct sockaddr_in serverSockaddrIn;
    std::map<int,std::string > clientSocketMap;
    bool keepRunning = false;
    
public:

    explicit SocketServer(unsigned int portNum):portNum(portNum)
    {
        cout << "[SocketServer]Creating socket @ Port : " << portNum << endl;
        if((serverSocketFd = socket(AF_INET, SOCK_STREAM, 0)) < 1)
        {
            cout << "[SocketServer]Exiting...Error creating socket @ Port : " << portNum << endl;
            exit(1);
        }
        keepRunning = true;
    }
    
    ~SocketServer()
    {
        cout << "[SocketServer]Destructing server...\n";
        keepRunning = false;
        close(serverSocketFd);
        cout << "[SocketServer]Exiting!!!\n";
    }
    
    void Bind()
    {
        cout << "[SocketServer]Binding socket...\n";
        
        memset(&serverSockaddrIn, 0, sizeof(serverSockaddrIn));
        serverSockaddrIn.sin_family         = AF_INET;
        serverSockaddrIn.sin_addr.s_addr    = INADDR_ANY;
        serverSockaddrIn.sin_port           = htons(portNum);
        
        if(bind(serverSocketFd, (sockaddr*)&serverSockaddrIn, sizeof(serverSockaddrIn)) < 0 )
        {
            cout << "[SocketServer]Exiting...Binding socket failed!\n";
            exit(1);
        }
    }
    
    void Listen()
    {
        if(listen(serverSocketFd, 10 ) < 0 )
        {
            cout << "[SocketServer]Exiting...Listen failed!\n";
            exit(1);
        }
    }
    
    void Accept()
    {

        while(keepRunning)
        {
            int clientSocketFd;
            struct sockaddr_in clientSockaddrIn;
            socklen_t clientSockLen = sizeof(clientSockaddrIn);
            memset(&clientSockaddrIn, 0, clientSockLen);
        
            if ((clientSocketFd = accept(serverSocketFd, (sockaddr*)&clientSockaddrIn, &clientSockLen)) < 0)
            {
                cout << "[SocketServer]Exiting...Accept failed!\n";
                exit(0);
            }

            cout << "[SocketServer]Accepted new connection...\n";
            std::thread commsThread(&SocketServer::SimplexCommunication, this, clientSocketFd);
            commsThread.detach();
        }
    }
    
    void SimplexCommunication(int clientSocketFd)
    {
        cout << "[SocketServer]SimplexCommunication started for clientSocketFd : " << clientSocketFd << "\n";

        ProcessClientHeader(clientSocketFd);

        bool clientActive = true;
        
        while(clientActive && keepRunning)
        {
           clientActive = ReceiveData(clientSocketFd);


            /* memset(&data, 0, sizeof(data));
            const char* serverGreeting = "\n";
            memcpy(&data, serverGreeting, strlen(serverGreeting));
            send(clientSocketFd, &data, strlen(data), 0); */
        }
    }
    
    void ProcessClientHeader(int clientSocketFd)
    {
        char data[255] = {0};
        std::string clientName;

        int bytesReceived = recv(clientSocketFd, &data, 255, 0);
        if (bytesReceived > 0)
            clientName = data;
        else
            clientName = "Unknown_" + std::to_string(clientSocketFd);
        
        clientSocketMap.emplace(clientSocketFd, clientName);
        cout << "[SocketServer]Registered  [" << data << "] with clientSocketFd : " << clientSocketFd << "\n";
    }
    
    bool ReceiveData(int clientSocketFd)
    {
        char data[255] = {0};
        int bytesReceived = 0;
        bytesReceived = recv(clientSocketFd, &data, 255, 0);
        if (bytesReceived <= 0)
        {
            cout << "Client[" << clientSocketMap[clientSocketFd] << "] bytesReceived : " << bytesReceived << endl;
            close(clientSocketFd);
            cout << "Client[" << clientSocketMap[clientSocketFd] << "] Exiting...\n";
            clientSocketMap.erase(clientSocketFd);
            for(auto& [skID,name] : clientSocketMap)
            {
                cout << "skID : " << skID << data << endl;
                cout << "name : " << name << data << endl;
            }
            return false;
        }
        else
        {
            cout << "Client[" << clientSocketMap[clientSocketFd] << "] bytesReceived : " << bytesReceived << endl;
            cout << "Client[" << clientSocketMap[clientSocketFd] << "] data : " << data << endl;
            return true;
        }
    }
    
    
};

void SignalHandler(int signal)
{
    switch(signal)
    {
        case SIGSEGV:
            cout << "SIGSEGV!!!\n";
            break;
        case SIGINT:
            cout << "SIGINT!!!\n";
            break;
        default:
            cout << "<UNKNOWN> : " << signal << endl;
    }
    exit(signal);
}

int main(int argc, char ** argv)
{
    unsigned int portNum = 8080;
    
    if(argc == 1)
    {
       cout << "Defaulting Server to PortNum : 8080\n" ;
    }
    else if (argc == 2)
    {
        portNum = atoi(argv[1]);
    }
    else
    {
        cout << "Usage : " << argv[0] << " <port_number>\n\tExample : " << argv[0] << " 8080\n";
        exit(1);
    }
    
    std::unique_ptr<SocketServer> sServer = make_unique<SocketServer>(portNum);
    
    signal(SIGSEGV, SignalHandler);
    signal(SIGINT, SignalHandler);

    sServer->Bind();
    sServer->Listen();
    sServer->Accept();
    while(true)
        sleep(5);
    
    return 0;
}