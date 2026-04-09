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
    void        (*push)(container_t* self, uint32_t value);
    uint32_t    (*pop)(container_t* self);

    void        (*peek)(container_t* self);

    /*Methods for queue_container*/
    void        (*enqueue)(container_t* self, uint32_t value);
    void        (*dequeue)(container_t* self);

    void        (*front_queue)(container_t* self);

    /*Methods for deque_container*/
    void        (*push_front)(container_t* self, uint32_t value);
    void        (*push_back)(container_t* self, uint32_t value);
    
    uint32_t    (*pop_front)(container_t* self);
    void        (*pop_back)(container_t* self);

    void        (*peek_front)(const container_t* self);
    void        (*peek_back)(const container_t* self);

    /*General methods*/
    void        (*size)(const container_t* self);
    void        (*clear)(container_t* self);
    void        (*reverse)(container_t* self);
    void        (*rotate)(container_t* self, uint32_t K, uint32_t direction);
    void        (*sort)(container_t* self, uint32_t ascending);
    void        (*find_index)(const container_t* self, uint32_t value);
    void        (*max)(const container_t* self);
    void        (*min)(const container_t* self);
    void        (*duplicate)(container_t* src, container_t* dest);
    void        (*merge)(container_t* src1, container_t* src2, container_t* dest);
    void        (*batch_transfer)(container_t* src, container_t* dest, uint32_t K);
    void        (*batch_transfer_range)(container_t* src, container_t* dest, size_t L, size_t R);
    void        (*rotate_partial)(container_t* self, size_t L, size_t R, uint32_t K);
    void        (*reverse_partial)(container_t* self, size_t L, size_t R);           
};


void container_init(container_t* self, TYPE_CONTAINER type) 
{
    self->head = NULL;
    self->tail = NULL;
    self->size_container = 0;

    switch (type) {
        case STACK:
            self->push = push;
            self->pop = pop;
            self->peek = peek;
            self->enqueue = NULL;
            self->dequeue = NULL;
            self->front_queue = NULL;
            self->push_front = NULL;
            self->push_back = NULL;
            self->pop_front = NULL;
            self->pop_back = NULL;
            self->peek_front = NULL;
            self->peek_back = NULL;
            break;

        case QUEUE:
            self->enqueue = enqueue;
            self->dequeue = dequeue;
            self->front_queue = peek;
            self->push = NULL;
            self->pop = NULL;
            self->peek = NULL;
            self->push_front = NULL;
            self->push_back = NULL;
            self->pop_front = NULL;
            self->pop_back = NULL;
            self->peek_front = NULL;
            self->peek_back = NULL;
            break;

        case DEQUE:
            self->push_front = push_front_deque;
            self->push_back = push_back_deque;
            self->pop_front = pop;
            self->pop_back = pop_back_deque;
            self->peek_front = peek;
            self->peek_back = peek_back_deque;
            self->push = NULL;
            self->pop = NULL;
            self->peek = NULL;
            self->enqueue = NULL;
            self->dequeue = NULL;
            self->front_queue = NULL;
            break;
    }

    self->size = size_container;
    self->clear = clear_container;
    self->reverse = reverse_container;
    self->rotate = rotate_container;
    self->sort = sort_container;
    self->find_index = find_index_container;
    self->max = max_container;
    self->min = min_container;
    self->duplicate = duplicate_container;
    self->merge = merge_containers;
    self->batch_transfer = batch_transfer;
    self->batch_transfer_range = batch_transfer_range;
    self->rotate_partial = rotate_partial;
    self->reverse_partial = reverse_partial;

}

void size_container(const container_t* self)
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

void max_container(const container_t* self)
{
    if (self->size_container == 0) {
        printf("error\n");
        return;
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
        return;
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
            printf("%u\n", idx);
            return;
        }
        tmp = tmp->ptr_next;
        ++idx;
    }

}

void rotate_container(container_t* self, uint32_t K, uint32_t direction)
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

    if (new_ptr != NULL) {
        new_ptr->value = value;
        new_ptr->ptr_next = self->head;
        new_ptr->ptr_prev = NULL;
        self->head = new_ptr;
        self->size_container++;
    }

    return;
}

uint32_t pop(container_t* self)
{
    if (self->head == NULL) {
        printf("error\n");
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
        printf("error\n");
        return;
    }

    node_t* tmp_ptr = self->head;
    uint32_t tmp_value = tmp_ptr->value;

    if (self->size_container == 1) {
        self->head = NULL;
        self->tail = NULL;
    } else {
        self->head = tmp_ptr->ptr_next;
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


    return;
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
    container_t stack = {0};
    container_t queue = {0};
    container_t deque = {0};

    container_init(&stack, STACK);
    container_init(&queue, QUEUE);
    container_init(&deque, DEQUE);

    uint32_t N;
    scanf("%u", &N);
    while (getchar() != '\n');

    char buffer[100];
    uint32_t value;

    for(size_t i = 0; i<N; i++){
        if(fgets(buffer, 100, stdin) == NULL){
            return 1;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        char *command = strtok(buffer, " ");
        if (!command) {
            printf("error\n");
            continue;
        }

        sscanf(buffer, "%s", command);

        if (strcmp(command, "push_stack") == 0) {
            if (sscanf(buffer, "push_stack %u", &value) == 1) {
                stack.push(&stack, value);
            }
        }
        else if (strcmp(command, "pop_stack") == 0) {
            stack.pop(&stack);
        }
        else if (strcmp(command, "peek_stack") == 0) {
            stack.peek(&stack);
        }
        else if (strcmp(command, "size_stack") == 0) {
            stack.size(&stack);
        }

        else if (strcmp(command, "enqueue") == 0) {
            if (sscanf(buffer, "enqueue %u", &value) == 1) {
                queue.enqueue(&queue, value);
            }
        }
        else if (strcmp(command, "dequeue") == 0) {
            queue.dequeue(&queue);
        }
        else if (strcmp(command, "front_queue") == 0) {
            queue.front_queue(&queue);
        }
        else if (strcmp(command, "size_queue") == 0) {
            queue.size(&queue);
        }
        else if (strcmp(command, "reverse_queue") == 0) {
            queue.reverse(&queue);
        }

        else if (strcmp(command, "push_front_deque") == 0) {
            if (sscanf(buffer, "push_front_deque %u", &value) == 1) {
                deque.push_front(&deque, value);
            }
        }
        else if (strcmp(command, "push_back_deque") == 0) {
            if (sscanf(buffer, "push_back_deque %u", &value) == 1) {
                deque.push_back(&deque, value);
            }
        }
        else if (strcmp(command, "pop_front_deque") == 0) {
            deque.pop_front(&deque);
        }
        else if (strcmp(command, "pop_back_deque") == 0) {
            deque.pop_back(&deque);
        }
        else if (strcmp(command, "peek_front_deque") == 0) {
            deque.peek_front(&deque);
        }
        else if (strcmp(command, "peek_back_deque") == 0) {
            deque.peek_back(&deque);
        }
        else if (strcmp(command, "size_deque") == 0) {
            deque.size(&deque);
        }
        else if (strcmp(command, "reverse_deque") == 0) {
            deque.reverse(&deque);
        }

    }
    
}