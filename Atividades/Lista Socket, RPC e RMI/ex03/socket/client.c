#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 65432

int main()
{
    int sock;
    struct sockaddr_in server_address;
    char buffer[1024];
    float n1, n2, n3;

    // Cria o socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("Erro ao criar socket");
        return 1;
    }

    // Configura o endereço do servidor
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Conecta ao servidor
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Erro ao conectar ao servidor");
        close(sock);
        return 1;
    }

    // Lê as notas do aluno
    printf("Digite a primeira nota: ");
    scanf("%f", &n1);
    printf("Digite a segunda nota: ");
    scanf("%f", &n2);
    printf("Digite a terceira nota: ");
    scanf("%f", &n3);

    // Envia as notas para o servidor
    snprintf(buffer, sizeof(buffer), "%.2f,%.2f,%.2f", n1, n2, n3);
    send(sock, buffer, strlen(buffer), 0);

    // Recebe o resultado do servidor
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Resultado: %s\n", buffer);

    // Fecha o socket
    close(sock);
    return 0;
}
