#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define DISCOVERY_SERVER_ADDR "127.0.0.1" 
#define DISCOVERY_SERVER_PORT 65432      
#define BUFFER_SIZE 1024                 

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int bytes_received;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Erro ao criar o socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(DISCOVERY_SERVER_PORT);
    if (inet_pton(AF_INET, DISCOVERY_SERVER_ADDR, &server_addr.sin_addr) <= 0) {
        perror("Erro ao converter o endereço do servidor");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Conectar ao serviço de descoberta
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Erro ao conectar ao serviço de descoberta");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Conectado ao serviço de descoberta.\n");

    // Enviar solicitação ao serviço de descoberta
    const char *request = "GET_SERVERS"; // Comando para obter a lista de servidores
    if (send(sockfd, request, strlen(request), 0) < 0) {
        perror("Erro ao enviar solicitação");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Solicitação enviada: %s\n", request);

    // Receber a resposta do servidor
    memset(buffer, 0, BUFFER_SIZE);
    bytes_received = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received < 0) {
        perror("Erro ao receber resposta");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Imprimir a resposta recebida
    buffer[bytes_received] = '\0';
    printf("Servidores disponíveis:\n%s\n", buffer);

    close(sockfd);
    return 0;
}