#include "list.h"

typedef struct {
    list_t **edges;
    int num_vertices;
    int num_edges;
} adj_list_t;

int *hamiltonian_dag_adj_list(adj_list_t *adj_list);
int *topological_sort_dag_adj_list(adj_list_t *adj_list);
int test_dag_adj_list(adj_list_t *adj_list);
void dfs_adj_list(adj_list_t *adj_list, int vertex,int *stack,int *stack_size,int *mark, int *loop);

adj_list_t *read_adj_list(FILE *file);
adj_list_t *new_adj_list(int num_vertices);
void add_adj_list(adj_list_t *adj_list, int vertex1, int vertex2);
int contains_adj_list(adj_list_t *adj_list, int vertex1, int vertex2);
void print_adj_list(adj_list_t *adj_list);
void output_adj_list(adj_list_t *adj_list, FILE *file);
void free_adj_list(adj_list_t *adj_list);