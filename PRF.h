#pragma once


#include <iostream>
#include <string>
#include <cmath>
#include <cstdint>
#include <stdio.h>


using namespace std;
using uint = uint32_t;

class PRF
{
private: uint key;
public:
    PRF(const uint key) {
        this->key = key;
    };

    ~PRF() {};

    uint work(uint x);
};

