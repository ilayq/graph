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
    
    def tarjan(self):
        index = 1
        ans = []
        st = deque()
        indexes = defaultdict(int)
        lowlinks = defaultdict(int)
        in_stack = defaultdict(int)
        
        def dfs(v):
            nonlocal index

            st.append(v)
            indexes[v] = index
            lowlinks[v] = index
            index += 1
            in_stack[v] = 1

            for neigh in self.gr[v]:
                if not indexes[neigh]:
                    dfs(neigh)
                    lowlinks[v] = min(lowlinks[v], lowlinks[neigh])
                elif in_stack[neigh]:
                    lowlinks[v] = min(lowlinks[v], indexes[neigh])

            if lowlinks[v] == indexes[v]:
                scc = []
                neigh = None
                while neigh != v:
                    neigh = st.pop()
                    in_stack[neigh] = 0
                    scc.append(neigh)
                ans.append(scc)

        for vert in self.gr:
            if vert not in indexes:
                dfs(vert)
        return ans


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
    print(gr.tarjan())


