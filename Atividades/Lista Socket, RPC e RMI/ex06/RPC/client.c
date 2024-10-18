#include <stdio.h>
#include <xmlrpc-c/base.h>
#include <xmlrpc-c/client.h>

#define NAME "Cliente Calculo Salario"
#define VERSION "1.0"

int main(int argc, const char **argv)
{
    xmlrpc_env env;
    xmlrpc_value *resultP;
    char *server_url = "http://localhost:8000/RPC2";
    const char *method_name = "calcular_salario_liquido";
    char nivel;
    float salario_bruto;
    int dependentes;

    if (argc != 4)
    {
        printf("Uso: %s <nivel> <salario_bruto> <dependentes>\n", argv[0]);
        return 1;
    }

    nivel = argv[1][0];
    salario_bruto = atof(argv[2]);
    dependentes = atoi(argv[3]);

    // Inicializa o ambiente
    xmlrpc_env_init(&env);

    // Faz a chamada ao servidor Python
    xmlrpc_client_init2(&env, XMLRPC_CLIENT_NO_FLAGS, NAME, VERSION, NULL, 0);
    resultP = xmlrpc_client_call(&env, server_url, method_name, "(sfi)", &nivel, salario_bruto, dependentes);

    // Tratamento de erro
    if (env.fault_occurred)
    {
        printf("Erro ao chamar método RPC: %s\n", env.fault_string);
    }
    else
    {
        double salario_liquido;
        xmlrpc_read_double(&env, resultP, &salario_liquido);
        printf("Salário Líquido: %.2f\n", salario_liquido);
    }

    // Limpeza
    xmlrpc_DECREF(resultP);
    xmlrpc_env_clean(&env);
    xmlrpc_client_cleanup();

    return 0;
}