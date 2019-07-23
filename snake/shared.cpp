#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

#include "snake.h"

namespace p = boost::python;
namespace np = boost::python::numpy;

/*
int main(int argc, char **argv) {
    //PyImport_AppendInittab(PYINIT_NAME_S, PYINIT_NAME);
    Py_Initialize();
    //np::initialize();
}
*/

char const* test () {
    Snake<DEF_BOARD_SIZE_X,DEF_BOARD_SIZE_Y,1> h;

    return "hellp wordsf";
}

np::ndarray create_new_games(int ngames) {
    // for now it returns only zeros ngames x 10 x 10
    np::dtype dt = np::dtype::get_builtin<int>();
    np::ndarray out = np::zeros(p::make_tuple(ngames, 10, 10), dt);
    return out;
}

BOOST_PYTHON_MODULE(NAME)
{
    using namespace boost::python;

    np::initialize();

    def("test", test);
    def("create_new_games", create_new_games);
}









