//
// Created by gravoo on 23.04.15.
//

#ifndef ARITHMETICCODING_ENCODER_H
#define ARITHMETICCODING_ENCODER_H

#include "ArithmeticCoder.h"

class Encoder : public ArithmeticCoder {

public:
    Encoder(int size, int range);
    std::queue<bool> encode(std::string inFileName);
    void toFile(std::queue<bool> myQueue, std::string outFileName);

private:
    std::string fileName;
    void endEncoding(int M);
    virtual void rescale(int M);
    char toChar(std::queue<bool> &myQueue, int size);


};


#endif //ARITHMETICCODING_ENCODER_H
