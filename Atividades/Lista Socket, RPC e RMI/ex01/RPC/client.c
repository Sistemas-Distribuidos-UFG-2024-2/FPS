#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Função callback para capturar a resposta do servidor
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    strcat(userdata, ptr);
    return size * nmemb;
}

int main()
{
    CURL *curl;
    CURLcode res;
    char response[1024] = {0};

    // Dados do funcionário
    char cargo[50];
    char nome[50];
    float salario;

    // Coletar dados do funcionário
    printf("Digite o nome do funcionário: ");
    scanf("%s", nome);
    printf("Digite o cargo (operador/programador): ");
    scanf("%s", cargo);
    printf("Digite o salário: ");
    scanf("%f", &salario);

    // Construir o corpo da solicitação XML-RPC
    char xml_request[1024];
    snprintf(xml_request, sizeof(xml_request),
             "<?xml version=\"1.0\"?>"
             "<methodCall>"
             "<methodName>calcular_reajuste</methodName>"
             "<params>"
             "<param><value><string>%s</string></value></param>"
             "<param><value><string>%s</string></value></param>"
             "<param><value><double>%.2f</double></value></param>"
             "</params>"
             "</methodCall>",
             cargo, salario);

    // Inicializar CURL
    curl = curl_easy_init();
    if (curl)
    {
        // Configurar a URL do servidor RPC
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:65432/RPC2");

        // Definir a solicitação como POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // Definir os dados do XML
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, xml_request);

        // Definir o callback para capturar a resposta
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        // Fazer a solicitação
        res = curl_easy_perform(curl);

        // Verificar se houve erro
        if (res != CURLE_OK)
        {
            fprintf(stderr, "Erro na solicitação RPC: %s\n", curl_easy_strerror(res));
        }
        else
        {
            // Exibir a resposta do servidor
            printf("Resposta do servidor: %s\n", response);
        }

        // Limpar CURL
        curl_easy_cleanup(curl);
    }

    return 0;
}
