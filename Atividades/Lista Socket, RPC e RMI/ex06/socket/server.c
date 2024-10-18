#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

float calcular_salario_liquido(char nivel, float salario_bruto, int dependentes)
{
    float desconto = 0;

    switch (nivel)
    {
    case 'A':
        desconto = dependentes > 0 ? 0.08 : 0.03;
        break;
    case 'B':
        desconto = dependentes > 0 ? 0.10 : 0.05;
        break;
    case 'C':
        desconto = dependentes > 0 ? 0.15 : 0.08;
        break;
    case 'D':
        desconto = dependentes > 0 ? 0.17 : 0.10;
        break;
    default:
        return -1; // Nível inválido
    }

    return salario_bruto - (salario_bruto * desconto);
}

int main()
{
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    char nome[50], nivel;
    float salario_bruto;
    int dependentes;

    // Criação do socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind e listen
    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);
    printf("Aguardando conexão...\n");

    addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
    printf("Cliente conectado.\n");

    // Recebe os dados do cliente
    recv(client_socket, buffer, sizeof(buffer), 0);
    sscanf(buffer, "%s %c %f %d", nome, &nivel, &salario_bruto, &dependentes);

    // Calcula o salário líquido
    float salario_liquido = calcular_salario_liquido(nivel, salario_bruto, dependentes);

    // Prepara a resposta
    sprintf(buffer, "Nome: %s\nNível: %c\nSalário Líquido: %.2f\n", nome, nivel, salario_liquido);

    // Envia o resultado para o cliente
    send(client_socket, buffer, strlen(buffer), 0);

    // Fecha as conexões
    close(client_socket);
    close(server_socket);

    return 0;
}