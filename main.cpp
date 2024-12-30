#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

long long decodeValue(const string& value, int base) {
    long long result = 0;
    for (char digit : value) {
        result = result * base + (isdigit(digit) ? digit - '0' : digit - 'a' + 10);
    }
    return result;
}

long long lagrangeInterpolation(const vector<pair<int, long long>>& points) {
    int k = points.size();
    long long constantTerm = 0;

    for (int i = 0; i < k; ++i) {
        long long term = points[i].second;
        long long denominator = 1;

        for (int j = 0; j < k; ++j) {
            if (i != j) {
                term *= -points[j].first;
                denominator *= (points[i].first - points[j].first);
            }
        }

        constantTerm += term / denominator;
    }

    return constantTerm;
}

long long processTestCase(const json& testcase) {
    int n = stoi(testcase["keys"]["n"].get<string>());
    int k = stoi(testcase["keys"]["k"].get<string>());

    vector<pair<int, long long>> points;

    for (auto it = testcase.begin(); it != testcase.end(); ++it) {
        if (it.key() != "keys") {
            int x = stoi(it.key());
            int base = stoi(it.value()["base"].get<string>());
            string value = it.value()["value"].get<string>();
            long long y = decodeValue(value, base);
            points.emplace_back(x, y);
        }
    }

    points.resize(k);

    return lagrangeInterpolation(points);
}

int main() {
    ifstream inputFile("testcases.json");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open testcases.json" << endl;
        return 1;
    }

    json testcases;
    inputFile >> testcases;
    inputFile.close();
    for(int i=1;i<=2;i++){
        cout << "Secret (c): " << processTestCase(testcases[to_string(i)]) << endl;
    }



    return 0;
}
