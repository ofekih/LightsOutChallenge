#include "LightsOutBoard.hpp"
using namespace lightsout;

#include <boost/python.hpp>
using namespace boost::python;

#include <ostream>

template <uint64_t W, uint64_t H>
void defineBoard()
{
	std::ostringstream o;
	o << "LightsOutBoard";
	o << W;
	o << "x";
	o << H;

	class_<LightsOutBoard<W, H>>(o.str().c_str())
		.def(init<LightsOutBoard<W, H>>())
	    .def("isOn", &LightsOutBoard<W, H>::isOn)
	    .def("isOnCoords", &LightsOutBoard<W, H>::isOnCoords)
	    .def("set", &LightsOutBoard<W, H>::set)
	    .def("setCoords", &LightsOutBoard<W, H>::setCoords)
	    .def("setAll", &LightsOutBoard<W, H>::setAll)
	    .def("flip", &LightsOutBoard<W, H>::flip)
	    .def("flipCoords", &LightsOutBoard<W, H>::flipCoords)
	    .def("getNumOn", &LightsOutBoard<W, H>::getNumOn)
	    .def("prettyPrint", &LightsOutBoard<W, H>::prettyPrint)
	    .def(self_ns::str(self_ns::self))
	;
}


BOOST_PYTHON_MODULE(LightsOutBoard)
{
    defineBoard<8uLL, 8uLL>();
    defineBoard<4uLL, 3uLL>();
}


// char const* greet()
// {
// 	return "hello, world!";
// }

// BOOST_PYTHON_MODULE(greeter)
// {
// 	boost::python::def("greet", greet);
// }