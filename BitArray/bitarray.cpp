#include "bitarray.h"
#include <iostream>

static inline int bit_to_byte_len(int bitlen)
{
    return (bitlen % 8 != 0) ? ((bitlen / 8) + 1) : (bitlen / 8);
}

/*
========== IMPLEMENTATIONS =================================================================================
*/
bitarray::bitarray(int s, bool clr) : bytes_(nullptr), bitlen_(s)
{
    int bytelen = bit_to_byte_len(s);
    bytes_ = new unsigned char[bytelen];
    if (clr)
        reset();
}

bitarray::bitarray(std::initializer_list<unsigned char> list) : bytes_(nullptr), bitlen_((int)list.size())
{
    int bytelen = bit_to_byte_len(bitlen_);
    bytes_ = new unsigned char[bytelen];

    reset();

    int idx;
    int i = 0;
    unsigned char* cbyte_ptr;
    for (std::initializer_list<unsigned char>::iterator it = list.begin(); it != list.end(); it++)
    {
        idx = i / 8;
        cbyte_ptr = &bytes_[idx];
        *cbyte_ptr |= (*it & 0x1) << (i % 8);
        i++;
    }
}

bitarray::~bitarray()
{
    delete[] bytes_;
}

bitarray::iterator bitarray::begin()
{
    return iterator(&bytes_[0], 0);
}

bitarray::iterator bitarray::end()
{
    return iterator(&bytes_[bit_to_byte_len(bitlen_)], bitlen_);
}

const int bitarray::length()
{
    return bitlen_;
}

void bitarray::reset()
{
    int bytelen = bit_to_byte_len(bitlen_);
    for (int i = 0; i < bytelen; i++)
        bytes_[i] = 0;
}

/*
===== ITERATOR =========================================================
*/

bitarray::iterator::iterator(pointer ptr, int bidx) : m_ptr(ptr), bidx_(bidx) {}

bitarray::iterator::value_type bitarray::iterator::operator *() const 
{
    unsigned char bmask = 0x1 << (bidx_ % 8);
    return (*m_ptr & bmask) == bmask;
}

bitarray::iterator::pointer bitarray::iterator::operator ->() { return m_ptr; }

bitarray::iterator& bitarray::iterator::operator ++() 
{
    bool isLastBitInByte = (bidx_ % 8) == 7;
    if (isLastBitInByte)
        m_ptr++;
    bidx_++;
    return *this;
}

bitarray::iterator bitarray::iterator::operator ++(int)
{
    iterator tmp = *this;
    ++(*this);
    return tmp; 
}

bool operator ==(const bitarray::iterator& a, const bitarray::iterator& b)
{
    return a.m_ptr == b.m_ptr && a.bidx_ == b.bidx_; 
}

bool operator !=(const bitarray::iterator& a, const bitarray::iterator& b)
{
    return a.m_ptr != b.m_ptr && a.bidx_ != b.bidx_;
}

/*
===== PROXY ============================================================
*/

bitarray::proxy bitarray::operator [](int i)
{
    if (i < 0 || i >= bitlen_)
        throw std::exception("Index out of range");
    return bitarray::proxy(this, i);
}

bitarray::proxy::proxy(bitarray* src, int idx) : src_(src), idx_(idx) {}

bool bitarray::proxy::get()
{
    unsigned char bmask = 1 << (idx_ % 8);
    unsigned char b = src_->bytes_[idx_ / 8];
    return (b & bmask) == bmask;
}

void bitarray::proxy::operator =(unsigned char bit)
{
    unsigned char bmask = (bit & 0x1) << (idx_ % 8);
    unsigned char* targetbit = &src_->bytes_[idx_ / 8];
    
    // clear old bit and set to new
    *targetbit = (*targetbit & ~(0x1 << (idx_ % 8))) | bmask;
}

std::ostream& operator <<(std::ostream& os, bitarray::proxy& p)
{
    os << p.get();
    return os;
}
