#include <stdio.h>
#include <assert.h>
#include "../src/graph.h"

void test_list();
void test_adj_list();

int main(int argc, char **argv) {
    test_list();
    test_adj_list();
}

void test_list() {
    list_t *list = new_list();
    int a=1,b=2,c=3;
    append_list(list,a);
    append_list(list,b);
    append_list(list,c);
    assert(contains_list(list,1)==1);
    assert(contains_list(list,1)==1);
    assert(contains_list(list,1)==1);
    assert(contains_list(list,4)==0);
    assert(contains_list(list,0)==0);
    printf("\u2705 list test passed\n");
}

void test_adj_list() {
    adj_list_t *adj_list = new_adj_list(3);
    add_adj_list(adj_list, 1, 2);
    add_adj_list(adj_list, 0, 1);
    add_adj_list(adj_list, 2, 3);
    assert(contains_adj_list(adj_list,1,2) == 1);
    assert(contains_adj_list(adj_list,0,1) == 1);
    assert(contains_adj_list(adj_list,2,3) == 0);
    int *hamiltonian  = hamiltonian_dag_adj_list(adj_list);
    assert(hamiltonian[0]==0 && hamiltonian[1]==1 && hamiltonian[2]==2);
    printf("\u2705 adj_list test passed\n");
}