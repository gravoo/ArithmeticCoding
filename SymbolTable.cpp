//
// Created by gravoo on 22.04.15.
//

#include "../include/SymbolTable.h"
SymbolTable::SymbolTable(int size, int range) : size(size), range(range),
                                                symbolTotal(size){
    sTable2.resize(size+3);
    for(auto &a:sTable2){
        a.first=1;
    }
    generateCumulativeProb<int,int>(sTable2);
    sTable2[size+1].second=range;
}

void SymbolTable::update(unsigned char a) {
    ++sTable2[a].first;
    ++symbolTotal;
    generateCumulativeProb<int,int>(sTable2);

}


int &SymbolTable::operator[](int i) {
    if(i<0) return sTable2[size+2].second;
    if(i==0) return sTable2[0].second;
    if(i>size) return sTable2[size+1].second;
    return sTable2[i].second;
}


int SymbolTable::getSize() const {
    return size;
}

template<typename T,typename A>
void SymbolTable::generateCumulativeProb(std::vector<std::pair<T,A>> &table) {
    for(int i=0;i<=size;++i){
        table[i].second=table[i].first+table[i-1].second;
    }

}

int SymbolTable::getSymbolTotal() const {
    return symbolTotal;
}

unsigned char SymbolTable::findChar(int interval) {
    for(int i=0;i<=size;++i){
        if(sTable2[i-1].second<=interval&&
           interval<sTable2[i].second){
            return i;
        }
    }

}
template <typename T,typename A>
void SymbolTable::getCumulativeVal(std::vector<std::pair<T, A>> &table) {
    for(int i=0;i<=size;++i){
        table[i].second=table[i].second+table[i-1].second;
    }
    symbolTotal=table[size].second;
}
void SymbolTable::rescaleTable() {
    for(int i=0;i<=size;++i){
        sTable2[i].first=1;
        if(sTable2[i].first==0)
            sTable2[i].first=1;
    }
    generateCumulativeProb<int,int>(sTable2);
    symbolTotal=sTable2[size].second;

}

