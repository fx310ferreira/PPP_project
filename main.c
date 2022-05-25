#include "structs.h"

int main() {
    pAlunos* tabela;
    criar_tabela(&tabela);
    for (int i = 0; i < 26; ++i) {
        if(tabela[i]->proximo==NULL)
            printf("%d ", i);
    }
    printf("\n");


    for (int i = 0; i < 4; ++i) {
        pAlunos novo_aluno;
        cria_ficha_para_novo_aluno(tabela, &novo_aluno);
        insere_novoAl_naTabela(tabela, novo_aluno);
    }

    for (int i = 0; i < 26; ++i) {
        if(tabela[i]->proximo==NULL)
            printf("%d ", i);
    }
    destroi_tabela(tabela);

    return 0;
}
