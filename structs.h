//
// Created by fx310 on 11/05/2022.
//

#ifndef PROJETO_STRUCTS_H
#define PROJETO_STRUCTS_H
#define TAM 200 // defenir o tamnho dos parametros usados na funcao valida para auxiliar as
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

typedef struct pNoAluno{
    pAlunos apontaPara;
    struct pNoAluno* proximo;
}pNoAluno;


/* Funcao para "processar" inputs */

int filtrar(int parametro_de_comaparacao, char* bufer, int tamanho_maximo);

int valida_inputs(char* msg_a_pedir_valor, char* msg_de_erro, int size_of_string, char* string, int parametro_de_comparacao);


/* Funções sobre datas */

int verifica_mes_30d(data* pData);

int verifica_se_a_data_e_valida(data* pData, int ano_atual);

int compra_datas(data* chave, data* data1);


/* Funções sobre despesas */

int inicializa_lista_de_depesas(pDespesas* plista);

int verifica_se_a_lista_de_despesas_estaVazia(pDespesas lista);

pDespesas destroi_lista_de_despesas(pDespesas lista);

void procura_lugar_para_despesa(pDespesas lista, data* pData, pDespesas* anterior, pDespesas* atual);

int cria_despesa(pDespesas* pldespesa);

void inser_despesa(pDespesas lista_De_Despesas);


/* Funções sobre alunos */

int inicializa_lista_de_alunos(pAlunos* lista_de_alunos);

int criar_tabela(pAlunos** tabela);

int index_da_tabela(char* string);

int verifica_lista_de_alunoVazia(pAlunos lista_de_aluno);

pAlunos destroi_lista_de_alunos(pAlunos lista);

void destroi_tabela(pAlunos* tabela);

pAlunos procura_aluno_na_tabela_peloNumero(int numero, pAlunos* tabela);

int cria_ficha_para_novo_aluno(pAlunos* tabela, pAlunos* novo_aluno);

void lugar_para_inserirAl(pAlunos* tabela, pAlunos* antrior, pAlunos* atual, pAlunos novo_elemento);

void insere_novoAl_naTabela(pAlunos* tabela, pAlunos novo_aluno);

void mostra_ficha_do_aluno(pAlunos aluno);

int usuario_procura_aluno(pAlunos* tabela, char* msg_a_preguntar_pelo_aluno, char* msg_aluno_nmao_encontrado, char* msg_aluno_encontrado, pAlunos* aluno_a_procurar);

int eliminar_Aluno(pAlunos* tabela);



void insere_novoAl_naFila(pAlunos fila, pAlunos novo_aluno);

void procurar_lugar_na_fila(pAlunos fila, pAlunos* antrior, pAlunos* atual, pAlunos novo_elemento);

/* Funções sobre pNoAluno */

int inicializa_lista_pNoal(pNoAluno** pLista);

int verifica_vazia_pNoal(pNoAluno* lista);

int cria_pNoal(pNoAluno** pnovo_elemento, pAlunos apontaPara);

void procura_lugar_pNoal_ordemalpha(pNoAluno* lista, pNoAluno** atual, pNoAluno** anterior, pNoAluno* novo_elemento);

void procura_lugar_pNoal_ordedecresscente(pNoAluno* lista, pNoAluno** atual, pNoAluno** anterior, pNoAluno* novo_elemento);

pNoAluno* destroi_lista_pNoal(pNoAluno* lista);

/* Funções sobre ficheiros */

void load(pAlunos* plista_de_alunos);

void save(pAlunos* plista_de_alunos);

#endif //PROJETO_STRUCTS_H
