from collections import defaultdict, deque
import math

class Graph:
    ...


class Tree(Graph):
    def __init__(self, root: int = 1):
        self.gr = defaultdict(list)
        self.root = root 
        self.parents = []
        self.depth = []
        self.up = []

    def add_edge(self, u, v):
        self.gr[u].append(v)
        self.gr[v].append(u)

    def make_parents_and_depth(self):
        q = deque()
        q.append((self.root, self.root, 0))
        self.parents = [self.root] * (len(self.gr) + 1)
        self.depth = [0] * (len(self.gr) + 1)
        while q:
            cur_v, par, depth = q.popleft()
            self.parents[cur_v] = par
            self.depth[cur_v] = depth
            for neigh in self.gr[cur_v]:
                if neigh != par:
                    q.append((neigh, cur_v, depth + 1))

    def bad_lca(self, u, v):
        h1, h2 = self.depth[u], self.depth[v]
        while h1 != h2:
            if h1 > h2:
                u = self.parents[u]
                h1 -= 1
            else:
                v = self.parents[v]
                h2 -= 1
        while u != v:
            u, v = self.parents[u], self.parents[v]
        return u # or v
        #time == O(h), h - depth of tree

if __name__ == "__main__":
    gr = Tree()
    gr.add_edge(1, 2)
    gr.add_edge(2, 3)
    gr.add_edge(2, 4)
    gr.add_edge(1, 5)
    gr.add_edge(5, 6)
    gr.add_edge(1, 7)
    gr.add_edge(1, 8)
    gr.add_edge(8, 9)
    gr.make_parents_and_depth()
    print(gr.bad_lca(3, 4))
    print(gr.bad_lca(3, 8))
    print(gr.bad_lca(2, 5))
    print(gr.bad_lca(7, 6))

