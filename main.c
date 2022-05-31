#include "structs.h"

int main() {
    pAlunos* tabela;

    load(&tabela);

    for (int i = 0; i < 26; ++i) {
        pAlunos temp=tabela[i];
        while (temp->proximo!=NULL){
            temp=temp->proximo;
            printf("%s %d\n", temp->ficha_aluno.nome, temp->ficha_aluno.numero);
        }
    }



    printf("\n");

    //pAlunos aluno_antrior_ao_procurado;
    //usuario_procura_aluno(tabela, "Qual o parametro que pretende usar:\n1.Numero\n2-Nome\n3- Parte do Nome", "Aluno nao encontrado", "Aluno encontrado", &aluno_antrior_ao_procurado);
    //printf("%s", aluno_antrior_ao_procurado->proximo->ficha_aluno.nome);
    //eliminar_Aluno(tabela);
    //mostra_aluno_pedidoUser(tabela);
    //usario_insere_aluno(tabela);
    //usario_insere_despesa(tabela);
    //carregar_a_conta_de_um_aluno(tabela);
    listar_todos_aluno_por_ordem_alfabetica(tabela);
    save(tabela);
    destroi_tabela(tabela);




    return 0;
}
