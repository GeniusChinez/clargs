#include "clargs.cpp"
#include <iostream>

int main(int argc, char* const argv[]) {
    clargs::Arguments args;
    args.parse(argc, argv);
}
