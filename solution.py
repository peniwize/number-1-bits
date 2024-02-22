# Start of "solution.py".

from collections import deque
import copy
import inspect
import time
from typing import List
from typing import Optional
from typing import Set

"""
    Write a function that takes the binary representation of an unsigned 
    integer and returns the number of '1' bits it has (also known as the 
    Hamming weight).

    Note:

        * Note that in some languages, such as Java, there is no unsigned 
          integer type. In this case, the input will be given as a signed 
          integer type. It should not affect your implementation, as the 
          integer's internal binary representation is the same, whether it 
          is signed or unsigned.
        
        * In Java, the compiler represents the signed integers using 2's 
          complement notation. Therefore, in Example 3, the input represents 
          the signed integer. -3.
"""

"""
    Time = O(8 * sizeof(n)) => O(sizeof(n)) => O(1)
           sizeof(n): number of octets composing 'n'.

    Space = O(1)

    Brute force solution.
    Test every single bit in the integer and count the number of one bits.
"""
class Solution1_BruteForce:
    def hammingWeight(self, n: int) -> int:
        result = 0
        for _ in range(32):
            if n & 1:
                result += 1
            n >>= 1
        return result

"""
    Time = O(8 * sizeof(n)) => O(sizeof(n)) => O(1)
           sizeof(n): number of octets composing 'n'.

    Space = O(1)

    Brian Kerneghan's solution.
    Any value bitwise anded with itself minus one will always flip the least
    significant one bit to zero.  The number of times this must be done to 
    clear all one bits is the number of one bits in 'n'.
"""
class Solution2_Kernighan:
    def hammingWeight(self, n: int) -> int:
        result = 0
        while n:
            n = n & (n - 1)
            result += 1
        return result

"""
    Time = O(8 * sizeof(n)) => O(sizeof(n)) => O(1)

    Space = O(1)

    Use a translation table to convert integers into bit counts.
    This solution keeps it simple by using a 256 entry table and 
    breaking n into byte sized chunks.

    Time = O(sizeof(n)) => O(1)
           sizeof(n): number of octets composing 'n'.

    Space = O(1)
            Table size never changes and it's immutable data so 
            it's not a factor.
"""
class Solution3_Table:
    __TO_BIT_COUNT = [
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
    ]
    def hammingWeight(self, n: int) -> int:
        # Unrolled loop since loop count would always be 4.
        return self.__TO_BIT_COUNT[(n >> 0) & 0xff] \
               + self.__TO_BIT_COUNT[(n >> 8) & 0xff] \
               + self.__TO_BIT_COUNT[(n >> 16) & 0xff] \
               + self.__TO_BIT_COUNT[(n >> 24) & 0xff]

"""
    Time = O(1)

    Space = O(1)

    Use the built in compiler/language intrinsic, which often boils down to
    a single machine instruction on popular hardware platforms.
"""
class Solution4_Intrinsic:
    def hammingWeight(self, n: int) -> int:
        return n.bit_count()

def test1(solution):
    n = 11
    expected = 3
    startTime = time.time()
    result = solution.hammingWeight(n)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test2(solution):
    n = 128
    expected = 1
    startTime = time.time()
    result = solution.hammingWeight(n)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test3(solution):
    n = 4294967293
    expected = 31
    startTime = time.time()
    result = solution.hammingWeight(n)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

if "__main__" == __name__:
    test1(Solution1_BruteForce())
    test1(Solution2_Kernighan())
    test1(Solution3_Table())
    test1(Solution4_Intrinsic())

    test2(Solution1_BruteForce())
    test2(Solution2_Kernighan())
    test2(Solution3_Table())
    test2(Solution4_Intrinsic())

    test3(Solution1_BruteForce())
    test3(Solution2_Kernighan())
    test3(Solution3_Table())
    test3(Solution4_Intrinsic())

# End of "solution.py".
