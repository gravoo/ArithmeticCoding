//
// Created by gravoo on 22.04.15.
//

#ifndef ARITHMETICCODING_SYMBOLTABLE_H
#define ARITHMETICCODING_SYMBOLTABLE_H
#include <vector>
#include <initializer_list>
#include <iostream>
#include <cmath>
class SymbolTable {

public:
    SymbolTable(){};
    SymbolTable(int size, int range);
    int & operator[](int i);
    int getSize() const;
    int getSymbolTotal() const;
    void update(unsigned char a);
    unsigned char findChar(int interval);
    void rescaleTable();

private:
    std::vector<std::pair<int,int>> sTable2;
    int size;
    int symbolTotal;
    int range;
    template <typename T,typename A>
    void generateCumulativeProb(std::vector<std::pair<T,A>> &table);
    template <typename T,typename A>
    void getCumulativeVal(std::vector<std::pair<T,A>> &table);



};


#endif //ARITHMETICCODING_SYMBOLTABLE_H
