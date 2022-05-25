#include "structs.h"

int main() {
    pAlunos lista_de_alunos;
    load(&lista_de_alunos);
    int command = -1;
    pAlunos novo_aluno;
    do{
        printf("_____________________________\n"
               "1-Crete a new student\n"
               "1-Crete a new student\n"
               "1-Crete a new student\n"
               "1-Crete a new student\n"
               "0-Leave\n"
               "Command:");
        scanf("%d", &command);
        switch (command) {
            case 1:
                cria_ficha_para_novo_aluno(&novo_aluno);
                lista_de_alunos->proximo->proximo=novo_aluno;
                break;
            case 0:
                command = 0;
                break;
            default:
                printf("Invalid input!\n");
                break;
        }
    } while (command != 0);

    printf("Saving...\n");
    save(&lista_de_alunos);
    printf("Saved.");
    return 0;
}
