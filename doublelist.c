#include <stdio.h>
#include <stdlib.h>

struct node {
    void *data;
    struct node *right;
    struct node *left;
};

struct list {
    struct node *front;
    struct node *back;
};

struct node *create_node(void *x);

struct list create_list();
int is_empty(struct list *l);
void push_front(struct list *l, void *x);
void pop_front(struct list *l);
void push_back(struct list *l, void *x);
void pop_back(struct list *l);
void delete(struct list *l);

void print_list(struct list *l, void (*print_node)(void *));

void print_int(void *x) { printf("%d", *(int*)(x)); }
void print_dloat(void *x) { printf("%f", *(float*)(x)); }

int main()
{
    struct list my_list = create_list();

    int i = 1;
    for (i = 1; i <= 5; i++) {
        int *x;

        x = malloc(sizeof(int));
        *x = -i;
        push_front(&my_list, x);

        x = malloc(sizeof(int));
        *x = i;
        push_back(&my_list, x);

        print_list(&my_list, print_int);
    }

    printf("Popping front:\n");
    pop_front(&my_list);
    print_list(&my_list, print_int);

    printf("Popping back:\n");
    pop_back(&my_list);
    print_list(&my_list, print_int);

    printf("Deleting:\n");
    delete(&my_list);
    print_list(&my_list, print_int);

    return 0;
}


struct node *create_node(void *x)
{
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = x;
    new_node->right = NULL;
    new_node->left = NULL;
    return new_node;
}


struct list create_list()
{
    struct list new_list;
    new_list.front = NULL;
    new_list.back = NULL;
    return new_list;
}


int is_empty(struct list *l)
{
    return (l->front == NULL && l->back == NULL);
}


void push_front(struct list *l, void *x)
{
    struct node *new_node = create_node(x);
    if (is_empty(l)) {
        l->front = new_node;
        l->back = new_node;
    } else {
        new_node->right = l->front;
        l->front->left = new_node;
        l->front = new_node;
    }
    return;
}


void pop_front(struct list *l)
{
    if (!is_empty(l)) {
        struct node *tmp = l->front;
        l->front = tmp->right;
        if (l->front == NULL)
            l->back = NULL;
        else
            l->front->left = NULL;
        free(tmp->data);
        free(tmp);
    }
    return;
}

void push_back(struct list *l, void *x)
{
    struct node *new_node = create_node(x);
    if (is_empty(l)) {
        l->front = new_node;
        l->back = new_node;
    } else {
        new_node->left = l->back;
        l->back->right = new_node;
        l->back = new_node;
    }
    return;
}

void pop_back(struct list *l)
{
    if (!is_empty(l)) {
        struct node *tmp = l->back;
        l->back = tmp->left;
        if (l->back == NULL)
            l->front = NULL;
        else
            l->back->right = NULL;
        free(tmp->data);
        free(tmp);
    }
    return;
}

void delete(struct list *l)
{
    while (l->front != NULL)
        pop_front(l);
}

void print_list(struct list *l, void (*print_node)(void *))
{
    if (is_empty(l)) {
        printf("List is empty!\n");
    } else {
        struct node *runner = l->front;
        printf("NULL <-> ");
        while (runner != NULL) {
            print_node(runner->data);
            printf(" <-> ");
            runner = runner->right;
        }
        printf("NULL\n");
    }
    return;
}
