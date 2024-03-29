#include "Bitset.h"
#include "Utils.h"
#include <iostream>
#include <assert.h>
#include <bitset>

/*
    Клас, представляващ референция към позиция (бит) в Bitset. Идеята е вдъхновена от std::bitset::reference. 
    Използва се, за да позволява четене и писане в Bitset последством оператор [], използвайки индексация по индекс на бит. 
*/
BitReference::BitReference() {}
BitReference::BitReference(unsigned long long& l, int bit) : ptr(&l), bit(bit) {}

BitReference::operator bool() const{

    return utils::get_kth_bit(*ptr, bit);
}

BitReference& BitReference::operator=(const bool val){

    if(utils::get_kth_bit(*ptr, bit) != val){
        utils::toggle_kth_bit(*ptr, bit);
    }

    return *this;
    
}

bool BitReference::operator != (const BitReference& o)const{

    return !(*this == o);
    
}

unsigned long long& BitReference::long_val(){

    return *ptr;
}


/*
    Класът Bitset е основната структура за съхранение и манипулиране на последователност от битове. Имплементиран е с вектор от unsigned long long.
    Поддържа случаен достъп до бит, конкатенация на Bitset-ове, преобразуване към стринг, хеширане и др.
*/
Bitset::Bitset() {}


void Bitset::add(const bool bit){

    if(next_free_bit % LL_BITS == 0 && next_free_bit >= bits.size() * LL_BITS){

        bits.push_back(0);
    }

    int last_long = next_free_bit / (LL_BITS);

    if(bit){

        utils::set_kth_bit(bits[last_long], next_free_bit);
    }
    
    next_free_bit ++;
}

void Bitset::reserve(const int len){

    assert(len > bits.size() * LL_BITS);

    int already_allocated = bits.size() * LL_BITS;

    int new_longs = ((len - already_allocated) / LL_BITS);
    if (len % LL_BITS) new_longs ++;

    for(int i=0; i<new_longs; i++){

        bits.push_back(0);
    }
}

void Bitset::clear(){

    bits.clear();
    next_free_bit = 0;

}

void Bitset::clear_head(const int len){

    int ll_remainder = len;
    while(ll_remainder >= 64){
        bits.erase(bits.begin());
        next_free_bit -= LL_BITS;
        ll_remainder -= LL_BITS;
    }

    bits.back() << ll_remainder;
    next_free_bit -= ll_remainder;
    
}

Bitset::operator std::string() const{

    std::string res;

    for(int i=0; i<bits.size(); i++){

        for(int bit_idx=0; bit_idx<LL_BITS; bit_idx++){
            
            if(i * LL_BITS + bit_idx >= next_free_bit) break;
            std::string curr_bit = std::to_string((int)utils::get_kth_bit(bits[i], bit_idx));
            res += curr_bit;
        }
    }
    return res;
}

Bitset::operator byte() const{

    return  bits[0] >> 56;
}

Bitset& Bitset::operator = (const Bitset& o){

    this->bits = o.bits;
    this->next_free_bit = o.next_free_bit;
    return *this;
}


const std::vector<unsigned long long>& Bitset::longs() const {

    return bits;
}

Bitset& Bitset::operator + (const Bitset& o){

    if(next_free_bit % LL_BITS == 0){

        for(int i=0; i<o.bits.size(); i++){

            bits.push_back(o.bits[i]);
        }

    }

    else{
        

        int non_empty_space = next_free_bit % LL_BITS;
        for(int i=0; i<o.bits.size(); i++){
            
            unsigned long long& last_long = bits[bits.size()-1];
            unsigned long long next_long = o.bits[i];

            utils::merge(last_long, next_long, non_empty_space);

            if(o.next_free_bit > LL_BITS - non_empty_space) bits.push_back(next_long);
        }
        
    }

    next_free_bit += o.next_free_bit;

    return *this;
}


Bitset& Bitset::operator += (const Bitset& o){

    *this = *this + o;
    return *this;
}

BitReference Bitset::operator[] (const int idx){

    assert(idx < bits.size() * LL_BITS);

    int long_idx = idx / LL_BITS;
    int bit_idx = idx % LL_BITS ;

    if(idx > next_free_bit) next_free_bit = idx + 1;
    return BitReference(bits[long_idx], bit_idx);
}

bool Bitset::operator == (Bitset& o) const {

    if(o.size() != next_free_bit) return false;
    for(int i=0; i<next_free_bit; i++){

        int long_idx = i / LL_BITS;
        int bit_idx = i % LL_BITS;

        if(utils::get_kth_bit(bits[long_idx], bit_idx) != o[i]) return false;

    }
    return true;
}

int Bitset::size() const{

    return next_free_bit;
}

std::size_t BitsetHash::operator() (const Bitset& b) const {

    std::hash<std::string> str_hash;

    return str_hash(std::string(b));
}