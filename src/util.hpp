#pragma once

template <typename T>
constexpr bool nth_bit(T num, int pos) { return (num >> pos) & 1;}

class NullStream : public std::ostream {
    class NullBuffer : public std::streambuf {
    public:
        int overflow( int c ) { return c; }
    } m_nb;
public:
    NullStream() : std::ostream( &m_nb ) {}
};