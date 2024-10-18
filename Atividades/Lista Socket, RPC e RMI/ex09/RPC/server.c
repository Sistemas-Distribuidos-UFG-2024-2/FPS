#include <stdio.h>
#include <string.h>

char **obter_nome_carta_1_svc(int *valores, struct svc_req *req)
{
    static char nome[100];
    int valor = valores[0];
    int naipe = valores[1];

    char *valores_str[] = {"Ás", "Dois", "Três", "Quatro", "Cinco", "Seis", "Sete", "Oito", "Nove", "Dez", "Valete", "Dama", "Rei"};
    char *naipes_str[] = {"Ouros", "Paus", "Copas", "Espadas"};

    sprintf(nome, "%s de %s", valores_str[valor - 1], naipes_str[naipe - 1]);
    return &nome;
}