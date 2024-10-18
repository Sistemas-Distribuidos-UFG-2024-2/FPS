#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void calcular_peso_ideal(char sexo, float altura, char *resultado)
{
    float peso_ideal;
    if (sexo == 'M')
    {
        peso_ideal = (72.7 * altura) - 58;
    }
    else
    {
        peso_ideal = (62.1 * altura) - 44.7;
    }
    sprintf(resultado, "Peso ideal: %.2f", peso_ideal);
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

    // Recebe dados do cliente
    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("Dados recebidos: %s\n", buffer);

    // Extrai altura e sexo do buffer
    float altura;
    char sexo;
    sscanf(buffer, "%f %c", &altura, &sexo);

    // Calcula o peso ideal
    char resultado[1024];
    calcular_peso_ideal(sexo, altura, resultado);

    // Envia o resultado de volta para o cliente
    send(client_socket, resultado, strlen(resultado), 0);

    // Fecha as conexões
    close(client_socket);
    close(server_socket);

    return 0;
}