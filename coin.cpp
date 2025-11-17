#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> coins = {1, 2, 6};
    int M = 11;

    vector<int> dp(M + 1, INT_MAX);
    vector<int> parent(M + 1, -1);
    dp[0] = 0;


    for (int i = 1; i <= M; i++)
    {
        for (int j = 0; j < coins.size(); j++)
        {
            int c = coins[j];
            if (i - c >= 0 && dp[i - c] != INT_MAX)
            {
                if (dp[i] > dp[i - c] + 1)
                {
                    dp[i] = dp[i - c] + 1;
                    parent[i] = c;
                }
            }
        }
    }


    if (dp[M] == INT_MAX)
    {
        cout << "No solution possible\n";
    }
    else
    {
        cout << "Minimum coins needed = " << dp[M] << endl;
        cout << "Coins used: ";

        int amount = M;
        vector<int> result;
        while (amount > 0)
        {
            int coin = parent[amount];
            result.push_back(coin);
            amount -= coin;
        }


        for (int i = 0; i < result.size(); i++)
        {
            cout << result[i] << " ";
        }
        cout << endl;
    }



    return 0;
}

