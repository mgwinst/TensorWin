#!/bin/bash

clang++ -std=c++23 -ltbb main.cc ./core/view.cc && ./a.out
#g++ -std=gnu++23 main.cc ./core/view.cc && ./a.out


