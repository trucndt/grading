#include <iostream>
#include <fstream>
#include "json.hpp"
#include <unordered_set>
#include <unordered_map>
#include <regex>

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */

using json = nlohmann::json;
using namespace std;

/// "Database" of vampire numbers and their fangs
unordered_map<ulong, unordered_set<ulong>> vampire;

/**
 * Find numbers in a given string, delimiters are space and tab
 * @param s input string
 * @return vector of numbers
 */
vector<ulong> tokenizeNumber(const string& s)
{
    vector<ulong> number;
    number.reserve(3);

    std::regex words_regex("[^\\ \t\n]+");
    auto words_begin = std::sregex_iterator(s.begin(), s.end(), words_regex);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        try
        {
            auto num = stoi((*i).str()); // try converting string to number
            number.push_back(num);
        }catch(...) // can't convert
        {
            break;
        }
    }

    return number;
}

/**
 * Run the program and check the output
 * @param cmd command to run the program
 * @return true if output is correct
 */
bool checkResult(const string& cmd)
{
    std::array<char, 1000> buffer{};

    // Run program
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);

    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) // get each line of the output
    {
        const auto& res = tokenizeNumber(string(buffer.data())); // get numbers from line

        if (res.size() < 2) continue; // Can't find more than 1 number in this line

        if (vampire.find(res[0]) != vampire.end())
        {
            // The is a vampire number, now check the fang
            auto& fang = vampire[res[0]];
            for (ulong i = 1; i < res.size(); ++i)
            {
                if (fang.find(res[i]) != fang.end())
                {
                    fang.erase(res[i]);
                }
                else return false;
            }

            if (fang.empty())
                vampire.erase(res[0]);
        }
        else return false;
    }

    return vampire.empty();
}

void mixCompile(const string& cmd)
{
    std::array<char, 128> buffer{};
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }

    cout << result << endl;
}

bool grade(const char* dbFile, const string& cmd)
{
    json j;

    ifstream file(dbFile);
    file >> j;
    file.close();

    vampire = j.get<unordered_map<ulong, unordered_set<ulong>>>();

    bool result = checkResult(cmd);

    if (result)
        cout << GREEN << "PASSED" << RESET << "\n";
    else
        cout << RED << "FAILED" << RESET << "\n";

    return result;
}

int main(int argc, char **argv)
{
    cout << "\n===== Grading program for Project 1 ===== \n\n";

    string mixCmd = "mix run proj1.exs";
    string cd = "cd " + string(argv[1]);

    cout << "Compiling ...\n";
    mixCompile(cd + " && mix compile");

    string cmdTmp = cd + " && " + mixCmd;

    uint cntPassed = 0;

    // ============= TEST 1 ================
    cout << "\nRunning TEST 1: 100 - 90000\n";
    if (grade("1k-9k.txt", cmdTmp + " 100 90000")) cntPassed++;

    // ============= TEST 2 ================
    cout << "\nRunning TEST 2: 100000 - 200000\n";
    if (grade("100k-200k.txt", cmdTmp + " 100000 200000")) cntPassed++;

    // ============= TEST 3 ================
    cout << "\nRunning TEST 3: 500000 - 1000000\n";
    if (grade("500k-999999.txt", cmdTmp + " 500000 1000000")) cntPassed++;

    // ============= TEST 4 ================
    cout << "\nRunning TEST 4: 100000 - 105000\n";
    if (grade("100k-105k.txt", cmdTmp + " 100000 105000")) cntPassed++;

    // ============= TEST 5 ================
    cout << "\nRunning TEST 5: 200000 - 205000\n";
    if (grade("200k-205k.txt", cmdTmp + " 200000 205000")) cntPassed++;

    // ============= TEST 6 ================
    cout << "\nRunning TEST 6 with time: 1000 - 1000000\n";
    cmdTmp = cd + " && time " + mixCmd;
    if (grade("1k-999999.txt", cmdTmp + " 1000 1000000")) cntPassed++;

    cout << "\nPASSED " << cntPassed << "/6 tests\n";

    return 0;
}