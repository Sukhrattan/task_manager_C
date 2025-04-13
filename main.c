#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_FONT_BOLD     "\x1b[1;37m"

struct todo{
    char tasks[50];
    char task_deadline[20];
    char task_priority[10];
    char task_status[20];
    struct todo *next;
};

void header();
int menu();
int addTask(struct todo *node);
void showTasks(struct todo *node);

int main(){
    
    
    

    struct todo *node = (struct todo *)malloc(sizeof(struct todo));
    node->next = NULL;

    while(1){
        header();
        int choice = menu();
        if(choice == 1){
            addTask(node);
        }

        else if(choice == 2){
            showTasks(node);
        }


        else if(choice == 6){
            break;
        }
    }
}

void header(){
    printf(ANSI_COLOR_YELLOW"/===================================\\"ANSI_COLOR_YELLOW"\n");
    printf(ANSI_COLOR_MAGENTA"\tTodo List Manager -C"ANSI_COLOR_MAGENTA"\n");
    printf(ANSI_COLOR_YELLOW"/===================================\\"ANSI_COLOR_YELLOW"\n");
}

int menu(){
    printf("|"" 1. Add a Task\n");
    printf("|"" 2. Show all Tasks\n");
    printf("|"" 3. Mark Tasks as Completed\n");
    printf("|"" 4. Delete a Task\n");
    printf("|"" 5. Edit a Task\n");
    printf("|"" 6. Quit Application\n");
    int choices;
    printf("------------------------\n");
    printf(ANSI_FONT_BOLD"Choose an Option to perform a Command! : "ANSI_FONT_BOLD);
    scanf("%d",&choices);
    printf("\n");
    return choices;
}

int addTask(struct todo *node){
    char command = ' ';
    struct todo *current = node;
    
    
    while(command!='X'){
        struct todo *task_ptr = (struct todo *)malloc(sizeof(struct todo));
        task_ptr->next=NULL;

        printf("\nEnter Task Name : ");
        scanf(" %[^\n]%*c",task_ptr->tasks);
        fflush(stdin);
        printf("\nEnter Task Deadline : ");
        scanf(" %[^\n]%*c",task_ptr->task_deadline);
        fflush(stdin);
        printf("\nEnter Task Priority (high,medium,low) : ");
        scanf(" %s",task_ptr->task_priority);
        
        strcpy(task_ptr->task_status,"Pending"); //default status while adding task in pending
        
        if(node->next==NULL){
            node->next = task_ptr;
        }
        else{
            while((current->next!=NULL)){
                current=current->next;
            }
            current->next=task_ptr;
        }
        printf("\nIf you want to go Back to Menu Press X otherwise press any key to add another task!");
        scanf(" %c",&command);
        

    }
    

}

void showTasks(struct todo *node){
    struct todo *printer = node->next;
    int serial = 1;
    printf("Serial No\tTask Name\tTask Deadline\tTask Status\tTask Priority\n");
    while(printer!=NULL){
        
        printf(" %d\t\t%s\t\t%s\t\t%s\t\t%s",serial,printer->tasks,printer->task_deadline,printer->task_status,printer->task_priority);
        printf("\n");
        printer = printer->next;
        serial += 1;
    }
    char request;
    do {
        printf("\nPress 'B' to go back to menu: ");
        scanf(" %c", &request);
    } while (request != 'B' && request != 'b');
}
    

