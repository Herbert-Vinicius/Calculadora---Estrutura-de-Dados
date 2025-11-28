#include <stdio.h>
#include <string.h>
#include "expressao.h"

int main() {
    Expressao e;

    strcpy(e.posFixa, "3 4 + 5 *");
    printf("Pos-fixa: %s\n", e.posFixa);

    strcpy(e.inFixa, getFormaInFixa(e.posFixa));
    printf("Infixa: %s\n", e.inFixa);

    e.Valor = getValorPosFixa(e.posFixa);
    printf("Valor: %.2f\n", e.Valor);

    return 0;
}