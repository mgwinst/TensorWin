g++-15 -std=gnu++23 test_main.cc -I../core/ \
    ../core/view.cc \
    tensor_properties.cc tensor_construction_assignment.cc tensor_functions.cc \
    buffer_properties.cc tensor_broadcasting.cc \
    -lgtest -lgtest_main && ./a.out
