import sys
from collections import defaultdict, deque


sys.setrecursionlimit(10 ** 6)


class Graph:
    def __init__(self):
        self.gr = {}
    
    def add_edge(self, u, v):
        if u not in self.gr:
            self.gr[u] = []
        self.gr[u].append(v)

    def find_strong_connected_tarjan(self) -> list[list[int]]:
        stack = []
        indexes = defaultdict(lambda: 0)
        lowlinks = defaultdict(lambda: 0)
        in_stack = defaultdict(lambda: False)
        scc = []
        strong_components = []

        def strong_connect(vertex):
            indexes[vertex], lowlinks[vertex] = len(indexes), len(indexes)
            stack.append(vertex)
            in_stack[vertex] = True

            # Обход вершин через поиск в глубину
            for neighbour_vertex in self.gr[vertex]:
                if indexes[neighbour_vertex] == 0:
                    strong_connect(neighbour_vertex)
                    lowlinks[vertex] = min(lowlinks[vertex], lowlinks[neighbour_vertex])
                elif in_stack[neighbour_vertex]:
                    lowlinks[vertex] = min(lowlinks[vertex], indexes[neighbour_vertex])

            # Попали в корень компонента связности, извлекаем вершины потомки
            if lowlinks[vertex] == indexes[vertex]:
                scc = []
                neighbour_vertex = None
                while vertex != neighbour_vertex:
                    neighbour_vertex = stack.pop()
                    scc.append(neighbour_vertex)
                    in_stack[neighbour_vertex] = False
                strong_components.append(scc)

        for asd in self.gr:
            if indexes[asd] == 0:
                strong_connect(asd)
 
        return strong_components


if __name__ == "__main__":
    gr = Graph()
    gr.gr = {
        'A': {'B'},
        'B': {'C'},
        'C': {'B', 'D'},
        'D': {'E'},
        'E': {'F'},
        'F': {'D'},
    }
    print(gr.find_strong_connected_tarjan())


