//
// Created by trucnguyen on 9/9/19.
//

#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include "json.hpp"

using namespace std;
// for convenience
using json = nlohmann::json;

unordered_map<ulong, unordered_set<ulong>> vampire;

void calcVampireNumber(long number)
{
    std::string numberString = std::to_string(number);
    std::sort(numberString.begin(), numberString.end());
    uint fangLen = numberString.length() / 2;

    long start = static_cast<long>( std::pow(10, fangLen - 1));
    long end = sqrt(number);

    for (long i = start; i <= end; i++)
    {
        if (number % i == 0)
        {
            long quotient = number / i;
            if ((i % 10 == 0) && (quotient % 10 == 0))
                continue;

            std::ostringstream numberStream;
            numberStream << i << quotient;
            std::string divisorString(numberStream.str());
            std::sort(divisorString.begin(), divisorString.end());

            if (divisorString == numberString)
            {
                vampire[number].insert(i);
                vampire[number].insert(quotient);
            }
        }
    }
}



int main()
{
    long tens = 3;

    std::ofstream file;
    file.open("1k-999999.txt");

    while (tens <= 5)
    {
        ulong start = pow(10, tens);

        for (ulong num = start; num < start * 10; ++num)
        {
            calcVampireNumber(num);
        }
        tens += 2;
    }

    json j = vampire;

    file << std::setw(4) << j << endl;
    file.close();



    return 0;
}