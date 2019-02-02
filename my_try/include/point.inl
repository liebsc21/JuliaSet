#ifndef POINT_INL
#define POINT_INL

template <typename T>
void Point<T>::set_point(const T &re, const T &im){
  m_z  = {re,im};
  m_it = 0;
}

template <typename T>
void Point<T>::f(){
  m_it++;
  /* TODO: problem, if T=float on laptop */
  m_z = pow(m_z,m_n) + m_c;
}

template <typename T>
int Point<T>::get_it(){
  while(abs(m_z)<=2 && m_it<=300) {
    f();
  }
  return m_it;
}

template <typename T>
T Point<T>::get_phi(){
  T phi = arg(m_z);
  if (phi>=0) return phi;
  else        return 2*M_PI+phi;
}

#endif /* POINT_INL */
