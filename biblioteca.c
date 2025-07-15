#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char nome[100];
    char email[100];
    char cpf[15];
    char matricula[20];
    int ativo;
} Student;

typedef struct Book {
    char titulo[100];
    char codigo[20];
    char autor[100];
    int disponivel;
} Book;

typedef struct QueueNode {
    char student_matricula[20];
    char book_codigo[20];
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

typedef struct {
    char book_codigos[100][20];
    int top;
} Stack;

Student* students;
Book* books;
int total_students = 0;
int total_books = 0;
int students_capacity = 10;
int books_capacity = 10;

Queue* create_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

void enqueue(Queue* queue, const char* student_matricula, const char* book_codigo) {
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
    strcpy(new_node->student_matricula, student_matricula);
    strcpy(new_node->book_codigo, book_codigo);
    new_node->next = NULL;
    
    if (queue->front == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

void dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return;
    }
    
    QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    
    free(temp);
}

void push(Stack* stack, const char* book_codigo) {
    if (stack->top == 100 - 1) {
        printf("Pilha cheia! Nao e possivel adicionar mais livros devolvidos.\n");
        return;
    }
    
    stack->top++;
    strcpy(stack->book_codigos[stack->top], book_codigo);
}

void pop(Stack* stack) {
    if (stack->top == -1) {
        return;
    }
    
    stack->top--;
}

void create_student() {
    if(total_students >= students_capacity) {
        students_capacity = students_capacity * 2;
        students = (Student*)realloc(students, students_capacity * sizeof(Student));
    }
    
    printf("Digite o nome do aluno: ");
    scanf("%s", students[total_students].nome);
    
    printf("Digite o email: ");
    scanf("%s", students[total_students].email);
    
    printf("Digite o CPF: ");
    scanf("%s", students[total_students].cpf);
    
    printf("Digite a matricula: ");
    scanf("%s", students[total_students].matricula);
    
    students[total_students].ativo = 1;
    total_students++;
    printf("Aluno cadastrado com sucesso!\n");
}

void list_students() {
    int i = 0;
    if(total_students == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    
    printf("\n=== LISTA DE ALUNOS ===\n");
    while(i < total_students) {
        if(students[i].ativo == 1) {
            printf("Nome: %s\n", students[i].nome);
            printf("Email: %s\n", students[i].email);
            printf("CPF: %s\n", students[i].cpf);
            printf("Matricula: %s\n", students[i].matricula);
            printf("-------------------\n");
        }
        i++;
    }
}

void update_student() {
    char matricula_busca[20];
    int encontrado = 0;
    int i = 0;
    
    printf("Digite a matricula do aluno a ser editado: ");
    scanf("%s", matricula_busca);
    
    while(i < total_students) {
        if(students[i].ativo == 1 && strcmp(students[i].matricula, matricula_busca) == 0) {
            encontrado = 1;
            printf("Aluno encontrado! Digite os novos dados:\n");
            
            printf("Novo nome: ");
            scanf("%s", students[i].nome);
            
            printf("Novo email: ");
            scanf("%s", students[i].email);
            
            printf("Novo CPF: ");
            scanf("%s", students[i].cpf);
            
            printf("Aluno atualizado com sucesso!\n");
            break;
        }
        i++;
    }
    
    if(encontrado == 0) {
        printf("Aluno nao encontrado!\n");
    }
}

void delete_student() {
    char matricula_busca[20];
    int encontrado = 0;
    int i = 0;
    
    printf("Digite a matricula do aluno a ser removido: ");
    scanf("%s", matricula_busca);
    
    while(i < total_students) {
        if(students[i].ativo == 1 && strcmp(students[i].matricula, matricula_busca) == 0) {
            students[i].ativo = 0;
            encontrado = 1;
            printf("Aluno removido com sucesso!\n");
            break;
        }
        i++;
    }
    
    if(encontrado == 0) {
        printf("Aluno nao encontrado!\n");
    }
}

void create_book() {
    if(total_books >= books_capacity) {
        books_capacity = books_capacity * 2;
        books = (Book*)realloc(books, books_capacity * sizeof(Book));
    }
    
    printf("Digite o titulo do livro: ");
    scanf("%s", books[total_books].titulo);
    
    printf("Digite o codigo do livro: ");
    scanf("%s", books[total_books].codigo);
    
    printf("Digite o autor: ");
    scanf("%s", books[total_books].autor);
    
    books[total_books].disponivel = 1;
    total_books++;
    printf("Livro cadastrado com sucesso!\n");
}

void list_books() {
    int i = 0;
    if(total_books == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }
    
    printf("\n=== LISTA DE LIVROS ===\n");
    while(i < total_books) {
        if(books[i].disponivel == 1) {
            printf("Titulo: %s\n", books[i].titulo);
            printf("Codigo: %s\n", books[i].codigo);
            printf("Autor: %s\n", books[i].autor);
            printf("-------------------\n");
        }
        i++;
    }
}

void update_book() {
    char codigo_busca[20];
    int encontrado = 0;
    int i = 0;
    
    printf("Digite o codigo do livro a ser editado: ");
    scanf("%s", codigo_busca);
    
    while(i < total_books) {
        if(books[i].disponivel == 1 && strcmp(books[i].codigo, codigo_busca) == 0) {
            encontrado = 1;
            printf("Livro encontrado! Digite os novos dados:\n");
            
            printf("Novo titulo: ");
            scanf("%s", books[i].titulo);
            
            printf("Novo autor: ");
            scanf("%s", books[i].autor);
            
            printf("Livro atualizado com sucesso!\n");
            break;
        }
        i++;
    }
    
    if(encontrado == 0) {
        printf("Livro nao encontrado!\n");
    }
}

void delete_book() {
    char codigo_busca[20];
    int encontrado = 0;
    int i = 0;
    
    printf("Digite o codigo do livro a ser removido: ");
    scanf("%s", codigo_busca);
    
    while(i < total_books) {
        if(books[i].disponivel == 1 && strcmp(books[i].codigo, codigo_busca) == 0) {
            books[i].disponivel = 0;
            encontrado = 1;
            printf("Livro removido com sucesso!\n");
            break;
        }
        i++;
    }
    
    if(encontrado == 0) {
        printf("Livro nao encontrado!\n");
    }
}

void request_book_loan() {
    char matricula[20];
    char codigo[20];
    
    printf("Digite a matricula do aluno: ");
    scanf("%s", matricula);
    
    printf("Digite o codigo do livro: ");
    scanf("%s", codigo);
    
    enqueue(loan_queue, matricula, codigo);
    printf("Solicitacao de emprestimo adicionada a fila com sucesso!\n");
}

void return_book() {
    char codigo[20];
    
    printf("Digite o codigo do livro a ser devolvido: ");
    scanf("%s", codigo);
    
    push(return_stack, codigo);
    printf("Livro devolvido com sucesso!\n");
}

void display_queue_recursive(QueueNode* node) {
    if (node == NULL) {
        return;
    }
    
    char* student_name = "Aluno nao encontrado";
    char* book_title = "Livro nao encontrado";
    int i = 0;
    
    while(i < total_students) {
        if(students[i].ativo == 1 && strcmp(students[i].matricula, node->student_matricula) == 0) {
            student_name = students[i].nome;
            break;
        }
        i++;
    }
    
    i = 0;
    while(i < total_books) {
        if(books[i].disponivel == 1 && strcmp(books[i].codigo, node->book_codigo) == 0) {
            book_title = books[i].titulo;
            break;
        }
        i++;
    }
    
    printf("Aluno: %s (Matricula: %s) | Livro: %s (Codigo: %s)\n", 
           student_name, node->student_matricula, book_title, node->book_codigo);
    display_queue_recursive(node->next);
}

void display_waiting_queue() {
    if (loan_queue->front == NULL) {
        printf("Nenhum aluno esperando por livros.\n");
        return;
    }
    
    printf("\n=== FILA DE ESPERA ===\n");
    display_queue_recursive(loan_queue->front);
}

void display_returned_books() {
    int contador=0;
    
    if (return_stack->top == -1) {
        printf("Nenhum livro foi devolvido ainda.\n");
        return;
    }
    
    printf("\n=== LIVROS DEVOLVIDOS ===\n");
    contador=return_stack->top;
    while(contador>=0){
        char* book_title = "Livro nao encontrado";
        int i = 0;
        
        while(i < total_books) {
            if(books[i].disponivel == 1 && strcmp(books[i].codigo, return_stack->book_codigos[contador]) == 0) {
                book_title = books[i].titulo;
                break;
            }
            i++;
        }
        
        printf("Livro: %s (Codigo: %s)\n", book_title, return_stack->book_codigos[contador]);
        contador=contador-1;
    }
}

void free_queue_recursive(QueueNode* node) {
    if (node == NULL) {
        return;
    }
    
    free_queue_recursive(node->next);
    free(node);
}

Queue* loan_queue;
Stack* return_stack;

int main() {
    students = (Student*)malloc(students_capacity * sizeof(Student));
    books = (Book*)malloc(books_capacity * sizeof(Book));
    loan_queue = create_queue();
    return_stack = create_stack();
    
    int choice;
    int continuar=1;
    int student_choice;
    int book_choice;
    int continuar_student = 1;
    int continuar_book = 1;
    
    while(continuar==1){
        printf("\n=== SISTEMA DE BIBLIOTECA IFAL ARAPIRACA ===\n");
        printf("1. Gerenciar alunos\n");
        printf("2. Gerenciar livros\n");
        printf("3. Solicitar emprestimo de livro\n");
        printf("4. Devolver livro\n");
        printf("5. Consultar fila de espera\n");
        printf("6. Consultar livros devolvidos\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);
        
        if(choice==1){
            continuar_student = 1;
            while(continuar_student == 1) {
                printf("\n=== GERENCIAMENTO DE ALUNOS ===\n");
                printf("1. Cadastrar aluno\n");
                printf("2. Listar alunos\n");
                printf("3. Editar aluno\n");
                printf("4. Remover aluno\n");
                printf("5. Voltar ao menu principal\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &student_choice);
                
                if(student_choice == 1) {
                    create_student();
                }
                else if(student_choice == 2) {
                    list_students();
                }
                else if(student_choice == 3) {
                    update_student();
                }
                else if(student_choice == 4) {
                    delete_student();
                }
                else if(student_choice == 5) {
                    continuar_student = 0;
                }
                else {
                    printf("Opcao invalida!\n");
                }
            }
        }
        else if(choice==2){
            continuar_book = 1;
            while(continuar_book == 1) {
                printf("\n=== GERENCIAMENTO DE LIVROS ===\n");
                printf("1. Cadastrar livro\n");
                printf("2. Listar livros\n");
                printf("3. Editar livro\n");
                printf("4. Remover livro\n");
                printf("5. Voltar ao menu principal\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &book_choice);
                
                if(book_choice == 1) {
                    create_book();
                }
                else if(book_choice == 2) {
                    list_books();
                }
                else if(book_choice == 3) {
                    update_book();
                }
                else if(book_choice == 4) {
                    delete_book();
                }
                else if(book_choice == 5) {
                    continuar_book = 0;
                }
                else {
                    printf("Opcao invalida!\n");
                }
            }
        }
        else if(choice==3){
            request_book_loan();
        }
        else if(choice==4){
            return_book();
        }
        else if(choice==5){
            display_waiting_queue();
        }
        else if(choice==6){
            display_returned_books();
        }
        else if(choice==7){
            printf("Saindo do sistema e liberando memoria...\n");
            free_queue_recursive(loan_queue->front);
            free(loan_queue);
            free(return_stack);
            free(students);
            free(books);
            continuar=0;
        }
        else{
            printf("Opcao invalida! Tente novamente.\n");
        }
    }
    
    return 0;
} 