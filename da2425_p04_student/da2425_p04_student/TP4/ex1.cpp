#include "exercises.h"
#include "cmath"


int maxSubsequenceHelper(int A[], int left, int right,int &i, int &j) {
    if(left==right) {
        i=j=left;
        return A[i];
    }
    int mid = (left+right)/2;
    int lefti, leftj, righti, rightj;   //helper variables to store positions to not overwrite i and j
    int leftsum =maxSubsequenceHelper(A ,left, mid,lefti,leftj);
    int rightsum = maxSubsequenceHelper(A,mid+1 ,right,righti,rightj);

    int cursum = A[mid];
    int bestCrossingsum1 = A[mid];
    int iCrossing = mid;
    for (int k = mid-1; k >= left; k--) {
        cursum += A[k];
        if (bestCrossingsum1 < cursum) {
            bestCrossingsum1 = cursum;
            iCrossing = k;
        }
    }
    cursum = A[mid+1];
    int bestCrossingsum2 = A[mid+1];
    int jCrossing = mid+1;
    for (int k = mid+2; k <= right; k++) {
        cursum += A[k];
        if (bestCrossingsum2 < cursum) {
            bestCrossingsum2 = cursum;
            jCrossing = k;
        }
    }
    int crossingsum = bestCrossingsum1 + bestCrossingsum2;

    // Find the maximum among the three cases
    if (leftsum >= rightsum && leftsum >= crossingsum) {
        i = lefti;
        j = leftj;
        return leftsum;
    }
    else if (rightsum >= leftsum && rightsum >= crossingsum) {
        i = righti;
        j = rightj;
        return rightsum;
    }
    i = iCrossing;
    j = jCrossing;
    return crossingsum;
}


int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j) {
    return maxSubsequenceHelper(A, 0,n-1,i, j);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex1, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    int i, j;
    EXPECT_EQ(maxSubsequenceDC(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDC(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDC(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDC(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}