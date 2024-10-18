#include <stdio.h>

float *calcular_credito_1_svc(float *saldo_medio, struct svc_req *req)
{
    static float credito;

    if (*saldo_medio >= 0 && *saldo_medio <= 200)
    {
        credito = 0;
    }
    else if (*saldo_medio >= 201 && *saldo_medio <= 400)
    {
        credito = *saldo_medio * 0.20;
    }
    else if (*saldo_medio >= 401 && *saldo_medio <= 600)
    {
        credito = *saldo_medio * 0.30;
    }
    else
    {
        credito = *saldo_medio * 0.40;
    }
    return &credito;
}