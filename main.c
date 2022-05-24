#include "structs.h"

int main() {
    //noAluno temp;
    //inicializa_lista_de_depesas(&temp.ficha_aluno.lista_De_Despesas);
    //for (int i = 0; i < 2; ++i)
    //    inser_despesa(temp.ficha_aluno.lista_De_Despesas);

    //if(temp.ficha_aluno.lista_De_Despesas->proximo->proximo!=NULL){ printf("ok");}
    //noDespesa* t= temp.ficha_aluno.lista_De_Despesas->proximo;
    //while (t!=NULL){
    //    printf("%s\n%d/%d/%d\n%f\n", t->ficha_despesa.desc, t->ficha_despesa.Data.dia, t->ficha_despesa.Data.mes, t->ficha_despesa.Data.ano, t->ficha_despesa.valor);
    //    t=t->proximo;
    //}
    pAlunos* tabela;
    criar_tabela(&tabela);
    for (int i = 0; i < 26; ++i) {
        if(tabela[i]->proximo==NULL)
            printf("%d ", i);
    }

    cria_ficha_para_novo_aluno(tabela, &tabela[0]->proximo);

    for (int i = 0; i < 26; ++i) {
        if(tabela[i]->proximo==NULL)
            printf("%d ", i);
    }

    return 0;
}
