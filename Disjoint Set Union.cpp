struct DSU{
    /*
        <<1-based>>
		Usage:
			Init
				DSU dsu(n);
            Update
                dsu.upd(a, b); // link a and b (if a & b isn't connected)
            Same
                bool ans = dsu.same(a, b); // True: a & b is connected
            Components numbers
                int re = dsu.com;
            Get x's Component's size
                int re = dsu.get_sz(x);
    */
	int com;
	vector<int> p;
	DSU(int n) : com(n), p(n+1, -1) {}
	int fp(int id) {return p[id] < 0 ? id : p[id] = fp(p[id]);}
	bool same(int a, int b) {return fp(a) == fp(b);}
    int get_sz(int id) {return -p[fp(id)];}
	void upd(int a, int b) {
		int ar = fp(a), br = fp(b);
		if(ar != br) {
			if(p[ar] > p[br]) swap(ar, br);
			p[ar] += p[br];
			p[br] = ar;
			com--;
		}
	}
};