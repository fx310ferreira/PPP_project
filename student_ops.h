#ifndef MAIN_C_STUDENT_OPS_H
#define MAIN_C_STUDENT_OPS_H

//Operations available

int eliminar_Aluno(pAlunos* tabela);

int mostra_aluno_pedidoUser(pAlunos* tabela);

int usario_insere_aluno(pAlunos* tabela);

int usario_insere_despesa(pAlunos* tabela);

int carregar_a_conta_de_um_aluno(pAlunos* tabela);

void listar_todos_aluno_por_ordem_alfabetica(pAlunos* tabela);

int listar_alunos_abaixo_de_um_certoSaldo(pAlunos* tabela);


#endif //MAIN_C_STUDENT_OPS_H
