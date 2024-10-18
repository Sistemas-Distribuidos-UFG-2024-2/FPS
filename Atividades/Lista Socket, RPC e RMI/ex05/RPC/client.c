#include <stdio.h>
#include <xmlrpc-c/base.h>
#include <xmlrpc-c/client.h>

#define NAME "Cliente Classificação Nadador"
#define VERSION "1.0"

int main(int argc, const char **argv)
{
    xmlrpc_env env;
    xmlrpc_value *resultP;
    char *server_url = "http://localhost:8000/RPC2";
    const char *method_name = "classificar_nadador";
    int idade;

    if (argc != 2)
    {
        printf("Uso: %s <idade>\n", argv[0]);
        return 1;
    }

    idade = atoi(argv[1]);

    // Inicializa o ambiente
    xmlrpc_env_init(&env);

    // Faz a chamada ao servidor Python
    xmlrpc_client_init2(&env, XMLRPC_CLIENT_NO_FLAGS, NAME, VERSION, NULL, 0);
    resultP = xmlrpc_client_call(&env, server_url, method_name, "(i)", idade);

    // Tratamento de erro
    if (env.fault_occurred)
    {
        printf("Erro ao chamar método RPC: %s\n", env.fault_string);
    }
    else
    {
        const char *resultado;
        xmlrpc_read_string(&env, resultP, &resultado);
        printf("Classificação: %s\n", resultado);
    }

    // Limpeza
    xmlrpc_DECREF(resultP);
    xmlrpc_env_clean(&env);
    xmlrpc_client_cleanup();

    return 0;
}