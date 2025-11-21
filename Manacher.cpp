// Is it correct? 
// TODO

int manacher(const string &_) {
	string s = "#";
	for(int i = 0; i < _.size(); i++)
		s += _[i], s += '#';
	const int n = s.size();
	vector<int> Z(n);
	Z[0] = 1;
	int re = 0;
	for(int i = 1, j = 0; i < n; i++) {
		if(j+Z[j]>i) Z[i] = min(j+Z[j]-i, Z[j-(i-j)]);
		while(i+Z[i]<n && i-Z[i]>=0 && s[i+Z[i]]==s[i-Z[i]])
			j = i, Z[i]++;
		re = max(re, Z[i]-1);
	}
	return re;
}