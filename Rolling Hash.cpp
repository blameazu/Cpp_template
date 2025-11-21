// Is it correct? 
// TODO

struct Hasher {
	const unsigned ll mod = 1e9+9, p1 = 87, p2 = 137;
	vector<unsigned ll> pp1, pp2, h1, h2;
	Hasher(const string &s) : pp1(1, 1), pp2(1, 1), h1(1, 0), h2(1, 0) {
		while(pp1.size() <= s.size())
			pp1.push_back(pp1.back()*p1%mod),
			pp2.push_back(pp2.back()*p2);
		for(int i = 1; i <= s.size(); i++)
			h1.push_back((h1.back()*p1 + s[i-1])%mod),
			h2.push_back(h2.back()*p2 + s[i-1]);
	}
	pair<unsigned ll, unsigned ll> get(int l, int r) {
		return {(h1[r+1] - h1[l] * pp1[r-l+1]%mod + mod)%mod,
				h2[r+1] - h2[l] * pp2[r-l+1]};
	}
};