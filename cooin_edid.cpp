#include <bits/stdc++.h>
using namespace std;

struct Coin
{
    int value;  // coin value
    int count;  // maximum number of coins of this type
};

int limitedCoinChange(vector<Coin>& coins, int N, int target, vector<pair<int,int>>& chosen)
{
    // dp[i][t] = minimum coins to make amount t using first i coins
    vector<vector<int>> dp(N + 1, vector<int>(target + 1, INT_MAX - 1));

    // Base case: 0 coins needed to make 0
    for (int i = 0; i <= N; i++)
        dp[i][0] = 0;

    // Fill DP table
    for (int i = 1; i <= N; i++)
    {
        for (int t = 1; t <= target; t++)
        {
            if (coins[i - 1].value > t)
            {
                // Can't take this coin → copy previous
                dp[i][t] = dp[i - 1][t];
            }
            else
            {
                // Start with not taking this coin
                dp[i][t] = dp[i - 1][t];

                // Try taking 1 to count coins
                for (int k = 1; k <= coins[i-1].count; k++)
                {
                    if (k * coins[i-1].value > t)
                        break; // cannot take more coins than target

                    int prev = dp[i-1][t - k*coins[i-1].value];
                    if (prev != INT_MAX - 1)
                    {
                        int take = prev + k;
                        if (take < dp[i][t])
                            dp[i][t] = take;
                    }
                }
            }
        }
    }

    // Backtrack to find which coins were used
    int t = target;
    for (int i = N; i > 0; i--)
    {
        for (int k = coins[i-1].count; k > 0; k--)
        {
            if (t >= k * coins[i-1].value &&
                dp[i][t] == dp[i-1][t - k*coins[i-1].value] + k)
            {
                chosen.push_back({i-1, k}); // coin index and how many used
                t -= k * coins[i-1].value;
                break;
            }
        }
    }

    // Return result
    if (dp[N][target] == INT_MAX - 1)
        return -1;
    else
        return dp[N][target];
}

int main()
{
    int N, target;
    cout << "Enter number of coins: ";
    cin >> N;
    cout << "Enter target amount: ";
    cin >> target;

    vector<Coin> coins(N);
    cout << "Enter coin values:\n";
    for (int i = 0; i < N; i++) cin >> coins[i].value;
    cout << "Enter coin counts:\n";
    for (int i = 0; i < N; i++) cin >> coins[i].count;

    vector<pair<int,int>> chosen;
    int minCoins = limitedCoinChange(coins, N, target, chosen);

    if (minCoins == -1)
        cout << "\nNo solution possible\n";
    else
    {
        cout << "\nMinimum coins needed = " << minCoins << endl;
        cout << "Coins used:\n";
        for (int i = chosen.size() - 1; i >= 0; i--)
        {
            int idx = chosen[i].first;
            int cnt = chosen[i].second;
            cout << cnt << " coin(s) of value " << coins[idx].value << "\n";
        }
    }

    return 0;
}
