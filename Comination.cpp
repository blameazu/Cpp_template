// Is it correct? 
// TODO

struct Combination {
    /*
        <<Need Define int long long>>
        Usage:
            Init:
                Combination CC(K, mod);
                // K is value bond
            C^n_m:
                int re = CC.C(n, m);
    */
    int N;
    vector<int> stair, inv;
    int mod;
    Combination(int N, int MOD) : N(N), mod(MOD) {
        stair.resize(N+1);
        inv.resize(N+1);
        solve();
    }
    int fpw(int a, int b) {
        int re = 1;
        while(b) {
            if(b&1) re = re*a%mod;
            a = a*a%mod;
            b >>= 1;
        }
        return re;
    }
    void solve() {
        stair[0] = stair[1] = 1;
        inv[1] = inv[0] = 1;
        for(int i = 2; i <= N; i++)
            stair[i] = 1ll*stair[i-1]*i%mod;
        inv[N] = fpw(stair[N], mod-2);
        for(int i = N-1; i >= 2; i--)
            inv[i] = 1ll*inv[i+1]*(i+1)%mod;
    }
    int C(int n, int m) {
        if(m > n) return 0;
        int re = 1ll*stair[n]*inv[n-m]%mod*inv[m]%mod;
        return re;
    }
};
