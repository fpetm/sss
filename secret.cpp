#include "secret.hpp"
#include <fstream>
#include <bit>
#include <cstdint>
#include <sstream>

std::vector<char> Key::serialize() const {
  std::stringstream ss;
  std::vector<char> data;
  ss << X << " " << Y;
  for (char c : ss.str()) data.push_back(c);
  return data;
}

Key::Key(std::vector<char> data) {
  uint64_t x, y, c;
  x = y = c = 0;

  std::string s; for (auto c : data) s.push_back(c);
  std::istringstream iss(s);
  iss >> X >> Y;
}

std::pair<double, double> Key::make_pair() {
  return std::make_pair(X, Y);
}

std::ostream& operator<<(std::ostream &os, const Key &key) {
  for (char part : key.serialize()) {
    os << part;
  }
  return os;
}

std::istream& operator>>(std::istream &is, Key &key) {
  is >> key.X >> key.Y;
  return is;
}

std::vector<Key> encrypt(double data, int n, int k) {
  srand (time(NULL));
  std::vector<double> coeffs(k);
  for (auto &e : coeffs) e = (double)rand() / RAND_MAX;
  coeffs[0] = data;
  Polynomial<double> p(coeffs);
  std::cout << "Encrypted polynomial: " << p << "\n";

  std::vector<Key> keys;
  for (int i = 0; i < n; i++) {
    double x, y;
    x = (double)rand() / RAND_MAX;
    y = p(x);

    keys.push_back(Key(x,y));
  }
  return keys;
}

double decrypt(std::vector<Key> keys) {
  std::vector<std::pair<double, double>> pairs;
  for (auto key : keys) pairs.push_back(key.make_pair());
  Polynomial<double> p = Polynomial<double>::FromPoints(pairs);
  std::cout << "Reconstructed polynomial: " << p << std::endl;

  return p(0);

}

void save_keys_to_file(std::vector<std::pair<Key, std::string>> keys) {
  for (auto [key, name] : keys) {
    std::ofstream file(name);
    file << key;
  }
}

Key load_key_from_file(std::string name) {
  std::ifstream file(name);
  Key key;
  file >> key;
  return key;
}
