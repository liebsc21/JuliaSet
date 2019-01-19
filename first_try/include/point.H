#ifndef POINT_H
#define POINT_H

#include <complex>
#include <cmath>

using namespace std;

template <class T>
class Point {

  private:
    const complex<T> I = {0.0,1.0};
    const int m_n;
    const complex<T> m_c;
    complex<T> m_z;
    int m_it;

  public:
    Point(const int &n, const T &r, const T &phi) : 
      m_n(n), m_c(polar(r,phi)) {}
    void set_point(const T &re, const T &im);
    void f();
    int get_it();
    T get_phi();
    T get_r(){ return abs(m_z); }
};

#include "point.inl"

#endif /* POINT_H */
