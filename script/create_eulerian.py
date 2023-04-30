from random import choice, randint, shuffle
from sys import argv


if len(argv) <= 3:
    print(f"Usage:\n\t$ {argv[0]} <output> <edge-factor> <n-min> [<n-max> [<step>]]")
    exit(1)

def create_cycle_r(m, cycle, n, nodes):
    if n == 1:
        if m[cycle[0]][cycle[-1]]:
            return None
        else:
            m[cycle[0]][cycle[-1]] = 1
            m[cycle[-1]][cycle[0]] = 1
            return cycle
    u = cycle[-1]
    options = list(nodes - set(cycle) - {v for v, d in enumerate(m[u]) if d})
    shuffle(options)
    for v in options:
        m[u][v] = 1
        m[v][u] = 1
        if c := create_cycle_r(m, cycle + [v], n-1, nodes):
            return c
        m[u][v] = 0
        m[v][u] = 0
    return None

def create_cycle(m, n, nodes):
    shuffle(nodes)
    for v in nodes:
        if c := create_cycle_r(m, [v], n, set(nodes)):
            return c
    return None

def create_eulerian_graph(n_nodes, n_edges):
    m = [[0 for _ in range(n_nodes)] for _ in range(n_nodes)]
    nodes = list(range(n_nodes))
    create_cycle(m, n_nodes, nodes)
    n_edges -= n_nodes
    while n_edges >= 3:
        n = min(n_nodes, choice([n_edges, randint(3, max(3, n_edges - 3))]))
        create_cycle(m, n, nodes)
        n_edges -= n
    return m

out = argv[1]
factor = float(argv[2])
start = int(argv[3])
end = int(argv[4]) if len(argv) > 4 else start
step = int(argv[5]) if len(argv) > 5 else 1
with open(out, "w") as f:
    for i in range(start, end+1, step):
        n_nodes, n_edges = i, int(factor*i)
        m = create_eulerian_graph(n_nodes, n_edges)
        f.write(f"{n_nodes} {n_edges}\n")
        for u in range(n_nodes):
            for v in range(u+1, n_nodes):
                if m[u][v]:
                    f.write(f"{u} {v}\n")