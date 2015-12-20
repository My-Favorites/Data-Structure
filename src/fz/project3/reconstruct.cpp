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

#include <algorithm>
#include <deque>
#include <iostream>
#include <cstdio>

// Size of hash table, N ∈ (0, 1000]
int N;

struct Number
{
    int value; // value of this number
    int index; // index of this number in given status of hash table
    int hash; // hash of this number
};

std::deque<Number> pendingNumbers; // pending numbers to be tested, bigger numbers will have lower indexes
std::deque<Number> rejectedNumbers; // numbers that were rejected before, bigger numbers will have lower indexes
std::deque<Number> inputSequence; // original input sequence
int positionIsTaken[1000]; // whether target position is being taken, 1 => taken, 0 => empty

/**
 * Tell whether all dependencies are met for given number to be pushed to inputSequence
 *
 * @param {Number} number - Number
 * @returns {bool} if true, that number is ready to be pushed to inputSequence
 */
bool isDependenciesMet (Number number)
{
    int hash = number.hash;
    int index = number.index;
    int i;

    if (index > hash) {
        // If index is greater than hash,
        // then the number must be inserted after all numbers of [hash, index) ready.
        // Otherwise, we reject.
        for (i = hash; i < index; ++i) {
            if (positionIsTaken[i] == 0) {
                return false;
            }
        }
    } else if (index < hash) {
        // If index is lower than hash,
        // then the number must be inserted after all numbers of [hash, N) and [0, index) ready.
        // Otherwise, we reject.
        for (i = hash; i % N != index; ++i) {
            if (positionIsTaken[i % N] == 0) {
                return false;
            }
        }
    }

    return true;
}


/**
 * Compare 2 Numbers based on number.value,
 * bigger numbers will have lower indexes
 */
bool compareNumber (Number i, Number j)
{
    return i.value > j.value;
}

/**
 * Print Number Deque (joined by space)
 */
void printNumberDeque (std::deque<Number> numbers) {
    for (int i = 0; i != numbers.size(); i++) {
        if (i > 0) {
            std::cout << " ";
        }
        std::cout << numbers[i].value;
    }
    std::cout << std::endl;
}

int main()
{

    // Read N
    scanf("%d", &N);

    // Init pending numbers
    int val;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &val);
        if (val >= 0) {
            Number num;
            num.value = val;
            num.hash = val % N;
            num.index = i;
            pendingNumbers.push_back(num);
        }
    }

    // Sort pending numbers
    std::sort(pendingNumbers.begin(), pendingNumbers.end(), compareNumber);

    // How it works:
    //
    // At first we have all valid numbers in pendingNumbers and rejectedNumbers is empty.
    // Then we while pendingNumbers is not empty
    //     we check if all dependencies of current smallest number in pendingNumbers met.
    //     If so, we push it to inputSequence.
    //         And for each number in rejectedNumbers, we check it.
    //         And recheck it until rejectedNumbers's size no longer changes.
    //     If not, we push it to rejectNumbers;
    int j = 0;
    while (pendingNumbers.size() > 0) {
        j++;
        Number num = pendingNumbers.back();
        pendingNumbers.pop_back();
        if (isDependenciesMet(num)) {
            inputSequence.push_back(num);
            positionIsTaken[num.index] = 1; // mark as taken
            // dependencies has changed for rejected numbers, recheck
            while (true) {

                std::deque<Number>::size_type sizeBefore = rejectedNumbers.size();

                // check all rejectedNumbers
                for (int i = sizeBefore - 1; i > -1; --i) {
                    num = rejectedNumbers[i];

                    if (isDependenciesMet(num)) {
                        inputSequence.push_back(num);
                        positionIsTaken[num.index] = 1; // mark as taken
                        rejectedNumbers.erase(rejectedNumbers.begin() + i);
                    }
                }
                std::deque<Number>::size_type sizeAfter = rejectedNumbers.size();

                // size not changed, no need to do another round of recheck
                if (sizeAfter == sizeBefore) {
                    break;
                }
            }
        } else {
            rejectedNumbers.push_front(num);
        }
    }

    printNumberDeque(inputSequence);

    return 0;
}
