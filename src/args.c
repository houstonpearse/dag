#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "args.h"

const struct option long_opts[] = {
    {"help",no_argument,NULL,'h'},
    {"sparsity", required_argument, NULL, 's'},
    {"connected", no_argument, NULL, 'c'},
    {"vertices", required_argument,NULL,'v'},
    {NULL, 0, NULL, 0}
};

const char *short_opts = "h:s:c:v:";

void print_help() {
    printf("Usage:\n\n");
    printf("\t./dag hamiltoinan\n\n");
    printf("\t\tReads a DAG from stdin and returns the hamiltonian path if it exists\n\n");
    printf("\t./dag test\n\n");
    printf("\t\tReads a graph from stdin and tests if it is a dag\n\n");
    printf("\t./dag t-sort\n\n");
    printf("\t\tReads a graph from stdin and performs a topilogical sort if it is a valid dag\n\n");
    printf("\t./dag generate --vertices 100 --sparsity 0.2 --connected\n\n");
    printf("\t\tGenerates a DAG and outputs it to stdout\n\n");
    printf("\t\t--vertices INT\n\n");
    printf("\t\t\tThis option specifies the size of the Graph i.e. the number of vertices.\n\n");
    printf("\t\t--sparsity FLOAT\n\n");
    printf("\t\t\tThis option specifies how many edges will be produced.\n\n");
    printf("\t\t\tIf 0 is specified then the graph will have no edges. \n\n");
    printf("\t\t\tIf 1 is specified then the graph will have n(n-1)/2 edges. \n\n");
    printf("\t\t\tIf 0.x is specified then the graph will have ~ 0.x * n(n-1)/2 edges.\n\n");
    printf("\t\t\tIf the --connected option is set than there will be at least n-1 edges.\n\n");
    printf("\t\t--connected\n\n");
    printf("\t\t\tThis option specifies whether or not the graph will be connected.\n\n");
    printf("\t\t\tIf the option is set then vertex will either have a edge leading to it or leaving from it\n\n");

}

void parse_args(int argc, char **argv, args *program_args) {
    int index;
    char c;
    while ((c = getopt_long(argc,argv,short_opts,long_opts,&index)) != -1) {
        switch (c) {
            case 'h':
                print_help();
                exit(0);
            case 's':
                program_args->sparsity = strtold(optarg,NULL);
                if (program_args->sparsity < 0 || program_args->sparsity > 1) {
                    fprintf(stderr,"sparsity must be a float > 0 and < 1");
                    exit(1);
                }
                break;
            case 'c':
                program_args->connected = 1;
                break;
            case 'v':
                program_args->vertices=atoi(optarg);
                if (program_args->vertices<=1) {
                    fprintf(stderr,"vertices must be greater than 1");
                    exit(1); 
                }
                break;
        }
    }
    int i;
    for (i = optind; i < argc; i++) {
        if (strcmp(argv[i],"hamiltonian")==0) {
            program_args->program = HAMILTONIAN;
        } else if (strcmp(argv[i],"test")==0) {
            program_args->program = TEST;
        } else if (strcmp(argv[i],"t-sort")==0) {
            program_args->program = T_SORT;
        } else if (strcmp(argv[i],"generate")==0) {
            program_args->program = GENERATE;
        } else {
            fprintf(stderr,"Unknown argument: %s\n",argv[i]);
            print_help();
            exit(1);
        }
    }  
}