#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int MAXN = 2e5 + 5;
int dp[MAXN];
vector<int> tallers;
vector<pair<int,int>> mounts;
set<int, greater<int>> sl;
set<int, greater<int>> sr;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int num;
    cin >> num;

    for(int i = 1, u; i <= num; ++i) {
        cin >> u;
        mounts.push_back({u, i});
    }

    sort(mounts.begin(), mounts.end(), greater<pair<int,int>>());

    int last_height = -1;
    for(auto m : mounts) {
        int h = m.first;
        int i = m.second;

        if(last_height != h) {
            for(int t : tallers) {
                sl.insert(t);
                sr.insert(t);
            }
            tallers.clear();
        }

        auto l_ptr = sl.lower_bound(i);
        auto r_ptr = sr.lower_bound(i);

        int l = (l_ptr == sl.end() ? 0 : *l_ptr);
        int r = (r_ptr == sr.end() ? 0 : *r_ptr);

        dp[i] = max(dp[l], dp[r]) + 1;

        tallers.push_back(i);
        last_height = h;
    }

    int best = 0;
    for(int i = 1; i <= num; ++i)
        best = max(best, dp[i]);

    cout << best << '\n';
}
