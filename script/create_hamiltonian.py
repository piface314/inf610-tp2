from random import choice, randint, shuffle
from sys import argv


if len(argv) <= 3:
    print(f"Usage:\n\t$ {argv[0]} <output> <edge-factor> <n-min> [<n-max> [<step>]]")
    exit(1)

def create_hamiltonian_graph(n_nodes, n_edges):
    m = [[0 for _ in range(n_nodes)] for _ in range(n_nodes)]
    nodes = list(range(n_nodes))
    shuffle(nodes)
    for i in range(n_nodes):
        u = nodes[i]
        v = nodes[(i+1)%n_nodes]
        m[u][v] = 1
        m[v][u] = 1
    n_edges -= n_nodes
    while n_edges:
        u = choice(nodes)
        v = choice([v for v, d in enumerate(m[u]) if not d and v != u])
        m[u][v] = 1
        m[v][u] = 1
        n_edges -= 1
    return m

out = argv[1]
factor = float(argv[2])
start = int(argv[3])
end = int(argv[4]) if len(argv) > 4 else start
step = int(argv[5]) if len(argv) > 5 else 1
with open(out, "w") as f:
    for i in range(start, end+1, step):
        n_nodes, n_edges = i, int(factor*i)
        m = create_hamiltonian_graph(n_nodes, n_edges)
        f.write(f"{n_nodes} {n_edges}\n")
        for u in range(n_nodes):
            for v in range(u+1, n_nodes):
                if m[u][v]:
                    f.write(f"{u} {v}\n")