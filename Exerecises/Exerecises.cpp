// Exerecises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>
using namespace std;

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

vector<string> LineToVector(string line)
{
    vector<string> res;
    char separator = ' ';
    string tmp;
    stringstream ss(line);

    while (getline(ss, tmp, separator)) 
    { 
        replace(tmp, "<", "");
        replace(tmp, ">", "");
        replace(tmp, "/", "");
        replace(tmp, "\"", "");
        replace(tmp, "\"", "");
        if (tmp != "=")
        {
            //cout << "getline: " << tmp << endl;
            res.push_back(tmp);
        }
    
    }

    return res;
}

void PossibleQueries(map<string, string>& queries, vector<string>& arr)
{
    string current_path;
    for (vector<string>::iterator it = arr.begin(); it != arr.end(); it++)
    {
        vector<string> line = LineToVector(*it);
        int querr_iter = 0;

        if (current_path.empty())
        {
            //cout << "empty string" << endl;
            current_path = line[0];
        }
        else if (current_path.find(line[0]) != string::npos)
        {
            //cout << "found ending" << endl;
            if (!replace(current_path, '.' + line[0], ""))
            {
                replace(current_path, line[0].c_str(), "");
            }

            //cout << "current string: " << current_path <<  endl;
        }
        else
        {
            //cout << "Add new tag" << endl;
            current_path += "." + line[0];
        }

        for (int i = 1; i < line.size() - 1; i+=2)
        {
            queries.insert({ current_path + "~" + line[i], line[i + 1] });
            //cout << "querry: " << current_path << " value: " << line[i + 1] << endl;
        }

    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n, q;
    cin >> n >> q;
    vector<string> arr(n, " ");
    vector<string> quer(q, " ");
    map<string, string> possibleQueries;

    // skip empty line
    string dummy;
    getline(cin, dummy);

    // Populate arr
    for (vector<string>::iterator it = arr.begin(); it != arr.end(); it++)
    {
        getline(cin, *it);
    }

    PossibleQueries(possibleQueries, arr);

    // Populate quer
    for (vector<string>::iterator it = quer.begin(); it != quer.end(); it++)
    {
        getline(cin, *it);
    }

    for (vector<string>::iterator qr = quer.begin(); qr != quer.end(); qr++)
    {
        if (possibleQueries.find(*qr) == possibleQueries.end())
        {
            cout << "Not Found!" << endl;
        }
        else 
        {
            cout << possibleQueries.at(*qr) << endl;
        }
        
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
