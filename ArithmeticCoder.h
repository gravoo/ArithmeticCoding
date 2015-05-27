//
// Created by gravoo on 24.04.15.
//

#ifndef ARITHMETICCODING_ARITHMETICCODER_H
#define ARITHMETICCODING_ARITHMETICCODER_H
#include <string>
#include <iostream>
#include <initializer_list>
#include <queue>
#include <fstream>

#include "SymbolTable.h"

class ArithmeticCoder {

public:

    ArithmeticCoder(int left, int right,int range,int size);
    ArithmeticCoder(int range,int size);
    ArithmeticCoder() { }

protected:
    int left,right;
    int range;
    int bitCounter;
    std::string fileName;
    SymbolTable symbols;
    std::queue<bool> myqueue;
    void updateLR(unsigned const char c);
    int fillQueue(int bitCounter, std::queue<bool> &myqueue, bool what);

private:

};


#endif //ARITHMETICCODING_ARITHMETICCODER_H
