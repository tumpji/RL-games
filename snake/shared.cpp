#include <boost/python/numpy.hpp>

#include "snake.h"

namespace p = boost::python;
namespace np = boost::python::numpy;


int init_lib () {
    Py_Initialize();
    np::initialize();
}

int test () {
    Snake<DEF_BOARD_SIZE_X,DEF_BOARD_SIZE_Y,1> h;

    return 1;
}


