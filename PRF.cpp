#include "PRF.h"

using u = uint64_t;
using e = uint8_t;
static inline u siphash24(const e*k,const e*d,size_t l){
#define R(x,b)((x<<b)|(x>>(64-b)))
#define S \
A+=B; B=R(B,13); B^=A; A=R(A,32); \
C+=D; D=R(D,16); D^=C; \
A+=D; D=R(D,21); D^=A; \
C+=B; B=R(B,17); B^=C; C=R(C,32);
    u A=0x736f6d6570736575,B=0x646f72616e646f6d,
             C=0x6c7967656e657261,D=0x7465646279746573,
             m,b=(u)l<<56;
    auto U=[](const e*p){
        return u(p[0])|(u(p[1])<<8)|(u(p[2])<<16)|
               (u(p[3])<<24)|(u(p[4])<<32)|(u(p[5])<<40)|
               (u(p[6])<<48)|(u(p[7])<<56);
    };
    A^=U(k); B^=U(k+8); C^=U(k); D^=U(k+8);
    for(size_t i=0,n=l&~7;i<n;i+=8){
        m=U(d+i); D^=m; S; A^=m;
    }
    for(size_t r=0,n=l&~7;r<l&7;r++) b|=(u)d[n+r]<<8*r;
    D^=b; S; A^=b;
    D^=0xff; for(int i=0;i<4;i++) S;
    return A^B^C^D;
#undef S;#undef R
}


uint PRF::work(uint x) {
    e k[16], m[8];
    // expand 32-bit key to 128-bit
    for (int i = 0; i < 16; i++)
        k[i] = key >> (8 * (i & 3));
    // pack x twice into 8 bytes
    for (int i = 0; i < 8; i++)
        m[i] = x >> (8 * (i & 3));
    // SipHash-2-4 → truncate to 32 bits
    return static_cast<uint32_t>(siphash24(k, m, 8));
}



