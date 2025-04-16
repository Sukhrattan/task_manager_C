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
int changeStatus(struct todo *node);
int length(struct todo *node);
void deleteTask(struct todo *node);
void editTask(struct todo *node);
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
        else if(choice == 3){
            changeStatus(node);
        }
        else if(choice == 4){
            deleteTask(node);
        }
        else if(choice == 5){
            editTask(node);
        }
        else if(choice == 6){
            break;
        }
    }
}

void header(){
    printf(ANSI_COLOR_YELLOW"/===================================\\"ANSI_COLOR_RESET"\n");
    printf(ANSI_COLOR_MAGENTA"\tTodo List Manager -C"ANSI_COLOR_MAGENTA"\n");
    printf(ANSI_COLOR_YELLOW"/===================================\\"ANSI_COLOR_RESET"\n");
}

int menu(){
    printf(ANSI_COLOR_GREEN"|"" 1. Add a Task\n");
    printf(ANSI_COLOR_GREEN"|"" 2. Show all Tasks\n");
    printf(ANSI_COLOR_GREEN"|"" 3. Mark Tasks as Completed\n");
    printf(ANSI_COLOR_GREEN"|"" 4. Delete a Task\n");
    printf(ANSI_COLOR_GREEN"|"" 5. Edit a Task\n");
    printf(ANSI_COLOR_GREEN"|"" 6. Quit Application\n"ANSI_COLOR_RESET);
    int choices;
    printf(ANSI_COLOR_YELLOW"---------------------------------"ANSI_COLOR_RESET"\n");
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
        
        printf("\nEnter Task Deadline : ");
        scanf(" %[^\n]%*c",task_ptr->task_deadline);
        
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
int length(struct todo *node){
    struct todo *counter = node->next;
    int count = 0;
    while(counter!=NULL){
        counter = counter->next;
        count++;
    }
    return count;
}


void showTasks(struct todo *node){
    struct todo *printer = node->next;
    int serial = 1;
    if(printer==NULL){
        printf("No Tasks Available");
    }
    else{
        printf("Serial No\tTask Name\tTask Deadline\tTask Status\tTask Priority\n");
    }
    
    while(printer!=NULL){
        
        if(strcmp(printer->task_status,"Completed")){
            printf(" %d\t\t%s\t\t%s\t\t"ANSI_COLOR_RED"%s"ANSI_COLOR_RESET"\t\t%s",serial,printer->tasks,printer->task_deadline,printer->task_status,printer->task_priority);
        }
        else{
            printf(" %d\t\t%s\t\t%s\t\t"ANSI_COLOR_GREEN"%s"ANSI_COLOR_RESET"\t\t%s",serial,printer->tasks,printer->task_deadline,printer->task_status,printer->task_priority);
        }
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
    
int changeStatus(struct todo *node){
    int len = length(node);
    showTasks(node);
    int count;
    int counter = 1;
    printf("\n Choose the Task Number you would like to Mark as Complete! : ");
    scanf(" %d",&count);
    struct todo *status = node->next;
    
    while(status!=NULL){
        if(counter==count){
            strcpy(status->task_status,"Completed");
            printf("Task Status Successfully Changed!");
            break;
        }
        counter++;
        status=status->next;
    } 
 
}

void deleteTask(struct todo *node){
    struct todo *delete = node->next;
    struct todo *prev = node;
    int counter = 1;
    int count;
    printf("\nWhich Task would you like to delete ? : ");
    scanf(" %d",&count);
    while(delete!=NULL){
        if(count == counter){
            prev->next=delete->next;
            free(delete);
            printf("\nTask %d successfully deleted from the Task List.",count);
            break;
            
        }
        counter++;
        prev = delete;
        delete = delete->next;
    }

}

void editTask(struct todo *node){
    struct todo *editor = node->next;
    int sno;
    printf("\nEnter the Serial Number of the Task you would like to edit");
    scanf(" %d",&sno);
    int counter = 1;
    while(editor!=NULL){
        if(sno == counter){
            printf("\nEnter The new Task Name : ");
            scanf(" %[^\n]%*c",editor->tasks);
            printf("\nEnter The new Task Deadline : ");
            scanf(" %[^\n]%*c",editor->task_deadline);
            printf("\nEnter The new Task Priority : ");
            scanf(" %[^\n]%*c",editor->task_priority);
        }
        editor = editor->next;
        counter++;
    }
    
}