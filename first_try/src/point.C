#include <iostream>

#include "point.H"

void Point::set_point(const double &re, const double &im){
  m_z  = (re,im);
  m_it = 0;
}

complex<double> Point::f(){
  m_it++;
  return pow(m_z,m_n) + m_r*exp(I*m_phi);
}

int Point::get_it(){
  while(abs(m_z)<=2 && m_it<=300) {
    f();
//    cout << "Number of iterations = " << m_it << "\n" ;
  }
  return m_it;
}
