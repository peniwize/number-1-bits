/*!
    \file "main.cpp"

    Author: Matt Ervin <matt@impsoftware.org>
    Formatting: 4 spaces/tab (spaces only; no tabs), 120 columns.
    Doc-tool: Doxygen (http://www.doxygen.com/)

    https://leetcode.com/problems/number-of-1-bits/
    https://github.com/peniwize/number-1-bits.git
*/

//!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "utils.hpp"

/*
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
*/

/*
    Time = O(8 * sizeof(n)) => O(sizeof(n)) => O(1)
           sizeof(n): number of octets composing 'n'.

    Space = O(1)

    Brute force solution.
    Test every single bit in the integer and count the number of one bits.
*/
class Solution1_BruteForce {
public:
    int hammingWeight(uint32_t n) {
        int result = 0;

        for (auto i = sizeof(n) * 8; 0 < i; --i) {
            if (1 == (n & 1)) {
                ++result;
            }
            n >>= 1;
        }

        return result;
    }
};

/*
    Time = O(8 * sizeof(n)) => O(sizeof(n)) => O(1)
           sizeof(n): number of octets composing 'n'.

    Space = O(1)

    Brian Kerneghan's solution.
    Any value bitwise anded with itself minus one will always flip the least
    significant one bit to zero.  The number of times this must be done to 
    clear all one bits is the number of one bits in 'n'.
*/
class Solution2_Kernighan {
public:
    int hammingWeight(uint32_t n) {
        int result;

        for (result = 0; n; ++result) {
            n = n & (n - 1);
        }
        
        return result;
    }
};

/*
    Time = O(8 * sizeof(n)) => O(sizeof(n)) => O(1)

    Space = O(1)

    Use a translation table to convert integers into bit counts.
    This solution keeps it simple by using a 256 entry table and 
    breaking n into byte sized chunks.

    Time = O(sizeof(n)) => O(1)
           sizeof(n): number of octets composing 'n'.

    Space = O(1)
            Table size never changes and it's immutable data stored in the 
            initialized data section so it's size is irrelevant.
*/
class Solution3_Table {
public:
    static constexpr int const toBitCount_[256] = {
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
    };
    int hammingWeight(uint32_t n) {
        int result;

        for (auto i = sizeof(n); i; --i) {
            result += toBitCount_[n & 0xff];
            n >>= 8;
        }
        
        return result;
    }
};

/*
    Time = O(1)

    Space = O(1)

    Use the built in compiler/language intrinsic, which often boils down to
    a single machine instruction on popular hardware platforms.
*/
class Solution4_Intrinsic {
public:
    int hammingWeight(uint32_t n) {
        return popcount(n);
    }
};

// {----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------}

namespace doctest {
    const char* testName() noexcept { return doctest::detail::g_cs->currentTest->m_name; }
} // namespace doctest {

TEST_CASE("Case 1")
{
    cerr << doctest::testName() << '\n';
    int n = 11u;
    int expected = 3;
    auto solution = Solution1_BruteForce{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.hammingWeight(n);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 2")
{
    cerr << doctest::testName() << '\n';
    int n = 128u;
    int expected = 1;
    auto solution = Solution1_BruteForce{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.hammingWeight(n);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 3")
{
    cerr << doctest::testName() << '\n';
    int n = 4294967293u;
    int expected = 31;
    auto solution = Solution1_BruteForce{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.hammingWeight(n);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 10")
{
    cerr << doctest::testName() << '\n';
    int n = 11u;
    int expected = 3;
    auto solution = Solution2_Kernighan{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.hammingWeight(n);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 20")
{
    cerr << doctest::testName() << '\n';
    int n = 128u;
    int expected = 1;
    auto solution = Solution2_Kernighan{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.hammingWeight(n);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 30")
{
    cerr << doctest::testName() << '\n';
    int n = 4294967293u;
    int expected = 31;
    auto solution = Solution2_Kernighan{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.hammingWeight(n);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 100")
{
    cerr << doctest::testName() << '\n';
    int n = 11u;
    int expected = 3;
    auto solution = Solution3_Table{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.hammingWeight(n);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 200")
{
    cerr << doctest::testName() << '\n';
    int n = 128u;
    int expected = 1;
    auto solution = Solution3_Table{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.hammingWeight(n);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 300")
{
    cerr << doctest::testName() << '\n';
    int n = 4294967293u;
    int expected = 31;
    auto solution = Solution3_Table{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.hammingWeight(n);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 1000")
{
    cerr << doctest::testName() << '\n';
    int n = 11u;
    int expected = 3;
    auto solution = Solution4_Intrinsic{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.hammingWeight(n);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 2000")
{
    cerr << doctest::testName() << '\n';
    int n = 128u;
    int expected = 1;
    auto solution = Solution4_Intrinsic{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.hammingWeight(n);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 3000")
{
    cerr << doctest::testName() << '\n';
    int n = 4294967293u;
    int expected = 31;
    auto solution = Solution4_Intrinsic{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.hammingWeight(n);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

/*
    End of "main.cpp"
*/
