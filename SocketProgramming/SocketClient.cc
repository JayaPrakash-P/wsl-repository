#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <list>
#include <cstring>
#include <csignal>
#include <memory>

using namespace std;

class SocketClient
{
    unsigned int portNum;
    std::string userName;
    int clientSocketFd;
    struct sockaddr_in serverSockaddrIn;
    bool keepRunning = false;
    
    
public:

    explicit SocketClient(unsigned int portNum, std::string userName):portNum(portNum),userName(userName)
    {
        cout << "[SocketClient]Creating socket @ Port : " << portNum << " : for user : " << userName << endl;
        if((clientSocketFd = socket(AF_INET, SOCK_STREAM, 0)) < 1)
        {
            cout << "[SocketClient]Exiting...Error creating socket @ Port : " << portNum << endl;
            exit(1);
        }
        keepRunning = true;
    }
    
    ~SocketClient()
    {
        cout << "[SocketClient]Destructing server...\n";
        keepRunning = false;
        close(clientSocketFd);
        cout << "[SocketClient]Exiting!!!\n";
    }
    
    void Connect()
    {
        cout << "[SocketClient]Connecting socket...\n";
        
        memset(&serverSockaddrIn, 0, sizeof(serverSockaddrIn));
        serverSockaddrIn.sin_family         = AF_INET;
        serverSockaddrIn.sin_addr.s_addr    = inet_addr("127.0.0.1");
        serverSockaddrIn.sin_port           = htons(portNum);
        
        if(connect(clientSocketFd, (sockaddr*)&serverSockaddrIn, sizeof(serverSockaddrIn)) < 0 )
        {
            cout << "[SocketClient]Exiting...Binding socket failed!\n";
            exit(1);
        }
        
        SimplexCommunication(clientSocketFd);
    }
    
    void SimplexCommunication(int clientSocketFd)
    {
        char data[255] = {0};
        memcpy(&data, userName.c_str(), userName.length());
        send(clientSocketFd, &data, strlen(data), 0);

        while(keepRunning)
        {
            memset(&data, 0, sizeof(data));
            cout << "Client[" << clientSocketFd << "](Me) : ";
            cin.getline(data, sizeof(data));
            send(clientSocketFd, &data, strlen(data), 0);
            /*int bytesReceived = recv(clientSocketFd, &data, 255, 0);
            if (bytesReceived < 0)
                break;
            else
                cout << "\nServer[" << clientSocketFd << "] : " << data << endl; */
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

    std::string userName;
    cout << "Your chat name : ";
    std::getline(std::cin, userName);
    
    std::unique_ptr<SocketClient> sClient = make_unique<SocketClient>(portNum,userName);
    
    signal(SIGSEGV, SignalHandler);
    signal(SIGINT, SignalHandler);
    
    sClient->Connect();

    while(true)
        sleep(5);
    
    return 0;
}