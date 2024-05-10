#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/* 
 * a function that tests if there is a hamitonian path
 * from the topologically sorted graph.
 * 
 * based on the conclusion that if all pairs of verticies 
 * in the topologically sorted graph 
 * form a edge then there exist a hamiltonian path
 * 
*/
int *hamiltonian_dag_adj_list(adj_list_t *adj_list) {
    int u,v,i,*topological_sort = topological_sort_dag_adj_list(adj_list);
    if (topological_sort == NULL) {
        return NULL;
    }
    // check if all vertex pairs are edges
    for (i=1;i<adj_list->num_vertices;i++) {
        u = topological_sort[i-1];
        v = topological_sort[i];
        if (!contains_list(adj_list->edges[u],v)) {
            free(topological_sort);
            return NULL;
        }
    }
    return topological_sort;
}

/*  
    returns the topological sort of a DAG.
    The size of the returned array is the same as the number of vertices
    in the adjacency list.
*/
int *topological_sort_dag_adj_list(adj_list_t *adj_list) {
    int stack_size=0, *stack = (int*)malloc(adj_list->num_vertices*sizeof(int));
    int loop=0,i,*mark = (int*)malloc(adj_list->num_vertices*sizeof(int));
    for (i=0;i<adj_list->num_vertices;i++) {
        mark[0] = 0;
    }
    for (i=0;i<adj_list->num_vertices;i++) {
        if (mark[i] == 0) {
            dfs_adj_list(adj_list,i,stack,&stack_size,mark,&loop);
        }
    }
    if (loop) {
        free(stack);
        free(mark);
        return NULL;
    }
    //reverse list
    for (i=0;i<adj_list->num_vertices;i++){
        mark[adj_list->num_vertices-1-i] = stack[i];
    }
    free(stack);
    return mark;
}

int test_dag_adj_list(adj_list_t *adj_list) {
    int stack_size=0, *stack = (int*)malloc(adj_list->num_vertices*sizeof(int));
    int loop=0,i,*mark = (int*)malloc(adj_list->num_vertices*sizeof(int));
    for (i=0;i<adj_list->num_vertices;i++) {
        mark[0] = 0;
    }
    for (i=0;i<adj_list->num_vertices;i++) {
        if (mark[i] == 0) {
            dfs_adj_list(adj_list,i,stack,&stack_size,mark,&loop);
        }
    }
    free(stack);
    free(mark);
    return !loop;
}

/* 
    Takes performs depth first search and 
    pushes items into a stack in reverse order.
    
    Checks if a loop exists by returning -1.

    int vertex: starting vertex
    int *stack: array to push visited vertices into
    int stack_size: size of array
    int mark: array to mark vertices as visted 
*/
void dfs_adj_list(adj_list_t *adj_list, int vertex,int *stack,int *stack_size,int *mark,int *loop) {
    node_t *tempnode;    
    if (mark[vertex] == -1) {
        *loop=1;// loop detected
        return;
    } else if (mark[vertex] == 1) {
        return; // already visited
    };
    mark[vertex] = -1; // mark node as in progress

    //look at neighbours 
    tempnode = adj_list->edges[vertex]->head;
    while (tempnode) {
	    dfs_adj_list(adj_list, tempnode->data,stack,stack_size,mark,loop);
        tempnode=tempnode->next;
	}

    mark[vertex] = 1; // mark node as visited
    stack[*stack_size]=vertex;
    *stack_size+=1;
    return;
}

/*******************************************************/
adj_list_t *read_adj_list(FILE *file) {
    int i=0,j=0,edges=0,vertices=0;
    adj_list_t *adj_list;
    char *line=NULL;
    size_t len;
    getline(&line,&len,file);
    sscanf(line,"%d %d\n",&vertices,&edges);
    adj_list = new_adj_list(vertices);
    while(getline(&line,&len,stdin) != -1) {
        if (sscanf(line,"%d %d\n",&i,&j)!=2) {
            fprintf(stderr,"Error: each line must contain two numbers");
        }
        add_adj_list(adj_list,i,j);
    }
    return adj_list;
}

adj_list_t *new_adj_list(int num_vertices) {
    adj_list_t *adj_list = (adj_list_t*)malloc(sizeof(adj_list_t));
    adj_list->edges = (list_t**)malloc(num_vertices*sizeof(list_t*));
    adj_list->num_vertices = num_vertices;
  
    // initialise edge lists
    int i;
    for(i=0; i<num_vertices; i++) {
        adj_list->edges[i] = new_list();
    }
    return adj_list;
}

void add_adj_list(adj_list_t *adj_list, int vertex1, int vertex2) {
    if ((vertex1 < adj_list->num_vertices) && (vertex2 < adj_list->num_vertices)) {
        append_list(adj_list->edges[vertex1], vertex2);
        adj_list->num_edges++;
    } else {
        fprintf(stderr,"Warning invalid edge: %d-%d\nPlease ensure vertices are less than %d\n",vertex1,vertex2,adj_list->num_vertices);
    }
}

int contains_adj_list(adj_list_t *adj_list, int vertex1, int vertex2) {
    if ((vertex1 < adj_list->num_vertices) && (vertex2 < adj_list->num_vertices)) {
        return contains_list(adj_list->edges[vertex1],vertex2);
    }
    return 0;
}

void free_adj_list(adj_list_t *adj_list) {
    int i;
    for(i=0; i<adj_list->num_vertices; i++) {
        free_list(adj_list->edges[i]);
    }
    free(adj_list->edges);
    free(adj_list);
}

void output_adj_list(adj_list_t *adj_list, FILE *file) {
    int i;
    node_t *node;
    fprintf(file,"%d %d\n",adj_list->num_vertices,adj_list->num_edges);
    for (i=0;i<adj_list->num_vertices;i++) {
        node = adj_list->edges[i]->head;
        while (node) {
            fprintf(file,"%d %d\n",i,node->data);
            node = node->next;
        }
    }
}

void print_adj_list(adj_list_t *adj_list) {
    int i;
    for(i=0; i<adj_list->num_vertices; i++) {
        printf("%d | ",i);
        print_list(adj_list->edges[i]);
    }
}
