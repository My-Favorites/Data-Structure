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

std::deque<Number> pendingNumbers; // bigger numbers will have lower indexes
std::deque<Number> rejectedNumbers; // bigger numbers will have lower indexes
std::deque<Number> inputSequence;

int positionIsTaken[1000];

/**
 * Tell whether all dependencies are met for given number
 *
 * @param {Number} number - Number
 * @returns {bool} if true, that number is ready to be inserted to inputNumbers
 */
bool isDependenciesMet (Number number)
{
    int hash = number.hash;
    int index = number.index;
    int i;
    if (index > hash) {
        for (i = hash; i < index; ++i) {
            if (positionIsTaken[i] == 0) {
                return false;
            }
        }
    } else if (index < hash) {
        for (i = hash; i % N != index; ++i) {
            if (positionIsTaken[i % N] == 0) {
                return false;
            }
        }
    }

    return true;
}


bool compareNumber (Number i, Number j)
{
    return i.value > j.value;
}

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

    scanf("%d", &N);

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

    std::sort(pendingNumbers.begin(), pendingNumbers.end(), compareNumber);

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
                for (int i = sizeBefore - 1; i > -1; --i) {
                    num = rejectedNumbers[i];

                    if (isDependenciesMet(num)) {
                        inputSequence.push_back(num);
                        positionIsTaken[num.index] = 1; // mark as taken
                        rejectedNumbers.erase(rejectedNumbers.begin() + i);
                    }
                }
                std::deque<Number>::size_type sizeAfter = rejectedNumbers.size();
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
