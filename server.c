#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    int server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    int client_socket_fd;
    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9000);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = bind(server_socket_fd, (struct sockaddr *)&server_address, sizeof(server_address));

    if(ret < 0)
    {
        printf("Bind not succesfull.\n");
        exit(1);
    }

    ret = listen(server_socket_fd, 10);

    if(ret < 0)
    {
        printf("Failed to listen.\n");
        exit(1);
    }

    printf("Listening on port ......\n");

    client_socket_fd = accept(server_socket_fd, NULL, NULL);

    while (1)
    {
        char buffer[256];
        ret = recv(client_socket_fd, buffer, sizeof(buffer), 0);

        if(ret < 0)
        {
            printf("Message not recieved.\n");
        }
        else
        {
            printf("%s\n", buffer);
        }

        ret = send(client_socket_fd, buffer, sizeof(buffer), 0);

        if (ret < 0)
        {
            printf("Message not sent.\n");
        }
    }

    close(server_socket_fd);
    close(client_socket_fd);
}