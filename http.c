#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h> // for getnameinfo()

// Usual socket headers
#include <sys/types.h>
#include <sys/socket.h>
// #include <netinet/in.h>

#include <arpa/inet.h>

#define BACKLOG 100

void getAddress(struct sockaddr *address);

void setHttpHeader(char *httpHeader)
{
    // File object to return
    FILE *htmlData = fopen("index.html", "r");

    // fseek(htmlData, 0, SEEK_END); // seek to end of file
    // long fileSize = ftell(htmlData); // get current file pointer
    // fseek(htmlData, 0, SEEK_SET);

    char line[120];
    char responseData[2400];
    while (fgets(line, 120, htmlData) != 0) {
        strcat(responseData, line);
    }
    // char httpHeader[8000] = "HTTP/1.1 200 OK\r\n\n";
    strcat(httpHeader, responseData);
}

int main(void)
{
    char httpHeader[2400] = "HTTP/1.1 200 OK\nDate: Wed, 21 Jul 2021 14:00:00 GMT\nConnection: keep-alive\nKeep-Alive: timeout=50, max=1000\nServer: ramache\nContent-Length: 2200\nContent-Type: text/html\n\n2370\n\n";

    int serverSocket = socket(
        AF_INET,      
        SOCK_STREAM,  
        0
    );

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8001);
    serverAddress.sin_addr.s_addr = inet_addr("192.168.60.189");

    bind(
        serverSocket,
        (struct sockaddr *) &serverAddress,
        sizeof(serverAddress)
    );

    int listening = listen(serverSocket, BACKLOG);
    if (listening < 0) {
        printf("Error: The server is not listening.\n");
        return 1;
    }
    printf("\n\n\tServer listening on http://192.168.60.189:8001\n");

    setHttpHeader(httpHeader);

    int clientSocket;
    struct sockaddr clientSocketAddr;
    int clientSocketAddrLen;
    printf("1\n");
    while(1) {
        clientSocket = accept(serverSocket, &clientSocketAddr, &clientSocketAddrLen);
        printf("2\n");
        printf("%s ddd", clientSocketAddr.sa_data);
        getAddress(&clientSocketAddr);
        send(clientSocket, httpHeader, sizeof(httpHeader), 0);
        close(clientSocket);
    }
    return 0;
    
}


struct log_socket_address
{
    char addressBuffer[INET_ADDRSTRLEN];
    char serviceBuffer[NI_MAXSERV];
};


void getAddress(struct sockaddr *address)
{
    char hostBuffer[INET_ADDRSTRLEN+1];
    char serviceBuffer[NI_MAXSERV+1]; // defined in `<netdb.h>`
    socklen_t addr_len = sizeof(*address);
    int err = getnameinfo(
        address,
        addr_len,
        hostBuffer,
        sizeof(hostBuffer),
        serviceBuffer,
        sizeof(serviceBuffer),
        NI_NUMERICHOST
    );
    if (err != 0) {
        // TODO ->  Write Logger funciton here 
        printf("Address translition error!");
    }

    

    printf("-> Request Got From: %s\t:%s",hostBuffer, serviceBuffer);

}

