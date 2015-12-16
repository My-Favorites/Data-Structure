#include <stdio.h>

/**
 * @file Project3 Hashing - Hard Version
 * @author Zeno Zeng
 * @see http://pta.patest.cn/pta/test/70/exam/4/question/1672
 *
 * Reconstruct the input sequence
 * from the given status of the hash table.
 * Whenever there are multiple choices,
 * the smallest number is always taken
 *
 * Hash Function: H(x) = x % N
 * Linear probing is used to solve collisions
 */

int main()
{
    // Size of hash table, N ∈ (0, 1000]
    int N;

    // Current status of hash table
    // A negative integer represents an empty cell in the hash table
    int hashTableStatus[1000];

    // Count of valid numbers in current hash table
    int numberCount = 0;

    scanf("%d", &N);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &hashTableStatus[i]);
        if (hashTableStatus[i] >= 0) {
            numberCount++;
        }
    }

    return 0;
}
