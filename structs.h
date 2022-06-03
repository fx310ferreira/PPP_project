#ifndef PROJETO_STRUCTS_H
#define PROJETO_STRUCTS_H

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

#endif //PROJETO_STRUCTS_H
