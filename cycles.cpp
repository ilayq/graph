#include <bits/stdc++.h>
// #define shit ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
// #include <ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
using namespace std;
// #define all(v) v.begin(), v.end()
// #define rall(v) v.rbegin(),v.rend()
#define int long long
// typedef tree<int,null_type,less<int>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;
// #define size(a) (int)a.size()
// #define vint vector<int>
// #define pb push_back
// #define pint pair<int, int>
// #define range(i, s, e) for (int i = s; i < e; ++i)
//bismillah


template <typename T> void print_arr(T& arr){
    for (auto& i : arr){
        cout << i << ' ';
    }
    cout << '\n';
}


class Graph{
    int n;
    unordered_map<int, unordered_set<int>> gr;
    public:
        Graph(int n);
        void add_edge(int u, int v);
        bool is_cyclic();
        vector<int> find_cycle();
        void euler_cycle(int v);
};

void Graph::euler_cycle(int v){

}


Graph::Graph(int n){
    this -> n = n;
    for (int i = 0 ; i < n + 1; ++i){
        gr[i] = {};
    } 
}

void Graph::add_edge(int u, int v){
    gr[u].insert(v);
    gr[v].insert(u);
}

bool Graph::is_cyclic(){
    unordered_map<int, int> visited;
    for (int i = 1 ; i < n + 1; ++i){
        visited[i] = 0;
    }
    for (int i = 1; i < n + 1; ++i){
        if (!visited[i]){
            stack<pair<int, int>> st; // v and from 
            st.push(make_pair(i, -1));
            while (st.size()){
                pair<int, int> cur = st.top();
                int cur_v = cur.first;
                int from = cur.second;
                visited[cur_v] = 1;
                st.pop();
                for (int neigh : gr[cur_v]){
                    if (!visited[neigh]){
                        st.push(make_pair(neigh, cur_v));
                    }
                    else{
                        if (from != neigh){
                            return true;
                        }
                    }
                } 
            }
        }
    }
    return false;
}


vector<int> Graph::find_cycle(){
    if (!(this -> is_cyclic()))
        return vector<int> {};
    unordered_map<int, int> visited;
    unordered_map<int, int> path;
    for (int i = 1 ; i < n + 1; ++i){
        visited[i] = 0;
    }
    for (int i = 1; i < n + 1; ++i){
        if (!visited[i]){
            stack<pair<int, int>> st; // v and from 
            st.push(make_pair(i, -1));
            while (st.size()){
                pair<int, int> cur = st.top();
                int cur_v = cur.first;
                int from = cur.second;
                path[cur_v] = from;
                visited[cur_v] = 1;
                st.pop();
                for (int neigh : gr[cur_v]){
                    if (!visited[neigh]){
                        st.push(make_pair(neigh, cur_v));
                    }
                    else{
                        if (from != neigh){
                            int cycle_end = neigh;
                            int current_vert = cur_v;
                            vector<int> ans;
                            while (current_vert != cycle_end){
                                ans.push_back(current_vert);
                                current_vert = path[current_vert];
                            }
                            ans.push_back(current_vert);
                            return ans;
                        }
                    }
                } 
            }
        }
    }
    return vector<int> {};
}

void solve(){
    // int n;
    // cin >> n;
    Graph* gr = new Graph(1);
    gr -> add_edge(1, 1);
    // for (int i = 0 ; i < n ; ++i){
    //     for (int j = 0 ; j < n ; ++j){
    //         int asd;
    //         cin >> asd;
    //         if (asd)
    //             gr -> add_edge(i + 1, j + 1);
    //     }
    // }
    bool cyclic = gr -> is_cyclic();
    if (cyclic){
        vector<int> ans = gr -> find_cycle();
        cout << "YES" << '\n';
        cout << ans.size() << '\n';
        print_arr(ans);
        return; 
    }
    cout << "NO" << '\n';
}


int32_t main(){
    solve();
}
