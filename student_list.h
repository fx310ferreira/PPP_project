#ifndef MAIN_C_STUDENT_LIST_H
#define MAIN_C_STUDENT_LIST_H

/* Funções sobre alunos */

int inicializa_lista_de_alunos(pAlunos* lista_de_alunos);

int verifica_lista_de_alunoVazia(pAlunos lista_de_aluno);

pAlunos destroi_lista_de_alunos(pAlunos lista);

void destroi_tabela(pAlunos* tabela);

pAlunos procura_aluno_na_tabela_peloNumero(int numero, pAlunos* tabela);

int cria_ficha_para_novo_aluno(pAlunos* tabela, pAlunos* novo_aluno);

void mostra_ficha_do_aluno(pAlunos aluno);

int usuario_procura_aluno(pAlunos* tabela, char* msg_a_preguntar_pelo_aluno, char* msg_aluno_nmao_encontrado, char* msg_aluno_encontrado, pAlunos* aluno_a_procurar);

/* Funções sobre pNoAluno */

void insere_novoAl_naTabela(pAlunos* tabela, pAlunos novo_aluno);

void lugar_para_inserirAl(pAlunos* tabela, pAlunos* antrior, pAlunos* atual, pAlunos novo_elemento);

int inicializa_lista_pNoal(pNoAluno** pLista);

int verifica_vazia_pNoal(pNoAluno* lista);

int cria_pNoal(pNoAluno** pnovo_elemento, pAlunos apontaPara);

void procura_lugar_pNoal_ordemalpha(pNoAluno* lista, pNoAluno** atual, pNoAluno** anterior, pNoAluno* novo_elemento);

void procura_lugar_pNoal_ordedecresscente(pNoAluno* lista, pNoAluno** atual, pNoAluno** anterior, pNoAluno* novo_elemento);

pNoAluno* destroi_lista_pNoal(pNoAluno* lista);

int criar_tabela(pAlunos** tabela);

int index_da_tabela(char* string);

#endif //MAIN_C_STUDENT_LIST_H
