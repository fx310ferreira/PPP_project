#include "structs.h"

int main() {
    pAlunos* tabela;
    criar_tabela(&tabela);
    //for (int i = 0; i < 26; ++i) {
    //    if(tabela[i]->proximo==NULL)
    //        printf("%d ", i);
    //}
    //printf("\n");
//
//
    for (int i = 0; i < 2; ++i) {
        pAlunos novo_aluno;
        cria_ficha_para_novo_aluno(tabela, &novo_aluno);
        insere_novoAl_naTabela(tabela, novo_aluno);
    }
    //
    //for (int i = 0; i < 26; ++i) {
    //    if(tabela[i]->proximo==NULL)
    //        printf("%d ", i);
    //}
    //destroi_tabela(tabela);
    //pAlunos lista;
    //inicializa_lista_de_alunos(&lista);
    //pAlunos novo_aluno;
//
    //for (int i = 0; i < 2; ++i) {
    //    cria_ficha_para_novo_aluno(tabela, &novo_aluno);
    //    insere_novoAl_naFila(lista, novo_aluno);
    //    //inser_despesa(novo_aluno->ficha_aluno.lista_De_Despesas);
    //}
//
    //save(&lista);
//
    //pAlunos temp= lista->proximo;
    //while (temp!=NULL){
    //    mostra_ficha_do_aluno(temp);
    //    temp=temp->proximo;
    //}
    //destroi_lista_de_alunos(lista);
    pAlunos aluno_antrior_ao_procurado;
    usuario_procura_aluno(tabela, "Qual o parametro que pretendo usar:\n1.Numero\n2-Nome\n3- Parte do Nome", "Aluno nao encontrado", "Aluno encontrado", &aluno_antrior_ao_procurado);
    //printf("%s", aluno_antrior_ao_procurado->proximo->ficha_aluno.nome);

    return 0;
}
