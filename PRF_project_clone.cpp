
#include <iostream>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include "PRF.h"
#include "RO.h"
#include "DIST.h"



#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "PRF.h"
#include "RO.h"
#include "DIST.h"

using namespace std;
using uint = uint32_t;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    const int N = 100000;
    float c0 = 0, c1 = 0, d0 = 0, d1 = 0;

    for (int i = 0; i < N; i++) {
        int choice = (rand() >> (i % 8)) & 1;
        uint decision = 0;
        DIST Distinguisher;
        vector<uint> response;

        if (choice == 0) {
            c0++;
            uint key = GRU();
            PRF funcPRF(key);
            uint x = 0;
            int num_calls = 0;

            while (true) {
                num_calls++;
                response = Distinguisher.work(x);
                if (response[0] == 0) {
                    if (num_calls > 32*2048) break;
                    x = funcPRF.work(response[1]);
                } else {
                    decision = response[1];
                    if (decision != 0) d0++;
                    break;
                }
            }
        } else {
            c1++;
            RO funcRO;
            uint x = 0;
            int num_calls = 0;

            while (true) {
                num_calls++;
                response = Distinguisher.work(x);
                if (response[0] == 0) {
                    if (num_calls > 32*2048) break;
                    x = funcRO.work(response[1]);
                } else {
                    decision = response[1];
                    if (decision != 0) d1++;
                    break;
                }
            }
        }
    }

    float adv = fabs(d0 / c0 - d1 / c1);
    cout << "Advantage = " << adv
         << ", c0 = " << c0 << ", c1 = " << c1
         << ", d0 = " << d0 << ", d1 = " << d1 << "\n";
    return 0;
}
