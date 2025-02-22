// By: Gonçalo Leão
// Updated by DA 24/25 Team

#include <algorithm>
#include <vector>
#include <iostream>
bool sortbyRatio(std::pair<int,int> p1,std::pair<int,int> p2) {
    return (p1.first/p1.second) > (p2.first/p2.second);
}

double fractionalKnapsackGR(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, double usedItems[]) {
    std::vector<std::pair<int,int>> valuesAndWeights(n);
    for (int i = 0; i < n; i++) {
        valuesAndWeights[i] = std::make_pair(values[i], weights[i]);
    }
    std::sort(valuesAndWeights.begin(), valuesAndWeights.end(), sortbyRatio);

    double curvalue =0;
    int curWeight=0;
    for (std::pair<int,int> value_and_weight : valuesAndWeights) {
        if (curWeight+ value_and_weight.second <= maxWeight) {
            curvalue += value_and_weight.first;
            curWeight += value_and_weight.second;
            for (unsigned int i = 0; i < n; i++) {
                if (values[i] == value_and_weight.first && weights[i] == value_and_weight.second) {
                    usedItems[i] = 1;
                    break; // Ensure we don't mark duplicate values multiple times
                }
            }
        }else {
            double percentage = (maxWeight-curWeight)/(double)value_and_weight.second;
            curvalue += (double)value_and_weight.first*percentage;
            for (unsigned int i = 0; i < n; i++) {
                if (values[i] == value_and_weight.first && weights[i] == value_and_weight.second) {
                    usedItems[i] = percentage;
                    break; // Ensure we don't mark duplicate values multiple times
                }
            }
            break;
        }
    }
    return curvalue;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex4, testFractionalKnapsack_3items) {
    const unsigned int n = 3;
    {
        unsigned int values[n] = {60, 100, 120};
        unsigned int weights[n] = {10, 20, 30};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsackGR(values, weights, n, 50, usedItems), 240.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 2.0/3.0, 0.00001);
    }
}

TEST(TP2_Ex4, testFractionalKnapsack_7items) {
    const unsigned int n = 7;
    {
        unsigned int values[n] = {10, 5, 15, 7, 6, 18, 3};
        unsigned int weights[n] = {2, 3, 5, 7, 1, 4, 1};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsackGR(values, weights, n, 15, usedItems), 52.0 + 10.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 2.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[3], 0.0, 0.00001);
        EXPECT_NEAR(usedItems[4], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[5], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[6], 1.0, 0.00001);
    }
}