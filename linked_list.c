#include <stdlib.h>
#include <stdio.h>


struct node {
    void *data;
    struct node *next;
    struct node *prev;
};

struct linked_list {
    struct node *head;
    struct node *tail;
    size_t qty;
};

typedef struct linked_list LinkedList_t;

// Constructor & Destructor
LinkedList_t *linkedList_create();
void linkedList_destroy(LinkedList_t *list);

// TODO Get & Set
void *linkedList_get(LinkedList_t *list, size_t index); // devuelve el dato guardado en el nodo en la posicion index
void *linkedList_set(LinkedList_t *list, size_t index, void *value); // cambia el dato de un nodo que ya existe
void *linkedList_insert(LinkedList_t *list, size_t index, void *value); // inserta un nuevo nodo en la posicion index

// Stack
void *linkedList_push(LinkedList_t *list, void *value);
void *linkedList_pop(LinkedList_t *list);

// Queue
void *linkedList_enqueue(LinkedList_t *list, void *value);
void *linkedList_dequeue(LinkedList_t *list);

// TODO ordenamiento

// TODO busqueda

// Print
void linkedList_print(LinkedList_t *list);


int _test_push_y_pop() {
    printf("Test de stacks\n");
    LinkedList_t *list = linkedList_create();
    int num1 = 1;
    if (linkedList_push(list, &num1) == NULL) {
        linkedList_destroy(list);
        return 1;
    }
    int num2 = 2;
    if (linkedList_push(list, &num2) == NULL) {
        linkedList_destroy(list);
        return 1;
    }
    int num3 = 3;
    if (linkedList_push(list, &num3) == NULL) {
        linkedList_destroy(list);
        return 1;
    }

    linkedList_print(list);
    putchar('\n');

    printf("Se quito el elemento %d \n", *((int*)linkedList_pop(list)));
    printf("Se quito el elemento %d \n", *((int*)linkedList_pop(list)));
    printf("Se quito el elemento %d \n", *((int*)linkedList_pop(list)));
    // usar asserts para ver que devuelva null
    linkedList_pop(list);
    linkedList_pop(list);
    linkedList_pop(list);

    linkedList_destroy(list);
    printf("\n\n");
    return 0;
}

int _test_enqueue_y_dequeue() {
    printf("Test de queues\n");
    LinkedList_t * list = linkedList_create();
    int num1 = 1;
    if (linkedList_enqueue(list, &num1) == NULL) {
        linkedList_destroy(list);
        return 1;
    }
    int num2 = 2;
    if (linkedList_enqueue(list, &num2) == NULL) {
        linkedList_destroy(list);
        return 1;
    }
    int num3 = 3;
    if (linkedList_enqueue(list, &num3) == NULL) {
        linkedList_destroy(list);
        return 1;
    }

    linkedList_print(list);
    putchar('\n');

    printf("Se quito el elemento %d \n", *((int*)linkedList_dequeue(list)));
    printf("Se quito el elemento %d \n", *((int*)linkedList_dequeue(list)));
    printf("Se quito el elemento %d \n", *((int*)linkedList_dequeue(list)));
    // usar assers para ver que devuelva null
    linkedList_dequeue(list);
    linkedList_dequeue(list);
    linkedList_dequeue(list);
    
    linkedList_destroy(list);
    printf("\n\n");
    return 0;
}

int _test_set_get() {
    printf("Test de set, get, insert\n");
    LinkedList_t * list = linkedList_create();
    int num1 = 1;
    if (linkedList_enqueue(list, &num1) == NULL) {
        linkedList_destroy(list);
        return 1;
    }
    int num2 = 2;
    if (linkedList_enqueue(list, &num2) == NULL) {
        linkedList_destroy(list);
        return 1;
    }
    int num3 = 3;
    if (linkedList_enqueue(list, &num3) == NULL) {
        linkedList_destroy(list);
        return 1;
    }

    linkedList_print(list);
    putchar('\n');

    int new_num = 5;
    size_t set_index = 1;
    if (linkedList_set(list, set_index, &new_num) == NULL) {
        linkedList_destroy(list);
        return 1;
    }
    printf("Se obtuvo el elemento en la posicion %zd: %d \n", set_index, *((int*)linkedList_get(list, set_index)));
    // usar assers para ver que devuelva null
    
    linkedList_destroy(list);
    printf("\n\n");
    return 0;
}

int _test_insert() {
    printf("Test de insert\n");
    LinkedList_t * list = linkedList_create();
    if (list == NULL) return 1;

    int num1 = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;
    int num5 = 5;
    printf("Se inserta un elemento en la posicion 0\n");
    linkedList_insert(list, 0, &num1);
    printf("Se obtiene el elemento en la posicion 0: %d \n", *((int*)linkedList_get(list, 0)));

    printf("Se inserta un nuevo elemento en la posicion 0\n");
    linkedList_insert(list, 0, &num2);
    printf("Se obtiene el nuevo elemento en la posicion 0: %d \n", *((int*)linkedList_get(list, 0)));

    printf("Se inserta un elemento al final (posicion 2)\n");
    linkedList_insert(list, 2, &num3);
    printf("Se obtiene el nuevo elemento en la posicion 2: %d \n", *((int*)linkedList_get(list, 2)));

    printf("Se inserta un elemento en el medio (posicion 1)\n");
    linkedList_insert(list, 1, &num4);
    printf("Se obtiene el nuevo elemento en la posicion 1: %d \n", *((int*)linkedList_get(list, 1)));

    printf("Se intenta insertar un elemento en la posicion 5 (deberia fallar)\n");
    if (linkedList_insert(list, 5, &num5) == NULL) {
        printf("La insercion fallo correctamente\n");
    }

    printf("Se imprime la lista completa:\n");
    linkedList_print(list);

    linkedList_destroy(list);
    printf("\n\n");
    return 0;
}

int main(void) {
    LinkedList_t *list = linkedList_create();
    if (list == NULL) return 1;

    _test_push_y_pop();
    _test_enqueue_y_dequeue();
    _test_set_get();
    _test_insert();

    linkedList_destroy(list);
    return 0;
}




struct node *_node_create(void *data) {
    struct node *node = malloc(sizeof(struct node));
    if (node == NULL) return NULL;

    node->data = data;
    node->prev = NULL;
    node->next = NULL;
}

void _node_destroy(struct node *node) {
    free(node);
}

LinkedList_t *linkedList_create() {
    LinkedList_t *list = malloc(sizeof(LinkedList_t));
    if (list == NULL) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->qty = 0;

    return list;
}

void linkedList_destroy(LinkedList_t *list) {
    struct node *actual = list->head;
    while (actual != NULL) {
        struct node *prev = actual;
        actual = actual->next;
        _node_destroy(prev);
    }
    free(list);
}

void *linkedList_get(LinkedList_t *list, size_t index) {
    if (index >= list->qty) return NULL;
    struct node *actual = list->head;
    for (size_t i = 0; i < index; i++) {
        actual = actual->next;
    }
    return actual->data;
}

void *linkedList_set(LinkedList_t *list, size_t index, void *value) {
    if (index >= list->qty) return NULL;
    struct node *actual = list->head;
    for (size_t i = 0; i < index; i++) {
        actual = actual->next;
    }
    actual->data = value;
    return actual->data;
}

// chequear casos donde quiero insertar en una lista vacia,
// donde quiero insertar algo en el primer lugar, 
// y donde quiero insertar en la ultima posicion
void *linkedList_insert(LinkedList_t *list, size_t index, void *value) {
    if (list == NULL || value == NULL || index > list->qty) return NULL;
    struct node *new_node = _node_create(value);
    if (new_node == NULL) return NULL;
    struct node *actual = list->head; // Si la lista esta vacia, actual == NULL 
    if (actual == NULL) {
        list->head = new_node;
    } else {
        struct node *prev = NULL;
        for (size_t i = 0; i < index; i++) {
            prev = actual;
            actual = actual->next;
        }
        // Si index == list-qty, actual == NULL
        if (index != 0) {
            if (index < list->qty) {
                new_node->next = actual->next;
            }
        }
        if (prev == NULL) {
            list->head->prev = new_node;
            new_node->next = list->head;

            list->head = new_node;
        } else {
            prev->next = new_node;
            new_node->next = actual;
        }
    }
    list->qty++;
    return new_node->data;
}


void *linkedList_push(LinkedList_t *list, void *value) {
    if (list == NULL || value == NULL) return NULL;
    struct node *new_node = _node_create(value);
    if (new_node == NULL) return NULL;

    if (list->head == NULL) { // Empty list
        list->head = new_node;
        list->tail = new_node;
    }
    else {
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->qty++;
}

void *linkedList_pop(LinkedList_t *list) {
    if (list == NULL || list->qty == 0) return NULL;
    void *data = list->tail->data;
    struct node *actual_tail = list->tail;
    
    list->tail = actual_tail->prev;
    if (list->tail != NULL) {
        list->tail->next = NULL;
        list->head = NULL;
    }
    _node_destroy(actual_tail);
    list->qty--;

    // Ver si se puede enganchar con la condicion de arriba
    if (list->qty == 0) {
        list->head = NULL;
    }

    return data;
}

void *linkedList_enqueue(LinkedList_t *list, void *value) {
    if (list == NULL || value == NULL) return NULL;
    if (linkedList_push(list, value) == NULL) return NULL;
    return value;
}

void *linkedList_dequeue(LinkedList_t *list) {
    if (list == NULL || list->qty == 0) return NULL;
    void *data = list->head->data;
    struct node *actual_head = list->head;


    list->head = list->head->next;
    if (list->head != NULL) {
        list->head->prev = NULL;
    }
    _node_destroy(actual_head);
    list->qty--;

    if (list->qty == 0) {
        list->tail = NULL;
    }
    return data;
}


void _node_print(struct node *node, void(*print)(void *value)) {
    print(node->data);
}

void _print(void *value) {
    printf("%d ", *((int *)value));
}

void linkedList_print(LinkedList_t *list) {
    struct node *actual = list->head;
    while (actual != NULL) {
        struct node *prev = actual;
        actual = actual->next;
        _node_print(prev, _print);
    }
}


