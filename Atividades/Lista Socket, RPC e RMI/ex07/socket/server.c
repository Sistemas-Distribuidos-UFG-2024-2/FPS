#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int verifica_aposentadoria(int idade, int tempo_servico)
{
    if (idade >= 65 || (idade >= 60 && tempo_servico >= 25) || tempo_servico >= 30)
    {
        return 1; // Pode se aposentar
    }
    return 0; // Não pode se aposentar
}

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("Listen");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        int idade, tempo_servico, resultado;
        char buffer[1024] = {0};

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("Accept");
            exit(EXIT_FAILURE);
        }

        read(new_socket, buffer, 1024);
        sscanf(buffer, "%d %d", &idade, &tempo_servico);

        resultado = verifica_aposentadoria(idade, tempo_servico);

        snprintf(buffer, sizeof(buffer), "%d", resultado);
        send(new_socket, buffer, strlen(buffer), 0);
        close(new_socket);
    }

    return 0;
}