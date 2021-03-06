// https://codingcompetitions.withgoogle.com/codejam/round/0000000000007706/0000000000045875

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class HopCroftKarpBPM {

    /*
        U, V = size of two bipartite sets
        Node IDs start from 1
    */

    const int NIL = 0;
    const int INF = 1<<30;
    int U, V;

    vector<int> Pair_U, Pair_V;

    vector<vector<int> > Adj;

    queue<int> Q;

    vector<int> Dist;


    bool BFS() {
        Q = queue<int>();
        for (int u = 1; u <= U; u ++) {
            if (Pair_U[u] == NIL) {
                Dist[u] = 0;
                Q.push(u);
            } else {
                Dist[u] = INF;
            }
        }

        Dist[NIL] = INF;
        
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            if (Dist[u] < Dist[NIL]) 
                for (int v: Adj[u]) 
                    if (Dist[ Pair_V[v] ] == INF) {
                        Dist[ Pair_V[v] ] = Dist[u] + 1;
                        Q.push(Pair_V[v]);    
                    }
        }

        return Dist[NIL] != INF;
    }

    bool DFS(int u) {
        if (u != NIL) {
            for (int v: Adj[u]) 
                if (Dist[ Pair_V[v] ] == Dist[u] + 1)
                    if (DFS(Pair_V[v])) {
                        Pair_V[v] = u;
                        Pair_U[u] = v;
                        return true;
                    }
            
            Dist[u] = INF;
            return false;
        }

        return true;
    }

    public:

    HopCroftKarpBPM() {}

    HopCroftKarpBPM(int U, int V, const vector<vector<int> >& E) {
        this->U = U;
        this->V = V;
        Pair_U = vector<int> (U + 1, NIL);
        Pair_V = vector<int> (V + 1, NIL);

        Dist = vector<int> (U + 1); 

        Adj = vector<vector<int> > (U + 1);

        for (int i = 1; i <= U; i ++) {
            Adj[i] = vector<int> (E[i].begin(), E[i].end());
        }
    }

    int Solve() {

    
        
        for (int u = 1; u <= U; u ++) 
            Pair_U[u] = NIL;

        for (int v = 1; v <= V; v ++) 
            Pair_V[v] = NIL;
        
        int matching = 0;

        while (BFS()) {
            for (int u = 1; u <= U; u ++) 
                if (Pair_U[u] == NIL)
                    if (DFS(u))
                        matching ++;
        }

        return matching;
    }
};

vector<vector<int> > edges;

vector< vector<pair<int,int> > > pos;

int id(int u, int n) {
    if (u > 0) return u + n;
    return -u;
}

int main() {
    freopen("data.in", "r", stdin);

    int t;
    scanf("%d", &t);
    for (int ca = 1; ca <= t; ca ++) {


        int n;
        scanf ("%d", &n);

        pos = vector<vector<pair<int,int> > > (2*n + 1);     

        for (int i = 1, a; i <= n; i ++) {
            for (int j = 1; j <= n; j ++) {
                scanf ("%d", &a);
                pos[id(a, n)].push_back({i, j});
            }
        }

       

        int cnt = 0;

        for (int i = 1; i <= 2*n; i ++) {
            
            if (!pos[i].size()) continue;

            edges = vector<vector<int> > (n + 1);

            for (pair<int, int> p: pos[i]) 
                edges[p.first].push_back(p.second);
            
            HopCroftKarpBPM bpm = HopCroftKarpBPM(n, n, edges);

            cnt += bpm.Solve();
        }

        printf("Case #%d: %d\n", ca, n*n - cnt);
        
    }

    return 0;
}