#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <cstdint>
#include <stdio.h>
#include<unordered_set>
#include <vector>


using namespace std;
using uint = uint32_t;

inline uint GRU() {
    uint r;
    r = (uint)(rand() % 2048);
    r = r * 2048;
    r += (uint)(rand() % 2048);
    r = r * 1024;
    r += (uint)(rand() % 1024);
    return r;
};

class RO
{
public:
    vector<uint> requests;
    vector<uint> responces;
    RO() {
        requests.resize(0);
        responces.resize(0);
    };

    ~RO() {
        requests.clear();
        responces.clear();
    };

    uint work(uint x);
};

