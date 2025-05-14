#include "PRF.h"



uint PRF::work(uint x){
    uint k=key^0xD2B74407u;
    for(int i=0;i<12;i++){
        x=(x^(k<<i|k>>(32-i)))*(0x9E3779Bu+(k&0xFFu));
        k+=(x>>(i*3&31))^0x7F4A7C15u;
        x^=(k+(x<<5))^(0xC2B2AE3Du|(k>>7));
    }
    x+=x<<13; x^=x>>17;
    return x*(k|1u);
}




