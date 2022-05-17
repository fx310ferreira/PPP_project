#include "structs.h"

int main() {
    data teste;
    insere_data(&teste);
    printf("\n%d/%d/%d", teste.dia, teste.mes, teste.ano);
    return 0;
}
