#include "RO.h"



uint RO::work(uint x) {
    uint y;
    for (int i = 0; i < requests.size(); i++) {
        if (x == requests[i]) {
            y = responces[i];
            return y;
        }
    }
    requests.push_back(x);
    y = GRU();
    responces.push_back(y);
    return y;
};