// By: Gonçalo Leão
// Updated by DA 24/25 Team
/*bool subsetsumBFhelper(unsigned int A[], unsigned int n, unsigned int T, unsigned int subset[], unsigned int &subsetSize) {
    if (T==0) return true; //found subset
    if (n==0) return false; //no more elements to see

    bool notTake = subsetsumBFhelper(A, n-1, T, subset, subsetSize); //not taking last element
    if (notTake) return true;
    bool take = false;
    if (A[n-1] <= T) {
        subset[subsetSize++] = A[n-1]; //include in the subset
        take = subsetsumBFhelper(A, n-1, T-A[n-1], subset, subsetSize);
        if (take == true) {return true;}
        subsetSize--;
    }
    return false;
}

bool subsetSumBF(unsigned int A[], unsigned int n, unsigned int T, unsigned int subset[], unsigned int &subsetSize) {
    subsetSize = 0;
    return subsetsumBFhelper(A, n, T, subset, subsetSize);
}*/

bool subsetSumBF(unsigned int A[], unsigned int n, unsigned int T, unsigned int subset[], unsigned int &subsetSize) {
    subsetSize = 0;
    unsigned int m[n] = {0}; //máscara de bits
    unsigned int allSubsets = 1<<n; //mesma coisa que fazer 2^n

    for (unsigned int mask = 0; mask < allSubsets; mask++) {
        int sum = 0;
        subsetSize = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) { // se aquele membro estiver selecionado
                sum += A[i];
                subset[subsetSize++] = A[i];
            }
        }
        if (sum == T) {
            return true;
        }
    }
    return false;
}

/// TESTS ///
#include <gtest/gtest.h>

unsigned int sum(unsigned int A[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

// Checks if A is a subset of B
bool isSubset(unsigned int A[], unsigned int nA, unsigned int B[], unsigned int nB) {
    for(unsigned int i = 0; i < nA; i++) {
        bool foundNum = false;
        for(unsigned int j = 0; j < nB; j++) {
            if(A[i] == B[j]) {
                foundNum = true;
                break;
            }
        }
        if(!foundNum) return false;
    }
    return true;
}

TEST(TP2_Ex2, testSubsetSum) {
    unsigned int A[] = {3, 34, 4, 12, 5, 2};
    unsigned int subset[6];
    unsigned int subsetSize;

    unsigned int T = 9;
    EXPECT_EQ(subsetSumBF(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 20;
    EXPECT_EQ(subsetSumBF(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 30;
    EXPECT_EQ(subsetSumBF(A,6,T,subset,subsetSize), false);
}