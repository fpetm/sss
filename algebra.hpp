#pragma once
#include <iostream>
#include <vector>
#include <type_traits>

std::string superscript(std::string s);

template<
    typename T, //real type
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
> 
class Polynomial {
public:
  Polynomial(std::vector<T> coeffs) : m_Coefficients(coeffs) {}

  static Polynomial<T> FromPoints(const std::vector<std::pair<T, T>> points) {
    std::cerr << "Creating a polynomial from points\n";
    Polynomial<T> P({0});
    for (int k = 0; k < points.size(); k++) {
      auto x = points[k].first;
      auto y = points[k].second;

      double weight = 1;
      for (int j = 0; j < points.size(); j++) {
        if (j == k) continue;
        weight *= (x-points[j].first);
      }

      Polynomial<T> numerator({1});
      for (int j = 0; j < points.size(); j++) {
        if (j == k) continue;
        numerator = Polynomial<T>({-points[j].first, 1}) * numerator;
      }


      P += numerator*(y/weight);
    }
    return P;
  }

  Polynomial<T> operator+=(Polynomial<T> p) {
    for (int i = 0; i <= std::max(p.degree(), degree()); i++) coefficient(i) += p[i];
    return *this;
  }

  Polynomial<T> operator-=(Polynomial<T> p) {
    for (int i = 0; i <= std::max(p.degree(), degree()); i++) coefficient(i) -= p[i];
    return *this;
  }

  Polynomial<T> operator*=(T lambda) {
    for (int i = 0; i <= degree(); i++) coefficient(i) *= lambda;
    return *this;
  }

  Polynomial<T> operator/=(T lambda) {
    for (int i = 0; i <= degree(); i++) coefficient(i) /= lambda;
    return *this;
  }

  Polynomial<T> operator+(Polynomial<T> p) {
    std::vector<T> coeffs(std::max(p.degree(), degree()) + 1);
    for (int i = 0; i <= std::max(p.degree(), degree()); i++) coeffs[i] = p[i] + coefficient(i);
    Polynomial<T> polynomial = Polynomial<T>(coeffs);
    return polynomial;
  }

  Polynomial<T> operator-(Polynomial<T> p) {
    std::vector<T> coeffs(std::max(p.degree(), degree()) + 1);
    for (int i = 0; i <= std::max(p.degree(), degree()) + 1; i++) coeffs[i] = p[i] - coefficient(i);
    Polynomial<T> polynomial = Polynomial<T>(coeffs);
    return polynomial;
  }

  Polynomial<T> operator*(T lambda) {
    std::vector<T> coeffs(degree() + 1);
    for (int i = 0; i <= degree(); i++) coeffs[i] = lambda * coefficient(i);
    Polynomial<T> polynomial = Polynomial<T>(coeffs);
    return polynomial;
  }

  Polynomial<T> operator/(T lambda) {
    std::vector<T> coeffs(degree() + 1);
    for (int i = 0; i <= degree(); i++) coeffs[i] = coefficient(i) / lambda;
    Polynomial<T> polynomial = Polynomial<T>(coeffs);
    return polynomial;
  }

  Polynomial<T> operator*(Polynomial<T> p) {
    int n = degree() + p.degree();
    std::vector<T> coeffs(n+1);
    for (int i = 0; i <= n; i++) {
      coeffs[i] = 0;
      for (int a = 0; a <= i; a++) {
        int b = i - a;
        coeffs[i] += coefficient(a) * p.coefficient(b);
      }
    }
    Polynomial<T> polynomial = Polynomial<T>(coeffs);
    return polynomial;
  }

  T& coefficient(int n) {
    if (n > degree())
      m_Coefficients.resize(n+1);
    return m_Coefficients[n];
  }

  T& operator[](int n) {
    return coefficient(n);
  }

  T coefficient(int n) const {
    if (n > degree())
      return 0;
    else
      return m_Coefficients[n];
  }

  T operator[](int n) const {
    return coefficient(n);
  }

  T operator()(T x) const {
    T sum = T();
    T xn = T()+1;
    for (auto coefficient : m_Coefficients) {
      sum += coefficient * xn;
      xn *= x;
    }
    return sum;
  }
  size_t degree() const { return m_Coefficients.size() - 1; }

  friend std::ostream& operator<<(std::ostream &os, const Polynomial<T> &polynomial) {
    for (int i = polynomial.degree()+1; i >= 0; i--) {
      if (polynomial[i] == 0) continue;
      if (i == 0) os << polynomial[i];
      else os << (polynomial[i] != 1 ? std::to_string(polynomial[i]) : "") << "x" << superscript(std::to_string(i)) << " + ";
    }
    return os;
  }

private:
  std::vector<T> m_Coefficients;
};

