int setbits(unsigned long long v){
    return __builtin_popcountll(v);
}
