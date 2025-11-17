
#include <bits/stdc++.h>

using namespace std;

struct Item
{
    int weight;
    int profit;
};


int knapsack(vector<Item>& items, int N, int W, vector<int>& chosen)
{
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));


    for (int i = 1; i <= N; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (items[i - 1].weight <= w)
                dp[i][w] = max(dp[i - 1][w], items[i - 1].profit + dp[i - 1][w - items[i - 1].weight]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }


    int w = W;
    for (int i = N; i > 0; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            chosen.push_back(i - 1);
            w -= items[i - 1].weight;
        }
    }

    return dp[N][W];
}

int main()
{
    int N, W;
    cout << "Enter number of items: ";
    cin >> N;
    cout << "Enter knapsack capacity: ";
    cin >> W;

    vector<Item> items(N);
    cout << "Enter weights of items:\n";
    for (int i = 0; i < N; i++) cin >> items[i].weight;
    cout << "Enter profits of items:\n";
    for (int i = 0; i < N; i++) cin >> items[i].profit;

    vector<int> chosen;
    int maxProfit = knapsack(items, N, W, chosen);

    cout << "\nMaximum Profit = " << maxProfit << endl;
    cout << "Items taken:\n";
    for (int i = chosen.size() - 1; i >= 0; i--)
    {
        int idx = chosen[i];
        cout << "Item " << idx
             << " (Weight=" << items[idx].weight
             << ", Profit=" << items[idx].profit << ")\n";
    }

    return 0;
}

