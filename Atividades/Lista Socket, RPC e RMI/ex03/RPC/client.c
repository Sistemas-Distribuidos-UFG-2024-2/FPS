#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define URL "http://localhost:65432"

// Estrutura para armazenar a resposta do servidor
struct response_data
{
    char *data;
    size_t size;
};

// Função de callback para escrever a resposta do servidor
size_t write_callback(void *ptr, size_t size, size_t nmemb, struct response_data *data)
{
    size_t total_size = size * nmemb;

    // Realoca memória para armazenar a resposta
    data->data = realloc(data->data, data->size + total_size + 1);
    if (data->data == NULL)
    {
        fprintf(stderr, "Failed to allocate memory\n");
        return 0;
    }

    // Copia a resposta para o buffer
    memcpy(&(data->data[data->size]), ptr, total_size);
    data->size += total_size;
    data->data[data->size] = '\0'; // Null-terminate the string

    return total_size;
}

int main()
{
    CURL *curl;
    CURLcode res;
    float n1, n2, n3;
    char postdata[256];
    struct response_data response;

    // Inicializa a estrutura de resposta
    response.data = malloc(1); // Inicializa com um byte
    response.data[0] = '\0';   // Null-terminate
    response.size = 0;

    // Inicializa o cURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        // Lê as notas do aluno
        printf("Digite a primeira nota: ");
        scanf("%f", &n1);
        printf("Digite a segunda nota: ");
        scanf("%f", &n2);
        printf("Digite a terceira nota: ");
        scanf("%f", &n3);

        // Monta os dados para enviar em formato XML-RPC
        snprintf(postdata, sizeof(postdata),
                 "<?xml version=\"1.0\"?>"
                 "<methodCall>"
                 "<methodName>calcular_aprovacao</methodName>"
                 "<params>"
                 "<param><value><array><data>"
                 "<value><double>%.2f</double></value>"
                 "<value><double>%.2f</double></value>"
                 "<value><double>%.2f</double></value>"
                 "</data></array></value></param>"
                 "</params>"
                 "</methodCall>",
                 n1, n2, n3);

        // Exibe o XML enviado (para debug)
        printf("XML enviado:\n%s\n", postdata);

        // Configura a URL
        curl_easy_setopt(curl, CURLOPT_URL, URL);

        // Configura o cabeçalho
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: text/xml");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Configura os dados a serem enviados
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);

        // Define a função de escrita para capturar a resposta
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Executa a requisição
        res = curl_easy_perform(curl);

        // Verifica por erros
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else
        {
            printf("Resposta do servidor:\n%s\n", response.data);
        }

        // Limpeza
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    // Libera a memória
    free(response.data);
    curl_global_cleanup();

    return 0;
}
