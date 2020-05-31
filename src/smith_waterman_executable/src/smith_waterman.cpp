#include "smith_waterman.h"
#include <smith_waterman_utils/matrix.h>
#include <utility>
#include <array>
#include <vector>
#include <algorithm>

namespace sw
{
SmithWatermanAlgorithm::SmithWatermanAlgorithm(std::string a, std::string b, const double penalty, ScoreFunc scoreFunc)
    : m_a(std::move(a)), m_b(std::move(b)), m_penalty(penalty), m_scoreFunc(std::move(scoreFunc))
{}

std::pair<std::string, std::string> SmithWatermanAlgorithm::compute()
{
    const auto sizeOfA = m_a.size();
    const auto sizeOfB = m_b.size();

    Matrix<double> matrix(sizeOfA + 1, sizeOfB + 1);

    fill(matrix, .0);

    Matrix<size_t> i_i(sizeOfA + 1, sizeOfB + 1);
    Matrix<size_t> i_j(sizeOfA + 1, sizeOfB + 1);

    const auto findMax = [](const std::array<double, 4>& traceBack) -> std::pair<double, size_t> {
        const auto it = std::max_element(traceBack.begin(), traceBack.end());
        return {*it, std::distance(traceBack.begin(), it)};
    };

    for (auto i = 1u; i <= sizeOfA; ++i)
    {
        for (auto j = 1u; j <= sizeOfB; ++j)
        {
            std::array<double, 4> traceBack{};

            traceBack[0] = matrix(i - 1, j - 1) + m_scoreFunc(m_a[i - 1], m_b[j - 1]);
            traceBack[1] = matrix(i - 1, j) + m_penalty;
            traceBack[2] = matrix(i, j - 1) + m_penalty;
            traceBack[3] = 0.;

            auto&& [max, index] = findMax(traceBack);

            matrix(i, j) = max;

            switch (index)
            {
            case 0:
                i_i(i, j) = i - 1;
                i_j(i, j) = j - 1;
                break;
            case 1:
                i_i(i, j) = i - 1;
                i_j(i, j) = j;
                break;
            case 2:
                i_i(i, j) = i;
                i_j(i, j) = j - 1;
                break;
            case 3:
                i_i(i, j) = i;
                i_j(i, j) = j;
                break;
            }
        }
    }

    auto&& [maxValue, maxI, maxJ] = maxElement(matrix);

    auto v = matrix(maxI, maxJ);

    auto currentI = maxI;
    auto currentJ = maxJ;

    auto nextI = i_i(currentI, currentJ);
    auto nextJ = i_j(currentI, currentJ);

    auto tick = 0;
    const auto consensusSize = sizeOfA + sizeOfB + 2;

    std::vector<char> consensusA;
    std::vector<char> consensusB;

    consensusA.resize(consensusSize);
    consensusB.resize(consensusSize);

    while ((currentI != nextI || currentJ != nextJ) && nextJ != 0 && nextI != 0)
    {
        if (nextI == currentI)
            consensusA[tick] = '-';  // deletion in A
        else
            consensusA[tick] = m_a[currentI - 1];  // match/mismatch in A

        if (nextJ == currentJ)
            consensusB[tick] = '-';  // deletion in B
        else
            consensusB[tick] = m_b[currentJ - 1];  // match/mismatch in B

        currentI = nextI;
        currentJ = nextJ;
        nextI = i_i(currentI, currentJ);
        nextJ = i_j(currentI, currentJ);

        ++tick;
    }

    std::string resultA, resultB;

    for (auto i = tick - 1; i >= 0; --i)
        resultA += consensusA[i];

    for (auto i = tick - 1; i >= 0; --i)
        resultB += consensusB[i];

    return {resultA, resultB};
}
}  // namespace sw
