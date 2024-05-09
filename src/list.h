typedef struct node node_t;
struct node {
    node_t *next;
    int data;
};

typedef struct list {
    node_t *head;
    node_t *tail;
} list_t;

list_t *new_list();
void append_list(list_t *list, int data);
void print_list(list_t *list);
int contains_list(list_t *list, int data);
void free_list(list_t *list);
node_t *new_node(int data);