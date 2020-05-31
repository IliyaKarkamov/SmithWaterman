#ifndef SMITH_WATERMAN_EXECUTABLE_SMITH_WATERMAN_H
#define SMITH_WATERMAN_EXECUTABLE_SMITH_WATERMAN_H

#include <string>
#include <functional>

namespace sw
{
using ScoreFunc = std::function<double(char, char)>;

class SmithWatermanAlgorithm
{
public:
    explicit SmithWatermanAlgorithm(std::string a, std::string b, double penalty, ScoreFunc scoreFunc);

    std::pair<std::string, std::string> compute();

private:
    std::string m_a;
    std::string m_b;

    double m_penalty; 
    ScoreFunc m_scoreFunc;
};
}  // namespace sw
#endif