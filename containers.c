#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h> 

typedef struct container container_t; 
typedef struct node node_t;
typedef struct cmd_table cmd_table_t;

void        push(container_t* self, uint32_t value);
uint32_t    pop(container_t* self);
void        peek(container_t* self);
void        enqueue(container_t* self, uint32_t value);
uint32_t    dequeue(container_t* self);
void        push_front_deque(container_t* self, uint32_t value);
void        push_back_deque(container_t* self, uint32_t value);
uint32_t    pop_back_deque(container_t* self);
void        peek_back_deque(container_t* self);
void        size_container(container_t* self);
void        clear_container(container_t* self);
void        reverse_container(container_t* self);
void        rotate_container(container_t* self, uint32_t K, uint8_t direction);
void        find_index_container(container_t* self, uint32_t value);
uint32_t    max_container(container_t* self);
uint32_t    min_container(container_t* self);
void        batch_transfer(container_t* src, container_t* dest, uint32_t K);
void        batch_transfer_range(container_t* src, container_t* dest, size_t L, size_t R);
void        rotate_partial(container_t* self, uint32_t L, uint32_t R, uint32_t K);
void        print_all(container_t* container);

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
    void        (*push)(container_t* self, uint32_t value);
    uint32_t    (*pop)(container_t* self);

    void        (*peek)(container_t* self);

    /*Methods for queue_container*/
    void        (*enqueue)(container_t* self, uint32_t value);
    uint32_t    (*dequeue)(container_t* self);

    void        (*front_queue)(container_t* self);

    /*Methods for deque_container*/
    void        (*push_front)(container_t* self, uint32_t value);
    void        (*push_back)(container_t* self, uint32_t value);
    
    uint32_t    (*pop_front)(container_t* self);
    uint32_t    (*pop_back)(container_t* self);

    void        (*peek_front)(container_t* self);
    void        (*peek_back)(container_t* self);

    /*General methods*/
    void        (*size)(container_t* self);
    void        (*clear)(container_t* self);
    void        (*reverse)(container_t* self);
    void        (*rotate)(container_t* self, uint32_t K, uint8_t direction);
    void        (*sort)(container_t* self, uint32_t ascending);
    void        (*find_index)(container_t* self, uint32_t value);
    uint32_t    (*max)(container_t* self);
    uint32_t    (*min)(container_t* self);
    void        (*duplicate)(container_t* src, container_t* dest);
    void        (*merge)(container_t* src1, container_t* src2, container_t* dest);
    void        (*batch_transfer)(container_t* src, container_t* dest, uint32_t K);
    void        (*batch_transfer_range)(container_t* src, container_t* dest, size_t L, size_t R);
    void        (*rotate_partial)(container_t* self, uint32_t L, uint32_t R, uint32_t K);
    void        (*reverse_partial)(container_t* self, size_t L, size_t R);
    void        (*print_all)(container_t* self);           
};

typedef enum
{
    CMD_PUSH_STACK,
    CMD_POP_STACK,
    CMD_PEEK_STACK,
    CMD_ENQUEUE_QUEUE,
    CMD_DEQUEUE_QUEUE,
    CMD_FRONT_QUEUE,
    CMD_REVERSE_QUEUE,
    CMD_PUSH_FRONT_DEQUE,
    CMD_PUSH_BACK_DEQUE,
    CMD_POP_FRONT_DEQUE,
    CMD_POP_BACK_DEQUE,
    CMD_PEEK_FRONT_DEQUE,
    CMD_PEEK_BACK_DEQUE,
    CMD_REVERSE_DEQUE,
    CMD_ROTATE_CONTAINER,
    CMD_SORT_CONTAINER,
    CMD_BATCH_TRANSFER_CONTAINER,
    CMD_BATCH_TRANSFER_RANGE_CONTAINER,
    CMD_ROTATE_PARTIAL_CONTAINER,
    CMD_REVERSE_PARTIAL_CONTAINER,
    CMD_FIND_INDEX_CONTAINER,
    CMD_MAX_CONTAINER,
    CMD_MIN_CONTAINER,
    CMD_CLEAR_CONTAINER,
    CMD_DUPLICATE_CONTAINER,
    CMD_MERGE_CONTAINER,
    CMD_SIZE_CONTAINER,
    CMD_PRINT_ALL_CONTAINER,
    CMD_ERR
} CMD_TYPE;

struct cmd_table
{
    const char* command;
    CMD_TYPE id;
};

static const cmd_table_t cmd_dict[] = {
    {"push_stack",           CMD_PUSH_STACK},
    {"pop_stack",            CMD_POP_STACK},
    {"peek_stack",           CMD_PEEK_STACK},
    {"size_stack",           CMD_SIZE_CONTAINER},
    {"enqueue",              CMD_ENQUEUE_QUEUE},
    {"dequeue",              CMD_DEQUEUE_QUEUE},
    {"front_queue",          CMD_FRONT_QUEUE},
    {"size_queue",           CMD_SIZE_CONTAINER},
    {"reverse_queue",        CMD_REVERSE_QUEUE},
    {"push_front_deque",     CMD_PUSH_FRONT_DEQUE},
    {"push_back_deque",      CMD_PUSH_BACK_DEQUE},
    {"pop_front_deque",      CMD_POP_FRONT_DEQUE},
    {"pop_back_deque",       CMD_POP_BACK_DEQUE},
    {"peek_front_deque",     CMD_PEEK_FRONT_DEQUE},
    {"peek_back_deque",      CMD_PEEK_BACK_DEQUE},
    {"size_deque",           CMD_SIZE_CONTAINER},
    {"reverse_deque",        CMD_REVERSE_DEQUE},
    {"rotate_container",     CMD_ROTATE_CONTAINER},
    {"sort_container",       CMD_SORT_CONTAINER},
    {"batch_transfer",       CMD_BATCH_TRANSFER_CONTAINER},
    {"batch_transfer_range", CMD_BATCH_TRANSFER_RANGE_CONTAINER},
    {"rotate_partial",       CMD_ROTATE_PARTIAL_CONTAINER},
    {"reverse_partial",      CMD_REVERSE_PARTIAL_CONTAINER},
    {"find_index",           CMD_FIND_INDEX_CONTAINER},
    {"max_container",        CMD_MAX_CONTAINER},
    {"min_container",        CMD_MIN_CONTAINER},
    {"clear_container",      CMD_CLEAR_CONTAINER},
    {"duplicate_container",  CMD_DUPLICATE_CONTAINER},
    {"merge_containers",     CMD_MERGE_CONTAINER},
    {"print_all",            CMD_PRINT_ALL_CONTAINER},
    {NULL,                   CMD_ERR}
};

void container_init(container_t* self, TYPE_CONTAINER type) 
{
    self->head = NULL;
    self->tail = NULL;
    self->size_container = 0;

    switch (type) {
        case STACK:
            self->push         = push;
            self->pop          = pop;
            self->peek         = peek;
            self->enqueue      = NULL;
            self->dequeue      = NULL;
            self->front_queue  = NULL;
            self->push_front   = NULL;
            self->push_back    = NULL;
            self->pop_front    = NULL;
            self->pop_back     = NULL;
            self->peek_front   = NULL;
            self->peek_back    = NULL;
            break;

        case QUEUE:
            self->enqueue      = enqueue;
            self->dequeue      = dequeue;
            self->front_queue  = peek;
            self->push         = NULL;
            self->pop          = NULL;
            self->peek         = NULL;
            self->push_front   = NULL;
            self->push_back    = NULL;
            self->pop_front    = NULL;
            self->pop_back     = NULL;
            self->peek_front   = NULL;
            self->peek_back    = NULL;
            break;

        case DEQUE:
            self->push_front   = push_front_deque;
            self->push_back    = push_back_deque;
            self->pop_front    = pop;
            self->pop_back     = pop_back_deque;
            self->peek_front   = peek;
            self->peek_back    = peek_back_deque;
            self->push         = NULL;
            self->pop          = NULL;
            self->peek         = NULL;
            self->enqueue      = NULL;
            self->dequeue      = NULL;
            self->front_queue  = NULL;
            break;
    }

    self->size                 = size_container;
    self->clear                = clear_container;
    self->reverse              = reverse_container;
    self->rotate               = rotate_container;
    self->sort                 = NULL;
    self->find_index           = find_index_container;
    self->max                  = max_container;
    self->min                  = min_container;
    self->duplicate            = NULL;
    self->merge                = NULL;
    self->batch_transfer       = batch_transfer;
    self->batch_transfer_range = batch_transfer_range;
    self->rotate_partial       = rotate_partial;
    self->reverse_partial      = NULL;
    self->print_all            = print_all;
}

void size_container(container_t* self)
{   
    printf("%u\n", self->size_container);
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

uint32_t max_container(container_t* self)
{
    if (self->size_container == 0) {
        return UINT32_MAX;
    }

    node_t* tmp_ptr = self->head;
    node_t* max_node = tmp_ptr;

    while (tmp_ptr != NULL) {
        if (tmp_ptr->value > max_node->value) {
            max_node = tmp_ptr;
        }
        tmp_ptr = tmp_ptr->ptr_next;
    }

    return max_node->value;
}

uint32_t min_container(container_t* self)
{
    if (self->size_container == 0) {
        return UINT32_MAX;
    }

    node_t* tmp_ptr = self->head;
    node_t* min_node = tmp_ptr;

    while (tmp_ptr != NULL) {
        if (tmp_ptr->value < min_node->value) {
            min_node = tmp_ptr;
        }
        tmp_ptr = tmp_ptr->ptr_next;
    }

    return min_node->value;
}

void find_index_container(container_t* self, uint32_t value)
{
    if (self->size_container == 0) {
        printf("error\n");
        return;
    }

    node_t* tmp = self->head;
    size_t idx = 0;

    while (tmp != NULL) {
        if (tmp->value == value) {
            printf("%u\n", idx);
            return;
        }
        tmp = tmp->ptr_next;
        ++idx;
    }

}

void rotate_container(container_t* self, uint32_t K, uint8_t direction)
{

    if(self->size_container <= 1 || K == 0 || K == self->size_container) {
        return;
    }

    if(K > self->size_container) {
        K %= self->size_container;
    }

    if(direction == 1) {
        K = self->size_container - K;   
    }

    node_t* current = self->head;
    size_t current_idx = 0;

    while(current != NULL) {
        if(current_idx == K) {
            break;
        }

        current = current->ptr_next;
        current_idx++;
    }

    self->tail->ptr_next = self->head;  
    self->head->ptr_prev = self->tail; 

    self->head = current->ptr_next;    
    self->head->ptr_prev = NULL;  

    current->ptr_next = NULL;         
    self->tail = current;  

}

void batch_transfer(container_t* src, container_t* dest, uint32_t K)
{
    if(src->size_container < K) {
        printf("error\n");
        return;
    }

    if(K == 0) {
        return;
    }

    uint32_t tmp_value;

    for(size_t i = 0; i < K; i++) {
        tmp_value = src->pop(src);

        if (tmp_value == UINT32_MAX) {
            printf("error\n");
            return;
        }

        dest->push_back(dest, tmp_value);
        printf("%u ", tmp_value);
    }

    printf("\n");
}

void batch_transfer_range(container_t* src, container_t* dest, size_t L, size_t R)
{
    if(L > R || L >= src->size_container || R >= src->size_container || (R - L + 1) > src->size_container) {
        printf("error\n");
        return;
    }

    node_t* current = src->head;
    node_t* next = NULL;
    uint32_t tmp_value;

    for(size_t i = 0; i < L; i++) {
        current = current->ptr_next;
    }

    for(size_t i = 0; i < (R - L + 1); i++) {
        tmp_value = current->value;
        next = current->ptr_next;

        if(current->ptr_prev != NULL) {
            current->ptr_prev->ptr_next = current->ptr_next;
        } else {
            src->head = current->ptr_next;
        }

        if(current->ptr_next != NULL) {
            current->ptr_next->ptr_prev = current->ptr_prev;
        } else {
            src->tail = current->ptr_prev;
        }

        if(dest->push_back != NULL) {
            dest->push_back(dest, tmp_value);
        } else if(dest->enqueue != NULL) {
            dest->enqueue(dest, tmp_value);
        } else if(dest->push != NULL) {
            dest->push(dest, tmp_value);
        }
        
        printf("%u ", tmp_value);

        free(current);
        current = next;
        src->size_container--;
    }

    printf("\n");
}

void rotate_partial(container_t* self, uint32_t L, uint32_t R, uint32_t K)
{
    if(L > R || R >= self->size_container) {
        printf("error\n");
        return;
    }

    if(self->size_container == 1 || L == R) {
        return;
    }
}

void push(container_t* self, uint32_t value) 
{
    node_t* new_ptr = malloc(sizeof(node_t));

    if(new_ptr == NULL) {
        return;
    }

    new_ptr->value = value;
    new_ptr->ptr_next = self->head;
    new_ptr->ptr_prev = NULL;
    self->head = new_ptr;
    self->size_container++;

    return;
}

uint32_t pop(container_t* self)
{
    if (self->head == NULL) {
        return UINT32_MAX;
    }

    node_t* tmp_ptr = self->head;
    uint32_t tmp_value = tmp_ptr->value;

    self->head = self->head->ptr_next;

    if (self->head != NULL) {
        self->head->ptr_prev = NULL;
    } else {
        self->tail = NULL;
    }

    self->size_container--;

    free(tmp_ptr);
    return tmp_value;
}

void peek(container_t* self)
{
    if (self->head == NULL) {
        printf("error\n");
        return;
    }

    printf("%u\n",self->head->value);
}

void enqueue(container_t* self, uint32_t value)
{
    node_t* new_ptr = malloc(sizeof(node_t));

    if(new_ptr == NULL) {
        return;
    }

    new_ptr->value = value;
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

uint32_t dequeue(container_t* self)
{
    if (self->size_container == 0) {
        return UINT32_MAX;
    }

    node_t* tmp_ptr = self->head;
    uint32_t tmp_value = tmp_ptr->value;

    if (self->size_container == 1) {
        self->head = NULL;
        self->tail = NULL;
    } else {
        self->head = tmp_ptr->ptr_next;
        self->head->ptr_prev = NULL;
    }

    self->size_container--;

    free(tmp_ptr);
    return tmp_value;
}

void push_front_deque(container_t* self, uint32_t value)
{
    node_t* new_ptr = malloc(sizeof(node_t));

    if(new_ptr == NULL) {
        return;
    }

    new_ptr->value = value;
    new_ptr->ptr_next = self->head;
    new_ptr->ptr_prev = NULL;

    if (self->head == NULL) {
        self->head = self->tail = new_ptr;
    } else {
        self->head->ptr_prev = new_ptr;
        self->head = new_ptr;
    }

    self->size_container++;
}

void push_back_deque(container_t* self, uint32_t value)
{
    node_t* new_ptr = malloc(sizeof(node_t));

    if (new_ptr == NULL) {
        return;
    }

    new_ptr->value = value;
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

uint32_t pop_back_deque(container_t* self)
{
    if (self->size_container == 0) {
        return UINT32_MAX;
    }

    node_t* tmp_ptr = self->tail;  
    uint32_t tmp_value = tmp_ptr->value;

    self->tail = tmp_ptr->ptr_prev;     

    if (self->tail != NULL) {
        self->tail->ptr_next = NULL;   
    } else {
        self->head = NULL;            
    }

    free(tmp_ptr);
    self->size_container--;

    return tmp_value;
}

void peek_back_deque(container_t* self)
{
    if(self->size_container == 0) {
        printf("error\n");
        return;
    }

    printf("%u\n", self->tail->value);
}

void print_all(container_t* container)
{
    node_t* tmp_ptr = container->head;

    if(container->size_container == 0) {
        printf("empty\n");
    } else {
        while(tmp_ptr != NULL) {
            printf("%u ", tmp_ptr->value);
            tmp_ptr = tmp_ptr->ptr_next;
        }
        printf("\n");
    }

}

CMD_TYPE cmd_table(char* command)
{
    for(size_t i = 0; cmd_dict[i].command != NULL; i++) {
        if(strcmp(cmd_dict[i].command, command) == 0) {
            return cmd_dict[i].id;
        }
    }

    return CMD_ERR;
}

int main(void) 
{
    container_t containers[3] = {0};

    container_init(&containers[STACK], STACK);
    container_init(&containers[QUEUE], QUEUE);
    container_init(&containers[DEQUE], DEQUE);

    uint32_t N;
    scanf("%u", &N);
    while (getchar() != '\n');

    char buffer[100];
    uint32_t value;
    uint32_t result;
    uint32_t K;
    uint32_t left;
    uint32_t right;
    uint8_t  direction;

    char* command = NULL;
    char* val_str = NULL;
    char* container_type = NULL;

    for(size_t i = 0; i<N; i++){
        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
            return 1;
        }

        buffer[strcspn(buffer, "\n\r")] = '\0';

        command = strtok(buffer, " ");
        if(!command) {
            printf("error\n");
            continue;
        }

        val_str = strtok(NULL, " ");

        /*STACK COMMANDS*/

        if(strcmp(command, "push_stack") == 0) {
            if(val_str != NULL) {
                value = (uint32_t)atoi(val_str);
                containers[STACK].push(&containers[STACK], value);
            } else {
                printf("error\n");
            }
        }
        else if(strcmp(command, "pop_stack") == 0) {
            result = containers[STACK].pop(&containers[STACK]);

            if(result == UINT32_MAX){
                printf("error\n");
            } else printf("%u\n", result);

        }
        else if(strcmp(command, "peek_stack") == 0) {
            containers[STACK].peek(&containers[STACK]);
        }
        else if(strcmp(command, "size_stack") == 0) {
            containers[STACK].size(&containers[STACK]);
        }

        /*QUEUE COMMANDS*/

        else if(strcmp(command, "enqueue") == 0) {
            if(val_str != NULL) {
                value = (uint32_t)atoi(val_str);
                containers[QUEUE].enqueue(&containers[QUEUE], value);
            } else {
                printf("error\n");
            }
        }
        else if(strcmp(command, "dequeue") == 0) {
            result = containers[QUEUE].dequeue(&containers[QUEUE]);
            
            if(result == UINT32_MAX) {
                printf("error\n");
            } else printf("%u\n", result);
        }
        else if(strcmp(command, "front_queue") == 0) {
            containers[QUEUE].front_queue(&containers[QUEUE]);
        }
        else if(strcmp(command, "size_queue") == 0) {
            containers[QUEUE].size(&containers[QUEUE]);
        }
        else if(strcmp(command, "reverse_queue") == 0) {
            containers[QUEUE].reverse(&containers[QUEUE]);
        }

        /*DEQUE COMMANDS*/

        else if(strcmp(command, "push_front_deque") == 0) {
            if(val_str != NULL) {
                value = (uint32_t)atoi(val_str);
                containers[DEQUE].push_front(&containers[DEQUE], value);
            } else printf("error\n");
        }
        else if(strcmp(command, "push_back_deque") == 0) {
            if(val_str != NULL) {
                value = (uint32_t)atoi(val_str);
                containers[DEQUE].push_back(&containers[DEQUE], value);
            } else printf("error\n");
        }
        else if(strcmp(command, "pop_front_deque") == 0) {
            result = containers[DEQUE].pop_front(&containers[DEQUE]);

            if(result == UINT32_MAX) {
                printf("error\n");
            } else printf("%u\n", result);
        }
        else if(strcmp(command, "pop_back_deque") == 0) {
            result = containers[DEQUE].pop_back(&containers[DEQUE]);

            if(result == UINT32_MAX) {
                printf("error\n");
            } else printf("%u\n", result);
        }
        else if(strcmp(command, "peek_front_deque") == 0) {
            containers[DEQUE].peek_front(&containers[DEQUE]);
        }
        else if (strcmp(command, "peek_back_deque") == 0) {
            containers[DEQUE].peek_back(&containers[DEQUE]);
        }
        else if(strcmp(command, "size_deque") == 0) {
            containers[DEQUE].size(&containers[DEQUE]);
        }
        else if(strcmp(command, "reverse_deque") == 0) {
            containers[DEQUE].reverse(&containers[DEQUE]);
        }

        /*GENERAL COMMANDS*/

        else if(strcmp(command, "print_all") == 0) {
            containers[STACK].print_all(&containers[STACK]);
            containers[QUEUE].print_all(&containers[QUEUE]);
            containers[DEQUE].print_all(&containers[DEQUE]);
        }
        else if(strcmp(command, "clear_container")) {

        }
        else {
            printf("error\n");
        }
    }
    
    return 0;
}