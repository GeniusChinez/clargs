#include "clargs.cpp"
#include <iostream>

int main(int argc, char* const argv[]) {
  auto args = clargs::get_arguments(argc, argv);
  const auto& naked_values = args.get_naked_values();

  for (const auto& value : naked_values) {
    std::cout <<  "naked: " << value << "\n";
  }
}
