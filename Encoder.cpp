//
// Created by gravoo on 23.04.15.
//

#include "../include/Encoder.h"

Encoder::Encoder(int size,int range):ArithmeticCoder(range,size) { }

std::queue<bool> Encoder::encode(std::string inFileName) {

    std::ifstream myfile(inFileName, std::ios::binary | std::ios::in);
    if (myfile.is_open()) {
        char c;
        while (myfile.get(c)) {

            updateLR(c);
            rescale(range+1);

            symbols.update(c);
            if(symbols.getSymbolTotal()>=std::pow(2,14))
            {
                std::cerr<<"||||";
                symbols.rescaleTable();
            }
        }
        endEncoding(range+1);
        myfile.close();
    }
    else {
        std::cerr << "error file not opened";
    }
    std::cerr<<"DONE\n";
    return myqueue;
}
void Encoder::endEncoding(int M) {

    int bitCounter=this->bitCounter+1;
    if(left<=M*0.25)
        fillQueue(bitCounter,myqueue,false);
    else
        fillQueue(bitCounter,myqueue,true);

}
void Encoder::rescale(int M) {

    int _left=left,_right=right;
    unsigned bitCounter=this->bitCounter;
    bool flag=true;
    while(flag){
        if(0<=_left&&_right<=0.5*M){
            bitCounter = fillQueue(bitCounter, myqueue, false);
        }
        else if(0.5*M<=_left&&_right<=M){
            bitCounter = fillQueue(bitCounter, myqueue, true);
            _left=_left-M*0.5;
            _right=_right-M*0.5;
        }
        else if(0.25*M<=_left&&_right<=0.75*M)
        {
            _left=_left-M*0.25;
            _right=_right-M*0.25;
            bitCounter++;
        }
        else
            break;

        _left*=2;
        _right=(2*_right)+1;

    }
    this->bitCounter=bitCounter;
    left=_left;
    right=_right;

}

void Encoder::toFile(std::queue<bool> myQueue, std::string outFileName) {

    std::ofstream myfile(outFileName);
    char tmp;
    if (myfile.is_open()) {
        while(myQueue.size()>7)
        {
            tmp= toChar(myQueue, 7);
            myfile<<tmp;

        }
        tmp= toChar(myQueue, myQueue.size());
        myfile<<tmp;
        myfile.close();
    }
    else {
        std::cerr << "error file not opened";
    }

}
char Encoder::toChar(std::queue<bool> &myQueue, int size) {
    char a = 0;
    for (int i = 0; i <= size; i++) {
        a = a << 1;
        if (myQueue.front()) {
            a++;
        }
        myQueue.pop();
    }
    return a;
}
