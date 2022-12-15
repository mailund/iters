#include <iostream>
#include <vector>

// Iterating in reverse...
template <typename iterable> struct reverse_range {
  iterable wrapped;
  auto begin() { return std::rbegin(wrapped); }
  auto end() { return std::rend(wrapped); }
};

template <typename iterable>
struct reverse_range<iterable> reverse(iterable &&wrapped) {
  return reverse_range<iterable>{wrapped}; // FIXME: check if I copy here!!!
}

// Enumerate
template <typename iterator>
struct enumerate_iterator {
  iterator wrapped;
  int index;

  enumerate_iterator(iterator w) : wrapped{w}, index{0} {}
  enumerate_iterator(iterator w, int idx) : wrapped{w}, index{idx} {}

  auto operator*() { return std::make_pair(index, *wrapped); }
  auto operator++() {
    ++wrapped;
    ++index;
    return *this;
  }
  bool operator!=(enumerate_iterator &other) {
    return this->wrapped != other.wrapped;
  }
};
template <typename iterable> struct enumerate_range {
  iterable wrapped;
  auto begin() { return enumerate_iterator(std::begin(wrapped)); }
  auto end() { return enumerate_iterator(std::end(wrapped)); }
};
template <typename iterable>
struct enumerate_range<iterable> enumerate(iterable &&wrapped) {
  return enumerate_range<iterable>{wrapped};
}


int main() {
  std::vector<int> v{1, 2, 3, 4, 5};

  for (auto i : v) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;

  for (auto i : reverse(v)) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;

  for (auto [i, j] : enumerate(v)) {
    std::cout << '(' << i << ',' << j << ") ";
  }
  std::cout << std::endl;

  for (auto [i, j] : enumerate(reverse(v))) {
    std::cout << '(' << i << ',' << j << ") ";
  }
  std::cout << std::endl;

/* This doesn't work yet, because enumerate doesn't know how to
 iterate in reverse. That would require that I figure out the
 length of the iteration to begin with... */
#if 0
  for (auto [i, j] : reverse(enumerate(v))) {
    std::cout << '(' << i << ',' << j << ") ";
  }
  std::cout << std::endl;
#endif

  return 0;
}