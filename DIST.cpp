#include "DIST.h"

vector<uint> DIST::work(uint x) {

    response.resize(2);
    if (state == 0) {
        response[0] = 0;
        response[1] = 0;
        state++;
    }
    else {
        response[0] = 1;
        if (x == 1) {
            response[1] = 0;
        }
        else {
            response[1] = 1;
        }
    }

    return response;
};