//
// Created by fx310 on 11/05/2022.
//

#ifndef PROJETO_STRUCTS_H
#define PROJETO_STRUCTS_H
#define TAM 200
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{ //estrutura que guarda datas
    int dia;
    int mes;
    int ano;
}data;

typedef struct{
    data Data;
    int valor;
    char desc[100];
}despesa;

typedef struct noDespesa{
    despesa ficha_despesa;
    struct noDespesa* proximo;
}noDespesa ;

typedef struct noDespesa* pDespesas;



typedef struct aluno{
    int num;
    char nome[TAM];
    float saldo;
    data nascimento;
    int ano;
    char turma;
    pDespesas lista_De_Despesas;
}aluno;

typedef struct no_filaAluno{
    aluno ficha_aluno;
    struct no_filaAluno * prox;
} no_filaAluno;

typedef struct filaAluno{
    no_filaAluno * inicio;
}filaAluno;


/* Funções sobre datas */

int verifica_mes_30d(data* pData);

int verifica_se_a_data_e_valida(data* pData, int ano_atual);

int valida_caracters(char* string_introduzida);

int insere_data(data* pData);

int compra_datas(data* chave, data* data1);


/* Funções sobre despesas */

int inicializa_lista_de_depesas(pDespesas* plista);

int verifica_se_a_lista_de_despesas_estaVazia(pDespesas lista);

int cria_despesa(pDespesas* pldespesa);

void inser_despesa(pDespesas lista_De_Despesas);

void mostra_tabela(pDespesas teste);

#endif //PROJETO_STRUCTS_H
