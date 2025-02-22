// By: Gonçalo Leão
// Updated by DA 24/25 Team
#include <iostream>
#include <vector>
#include <climits>
#include <cstring>

/*bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    unsigned int allSubsets = 1<<n; //mesma coisa que fazer 2^n
    unsigned int coinUsed = 1000000000;
    bool flag = false;
    for (unsigned int mask = 0; mask < allSubsets; mask++) {
        int sum = 0;
        int coincount =0;
        unsigned int used[n] = {0};
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) { // se aquele membro estiver selecionado
               for (int j =1 ; j<= Stock[i] && sum + j*C[i] <= T; j++) {
                   sum += C[i];
                   coincount++;
                   used[i]++;
                   if (sum == T) break;
               }
            }
        }
        if (sum == T && coincount < coinUsed) {
            flag = true;
            coinUsed = coincount;
            for (int i = 0; i < n; i++) {
                usedCoins[i] = used[i];
            }
        }
    }
    if (flag == true) {return true;}
    return false;
}*/

bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    unsigned int minCoins = UINT_MAX;
    bool foundSolution = false;

    unsigned int maxMask = 1 << n; // 2^n subsets

    for (unsigned int mask = 0; mask < maxMask; mask++) {
        int sum = 0;
        int coinCount = 0;
        unsigned int used[n];
        memset(used, 0, sizeof(used));

        // Try all possible numbers of each coin
        for (int i = n-1; i >=0; i--) {
            if (mask & (1 << i)) { // If this coin is selected
                for (int j = 1; j <= Stock[i]; j++) {
                    if (sum +  C[i] > T) break;
                    sum += C[i];
                    used[i]++;
                    coinCount++;
                    if (sum == T) break;
                }
            }
        }

        if (sum == T && coinCount < minCoins) { // Valid solution found
            foundSolution = true;
            minCoins = coinCount;
            memcpy(usedCoins, used, sizeof(unsigned int) * n);
        }
    }

    return foundSolution;
}

bool changeMakingGR(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    memset(usedCoins, 0, sizeof(usedCoins));
    int sum =0;
    for (int i = n-1; i >= 0; i--) {
        int maxusable = std::min(Stock[i],T/C[i]);
        T-= C[i]*maxusable;
        usedCoins[i]=maxusable;
    }
    if (T==0) return true;
    return false;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex5, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP2_Ex5, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBF(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP2_Ex5, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBF(C,Stock,n,1,usedCoins), false);
}


TEST(TP2_Ex5, hasGreedyChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingGR(C, Stock, n, 13, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingGR(C, Stock2, n, 38, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);
}

TEST(TP2_Ex5, hasNoGreedyChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingGR(C, Stock, n, 18, usedCoins), false);
    EXPECT_EQ(changeMakingGR(C, Stock, n, 1, usedCoins), false);
}