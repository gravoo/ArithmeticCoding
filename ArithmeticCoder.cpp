//
// Created by gravoo on 24.04.15.
//

#include "../include/ArithmeticCoder.h"

ArithmeticCoder::ArithmeticCoder(int range, int size):left(0),right(range)
        ,range(range),bitCounter(0) {
    SymbolTable symbols{size,range};
    this->symbols = symbols;
}

ArithmeticCoder::ArithmeticCoder(int left, int right,
                                 int size,int range) : left(left),right(right),range(range) {
    SymbolTable symbols{size,range};
    this->symbols = symbols;
}

void ArithmeticCoder::updateLR(unsigned const char c) {

    int  _left = left, _right = right;
    int  lr=(_right - _left+1);
     double  tmp=(double)lr*(double)symbols[c -(unsigned char) 1];

     double  symTot=(double)symbols.getSymbolTotal();
    tmp= std::floor(tmp/symTot)+(double)_left;
    left = tmp;
    tmp=(double)lr *(double)symbols[c];
    tmp= std::floor(tmp/symTot)+(double)_left-1.0;
    right =tmp;
}

int ArithmeticCoder::fillQueue(int bitCounter, std::queue<bool> &myqueue, bool what) {
    myqueue.emplace(what);
    while(bitCounter--){
        myqueue.emplace(!what);
    }
    return 0;
}





