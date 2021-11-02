#ifndef BITARRAY_H
#define BITARRAY_H

#include <iostream>
#include <iterator>
#include <cstddef>

class bitarray
{
private:
    unsigned char* bytes_;
    int bitlen_;

public:

    struct iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = unsigned char;
        using pointer           = unsigned char*;
        using reference         = unsigned char&;

    private:
        pointer m_ptr;
        int bidx_;

    public:
        iterator(pointer ptr, int bidx);

        value_type operator *() const;
        pointer operator->();
        iterator& operator++();
        iterator operator++(int);

        friend bool operator ==(const iterator& a, const iterator& b);
        friend bool operator !=(const iterator& a, const iterator& b);
    };

    class proxy
    {
    private:
        bitarray* src_;
        int idx_;

    public:
        proxy(bitarray* src, int idx);
        bool get();

        void operator =(unsigned char bit);
        operator unsigned char();

        friend std::ostream& operator <<(std::ostream& os, proxy& p);
    };

    bitarray(int s, bool clr = true);
    bitarray(std::initializer_list<unsigned char> list);
    ~bitarray();
    iterator begin();
    iterator end();
    const int length();
    void reset();

    proxy operator [](int i);
};

#endif