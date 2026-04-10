#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h> 
#include <limits.h>

typedef struct container container_t; 
typedef struct node node_t;
typedef struct cmd_table cmd_table_t;
typedef struct type_table type_table_t;

void        push(container_t* self, int value);
int         pop(container_t* self);
void        peek(container_t* self);
void        enqueue(container_t* self, int value);
int         dequeue(container_t* self);
void        push_front_deque(container_t* self, int value);
void        push_back_deque(container_t* self, int value);
int         pop_back_deque(container_t* self);
void        peek_back_deque(container_t* self);
void        size(container_t* self);
void        clear_container(container_t* self);
void        reverse_container(container_t* self);
void        rotate_container(container_t* self, uint8_t direction, int K);
void        find_index_container(container_t* self, int value);
int         max_container(container_t* self);
int         min_container(container_t* self);
void        duplicate_container(container_t* src, container_t* dest);
void        batch_transfer(container_t* src, container_t* dest, int K);
void        batch_transfer_range(container_t* src, container_t* dest, int L, int R);
void        rotate_partial(container_t* self, int L, int R, int K);
void        reverse_partial(container_t* self, int L, int R);
void        sort_container(container_t* self, uint8_t ascending);
void        merge_containers(container_t* src1, container_t* src2, container_t* dest);
void        print_all(container_t* container);

struct node
{
    int value;
    
    node_t*  ptr_next;
    node_t*  ptr_prev;
};

struct container
{
    /*Pointers on data_list*/
    node_t *head, *tail;

    size_t size_container;

    /*Methods for stack_container*/
    void        (*push)(container_t* self, int value);
    int         (*pop)(container_t* self);

    void        (*peek)(container_t* self);

    /*Methods for queue_container*/
    void        (*enqueue)(container_t* self, int value);
    int         (*dequeue)(container_t* self);

    void        (*front_queue)(container_t* self);

    /*Methods for deque_container*/
    void        (*push_front)(container_t* self, int value);
    void        (*push_back)(container_t* self, int value);
    
    int         (*pop_front)(container_t* self);
    int         (*pop_back)(container_t* self);

    void        (*peek_front)(container_t* self);
    void        (*peek_back)(container_t* self);

    /*General methods*/
    void        (*size)(container_t* self);
    void        (*clear)(container_t* self);
    void        (*reverse)(container_t* self);
    void        (*rotate)(container_t* self, uint8_t direction, int K);
    void        (*sort)(container_t* self, uint8_t ascending);
    void        (*find_index)(container_t* self, int value);
    int         (*max_)(container_t* self);
    int         (*min_)(container_t* self);
    void        (*duplicate)(container_t* src, container_t* dest);
    void        (*merge)(container_t* src1, container_t* src2, container_t* dest);
    void        (*batch_transfer)(container_t* src, container_t* dest, int K);
    void        (*batch_transfer_range)(container_t* src, container_t* dest, int L, int R);
    void        (*rotate_partial)(container_t* self, int L, int R, int K);
    void        (*reverse_partial)(container_t* self, int L, int R);
    void        (*print_all)(container_t* self);           
};

typedef enum
{
    CMD_PUSH_STACK,
    CMD_POP_STACK,
    CMD_PEEK_STACK,
    CMD_SIZE_STACK,
    CMD_ENQUEUE_QUEUE,
    CMD_DEQUEUE_QUEUE,
    CMD_FRONT_QUEUE,
    CMD_REVERSE_QUEUE,
    CMD_SIZE_QUEUE,
    CMD_PUSH_FRONT_DEQUE,
    CMD_PUSH_BACK_DEQUE,
    CMD_POP_FRONT_DEQUE,
    CMD_POP_BACK_DEQUE,
    CMD_PEEK_FRONT_DEQUE,
    CMD_PEEK_BACK_DEQUE,
    CMD_REVERSE_DEQUE,
    CMD_SIZE_DEQUE,
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
    {"size_stack",           CMD_SIZE_STACK},
    {"enqueue",              CMD_ENQUEUE_QUEUE},
    {"dequeue",              CMD_DEQUEUE_QUEUE},
    {"front_queue",          CMD_FRONT_QUEUE},
    {"size_queue",           CMD_SIZE_QUEUE},
    {"reverse_queue",        CMD_REVERSE_QUEUE},
    {"push_front_deque",     CMD_PUSH_FRONT_DEQUE},
    {"push_back_deque",      CMD_PUSH_BACK_DEQUE},
    {"pop_front_deque",      CMD_POP_FRONT_DEQUE},
    {"pop_back_deque",       CMD_POP_BACK_DEQUE},
    {"peek_front_deque",     CMD_PEEK_FRONT_DEQUE},
    {"peek_back_deque",      CMD_PEEK_BACK_DEQUE},
    {"size_deque",           CMD_SIZE_DEQUE},
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

typedef enum
{
    STACK,
    QUEUE,
    DEQUE,
    ERR_TYPE

} TYPE_CONTAINER;

struct type_table
{
    const char* container_type;
    TYPE_CONTAINER id;
};

static const type_table_t type_dict[] = {
    {"STACK", STACK},
    {"QUEUE", QUEUE},
    {"DEQUE", DEQUE},
    {NULL, ERR_TYPE}
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

    self->size                 = size;
    self->clear                = clear_container;
    self->reverse              = reverse_container;
    self->rotate               = rotate_container;
    self->sort                 = NULL;
    self->find_index           = find_index_container;
    self->max_                 = max_container;
    self->min_                 = min_container;
    self->duplicate            = duplicate_container;
    self->merge                = NULL;
    self->batch_transfer       = batch_transfer;
    self->batch_transfer_range = batch_transfer_range;
    self->rotate_partial       = rotate_partial;
    self->reverse_partial      = NULL;
    self->print_all            = print_all;
}

void size(container_t* self)
{   
    printf("%zu\n", self->size_container);
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

int max_container(container_t* self)
{
    if (self->size_container == 0) {
        return INT_MAX;
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

int min_container(container_t* self)
{
    if (self->size_container == 0) {
        return INT_MAX;
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

void find_index_container(container_t* self, int value)
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

    printf("error\n");

}

void rotate_container(container_t* self, uint8_t direction, int K)
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
        if(current_idx == K - 1) {
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

void batch_transfer(container_t* src, container_t* dest, int K)
{
    if(K < 0 || src->size_container < (size_t)K) {
        printf("error\n");
        return;
    }

    if(K == 0) {
        return;
    }

    int tmp_value;

    for(size_t i = 0; i < K; i++) {

        if(src->pop != NULL) {
            tmp_value = src->pop(src);
        } else if(src->dequeue != NULL) {
            tmp_value = src->dequeue(src);
        } else if(src->pop_front != NULL) {
            tmp_value = src->pop_front(src);
        } else {
            printf("error\n");
            return;
        }

        if(dest->push_back != NULL) {
            dest->push_back(dest, tmp_value);
        } else if(dest->enqueue != NULL) {
            dest->enqueue(dest, tmp_value);
        } else if(dest->push != NULL) {
            dest->push(dest, tmp_value);
        }

        if(i > 0) printf(" ");
        printf("%d", tmp_value);
    }

    printf("\n");
}

void batch_transfer_range(container_t* src, container_t* dest, int L, int R)
{
    if(L > R || L >= src->size_container || R >= src->size_container || (R - L + 1) > src->size_container) {
        printf("error\n");
        return;
    }

    node_t* current = src->head;
    node_t* next = NULL;
    int tmp_value;

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
        
        printf("%d ", tmp_value);

        free(current);
        current = next;
        src->size_container--;
    }

    printf("\n");
}

void rotate_partial(container_t* self, int L, int R, int K)
{
    if(L < 0 || R < 0 || L > R || R >= (int)self->size_container) {
        printf("error\n");
        return;
    }

    int len = R - L + 1;
    K = K % len;

    if(K < 0) {
        K += len;
    }

    if(K == 0) {
        return;
    }

    reverse_partial(self, L, L + K - 1);
    reverse_partial(self, L + K, R);
    reverse_partial(self, L, R);
}

void reverse_partial(container_t* self, int L, int R)
{
    if(L < 0 || R < 0 || L > R || R >= (int)self->size_container) {
        printf("error\n");
        return;
    }

    node_t* left_ptr = self->head;
    for(int i = 0; i < L; i++) {
        left_ptr = left_ptr->ptr_next;
    }

    node_t* right_ptr = self->head;
    for(int i = 0; i < R; i++) {
        right_ptr = right_ptr->ptr_next;
    }

    int tmp_value;

    while(left_ptr != right_ptr && left_ptr->ptr_prev != right_ptr) {
        tmp_value = left_ptr->value;
        left_ptr->value = right_ptr->value;
        right_ptr->value = tmp_value;

        left_ptr = left_ptr->ptr_next;
        right_ptr = right_ptr->ptr_prev;
    }
}

void merge_containers(container_t* src1, container_t* src2, container_t* dest)
{
    dest->clear(dest);

    node_t* tmp_ptr = src1->head;
    while(tmp_ptr != NULL) {
        enqueue(dest, tmp_ptr->value);
        tmp_ptr = tmp_ptr->ptr_next;
    }

    tmp_ptr = src2->head;
    while(tmp_ptr != NULL) {
        enqueue(dest, tmp_ptr->value);
        tmp_ptr = tmp_ptr->ptr_next;
    }

    src1->clear(src1);
    src2->clear(src2);

    print_all(dest);
}

void duplicate_container(container_t* src, container_t* dest) {
    dest->clear(dest);

    node_t* tmp_ptr = src->head;

    while (tmp_ptr != NULL) {
        enqueue(dest, tmp_ptr->value);
        tmp_ptr = tmp_ptr->ptr_next;
    }
}

void push(container_t* self, int value) 
{
    node_t* new_ptr = malloc(sizeof(node_t));
    if (new_ptr == NULL) {
        return;
    }

    new_ptr->value = value;
    new_ptr->ptr_next = self->head;
    new_ptr->ptr_prev = NULL;

    if (self->head == NULL) {
        self->tail = new_ptr;
    } else {
        self->head->ptr_prev = NULL;
    }

    self->head = new_ptr;
    self->size_container++;
}

int pop(container_t* self)
{
    if (self->head == NULL) {
        return INT_MAX;
    }

    node_t* tmp_ptr = self->head;
    int tmp_value = tmp_ptr->value;

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

    printf("%d\n",self->head->value);
}

void enqueue(container_t* self, int value)
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

int dequeue(container_t* self)
{
    if (self->size_container == 0) {
        return INT_MAX;
    }

    node_t* tmp_ptr = self->head;
    int tmp_value = tmp_ptr->value;

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

void push_front_deque(container_t* self, int value)
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

void push_back_deque(container_t* self, int value)
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
int pop_back_deque(container_t* self)
{
    if (self->size_container == 0) {
        return INT_MAX;
    }

    node_t* tmp_ptr = self->tail;  
    int32_t tmp_value = tmp_ptr->value;

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

    printf("%d\n", self->tail->value);
}

void print_all(container_t* container)
{
    node_t* tmp_ptr = container->head;

    if(container->size_container == 0) {
        printf("empty\n");
    } else {
        while(tmp_ptr != NULL) {
            printf("%d ", tmp_ptr->value);
            tmp_ptr = tmp_ptr->ptr_next;
        }
        printf("\n");
    }

}

CMD_TYPE search_cmd_table(char* command)
{
    for(size_t i = 0; cmd_dict[i].command != NULL; i++) {
        if(strcmp(cmd_dict[i].command, command) == 0) {
            return cmd_dict[i].id;
        }
    }

    return CMD_ERR;
}

TYPE_CONTAINER search_type_table(char* container_type)
{
    for(size_t i = 0; type_dict[i].container_type != NULL; i++){
        if(strcmp(type_dict[i].container_type, container_type) == 0) {
            return type_dict[i].id;
        }
    } 

    return ERR_TYPE;
}

uint8_t direction_container(char* direction){
    if(strcmp(direction, "left") == 0) {
        return 0;
    } else if(strcmp(direction, "right") == 0) {
        return 1;
    } else return UINT8_MAX;
}

int main(void) 
{
    container_t containers[3] = {0};
    CMD_TYPE type_command;
    TYPE_CONTAINER container_type;
    TYPE_CONTAINER src_type;
    TYPE_CONTAINER dst_type;

    container_init(&containers[STACK], STACK);
    container_init(&containers[QUEUE], QUEUE);
    container_init(&containers[DEQUE], DEQUE);

    uint32_t N;
    scanf("%u", &N);
    while (getchar() != '\n');

    char buffer[100];
    char* args[4];
    int value;
    int result;
    int K;
    int left;
    int right;
    uint8_t  direction;

    char* command = NULL;

    for(size_t i = 0; i<N; i++){
        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
            return 1;
        }

        buffer[strcspn(buffer, "\n\r")] = '\0';

        command = strtok(buffer, " ");
        
        type_command = search_cmd_table(command);

        if(type_command == CMD_ERR) {
            printf("error\n");
            continue;
        }

        args[0] = strtok(NULL, " ");
        args[1] = strtok(NULL, " ");
        args[2] = strtok(NULL, " ");
        args[3] = strtok(NULL, " ");

        switch(type_command){

            /*STACK COMMANDS*/

            case CMD_PUSH_STACK:

                if(args[0] == NULL){
                    printf("error\n");
                    break;
                }
                
                value = atoi(args[0]);
                containers[STACK].push(&containers[STACK], value);
                break;

            case CMD_POP_STACK:
                result = containers[STACK].pop(&containers[STACK]);

                if(result == INT_MAX) {
                    printf("error\n");
                } else printf("%d\n", result);

                break;

            case CMD_PEEK_STACK:
                containers[STACK].peek(&containers[STACK]);
                break;
            
            case CMD_SIZE_STACK:
                containers[STACK].size(&containers[STACK]);
                break;

            /*QUEUE COMMANDS*/

            case CMD_ENQUEUE_QUEUE:

                if(args[0] == NULL){
                    printf("error\n");
                    break;
                }
                            
                value = atoi(args[0]);
                containers[QUEUE].enqueue(&containers[QUEUE], value);
                break;
            
            case CMD_DEQUEUE_QUEUE:
                result = containers[QUEUE].dequeue(&containers[QUEUE]);

                if(result == INT_MAX) {
                    printf("error\n");
                } else printf("%d\n", result);

                break;
            
            case CMD_FRONT_QUEUE:
                containers[QUEUE].front_queue(&containers[QUEUE]);
                break;
            
            case CMD_REVERSE_QUEUE:
                containers[QUEUE].reverse(&containers[QUEUE]);
                break;

            case CMD_SIZE_QUEUE:
                containers[QUEUE].size(&containers[QUEUE]);
                break;
    
            /*DEQUE COMMANDS*/

            case CMD_PUSH_FRONT_DEQUE:

                if(args[0] == NULL){
                    printf("error\n");
                    break;
                }
                
                value = atoi(args[0]);
                containers[DEQUE].push_front(&containers[DEQUE], value);
                break;  
            
            case CMD_PUSH_BACK_DEQUE:

                if(args[0] == NULL){
                    printf("error\n");
                    break;
                }
                
                value = atoi(args[0]);
                containers[DEQUE].push_back(&containers[DEQUE], value);
                break;
                
            case CMD_POP_FRONT_DEQUE:
                result = containers[DEQUE].pop_front(&containers[DEQUE]);

                if(result == INT_MAX) {
                    printf("error\n");
                } else printf("%d\n", result);

                break;
            
            case CMD_POP_BACK_DEQUE:
                result = containers[DEQUE].pop_back(&containers[DEQUE]);

                if(result == INT_MAX) {
                    printf("error\n");
                } else printf("%d\n", result);

                break;
            
            case CMD_PEEK_FRONT_DEQUE:
                containers[DEQUE].peek_front(&containers[DEQUE]);
                break;

            case CMD_PEEK_BACK_DEQUE:
                containers[DEQUE].peek_back(&containers[DEQUE]);
                break;

            case CMD_SIZE_DEQUE:
                containers[DEQUE].size(&containers[DEQUE]);
                break;

            case CMD_REVERSE_DEQUE:
                containers[DEQUE].reverse(&containers[DEQUE]);
                break;
                    
            /*GENERAL COMMANDS*/
            
            case CMD_PRINT_ALL_CONTAINER:
                containers[STACK].print_all(&containers[STACK]);
                containers[QUEUE].print_all(&containers[QUEUE]);
                containers[DEQUE].print_all(&containers[DEQUE]);
                break;

            case CMD_CLEAR_CONTAINER:

                if(args[0] == NULL) { 
                    printf("error\n");
                    break;
                } 

                container_type = search_type_table(args[0]);

                if(container_type == ERR_TYPE) {
                    printf("error\n");
                    break;
                }

                containers[container_type].clear(&containers[container_type]);
                
                break;

            case CMD_FIND_INDEX_CONTAINER:
                if(args[0] == NULL || args[1] == NULL) {
                    printf("error\n");
                    break;
                }

                container_type = search_type_table(args[0]);

                if(container_type == ERR_TYPE) {
                    printf("error\n");
                    break;
                }

                K = atoi(args[1]);

                containers[container_type].find_index(&containers[container_type], K);

                break;
             
            case CMD_MIN_CONTAINER:
                
                if(args[0] == NULL) { 
                    printf("error\n");
                    break;
                } 

                container_type = search_type_table(args[0]);

                if(container_type == ERR_TYPE) {
                    printf("error\n");
                    break;
                }
                
                result = containers[container_type].min_(&containers[container_type]);

                if(result == INT_MAX) {
                    printf("error\n");
                } else printf("%d\n", result);

                break;

            case CMD_MAX_CONTAINER:
                
                if(args[0] == NULL) { 
                    printf("error\n");
                    break;
                } 

                container_type = search_type_table(args[0]);

                if(container_type == ERR_TYPE) {
                    printf("error\n");
                    break;
                }
                
                result = containers[container_type].max_(&containers[container_type]);

                if(result == INT32_MAX) {
                    printf("error\n");
                } else printf("%d\n", result);

                break;

            case CMD_ROTATE_CONTAINER:
                if(args[0] == NULL || args[1] == NULL || args[2] == NULL) {
                    printf("error\n");
                    break;
                }

                container_type = search_type_table(args[0]);

                if(container_type == ERR_TYPE) {
                    printf("error\n");
                    break;
                }                

                direction = direction_container(args[1]);

                if(direction == UINT8_MAX) {
                    printf("error\n");
                    break;
                }

                K = atoi(args[2]);

                containers[container_type].rotate(&containers[container_type], direction, K);

                break;

            case CMD_DUPLICATE_CONTAINER:
                src_type = search_type_table(args[0]);
                dst_type = search_type_table(args[1]);

                if(src_type == ERR_TYPE || dst_type == ERR_TYPE) {
                    printf("error\n");
                    break;
                }
        
                containers[src_type].duplicate(&containers[src_type], &containers[dst_type]);

                break;
                
            case CMD_BATCH_TRANSFER_CONTAINER:
                if(args[2] == NULL) {
                    printf("error\n");
                    break;
                }

                src_type = search_type_table(args[0]);
                dst_type = search_type_table(args[1]);

                if(src_type == ERR_TYPE || dst_type == ERR_TYPE) {
                    printf("error\n");
                    break;
                }

                K = atoi(args[2]);

                containers[src_type].batch_transfer(&containers[src_type], &containers[dst_type], K);

                break;
            
            case CMD_BATCH_TRANSFER_RANGE_CONTAINER:

                if(args[0] == NULL || args[1] == NULL || args[2] == NULL || args[3] == NULL) {
                    printf("error\n");
                    break;
                }

                src_type = search_type_table(args[0]);
                dst_type = search_type_table(args[1]);

                if(src_type == ERR_TYPE || dst_type == ERR_TYPE) {
                    printf("error\n");
                    break;
                }

                left = atoi(args[2]);
                right = atoi(args[3]);
                containers[src_type].batch_transfer_range(&containers[src_type], &containers[dst_type], left, right);

                break;
                
            case CMD_MERGE_CONTAINER:

                if(args[0] == NULL || args[1] == NULL || args[2] == NULL) {
                    printf("error\n");
                    break;
                }

                src_type = search_type_table(args[0]);
                dst_type = search_type_table(args[1]);
                container_type = search_type_table(args[2]);

                if(src_type == ERR_TYPE || dst_type == ERR_TYPE || container_type == ERR_TYPE) {
                    printf("error\n");
                    break;
                }

                containers[src_type].merge(&containers[src_type], &containers[dst_type], &containers[container_type]);

                break;
        
            /*INVALID INPUT*/        
            
            default:
                printf("error\n");
                break;
        }

    }
    
    return 0;
}