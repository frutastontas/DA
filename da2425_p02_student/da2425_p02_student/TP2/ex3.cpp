// By: Gonçalo Leão
// Updated by DA 24/25 Team

#include <vector>
#include <algorithm> // for sort
#include <iostream>


unsigned int knapsackBF(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    int mask[n] = {0};
    int maxSubsets = 1<<n;
    int maxValue=0;

    for (int mask =0; mask<maxSubsets; mask++) {
        int curweight = 0;
        int curvalue = 0;
        bool curSubsetUsed[n] = {0};
        for (int i=0; i<n; i++) {
            if (mask & (1<<i)) {
                curweight += weights[i];
                curvalue += values[i];
                curSubsetUsed[i]=1;
            }
        }

        if (curweight <= maxWeight && curvalue > maxValue) {
            maxValue = curvalue;
            for (int i = 0; i < n; i++) {
                usedItems[i]= curSubsetUsed[i];
            }
        }
    }
    return maxValue;
}

bool sortbyValue(std::pair<int,int> p1,std::pair<int,int> p2) {
    return p1.first > p2.first;
}

// does not guarantee the optimal solution in the current form
unsigned int knapsackGreedyValue(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    std::vector<std::pair<int,int>> valuesAndWeights(n);
    for (int i = 0; i < n; i++) {
        valuesAndWeights[i] = std::make_pair(values[i], weights[i]);
    }
    std::sort(valuesAndWeights.begin(), valuesAndWeights.end(), sortbyValue);
    int curvalue =0;
    int curWeight=0;
    for (std::pair<int,int> value_and_weight : valuesAndWeights) {
        if (curWeight+ value_and_weight.second <= maxWeight) {
            std::cout<<value_and_weight.first<<" "<<value_and_weight.second << " " << maxWeight<<std::endl;
            curvalue += value_and_weight.first;
            curWeight += value_and_weight.second;
            for (unsigned int i = 0; i < n; i++) {
                if (!usedItems[i] && values[i] == value_and_weight.first && weights[i] == value_and_weight.second) {
                    usedItems[i] = true;
                    break; // Ensure we don't mark duplicate values multiple times
                }
            }
        }
    }
    return curvalue;
}

bool sortbyWeight(std::pair<int,int> p1,std::pair<int,int> p2) {
    return p1.second > p2.second;
}

// does not guarantee the optimal solution in the current form
unsigned int knapsackGreedyWeight(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    std::vector<std::pair<int,int>> valuesAndWeights(n);
    for (int i = 0; i < n; i++) {
        valuesAndWeights[i] = std::make_pair(values[i], weights[i]);
    }
    std::sort(valuesAndWeights.begin(), valuesAndWeights.end(), sortbyWeight);

    int curvalue =0;
    int curWeight=0;
    for (std::pair<int,int> value_and_weight : valuesAndWeights) {
        if (curWeight+ value_and_weight.second <= maxWeight) {
            std::cout<<value_and_weight.first<<" "<<value_and_weight.second << " " << maxWeight<<std::endl;
            curvalue += value_and_weight.first;
            curWeight += value_and_weight.second;
            for (unsigned int i = 0; i < n; i++) {
                if (!usedItems[i] && values[i] == value_and_weight.first && weights[i] == value_and_weight.second) {
                    usedItems[i] = true;
                    break; // Ensure we don't mark duplicate values multiple times
                }
            }
        }
    }
    return curvalue;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex3, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
    }

    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

// this test is expected to fail
TEST(TP2_Ex3, testKnapsack_4items_greedy_fail) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 5};
        bool usedItems[n];

        EXPECT_EQ(knapsackGreedyValue(values, weights, n, 5, usedItems), 28);
        weights[0]=1;
        weights[1]=1;
        weights[3]=3;
        EXPECT_EQ(knapsackGreedyWeight(values, weights, n, 5, usedItems), 36);

    }
}


TEST(TP2_Ex3, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}


TEST(TP2_Ex3, testKnapsack_40items) {
    const unsigned int n = 20;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4, 1,  2, 3, 8, 4,12, 20,
                                  1, 4, 4 ,3, 3, 6, 6, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 4,3, 2, 1, 4, 6,10, 10, 3, 1, 6,2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 10, usedItems), 24);

    }
}