#include <stdio.h>

int *verifica_aposentadoria_1_svc(int *args, struct svc_req *req)
{
    static int resultado;
    int idade = args[0];
    int tempo_servico = args[1];

    if (idade >= 65 || (idade >= 60 && tempo_servico >= 25) || tempo_servico >= 30)
    {
        resultado = 1; // Pode se aposentar
    }
    else
    {
        resultado = 0; // Não pode se aposentar
    }
    return &resultado;
}