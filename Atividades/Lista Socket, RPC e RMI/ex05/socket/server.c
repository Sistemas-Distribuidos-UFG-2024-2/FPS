#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void classificar_nadador(int idade, char *classificacao)
{
    if (idade >= 5 && idade <= 7)
    {
        strcpy(classificacao, "Infantil A (5-7 anos)");
    }
    else if (idade >= 8 && idade <= 10)
    {
        strcpy(classificacao, "Infantil B (8-10 anos)");
    }
    else if (idade >= 11 && idade <= 13)
    {
        strcpy(classificacao, "Juvenil A (11-13 anos)");
    }
    else if (idade >= 14 && idade <= 17)
    {
        strcpy(classificacao, "Juvenil B (14-17 anos)");
    }
    else if (idade >= 18)
    {
        strcpy(classificacao, "Adulto (maiores de 18 anos)");
    }
    else
    {
        strcpy(classificacao, "Sem categoria (menos de 5 anos)");
    }
}

int main()
{
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];

    // Cria o socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Liga o socket à porta
    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Escuta por conexões
    listen(server_socket, 5);
    printf("Aguardando conexão...\n");

    addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
    printf("Cliente conectado.\n");

    // Recebe idade do cliente
    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("Dados recebidos: %s\n", buffer);

    // Extrai a idade
    int idade;
    sscanf(buffer, "%d", &idade);

    // Classifica o nadador
    char classificacao[1024];
    classificar_nadador(idade, classificacao);

    // Envia o resultado de volta para o cliente
    send(client_socket, classificacao, strlen(classificacao), 0);

    // Fecha as conexões
    close(client_socket);
    close(server_socket);

    return 0;
}