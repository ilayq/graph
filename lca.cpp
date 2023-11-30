#include <iostream>
#include <vector>

using namespace std;


class Graph{
    public:
    int n, l;
    vector < vector<int> > g;
    vector<int> tin, tout;
    int timer;
    vector < vector<int> > up;
    
    Graph(int n);
    void push_edge(int u, int v); 
    void dfs(int v, int p);
    bool upper(int a, int b);
    int lca(int a, int b);
};

Graph::Graph(int n){
    this -> l = 1;
    while ((1 << l) <= n) ++(this -> l);
    this -> g = vector<vector<int>>(n);
    this -> tin = vector<int>(n);
    this -> tout = vector<int>(n);
    this -> up = vector<vector<int>>(n, vector<int>(l + 1));
}

void Graph::push_edge(int u, int v){
    g[u].push_back(v);
    g[v].push_back(u);
}


void Graph::dfs (int v, int p) {
	tin[v] = ++timer;
	up[v][0] = p;
	for (int i=1; i<=l; ++i)
		up[v][i] = up[up[v][i-1]][i-1];
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (to != p)
			dfs (to, v);
	}
	tout[v] = ++timer;
}

bool Graph::upper(int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int Graph::lca (int a, int b) {
	if (upper (a, b))  return a;
	if (upper (b, a))  return b;
	for (int i=l; i>=0; --i)
		if (!upper(up[a][i], b))
			a = up[a][i];
	return up[a][0];
}


int main(){
    int n;
    cin >> n;
    Graph* gr = new Graph(n);
    for (int i = 0; i < n - 1; ++i){
        int a, b;
        cin >> a >> b;
        gr -> push_edge(a, b);
    }
    gr -> dfs(0, 0);
    for (int i = 0; i < (gr -> up).size(); ++i){
        for (int j = 0; j < (gr -> up)[i].size(); ++j){
            cout << (gr -> up)[i][j] << ' ';
        }
        cout << endl;
    }
    for (int i = 0; i < n - 1; ++i){
        for (int j = i + 1; j < n; ++j){
            printf("lca of %d and %d: %d\n", i, j, gr -> lca(i, j));
        }
    }
}
