#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "util.h"
#include "args.h"

void tsort();
void hamiltonian();
void test();
void generate(int vertices, long double p, int connected);

int main(int argc, char **argv) {
    args program_args = {0,0.1,20,GENERATE};
    parse_args(argc,argv,&program_args);
    switch (program_args.program) {
        case TEST: 
            test();
            break;
        case HAMILTONIAN:
            hamiltonian();
            break;
        case T_SORT:
            tsort();
            break;
        case GENERATE:
            generate(program_args.vertices,program_args.sparsity,program_args.connected);
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
        // ensure connected
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
