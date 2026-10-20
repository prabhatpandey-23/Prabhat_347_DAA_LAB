#include <stdio.h>

int main()
{
    int N, W;

    scanf("%d", &N);

    int value[N];
    int weight[N];

    // Read values
    for (int i = 0; i < N; i++)
        scanf("%d", &value[i]);

    // Read weights
    for (int i = 0; i < N; i++)
        scanf("%d", &weight[i]);

    // Read knapsack capacity
    scanf("%d", &W);

    // dp[j] = maximum value possible with capacity j
    int dp[W + 1];

    for (int j = 0; j <= W; j++)
        dp[j] = 0;

    // Process each item
    for (int i = 0; i < N; i++)
    {
        // Traverse backwards to ensure each item is used only once
        for (int j = W; j >= weight[i]; j--)
        {
            if (dp[j - weight[i]] + value[i] > dp[j])
            {
                dp[j] = dp[j - weight[i]] + value[i];
            }
        }
    }

    printf("%d\n", dp[W]);

    return 0;
}
