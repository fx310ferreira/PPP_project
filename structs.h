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

typedef struct noDespesa* pLista_de_despesas;

typedef struct aluno{
    int num;
    char nome[TAM];
    float saldo;
    data nascimento;
    int ano;
    char turma;
}aluno;

typedef struct no_filaAluno{
    aluno valor;
    struct no_filaAluno * prox;
} no_filaAluno;

typedef struct filaAluno{
    no_filaAluno * inicio;
}filaAluno;

int verifica_mes_30d(data* pData);

int verifica_se_a_data_e_valida(data* pData, int ano_atual);

int valida_caracters(char* string_introduzida);

void insere_data(data* pData);

#endif //PROJETO_STRUCTS_H
