#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 65432
#define SERVER_IP "127.0.0.1"

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *message = "Olá, servidor!";
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nErro ao criar socket\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Converte o endereço IP do servidor para o formato binário
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        printf("\nEndereço inválido/Endereço não suportado\n");
        return -1;
    }

    // Conecta ao servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConexão falhou\n");
        return -1;
    }

    // Envia a mensagem para o servidor
    send(sock, message, strlen(message), 0);
    printf("Mensagem enviada: %s\n", message);

    // Recebe a resposta do servidor
    int valread = read(sock, buffer, 1024);
    printf("Resposta do servidor: %s\n", buffer);

    close(sock);
    return 0;
}
