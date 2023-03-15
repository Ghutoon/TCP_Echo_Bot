#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    int client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9000);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = connect(client_socket_fd, (struct sockaddr *)&server_address, sizeof(server_address));

    if(ret < 0)
    {
        printf("Connection not established.\n");
        exit(1);
    }
    else
    {
        printf("Connection established with server.\n");

    }
    char buffer[256];
    while(fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        ret = send(client_socket_fd, buffer, sizeof(buffer), 0);

        if (ret < 0)
        {
            printf("Message not sent.\n");
        }

        ret = recv(client_socket_fd, buffer, sizeof(buffer), 0);

        if (ret < 0)
        {
            printf("Message not recieved.\n");
        }
        else
        {
            printf("%s\n", buffer);
        }
    }
    close(client_socket_fd);
}