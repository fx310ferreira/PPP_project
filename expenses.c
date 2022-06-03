#include "imports.h"

int inicializa_lista_de_depesas(pDespesas* plista){
    noDespesa* temp= (noDespesa*) malloc(sizeof(noDespesa));
    if(temp!=NULL){
        temp->proximo=NULL;
        *plista=temp;
        return 0;
    } else
        return 1;
}

int verifica_se_a_lista_de_despesas_estaVazia(pDespesas lista){
    if(lista->proximo==NULL)
        return 1;
    return 0;
}

pDespesas destroi_lista_de_despesas(pDespesas lista){
    pDespesas temp;
    while (!verifica_se_a_lista_de_despesas_estaVazia(lista)){
        temp=lista;
        lista=lista->proximo;
        free(temp);
    }
    free(lista);
    return NULL;
}

void procura_lugar_para_despesa(pDespesas lista, data* pData, pDespesas* anterior, pDespesas* atual){
    *anterior=lista;
    *atual=lista->proximo;
    while ((*atual)!=NULL && compra_datas(pData, &((*atual)->ficha_despesa.Data))>=1){
        *anterior=*atual;
        *atual=(*atual)->proximo;
    }
    if((*atual)!=NULL && compra_datas(&(*atual)->ficha_despesa.Data, pData)!=2)
        (*atual)=NULL;
}


int cria_despesa(pDespesas* pldespesa){
    noDespesa* temp=(noDespesa*) malloc(sizeof(noDespesa));
    if (temp == NULL) return 1;

    printf("____________________Create An Expense____________________\n\n");

    char valor_da_despesa[7];
    char msg_a_pedir_valor_da_despesa[]="Input the expense value:";
    char msg_valor_nValido[]="ERROR: Invalid input.";
    valida_inputs(msg_a_pedir_valor_da_despesa, msg_valor_nValido, 7, valor_da_despesa, 0);
    sscanf(valor_da_despesa, "%f", &temp->ficha_despesa.valor);

    char msg_pede_descricao[]="Input the expense description:";
    char msg_erro_input_invalido[]="ERROR: Invalid input.";
    valida_inputs(msg_pede_descricao, msg_erro_input_invalido, 100, temp->ficha_despesa.desc, 5);

    char data[11];
    char msg_pede_data[]="Input the expense date(DD/MM/YYYY):";
    char msg_data_invalida[]="ERROR: Invalid input.";
    valida_inputs(msg_pede_data, msg_data_invalida, 11, data, 1);
    sscanf(data, "%d/%d/%d", &temp->ficha_despesa.Data.dia, &temp->ficha_despesa.Data.mes, &temp->ficha_despesa.Data.ano);


    temp->proximo=NULL;

    *pldespesa=temp;
    return 0;
}

int inser_despesa(pAlunos aluno, pDespesas nova_despesa){
    pDespesas antrior, atual;
    procura_lugar_para_despesa(aluno->ficha_aluno.lista_De_Despesas, &nova_despesa->ficha_despesa.Data, &antrior, &atual);
    if(aluno->ficha_aluno.saldo < nova_despesa->ficha_despesa.valor) return 3;
    aluno->ficha_aluno.saldo-=nova_despesa->ficha_despesa.valor;
    nova_despesa->proximo=antrior->proximo;
    antrior->proximo=nova_despesa;
    return 0;
}

void insere_despesa_auxiliar_load(pAlunos aluno, pDespesas nova_despesa){
    pDespesas antrior, atual;
    procura_lugar_para_despesa(aluno->ficha_aluno.lista_De_Despesas, &nova_despesa->ficha_despesa.Data, &antrior, &atual);
    nova_despesa->proximo=antrior->proximo;
    antrior->proximo=nova_despesa;
}
