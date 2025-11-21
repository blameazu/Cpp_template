struct MCMF {
	/*
		<<1-based>>
		<<Need define int long long>>
		Declaration:
			s: source
			t: sink
		Usage:
			Init:
				MCMF flow(n, s, t);
			Add edge:
				flow.addedge(a, b, Flow, Cost);
				// a -> b & it will add a reversed edge
			Solve:
				auto [Max_flow, Min_cost] = flow.solve();
	*/
	int n;
	int s, t; // source and sink
	vector<array<int, 3> > edges;
	vector<vector<int> > f;
	vector<int> pa, dis, mnf;
	MCMF(int n, int s, int t) : n(n), s(s), t(t) {
		f.resize(n+1);
		pa.resize(n+1);
		dis.resize(n+1);
		mnf.resize(n+1);
	}
	int add(int i, int F, int C) {
		edges.push_back({i, F, C});
		return edges.size()-1;
	}
	void addedge(int a, int b, int F, int C) {
		f[a].push_back(add(b, F, C));
		f[b].push_back(add(a, 0, -C));
	}
	int spfa() {
		dis[s] = 0; mnf[s] = INT_MAX;
		queue<int> qq;
		qq.push(s);
		while(qq.size()) {
			auto id = qq.front(); qq.pop();
			for(auto &i : f[id]) {
				auto [d, F, C] = edges[i];
				if(F > 0 && (dis[d] == -1 || dis[d] > dis[id] + C)) {
					dis[d] = dis[id] + C;
					mnf[d] = min(mnf[id], F);
					pa[d] = i;
					qq.push(d);
				}
			}
		}
		if(dis[t] == -1) return 0;
		return mnf[t];
	};
	pair<int, int> solve() {
		int Flow = 0, Cost = 0;
		while(true) {
			fill(dis.begin(), dis.end(), -1);
			int flow = spfa();
			if(flow <= 0) break;
			Flow += flow;
			int now = t;
			while(now != s) {
				{
					auto &[d, F, C] = edges[pa[now]];
					Cost += flow * C;
					F -= flow;
				}
				{
					auto &[d, F, C] = edges[pa[now]^1];
					F += flow;
					now = d;
				}
			}
		}
		return {Flow, Cost};
	}
};