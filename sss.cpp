#include <iostream>
#include "secret.hpp"
#include <math.h>

int main(int argc, char *argv[]) {
//  std::cout << Polynomial<double>::FromPoints({{1,1}, {2,2}, {3,3}}) << std::endl;
//  return 0;
  if (argc == 1) {
    std::cout << "Must provide positional argument\n";
    return -1;
  }
  if (std::string(argv[1]) == "encrypt") {
    uint64_t data, n, k;
    std::cout << "Enter (n,k): ";
    std::cin >> n >> k;
    std::cout << "  (n=" << n << ", k=" << k << ")" << std::endl;
    std::cout << "Enter data: ";
    std::cin >> data;
    std::cout << "  (data=" << data << ")" << std::endl;
    std::cout << "Encrypting..";

    std::vector<Key> keys = encrypt(data, n, k);
    std::vector<std::pair<Key, std::string>> knames(n);
    for (int i = 0; i < n; i++) knames[i] = std::make_pair(keys[i], std::string(std::to_string(i) + ".key"));

    save_keys_to_file(knames);
  }
  else if (std::string(argv[1]) == "decrypt") {
    int k;
    std::cout << "Enter (k): ";
    std::cin >> k;
    std::cout << "  (k=" << k << ")" << std::endl;
    std::vector<Key> keys;
    for (int i = 0; i < k; i++) {
      std::string fname;
      std::cout << "Enter file name (#" << i << ", default=" << i << ".key): ";
      std::cin >> fname;
      if (fname == "") fname = std::to_string(i) + ".key";
      Key k = load_key_from_file(fname);
      keys.push_back(k);
    }

    auto data = decrypt(keys);
    std::cout << "Data = " << data << std::endl;
  }
}
