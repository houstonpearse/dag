#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "util.h"
#include "time.h"

void tsort();
void hamiltonian();
void test();
void generate(int vertices, long double p, int connected);

#define COMMAND 4

int main(int argc, char **argv) {
    switch (COMMAND) {
        case 1: 
            test();
            break;
        case 2:
            hamiltonian();
            break;
        case 3:
            tsort();
            break;
        case 4:
            generate(100,0,1);
            break;
    }
}

void generate(int vertices, long double p, int connected) {
    srand(time(NULL));
    adj_list_t *adj_list = new_adj_list(vertices);
    int i,j,*perm = permutation(vertices);
    for (i=0;i<vertices;i++) {
        for (j=i+1;j<vertices;j++) {
            if (observe(p)) {
                add_adj_list(adj_list,perm[i],perm[j]);
            }
        }
        if (i != vertices-1 && connected && adj_list->edges[perm[i]]->head == NULL) {
            j = (rand() % ((vertices-1)-(i+1)+1)) + (i+1); // rand int between i+1 and n-1
            add_adj_list(adj_list,perm[i],perm[j]);
        }
    }
    output_adj_list(adj_list,stdout);
}

void test() {
    adj_list_t *adj_list = read_adj_list(stdin);
    printf("%d",test_dag_adj_list(adj_list));
    free_adj_list(adj_list);
}

void hamiltonian() {
    adj_list_t *adj_list = read_adj_list(stdin);
    int *hamiltonian = hamiltonian_dag_adj_list(adj_list);
    if (hamiltonian) {
        print_int_array(hamiltonian,adj_list->num_vertices,'\n');
    } 
    free_adj_list(adj_list);
}

void tsort() {
    adj_list_t *adj_list = read_adj_list(stdin);
    int *tsort = topological_sort_dag_adj_list(adj_list);
    if (tsort) {
        print_int_array(tsort,adj_list->num_vertices,'\n');
    } 
    free_adj_list(adj_list);
}
