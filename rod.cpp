#include <bits/stdc++.h>
using namespace std;

int main() {
    // Rod lengths and their prices
    vector<int> lengths = {1, 2, 3, 6, 10};
    vector<int> prices  = {2, 5, 10, 13, 25};

    int n = 10; // rod length

    // DP arrays
    vector<int> dp(n + 1, 0);     // dp[i] = max revenue for length i
    vector<int> cut(n + 1, -1);   // cut[i] = first cut length chosen

    // Compute max revenue for each length
    for (int len = 1; len <= n; len++) {
        for (int j = 0; j < lengths.size(); j++) { // classic for loop
            int pLen = lengths[j];
            int pVal = prices[j];
            if (pLen <= len) {
                if (dp[len] < pVal + dp[len - pLen]) {
                    dp[len] = pVal + dp[len - pLen];
                    cut[len] = pLen;
                }
            }
        }
    }

    // Print maximum revenue
    cout << "Maximum Revenue = " << dp[n] << endl;

    // Backtrack to find cuts
    int length = n;
    vector<int> pieces;
    while (length > 0) {
        int c = cut[length];
        pieces.push_back(c);
        length -= c;
    }

    // Print cuts using normal for loop
    cout << "Pieces: ";
    for (int i = 0; i < pieces.size(); i++) {
        cout << pieces[i] << " ";
    }
    cout << endl;

    return 0;
}

