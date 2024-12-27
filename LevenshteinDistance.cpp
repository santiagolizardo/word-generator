#include "LevenshteinDistance.hpp"

#include <algorithm>
#include <vector>

int LevenshteinDistance::compute(const string &s, const string &t)
{
    int n = s.length();
    int m = t.length();

    if (n == 0)
    {
        return m;
    }

    if (m == 0)
    {
        return n;
    }

    // Step 2: Create a 2D vector (n+1) x (m+1)
    std::vector<std::vector<int>> d(n + 1, std::vector<int>(m + 1));

    // Step 3: Initialize the base cases
    for (int i = 0; i <= n; ++i) {
        d[i][0] = i;
    }
    for (int j = 0; j <= m; ++j) {
        d[0][j] = j;
    }

    // Step 4: Compute the Levenshtein distance
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            // Step 5: Calculate the cost
            int cost = (t[j - 1] == s[i - 1]) ? 0 : 1;

            // Step 6: Take the minimum of the three possible operations
            d[i][j] = std::min(
                std::min(d[i - 1][j] + 1, d[i][j - 1] + 1),
                d[i - 1][j - 1] + cost
            );
        }
    }

    // Step 7: Return the final result
    return d[n][m];
}
