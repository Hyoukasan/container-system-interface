#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct container container_t; 
typedef struct node node_t;

struct node
{
    uint32_t value;
    
    node_t*  ptr_next;
    node_t*  ptr_prev;
};

typedef enum
{
    STACK,
    QUEUE,
    DEQUE

} TYPE_CONTAINER;

struct container
{
    /*Pointers on data_list*/
    node_t *head, *tail;

    size_t size_container;

    /*Methods for stack_container*/
    void     (*push)(container_t* self, uint32_t* value);
    void     (*pop)(container_t* self);

    void     (*peek)(container_t* self);

    /*Methods for queue_container*/
    void     (*enqueue)(container_t* self, uint32_t* value);
    void     (*dequeue)(container_t* self);

    void     (*front_queue)(container_t* self);

    /*Methods for deque_container*/
    void     (*push_front)(container_t* self, uint32_t* value);
    void     (*push_back)(container_t* self, uint32_t* value);
    
    void     (*pop_front)(container_t* self);
    void     (*pop_back)(container_t* self);

    void     (*peek_front)(const container_t* self);
    void     (*peek_back)(const container_t* self);

    /*General methods*/
    void     (*size)(const container_t* self);
    void     (*free)(container_t* self);
    void     (*reverse)(container_t* self);
    void     (*rotate)(container_t* self, uint32_t k); 
    void     (*sort)(container_t* self, uint32_t ascending);
    void     (*find_index)(const container_t* self, uint32_t value); 
    void*    (*max)(const container_t* self);          
    void*    (*min)(const container_t* self);            
};

void size(const container_t* self)
{   
    printf("%u", self->size_container);
}

void print_all(container_t* self) 
{
    node_t* tmp_ptr = self->head;

    if (tmp_ptr == NULL) {
        printf("empty\n");
        return;
    }

    while (tmp_ptr != NULL) {
        printf("%u ", tmp_ptr->value);

        tmp_ptr = tmp_ptr->ptr_next;
    }

    return;
}

void clear_container(container_t* self)
{
    node_t* tmp_ptr = NULL;
    node_t* new_ptr = self->head;

    while (new_ptr != NULL) {
        tmp_ptr = new_ptr;
        new_ptr = new_ptr->ptr_next;
        free(tmp_ptr);
    }

    self->head = NULL;
    self->tail = NULL;
    self->size_container = 0;
    return;
}

void reverse_container(container_t* self)
{
    node_t* current = self->head;
    node_t* tmp = NULL;

    while (current != NULL) {
        tmp = current->ptr_prev;
        current->ptr_prev = current->ptr_next;
        current->ptr_next = tmp;
        current = current->ptr_prev;
    }

    tmp = self->head;
    self->head = self->tail;
    self->tail = tmp;
}

void max_container(const container_t* self)
{
    if (self->size_container == 0) {
        printf("error\n");
        return NULL;
    }

    node_t* tmp = self->head;
    node_t* max_node = tmp;

    while (tmp != NULL) {
        if (tmp->value > max_node->value) {
            max_node = tmp;
        }
        tmp = tmp->ptr_next;
    }

    printf("%u\n", max_node->value);
}

void min_container(const container_t* self)
{
    if (self->size_container == 0) {
        printf("error\n");
        return NULL;
    }

    node_t* tmp = self->head;
    node_t* min_node = tmp;

    while (tmp != NULL) {
        if (tmp->value < min_node->value) {
            min_node = tmp;
        }
        tmp = tmp->ptr_next;
    }

    printf("%u\n", min_node->value);
}

void find_index_container(const container_t* self, uint32_t value)
{
    if (self->size_container == 0) {
        printf("error\n");
        return;
    }

    node_t* tmp = self->head;
    size_t idx = 0;

    while (tmp != NULL) {
        if (tmp->value == value) {
            printf("%zu\n", idx);
            return;
        }
        tmp = tmp->ptr_next;
        ++idx;
    }

}

void rotate_container(container_t* self, uint32_t K)
{
    node_t* tmp_ptr = self->head;
    size_t current_idx = 0;

    while(tmp_ptr != NULL) {
        if(current_idx == K) {
            break;
        }

        tmp_ptr = tmp_ptr->ptr_next;
        current_idx++;
    }


}

void push(container_t* self, uint32_t* value) 
{
    node_t* new_ptr = malloc(sizeof(node_t));

    if (new_ptr != NULL) {
        new_ptr->value = *value;
        new_ptr->ptr_next = self->head;
        new_ptr->ptr_prev = NULL;
        self->head = new_ptr;
        self->size_container++;
    }

    return;
}

void pop(container_t* self)
{
    if (self->head == NULL) {
        printf("error\n");
        return;
    }

    node_t* tmp_ptr = self->head;

    self->head = self->head->ptr_next;
    self->size_container--;

    printf("%u\n", tmp_ptr->value);
    free(tmp_ptr);
    return;
}

void peek(container_t* self)
{
    if (self->head == NULL) {
        printf("error\n");
        return;
    }

    printf("%u\n",self->head->value);
}

void enqueue(container_t* self, uint32_t* value)
{
    node_t* new_ptr = malloc(sizeof(node_t));

    if(new_ptr == NULL) {
        return;
    }

    new_ptr->value = *value;
    new_ptr->ptr_next = NULL;
    new_ptr->ptr_prev = self->tail;

    if (self->head == NULL) {
        self->head = new_ptr;
        self->tail = new_ptr;
    } else {
        self->tail->ptr_next = new_ptr;
        self->tail = new_ptr;
    }

    self->size_container++;

    return;
}

void dequeue(container_t* self)
{
    if (self->size_container == 0) {
        printf("error\n");
        return;
    }

    node_t* tmp_ptr = self->head;

    if (self->size_container == 1) {
        self->head = NULL;
        self->tail = NULL;
    } else {
        self->head = tmp_ptr->ptr_next;
    }

    self->size_container--;

    printf("%u\n", tmp_ptr->value);
    free(tmp_ptr);
    return;
}

void front_queue(container_t* self) 
{
    if (self->size_container == 0) {
        printf("error\n");
        return;
    }

    printf("%u\n", self->head->value);
}

void push_front_deque(container_t* self, uint32_t* value)
{
    node_t* new_ptr = malloc(sizeof(node_t));

    if(new_ptr == NULL) {
        return;
    }

    new_ptr->value = *value;
    new_ptr->ptr_next = self->head;
    new_ptr->ptr_prev = NULL;

    if (self->head == NULL) {
        self->head = self->tail = new_ptr;
    } else {
        self->head->ptr_prev = new_ptr;
        self->head = new_ptr;
    }

    self->size_container++;


    return;
}


void push_back_deque(container_t* self, uint32_t* value)
{
    node_t* new_ptr = malloc(sizeof(node_t));
    if (new_ptr == NULL) {
        return;
    }

    new_ptr->value = *value;
    new_ptr->ptr_next = NULL;
    new_ptr->ptr_prev = self->tail;

    if (self->tail == NULL) {
        self->head = self->tail = new_ptr;
    } else {
        self->tail->ptr_next = new_ptr;
        self->tail = new_ptr;
    }

    self->size_container++;
}

void pop_front_deque(container_t* self)
{
    if (self->size_container == 0) {
        printf("error\n");
        return;
    }

    node_t* tmp = self->head;
    printf("%u\n", tmp->value);

    self->head = tmp->ptr_next;
    if (self->head != NULL) {
        self->head->ptr_prev = NULL;
    } else {
        self->tail = NULL;
    }

    free(tmp);
    self->size_container--;
}

void pop_back_deque(container_t* self)
{
    if (self->size_container == 0) {
        printf("error\n");
        return;
    }

    node_t* tmp = self->tail;  
    printf("%u\n", tmp->value);

    self->tail = tmp->ptr_prev;     

    if (self->tail != NULL) {
        self->tail->ptr_next = NULL;   
    } else {
        self->head = NULL;            
    }

    free(tmp);
    self->size_container--;
}

void peek_front_deque(const container_t* self)
{
    if(self->size_container == 0) {
        printf("error\n");
        return;
    }

    printf("%u\n", self->head->value);
}

void peek_back_deque(const container_t* self)
{
    if(self->size_container == 0) {
        printf("error\n");
        return;
    }

    printf("%u\n", self->tail->value);
}


int main(void) 
{
    container_t STACK = {0};
    container_t QUEUE = {0};
    container_t DEQUE = {0};

    uint32_t N;
    scanf("%u", N);
    while (getchar() != '\n');

    char buffer[100];

    for(size_t i = 0; i<N, i++){
        if(fgets(buffer, 100, stdin) == NULL){
            return;
        }


    }
    
}