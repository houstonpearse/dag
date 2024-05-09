<h1 align="center">DAG Generator and DAG Hamiltonian finder</h1>
<br />
<div align="center">
  <a href="https://github.com/houstonpearse/dag">
    <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/f/fe/Tred-G.svg/640px-Tred-G.svg.png" alt="Logo" width="200" height="200">
  </a>
  <a href="https://github.com/houstonpearse/dag">
    <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/c6/Topological_Ordering.svg/1024px-Topological_Ordering.svg.png" alt="Logo" width="200" height="200">
  </a>

<h3 align="center">DAG</h3>
<p>
A program for generating graphs and determining if there exists a Hamiltonian path for Directed Acyclic Graphs(DAGs).
</p>
</div>

## Features

Find the hamiltonian path for a DAG
`./dag hamiltonian`

Test that a Graph contains no cycles.
`./dag test`

Perform a topological sort on the DAG
`./dag t-sort`

Generate a DAG
`./dag generate --vertices 440 --sparsity 0.4 --connected`

Generate a DAG and find a hamiltonian
`./dag generate --vertices 100 --sparsity 1 --connected | ./dag hamiltonian`

## Usage

compile with `make dag`

run with `./dag --help`

unit-test with `make unit-test`

validation test with `make validation-test`


## Dag generation

let $G$ be a graph with $n$ vertices $V = \{0,1,...,n-1\}$, $v_i \in V$ and $m$ edges $e_{i,j} \in E$

A DAG Must have an ordring $\{v_0, v_1, ... v_{n-1}\}$ of $V$ such that $\forall v_i, v_j: i > j \implies \nexists e(i,j)$

Which means for a DAG $max(m) = 0 + 1 + 2 + ...+ n -1 = n(n-1)/2$

or alternatively $0 <= m <= n(n-1)/2$

So if we want to generate a random DAG then we need to

$\forall i < j$ let $Pr(e_{i,j}) = p$ , $p\in[0,1]$

$\forall i \ge j$ let $Pr(e_{i,j}) = 0 $

Then $m = pn(n-1)/2$

And when $p$ ~ $0$ we have a very sparse DAG and when $p$ ~ $1$ we have a very dense DAG.

### connected DAG

For DAG with N vertices. A DAG is connected, if, for each vertex A, the sum of vertices that can be reached from A, and the sum of vertices that can reach A, total to N.

To generate a DAG that is connected. For each vertex $v_i$ we must ensure $$\sum^{i \lt j}e_{i,j} + \sum^{i \lt j}e_{j,i} \ge 1$$

## topological sort

A topological sort is an ordering of vertices where each vertex will only appear if each vertex pointing to it has already appeared.

This means that if there exists a cycle within the graph then there is no valid topological sort.

Visual example.

<a href="https://github.com/houstonpearse/dag">
    <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/c6/Topological_Ordering.svg/1024px-Topological_Ordering.svg.png" alt="Logo" width="200" height="200">
  </a>

### Algorithm

by performaing a depth first search on the graph and pushing vertices on a stack we can construct an array that will be the topological sort of the DAG. If a loop is detected then there is no valid topological sort.

## hamiltonian

A Hamiltonion path is a path that visits each vertex in the graph.

### Algorithm

First perform a topological sort then each neighbouring element in the topological sort will be connected if a hamiltonian exists. This is easy to see from the topological sort example above.
