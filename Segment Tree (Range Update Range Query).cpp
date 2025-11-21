// 還沒測過正確性 TODO

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
			Point update
				seg.upd(qid, qx, 1); // A_{qid} = qx
				seg.upd(qid, qx, 2); // A_{qid} += qx
            Range update
                seg.upd(ql, qr, qx, 1); // A_[ql...qr] = qx;
                seg.upd(ql, qr, qx, 2); // A_[ql...qr] += qx;
			Range query
				int ans = seg.qry(ql, qr); // return [ql, qr]'s ans
	*/
    int mode = 1;
	vector<int> tr, tag, tag2;
    int bsc = INT_MIN;
    int n;
	Seg(int n, int MODE = -1) : n(n) {
        if(MODE != -1) mode = MODE;
        if(mode == 1) bsc = INT_MIN;
		if(mode == 2) bsc = INT_MAX;
		if(mode == 3) bsc = 0;
        tr.resize((n<<2)+87, bsc);
        tag.resize((n<<2)+87, 0);
        tag2.resize((n<<2)+87, 0);
    }
	void pull(int& a, int b, int c) {
		if(mode == 1) a = max(b, c);
		if(mode == 2) a = min(b, c);
		if(mode == 3) a = b + c;
	}
	void build(const vector<int> &v, int l, int r, int id = 1) {
		if(l == r) return tr[id] = v[l], void();
		int mid = l+r>>1;
		build(v, l, mid, id<<1), build(v, mid+1, r, id<<1|1);
		pull(tr[id], tr[id<<1], tr[id<<1|1]);
	}
    void build(const vector<int> &v) {build(v, 1, n);}
	void addtag(int id, int x, int l, int r, int op) {
        if(op == 1) {
            if(mode == 3) tr[id] = x*(r-l+1);
            if(mode == 1 || mode == 2) tr[id] = x;
            tag[id] = x;
        }
		if(op == 2) {
            if(mode == 3) tr[id] += x*(r-l+1);
            if(mode == 1 || mode == 2) tr[id] += x;
            tag2[id] += x;
        }
	}
	void push(int id, int l, int r) {
		int mid = (l+r)>>1;
		if(tag[id]) {
			addtag(id<<1, tag[id], l, mid, 1);
			addtag(id<<1|1, tag[id], mid+1, r, 1);
			tag[id] = 0;
		}
        if(tag2[id]) {
			addtag(id<<1, tag2[id], l, mid, 2);
			addtag(id<<1|1, tag2[id], mid+1, r, 2);
			tag2[id] = 0;
		}
	}
	void upd(int ql, int qr, int qx, int l, int r, int op, int id = 1) {
		if(ql <= l && r <= qr) {
			addtag(id, qx, l, r, op);
			return;
		}
		push(id, l, r);
		int mid = (l+r)>>1;
		if(ql <= mid) upd(ql, qr, qx, l, mid, id<<1);
		if(qr > mid) upd(ql, qr, qx, mid+1, r, id<<1|1);
		pull(tr[id], tr[id<<1], tr[id<<1|1]);
	}
	void upd(int qid, int qx, int op) {upd(qid, qid, qx, 1, n, op);}
	void upd(int ql, int qr, int qx, int op) {upd(ql, qr, qx, 1, n, op);}
	int qry(int ql, int qr, int l, int r, int id = 1) {
		if(ql <= l && r <= qr) return tr[id];
		int mid = (l+r)>>1;
		push(id, l, r);
		int re = bsc;
		if(ql <= mid) pull(re, re, qry(ql, qr, l, mid, id<<1));
		if(qr > mid) pull(re, re, qry(ql, qr, mid+1, r, id<<1|1));
		return re;
	}
	int qry(int ql, int qr) {return qry(ql, qr, 1, n);}
};