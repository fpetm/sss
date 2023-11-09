#pragma once
#include "algebra.hpp"
#include <stdint.h>

class Key {
  public:
  Key(double x, double y) : X(x), Y(y) {}
  Key() {}
  Key(std::vector<char> data);
  std::vector<char> serialize() const;

  std::pair<double, double> make_pair();

  double X, Y;
};
std::ostream& operator<<(std::ostream &os, const Key &key);

std::vector<Key> encrypt(double data, int n, int k);
double decrypt(std::vector<Key> keys);

void save_keys_to_file(std::vector<std::pair<Key, std::string>> keys);
Key load_key_from_file(std::string name);
