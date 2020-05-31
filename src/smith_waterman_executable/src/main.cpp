#include "smith_waterman.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void fromConsole(std::string& a, std::string& b)
{
    std::cout << "Please enter the first sequence: ";
    std::cin >> a;

    std::cout << "Please enter the second sequence: ";
    std::cin >> b;
}

void fromFiles(std::string& a, std::string& b)
{
    const auto fromFile = [](const std::string& filename) -> std::string {
        const std::ifstream t(filename);

        std::stringstream buffer;
        buffer << t.rdbuf();

        return buffer.str();
    };

    std::cin.ignore();

    std::string filename;

    std::cout << "Please enter the first sequence input file name [Default = a.txt]: ";
    std::getline(std::cin, filename);

    a = fromFile(filename.empty() ? "a.txt" : filename);

    std::cout << "Please enter the second sequence input file name [Default = b.txt]: ";
    std::getline(std::cin, filename);

    b = fromFile(filename.empty() ? "b.txt" : filename);
}

int main()
{
    try
    {
        std::cout << "Smith-Waterman Algorithm.\n";
        std::cout << "Choose sequences input method [1 = Console, 2 = Files]: ";

        int inputMethod;
        std::cin >> inputMethod;

        std::string a, b;

        if (inputMethod == 1)
            fromConsole(a, b);
        else if (inputMethod == 2)
            fromFiles(a, b);
        else
        {
            std::cout << "\nUnsupported sequences input method.\n";
            return 1;
        }

        constexpr auto penalty = -4.;

        sw::SmithWatermanAlgorithm algorithm(a, b, penalty, [penalty](const char a, const char b) -> double {
            if (a == b)
                return 1;

            return penalty;
        });

        auto&& [sequenceA, sequenceB] = algorithm.compute();

        std::cout << "\nResult alignment:\n" << sequenceA << "\n" << sequenceB << "\n\n";

        std::cin.get();
    }
    catch (const std::exception& e)
    {
        std::cout << "An error occured! Message: " << e.what();
        return 1;
    }
    catch (...)
    {
        std::cout << "An unexpected error occured!";
    }

    return 0;
}
