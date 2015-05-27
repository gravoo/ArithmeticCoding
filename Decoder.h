//
// Created by gravoo on 23.04.15.
//

#ifndef ARITHMETICCODING_DECODER_H
#define ARITHMETICCODING_DECODER_H

#include "ArithmeticCoder.h"
#include <cmath>
#include <bitset>
class Decoder : public ArithmeticCoder{

public:
    Decoder(int size, int range);
    void decode(std::queue<bool> inQueue, std::string fileOut);

private:
    template<size_t _Nb>
    void getBits(std::queue<bool> &inQueue, std::bitset<_Nb> &bits);
    template<size_t _Nb>
    void shift(std::queue<bool> &inQueue, std::bitset<_Nb> &bits);
    template<size_t _Nb>
    int getTag(std::bitset<_Nb> &bits);
    template<size_t _Nb>
    std::bitset<_Nb> toBits(int tag);

protected:
    template<size_t _Nb>
    void rescale(int M, std::queue<bool> &inQueue,
                 std::bitset<_Nb> &bits);
    void updateParameters(int &M, int &_left,
                          int &_right, int &tag,
                          double param);

};


#endif //ARITHMETICCODING_DECODER_H
