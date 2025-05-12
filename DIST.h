#pragma once
#include <unordered_set>
#include <unordered_map>
#include <iostream>

#include <stdio.h>
#include <time.h>

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <vector>

using namespace std;
using uint = uint32_t;


class DIST
{
public:
    vector<uint> requests;
    vector<uint> response;
    int state;
    DIST() {
        requests.resize(0);
        response.resize(0);
        state = 0;
    };

    ~DIST() {
        requests.clear();
        response.clear();
    };

    vector<uint> work(uint x);

};

