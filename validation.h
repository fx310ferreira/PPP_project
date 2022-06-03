#ifndef MAIN_C_VALIDATION_H
#define MAIN_C_VALIDATION_H

//Validation related functions

int filtrar(int parametro_de_comaparacao, char* bufer, int tamanho_maximo);

int valida_inputs(char* msg_a_pedir_valor, char* msg_de_erro, int size_of_string, char* string, int parametro_de_comparacao);


//Date related functions

int verifica_mes_30d(data* pData);

int verifica_se_a_data_e_valida(data* pData, int ano_atual);

int compra_datas(data* chave, data* data1);

//File related functions

int load(pAlunos** ptabela);

void save(pAlunos* tabela);


#endif //MAIN_C_VALIDATION_H
