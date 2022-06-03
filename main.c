#include "imports.h"

int main() {
    pAlunos *tabela;
    int control = load(&tabela);
    if (control) {
        printf("Error loading file. Data might be corrupted! \n");
        return 1;
    }
    int command = 3;
    char buffer[3] = "";
    int clearbuffer;
    do {

        printf("_________________________________________________________\n\n"
               "    1-Crete a new student\n"
               "    2-Delete a student\n"
               "    3-List all students\n"
               "    4-Sort by balance\n"
               "    5-Student Information\n"
               "    6-Create an expense\n"
               "    7-Charge student account\n"
               "    0-Leave\n"
               "Enter-Repeat last instruction\n"
               "\n_________________________________________________________\n"
               "--\32");
        fgets(buffer, 3, stdin);
        sscanf(buffer, "%d", &command);
        switch (command) {
            case 1:
                control = usario_insere_aluno(tabela);
                if (control) {
                    printf("ERROR!\n");
                } else {
                    printf("Student created.\n");
                }
                break;
            case 2:
                control = eliminar_Aluno(tabela);
                if (control == 3) {
                    printf("Deletion canceled\n");
                } else if (control == 2) {
                    printf("ERROR! Student Not Found.\n");
                } else if (control == 1) {
                    printf("ERROR! Problem related to memory allocation.\n");
                } else {
                    printf("Student deleted.\n");
                }
                break;
            case 3:
                listar_todos_aluno_por_ordem_alfabetica(tabela);
                break;
            case 4:
                control = listar_alunos_abaixo_de_um_certoSaldo(tabela);
                if (control == 1) {
                    printf("ERROR! Problem related to memory allocation.\n");
                }
                break;
            case 5:
                control = mostra_aluno_pedidoUser(tabela);
                if (control == 2) {
                    printf("ERROR! Student Not Found.\n");
                } else if (control == 1) {
                    printf("ERROR! Problem related to memory allocation.\n");
                }
                break;
            case 6:
                control = usario_insere_despesa(tabela);
                if(control == 1){
                    printf("ERROR! Problem related to memory allocation.\n");
                }else if(control == 2){
                    printf("ERROR! Student Not Found.\n");
                }else if(control == 3){
                    printf("ERROR: Student does not have enough balance.");
                }else{
                    printf("Expense created.\n");
                }
                break;
            case 7:
                control = carregar_a_conta_de_um_aluno(tabela);
                if(control == 1){
                    printf("ERROR! Problem related to memory allocation.\n");
                }else if(control == 2){
                    printf("ERROR! Student Not Found.\n");
                }else{
                    printf("Student account charged successfully.\n");
                }
                break;
            case 0:
                command = 0;
                break;
            default:
                printf("Invalid input!\n");
                break;
            }
        if(command != 0){
            printf("\n_______________Press enter to continue___________________\n");
            do {
                clearbuffer = getchar();
            } while (clearbuffer != '\n' && clearbuffer != EOF);

            printf("\n\n\n\n\n\n\n\n\n\n\n");
            printf("\n\n\n\n\n\n\n\n\n\n\n");
            printf("\n\n\n");

        }
        }while (command != 0);
                //Save in file
                printf("\nSaving...\n");
                save(tabela);
                destroi_tabela(tabela);
                printf("Saved.");
                return 0;
        }
