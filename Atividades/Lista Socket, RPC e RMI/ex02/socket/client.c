#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sock;
    struct sockaddr_in server;
    char message[100], server_reply[200];

    // Criando o socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("Erro ao criar socket\n");
        return 1;
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(65432);

    // Conectando ao servidor
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Erro ao conectar\n");
        return 1;
    }

    printf("Conectado ao servidor\n");

    // Coletando informações do usuário
    char nome[50];
    char sexo;
    int idade;

    printf("Digite o nome: ");
    scanf("%s", nome);
    printf("Digite o sexo (M/F): ");
    scanf(" %c", &sexo);
    printf("Digite a idade: ");
    scanf("%d", &idade);

    // Formatando mensagem no formato nome,sexo,idade
    sprintf(message, "%s,%c,%d", nome, sexo, idade);

    // Enviando dados para o servidor
    if (send(sock, message, strlen(message), 0) < 0)
    {
        printf("Erro ao enviar\n");
        return 1;
    }

    // Recebendo resposta do servidor
    if (recv(sock, server_reply, 200, 0) < 0)
    {
        printf("Erro ao receber resposta\n");
        return 1;
    }

    printf("Resposta do servidor: %s\n", server_reply);

    // Fechando o socket
    close(sock);
    return 0;
}
