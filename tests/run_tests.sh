clang++ -std=c++23 test_main.cpp -I../core/ \
    ../core/view.cpp ../core/utils.cpp \
    tensor_properties.cpp tensor_construction_assignment.cpp tensor_functions.cpp \
    buffer_properties.cpp \
    -lgtest -lgtest_main && ./a.out
