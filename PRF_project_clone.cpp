
#include <iostream>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include "PRF.h"
#include "RO.h"
#include "DIST.h"



int main()
{

	srand(time(0));

	// a single experiment

	float c0 = 0, c1 = 0, d0 = 0, d1 = 0;
	for (int i = 0; i < 100000; i++) {

		int choice = (rand() >> (i % 8)) & 1;
		uint decision;

		DIST Distinguisher;
		vector<uint> response;

		if (choice == 0) {
			c0++;
			uint key = GRU();
			PRF funcPRF(key);
			uint x = 0;
			uint num_calls = 0;
			while (true) {
				num_calls++;
				response = Distinguisher.work(x);

				if (response[0] == 0) {						//if the final decision is not made yet

					// do not try to bruteforce, otherwise you'll be kicked out with a default result decision = 0.
					if (num_calls > 32*2048)  break;

					x = funcPRF.work(response[1]);
				}
				else {										//if this is the final decision of Distinguisher
					decision = response[1];
					if (decision != 0) d0++;
					break;
				};
			}

		}
		else {

			c1++;
			RO funcRO;
			uint x = 0;
			int num_calls = 0;
			while (true) {
				num_calls++;
				response = Distinguisher.work(x);
				if (response[0] == 0) {
					if (num_calls > 32*2048)  break;
					x = funcRO.work(response[1]);
				}
				else {
					decision = response[1];
					if (decision != 0) d1++;
					break;
				};
			}
		};
	};
	float adv = abs(d0 / c0 - d1 / c1);
	std::cout << "Advantage=" << adv << ", c0 = " << c0 << ", c1 = " << c1 << "\n";


}

