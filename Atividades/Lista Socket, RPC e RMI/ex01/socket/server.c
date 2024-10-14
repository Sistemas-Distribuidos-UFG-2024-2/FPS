#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 65432

// Função para calcular o salário reajustado com base no cargo
float calcular_reajuste(char *cargo, float salario)
{
    if (strcmp(cargo, "operador") == 0)
    {
        return salario * 1.20;
    }
    else if (strcmp(cargo, "programador") == 0)
    {
        return salario * 1.18;
    }
    else
    {
        return salario; // Sem reajuste se cargo for desconhecido
    }
}

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Criando o socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Falha na criação do socket");
        exit(EXIT_FAILURE);
    }

    // Configurando o socket para reutilizar o endereço
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("Falha na configuração do socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Vinculando o socket ao endereço
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Falha no bind");
        exit(EXIT_FAILURE);
    }

    // Escutando por conexões
    if (listen(server_fd, 3) < 0)
    {
        perror("Falha no listen");
        exit(EXIT_FAILURE);
    }

    printf("Servidor aguardando conexão...\n");

    // Aceitando uma conexão
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("Falha ao aceitar conexão");
        exit(EXIT_FAILURE);
    }

    // Recebendo os dados do cliente
    read(new_socket, buffer, 1024);

    // Separar os dados recebidos
    char nome[50], cargo[50];
    float salario;
    sscanf(buffer, "%[^,],%[^,],%f", nome, cargo, &salario);

    // Calcular o salário reajustado
    float salario_reajustado = calcular_reajuste(cargo, salario);

    // Preparar a resposta para o cliente
    char resposta[1024];
    snprintf(resposta, sizeof(resposta), "Nome: %s, Salário reajustado: %.2f", nome, salario_reajustado);

    // Enviar a resposta de volta ao cliente
    send(new_socket, resposta, strlen(resposta), 0);

    // Fechar a conexão
    close(new_socket);
    close(server_fd);

    return 0;
}
