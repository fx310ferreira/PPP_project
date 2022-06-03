#ifndef MAIN_C_EXPENSES_H
#define MAIN_C_EXPENSES_H

//Expenses related functions

int inicializa_lista_de_depesas(pDespesas* plista);

int verifica_se_a_lista_de_despesas_estaVazia(pDespesas lista);

pDespesas destroi_lista_de_despesas(pDespesas lista);

void procura_lugar_para_despesa(pDespesas lista, data* pData, pDespesas* anterior, pDespesas* atual);

int cria_despesa(pDespesas* pldespesa);

int inser_despesa(pAlunos aluno, pDespesas nova_despesa);

void insere_despesa_auxiliar_load(pAlunos aluno, pDespesas nova_despesa);


#endif //MAIN_C_EXPENSES_H
