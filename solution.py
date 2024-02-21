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
    Time = O(?)

    Space = O(?)
"""
class Solution:
    def hammingWeight(self, n: int) -> int:
        #
        # TODO: >>> Under Construction <<<
        #
        return -1

def test1(solution):
    n = 11
    expected = 3
    startTime = time.time()
    result = solution.hammingWeight(n)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test1(solution):
    n = 128
    expected = 1
    startTime = time.time()
    result = solution.hammingWeight(n)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test1(solution):
    n = 4294967293
    expected = 31
    startTime = time.time()
    result = solution.hammingWeight(n)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

if "__main__" == __name__:
    test1(Solution())

# End of "solution.py".
