//
// Created by fx310 on 11/05/2022.
//

#include "structs.h"

int verifica_mes_30d(data* pData){
    int var_de_controlo=0;
    int mes_com_30[]={4, 6, 9, 11};

    for (int* i = mes_com_30  ; i<=3+mes_com_30 ; i++) {
        if(*i==pData->mes)
            var_de_controlo=1;
    }
    return var_de_controlo;
}

int verifica_se_a_data_e_valida(data* pData, int ano_atual){
    if(pData->ano<ano_atual || pData->mes>12 || pData->mes<1 || pData->dia<1 || pData->dia>31)
        return 0;
    if(pData->mes==2){
        if( ((pData->ano)%4==0) && ( (((pData->ano)%100==0)&&((pData->ano)%400==0)) ||  ((pData->ano)%100!=0) )){
            if (pData->dia <= 29)
                return 1;
            else
                return 0;
        }
        if(pData->dia<=28)
            return 1;
        else
            return 0;

    }
    if(verifica_mes_30d(pData)){
        if(pData->dia<=30)
            return 1;
        else
            return 0;
    }
    return 1;
}

int valida_caracters(char* string_introduzida){
    int controlo=1;

    for (int i = 0; i < 10; ++i) {
        if(i==2  || i==5){
            if(string_introduzida[i]!='/')
                controlo=0;
        }else {
            if('9'<string_introduzida[i])
                controlo=0;
            if('0'>string_introduzida[i])
                controlo=0;
        }
    }

    return controlo;
}

void insere_data(data* pData){
    char bufer[12];
    int var_controlo=0;

    while (var_controlo==0){
        printf("Introduza uma data valida no formato >> \"DD/MM/AAAA\": \n");
        fseek(stdin, 0, 2);
        fgets(bufer, 12, stdin);
        if(bufer[strlen(bufer)-1]=='\n')
            bufer[strlen(bufer)-1]='\0';
        if(valida_caracters(bufer)==1 && strlen(bufer)==10){
            sscanf(bufer, "%d/%d/%d", &(pData->dia), &(pData->mes), &(pData->ano));
            if(verifica_se_a_data_e_valida(pData, 2000)){
                var_controlo=1;
            }
        }
    }
}