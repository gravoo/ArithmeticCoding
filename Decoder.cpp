//
// Created by gravoo on 23.04.15.
//

#include "../include/Decoder.h"

Decoder::Decoder(int size, int range) : ArithmeticCoder(range, size) { };

void Decoder::decode(std::queue<bool> inQueue, std::string fileOut) {

    unsigned const _Nb=16;
    std::bitset<_Nb> bits;
    getBits<_Nb>(inQueue, bits);
    int tag=getTag<_Nb>(bits),t_star;
    char tmp;
    std::ofstream myfile(fileOut);
    if (myfile.is_open()) {
        while (tag||!inQueue.empty()) {

                t_star = (((tag - left + 1) * symbols.getSymbolTotal() - 1)) /
                         (right - left + 1);

            tmp = symbols.findChar(t_star);
            myfile<<tmp;
            updateLR(tmp);
            rescale<_Nb>(range + 1, inQueue, bits);
            tag = getTag<_Nb>(bits);

            symbols.update(tmp);

            if(symbols.getSymbolTotal()>=std::pow(2,_Nb-2))
            {
                std::cerr<<"||||";
                symbols.rescaleTable();
            }

        }
        std::cerr<<"DONE\n";
        myfile.close();
    }
    else {
        std::cerr << "error file not opened";
    }

}

template<size_t _Nb>
void Decoder::shift(std::queue<bool> &inQueue, std::bitset<_Nb> &bits) {
    bits<<=1;
    if(!inQueue.empty()&&inQueue.front()){
        bits.set(0);
    }
    if(!inQueue.empty())
        inQueue.pop();

}
template<size_t _Nb>
void Decoder::getBits(std::queue<bool> &inQueue, std::bitset<_Nb> &bits) {

    for(int i=0;i<_Nb;++i){
        bits<<=1;
        if(inQueue.front())
            bits.set(0);
        inQueue.pop();
    }

}
template<size_t _Nb>
int Decoder::getTag(std::bitset<_Nb> &bits) {
    return bits.to_ulong();
}
template<size_t _Nb>
void Decoder::rescale(int M, std::queue<bool> &inQueue,
                      std::bitset<_Nb> &bits) {

    int _left=left,_right=right;
    int tag=getTag<_Nb>(bits);
    bool flag=true;
    while(flag){
        if(0<=_left&&_right<=0.5*M){
        }
        else if(0.5*M<=_left&&_right<=M){
            updateParameters(M, _left, _right,
                             tag, 0.5);
            bits=toBits<_Nb>(tag);
        }
        else if(0.25*M<=_left&&_right<=0.75*M)
        {
            updateParameters(M, _left, _right,
                             tag, 0.25);
            bits=toBits<_Nb>(tag);
        }
        else
        {
            if(inQueue.empty()&&((tag==M/2)||(tag==M/4)))
                bits.reset();
            break;
        }

        shift<_Nb>(inQueue,bits);
        tag=getTag<_Nb>(bits);
        _left*=2;
        _right=(2*_right)+1;

    }

    left=_left;
    right=_right;

}

void Decoder::updateParameters(int &M, int &_left,
                               int &_right, int &tag,
                               double param) {
    tag-=param*M;
    _left-=M*param;
    _right-=M*param;
}

template<size_t _Nb>
std::bitset<_Nb> Decoder::toBits(int tag) {
    std::bitset<_Nb> tmp(tag);
    return tmp;
}
