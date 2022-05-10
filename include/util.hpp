#pragma once

#include <iostream>

template <typename T>
constexpr bool nth_bit(T num, int pos) { return (num >> pos) & 1;}


class nullstream_t : public std::ostream 
{
    class nullbuf_t : public std::streambuf 
    {
        public:
            int overflow( int c ) { return c; }
    } m_nb;

public:
    nullstream_t() : std::ostream( &m_nb ) {}
};


extern nullstream_t nullstream;