struct Seg {
	/*
		<<Need Define int long long>>
		<<1-based>>
		Declaration:
			mode: 1 -> MAX
			mode: 2 -> MIN
			mode: 3 -> SUM
		Usage:
			Init
				Seg seg(len, mode);
			Build
				seg.build(v); // use vector<int> v(n+1) (1-based) to init a tree
			Point update
				seg.upd(qid, qx, 1); // A_{qid} = qx
				seg.upd(qid, qx, 2); // A_{qid} += qx
			Range query
				int ans = seg.qry(ql, qr); // return [ql, qr]'s ans
	*/
	int mode = 1;
	vector<int> tr;
	int bsc = INT_MIN;
	int n;
	Seg(int n, int MODE = -1) : n(n) {
		if(MODE != -1) mode = MODE;
		if(mode == 1) bsc = INT_MIN;
		if(mode == 2) bsc = INT_MAX;
		if(mode == 3) bsc = 0;
		tr.resize((n<<2)+87, bsc);
	}
	void pull(int& a, int b, int c) {
		if(mode == 1) a = max(b, c);
		if(mode == 2) a = min(b, c);
		if(mode == 3) a = b + c;
	}
	void build(const vector<int> &v, int l, int r, int id = 1) {
		if(l == r) return tr[id] = v[l], void();
		int mid = (l+r)>>1;
		build(v, l, mid, id<<1);
		build(v, mid+1, r, id<<1|1);
		pull(tr[id], tr[id<<1], tr[id<<1|1]);
	}
	void build(const vector<int> &v) {build(v, 1, n);}
	void upd(int qid, int qx, int l, int r, int op, int id = 1) {
		if(l == r) return tr[id] = (op == 1 ? qx : tr[id]+qx), void();
		int mid = (l+r)>>1;
		if(qid <= mid) upd(qid, qx, l, mid, op, id<<1);
		else upd(qid, qx, mid+1, r, op, id<<1|1);
		pull(tr[id], tr[id<<1], tr[id<<1|1]);
	}
	void upd(int qid, int qx, int op = 1) {upd(qid, qx, 1, n, op);}
	int qry(int ql, int qr, int l, int r, int id = 1) {
		if(ql <= l && r <= qr) return tr[id];
		int mid = (l+r)>>1;
		int re = bsc;
		if(ql <= mid) pull(re, re, qry(ql, qr, l, mid, id<<1));
		if(qr > mid) pull(re, re, qry(ql, qr, mid+1, r, id<<1|1));
		return re;
	}
	int qry(int ql, int qr) {return qry(ql, qr, 1, n);}
};