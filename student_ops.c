#include "imports.h"

int eliminar_Aluno(pAlunos* tabela){
    pAlunos alunoAntrior_a_eleminar;
    printf("____________________Student Deletion_____________________\n\n");

    char msg_pede_parametro[]="Delete student by:\n"
                              "1-Number\n"
                              "2-Name\n"
                              "--\32";
    int controlo= usuario_procura_aluno(tabela, msg_pede_parametro, "", "", &alunoAntrior_a_eleminar);
    if(controlo==3){
        return 3;
    }else if(controlo==2){
        return 2;
    }
    else if (controlo==1)
        return 1;
    else{
        pAlunos temp=alunoAntrior_a_eleminar->proximo;
        char comand;
        char string[2];
        printf("Do you want to delete the student\n"
               "Name: %s\n"
               "Number: %d\n", alunoAntrior_a_eleminar->proximo->ficha_aluno.nome,  alunoAntrior_a_eleminar->proximo->ficha_aluno.numero);
        while (controlo==0) {
            valida_inputs("(Y/N)--\32", "ERROR: Chose betwen Y(yes) and N(no)", 2, string, 3);
            sscanf(string, "%c", &comand);
            if(comand=='Y' || comand=='N'){
                controlo=1;
                if(comand =='N') return 3;
            } else
                printf("ERROR: Chose between Y(yes) and N(no)");
        }
        alunoAntrior_a_eleminar->proximo=temp->proximo;
        free(temp);
    }
    return 0;
}

int mostra_aluno_pedidoUser(pAlunos* tabela){
    pAlunos alunoAntrior_aoProcurado;
    char msg_pede_parametro[]="Delete student by:\n"
                              "1-Number\n"
                              "2-Name\n"
                              "--\32";
    int controlo= usuario_procura_aluno(tabela, msg_pede_parametro, "", "", &alunoAntrior_aoProcurado);
    if(controlo==2)
        return 2;
    else if (controlo==1)
        return 1;
    else{
        mostra_ficha_do_aluno(alunoAntrior_aoProcurado->proximo);
    }
    return 0;
}

int usario_insere_aluno(pAlunos* tabela){
    pAlunos novo_aluno, anterior, atual;
    printf("____________________Student Creation_____________________\n\n");
    if(cria_ficha_para_novo_aluno(tabela, &novo_aluno)==1) return 1;
    lugar_para_inserirAl(tabela, &anterior, &atual, novo_aluno);
    anterior->proximo=novo_aluno;
    novo_aluno->proximo=atual;
    return 0;
}

int usario_insere_despesa(pAlunos* tabela){
    pAlunos alunoAntrior_ao_pretendido;
    char msg_pede_parametro[]="Add expense by:\n"
                              "1-Number\n"
                              "2-Name\n"
                              "--\32";
    int controlo= usuario_procura_aluno(tabela, msg_pede_parametro, "", "", &alunoAntrior_ao_pretendido);
    printf("\n");
    if(controlo==2)
        return 2;
    else if (controlo==1)
        return 1;
    else{
        pDespesas nova_despesa;
        if(cria_despesa(&nova_despesa)==1) return 1;
        int control = inser_despesa(alunoAntrior_ao_pretendido->proximo, nova_despesa);
        if(control == 3) return 3;
    }
    return 0;
}

int carregar_a_conta_de_um_aluno(pAlunos* tabela){
    pAlunos alunoAntrior_aoProcurado;
    char msg_pede_parametro[]="Add balance by:\n"
                              "1-Number\n"
                              "2-Name\n"
                              "--\32";
    int controlo= usuario_procura_aluno(tabela, msg_pede_parametro, "", "", &alunoAntrior_aoProcurado);
    if(controlo==2)
        return 2;
    else if (controlo==1)
        return 1;
    else{
        float carregamento;
        char valor_a_carregar[7];
        char msg_a_pedir_calor_a_carregar[]="Input the amount to charge the student account: ";
        char msg_erro_valor_introduzido[]="ERROR: Invalid inout.";
        valida_inputs(msg_a_pedir_calor_a_carregar, msg_erro_valor_introduzido, 7, valor_a_carregar, 0);
        sscanf(valor_a_carregar, "%f", &carregamento);
        alunoAntrior_aoProcurado->proximo->ficha_aluno.saldo+=carregamento;
    }
    return 0;
}

void listar_todos_aluno_por_ordem_alfabetica(pAlunos* tabela){
    pAlunos temp;
    printf("\n");
    printf("______________________Students List______________________\n\n");
    for (int i = 0; i < 26; ++i) {
        temp=tabela[i]->proximo;
        if(temp!=NULL){
            printf("__________________________%c______________________________\n", 'A'+i);
            while (temp!=NULL){
                printf("Name:%28s, Number:%3d, Class:%d %c\n", temp->ficha_aluno.nome, temp->ficha_aluno.numero, temp->ficha_aluno.ano, temp->ficha_aluno.turma);
                temp=temp->proximo;
            }
        }
    }
}

int listar_alunos_abaixo_de_um_certoSaldo(pAlunos* tabela){
    float valor_maximo;
    char valor[7];
    char msg_a_pedir_valor_minimo[]="Input the balance from which you whish to list the students:";
    char msg_erro_input_invalido[]="ERROR: Invalid value.";
    valida_inputs(msg_a_pedir_valor_minimo, msg_erro_input_invalido, 7, valor, 0);
    sscanf(valor, "%f", &valor_maximo);
    pNoAluno* lista;
    pAlunos temp;
    inicializa_lista_pNoal(&lista);
    for (int i = 0; i < 26; ++i) {
        temp=tabela[i]->proximo;
        while (temp!=NULL){
            if(temp->ficha_aluno.saldo<valor_maximo){
                pNoAluno* novo_elm, *antrior, *atual;
                if(cria_pNoal(&novo_elm, temp)==1) return 1;
                procura_lugar_pNoal_ordedecresscente(lista, &atual, &antrior, novo_elm);
                antrior->proximo=novo_elm;
                novo_elm->proximo=atual;
            }
            temp=temp->proximo;
        }
    }
    pNoAluno* t=lista->proximo;
    if(verifica_vazia_pNoal(lista)==1){
        printf("WARNING: No student has a balance inferior the boundary.\n");
    } else {
        printf("_________Students With Balance Bellow to %3.2f__________\n", valor_maximo);
        while (t!=NULL){
            printf("Name: %38s Budget:%3.2f\n", t->apontaPara->ficha_aluno.nome, t->apontaPara->ficha_aluno.saldo);
            t=t->proximo;
        }
    }
    lista= destroi_lista_pNoal(lista);
    return 0;
}
