#include "algebra.hpp"
#include <algorithm>

std::string superscript(std::string s) {
  std::string o;
  for (char c : s)
    switch (c) {
      case '0': o.append("⁰"); break;
      case '1': o.append("¹"); break;
      case '2': o.append("²"); break;
      case '3': o.append("³"); break;
      case '4': o.append("⁴"); break;
      case '5': o.append("⁵"); break;
      case '6': o.append("⁶"); break;
      case '7': o.append("⁷"); break;
      case '8': o.append("⁸"); break;
      case '9': o.append("⁹"); break;
      default: o.append(std::to_string(c)); break;
    }
  return o;
}
