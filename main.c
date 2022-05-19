#include "structs.h"

int main() {
    no_filaAluno temp;
    inicializa_lista_de_depesas(&temp.ficha_aluno.lista_De_Despesas);
    for (int i = 0; i < 2; ++i)
        inser_despesa(temp.ficha_aluno.lista_De_Despesas);

    //if(temp.ficha_aluno.lista_De_Despesas->proximo->proximo!=NULL){ printf("ok");}
    noDespesa* t= temp.ficha_aluno.lista_De_Despesas->proximo;
    while (t!=NULL){
        printf("%s\n%d/%d/%d\n%d\n", t->ficha_despesa.desc, t->ficha_despesa.Data.dia, t->ficha_despesa.Data.mes, t->ficha_despesa.Data.ano, t->ficha_despesa.valor);
        t=t->proximo;
    }
    return 0;
}
