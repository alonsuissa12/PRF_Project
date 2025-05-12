#include "PRF.h"

#include <cstdint>

uint PRF::work(uint x)
{
#define F(i, n) for (int i = 0; i < n; i++)
#define M(x, n) ((x >> n) & 255)
#define D delete[]
#define N(n) auto n = new uint8_t[32]
#define P(s) { N(t); F(i, 32) t[i] = s[(i * 9 + 3) % 32]; F(i, 32) s[i] = t[i]; D t; }

    N(s);
    F(i, 32) s[i] = 49;
    F(r, 4) {
        s[0] ^= M(key, r * 8);
        P(s)
    }
    F(r, 4) {
        s[0] ^= M(x, r * 8);
        P(s)
    }
    F(r, 4) {
        s[0] ^= M(key, r * 8);
        P(s)
    }
    F(r, 4) {
        s[0] ^= M(x, r * 8);
        P(s)
    }
    uint y = 0;
    F(r, 4) {
        y = (y << 8) | s[0];
        P(s)
    }
    D s;
    //printf("%08X\n", y);
    return y;
};