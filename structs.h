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
    float valor;
    char desc[100];
}despesa;

typedef struct noDespesa{
    despesa ficha_despesa;
    struct noDespesa* proximo;
}noDespesa;

typedef struct noDespesa* pDespesas;



typedef struct ficha_aluno{
    int numero;
    char nome[TAM];
    float saldo;
    data data_nascimento;
    int ano;
    char turma;
    pDespesas lista_De_Despesas;
}aluno;

typedef struct noAluno{
    aluno ficha_aluno;
    struct noAluno * proximo;
} noAluno;


typedef struct noAluno* pAlunos;

//typedef struct filaAluno{
//    no_filaAluno * inicio;
//}filaAluno;

/* Funcao para "processar" inputs */

int filtrar(int parametro_de_comaparacao, char* bufer, int tamanho_maximo);

int valida_inputs(char* msg_a_pedir_valor, char* msg_de_erro, int size_of_string, char* string, int parametro_de_comparacao);

/* Funções sobre datas */

int verifica_mes_30d(data* pData);

int verifica_se_a_data_e_valida(data* pData, int ano_atual);

int valida_caracters(char* string_introduzida);

int compra_datas(data* chave, data* data1);


/* Funções sobre despesas */

int inicializa_lista_de_depesas(pDespesas* plista);

int verifica_se_a_lista_de_despesas_estaVazia(pDespesas lista);

int cria_despesa(pDespesas* pldespesa);

void inser_despesa(pDespesas lista_De_Despesas);

void mostra_tabela(pDespesas teste);

/* Funções sobre alunos */

int inicializa_lista_de_alunos(pAlunos* lista_de_alunos);

int criar_tabela(pAlunos** tabela);

int index_da_tabela(char* string);

int verifica_lista_de_alunoVazia(pAlunos lista_de_aluno);

pAlunos destroi_lista_de_alunos(pAlunos lista);

void destroi_tabela(pAlunos* tabela);

int cria_ficha_para_novo_aluno(pAlunos* tabela, pAlunos* novo_aluno);

#endif //PROJETO_STRUCTS_H
