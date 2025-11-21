// Is it correct? 
// TODO

struct BCC {
    /*
        <<Node 1-based>>
        <<Edges_id 0-based>>
        Declaration:
            n: node
            m: edges number
        Usage:
            Init:
                // edges -> {a, b} // pair<int,int>
                BCC bcc(n, edges);
            Solve:
                auto [bridges, aps] = bcc.solve();
    */
    int n, m;
    vector<vector<pair<int, int> > > f; // d, edges_id
    vector<bool> bridge, ap;
    vector<int> dep, low;
    int dfn = 0;
    BCC(int n, const vector<pair<int, int> > &edges) : n(n) {
        dep.resize(n+1);
        low.resize(n+1);
        bridge.resize(edges.size());
        ap.resize(n+1);
        m = edges.size();
        for(int i = 0; i < m; i++) {
            auto [a, b] = edges[i];
            f[a].push_back({b, i});
            f[b].push_back({a, i});
        }
    }
    void dfs(int id, int pa) {
        dep[id] = low[id] = ++dfn;
        int child = 0;
        for(auto &[d, w_id] : f[id]) if(d != pa) {
            child++;
            if(!dep[d]) {
                dfs(d, id), low[id] = min(low[id], low[d]);
                if(low[d] >= dep[id] && pa != -1) {
                    ap[d] = true;
                    bridge[w_id] = true;
                }
            }
            else low[id] = min(low[id], dep[d]);
        }
        if(pa == -1 && child > 1) {
            ap[id] = true;
            for(auto &[d, c] : f[id]) bridge[c] = true;
        }
    }
    pair<vector<int>, vector<int> > solve() {
        dfs(1, -1);
        vector<int> bridges;
        for(int i = 0; i < m; i++) if(bridge[i]) bridges.push_back(i);
        vector<int> aps;
        for(int i = 1; i <= n; i++) if(ap[i]) aps.push_back(i);
        return {bridges, aps};
    }
};