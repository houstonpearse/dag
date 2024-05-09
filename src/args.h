#define HAMILTONIAN 0 
#define TEST 1
#define T_SORT 2
#define GENERATE 3

typedef struct {
    int connected;
    long double sparsity;
    int vertices;
    int program;
} args;

void parse_args(int argc, char **argv, args *program_args);