#include <stdio.h>
#include <xmlrpc-c/base.h>
#include <xmlrpc-c/client.h>

#define NAME "Peso Ideal RPC Cliente"
#define VERSION "1.0"

int main(int argc, const char **argv)
{
    xmlrpc_env env;
    xmlrpc_value *resultP;
    char *server_url = "http://localhost:8000/RPC2";
    const char *method_name = "calcular_peso_ideal";
    double altura;
    char sexo;

    if (argc != 3)
    {
        printf("Uso: %s <altura> <sexo(M/F)>\n", argv[0]);
        return 1;
    }

    altura = atof(argv[1]);
    sexo = argv[2][0];

    // Inicializa o ambiente
    xmlrpc_env_init(&env);

    // Faz a chamada ao servidor Python
    xmlrpc_client_init2(&env, XMLRPC_CLIENT_NO_FLAGS, NAME, VERSION, NULL, 0);
    resultP = xmlrpc_client_call(&env, server_url, method_name, "(ds)", altura, sexo);

    // Tratamento de erro
    if (env.fault_occurred)
    {
        printf("Erro ao chamar método RPC: %s\n", env.fault_string);
    }
    else
    {
        double resultado;
        xmlrpc_read_double(&env, resultP, &resultado);
        printf("Peso ideal: %.2f\n", resultado);
    }

    // Limpeza
    xmlrpc_DECREF(resultP);
    xmlrpc_env_clean(&env);
    xmlrpc_client_cleanup();

    return 0;
}