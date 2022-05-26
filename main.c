#include "structs.h"

int main() {
    pAlunos lista_de_alunos;
    load(&lista_de_alunos);
    int command = -1;
    pAlunos novo_aluno;
    char waiter;
    do{
        printf("_____________________________\n"
               "1-Crete a new student\n"
               "2-Delete a student\n"
               "3-List all students\n"
               "1-Crete a new student\n"
               "1-Student Information\n"
               "0-Leave\n"
               "Command:");
        scanf("%d", &command);
        switch (command) {
            case 1:
                cria_ficha_para_novo_aluno(&novo_aluno);
                lista_de_alunos->proximo->proximo=novo_aluno;
                break;
            case 2:
                print_student(&lista_de_alunos);
                char nome[NAME];
                printf("Wich student do you want to delete?");
                scanf(" %[^\n]s",nome);
                int control = delete_student(&lista_de_alunos, nome);
                if(control){
                    printf("Student deleted\n");
                }else{
                    printf("ERROR!\n");
                }
                break;
            case 3:
                print_student(&lista_de_alunos);
                break;
            case 0:
                command = 0;
                break;
            default:
                printf("Invalid input!\n");
                break;
        }
        printf("Press any button to continue.\n");
        if(getchar()=='\n')
            continue;
    } while (command != 0);

    printf("Saving...\n");
    save(&lista_de_alunos);
    printf("Saved.");
    return 0;
}
