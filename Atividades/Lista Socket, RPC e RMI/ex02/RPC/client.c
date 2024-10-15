#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

int main(void)
{
    CURL *curl;
    CURLcode res;

    // Definindo os dados de exemplo
    char nome[50];
    char sexo[10];
    int idade;

    // Solicitando entrada do usuário
    printf("Digite o nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0; // Remove o \n do final da string

    printf("Digite o sexo (masculino/feminino): ");
    fgets(sexo, sizeof(sexo), stdin);
    sexo[strcspn(sexo, "\n")] = 0; // Remove o \n do final da string

    printf("Digite a idade: ");
    scanf("%d", &idade);

    // Construindo a string XML-RPC com os dados
    char postdata[512];
    snprintf(postdata, sizeof(postdata),
             "<?xml version=\"1.0\"?>"
             "<methodCall>"
             "<methodName>verificar_maioridade</methodName>"
             "<params>"
             "<param><value><string>%s</string></value></param>"
             "<param><value><string>%s</string></value></param>"
             "<param><value><int>%d</int></value></param>"
             "</params>"
             "</methodCall>",
             nome, sexo, idade);

    // Inicializando o CURL
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8000/RPC2");
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL); // Desabilita a saída desnecessária

        // Executa a requisição
        res = curl_easy_perform(curl);

        // Verifica se houve algum erro
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Limpeza
        curl_easy_cleanup(curl);
    }

    return 0;
}
