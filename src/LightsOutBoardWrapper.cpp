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
		.def("is_on", &LightsOutBoard<W, H>::isOn)
		.def("is_on_coords", &LightsOutBoard<W, H>::isOnCoords)
		.def("is_output_vertex", &LightsOutBoard<W, H>::isOutputVertex)
		.def("is_output_vertex_coords", &LightsOutBoard<W, H>::isOutputVertexCoords)
		.def("set", &LightsOutBoard<W, H>::set)
		.def("set_list", &LightsOutBoard<W, H>::setList)
		.def("set_coords", &LightsOutBoard<W, H>::setCoords)
		.def("set_all", &LightsOutBoard<W, H>::setAll)
		.def("set_random", &LightsOutBoard<W, H>::setRandom)
		.def("set_output_vertex", &LightsOutBoard<W, H>::setOutputVertex)
		.def("set_output_vertex_list", &LightsOutBoard<W, H>::setOutputVertexList)
		.def("set_output_vertex_coords", &LightsOutBoard<W, H>::setOutputVertexCoords)
		.def("set_all_output_vertex", &LightsOutBoard<W, H>::setAllOutputVertices)
		.def("set_random_output_vertices", &LightsOutBoard<W, H>::setRandomOutputVertices)
		.def("set_random_seed", &LightsOutBoard<W, H>::setRandomSeed)
		.def("flip", &LightsOutBoard<W, H>::flip)
		.def("flip_list", &LightsOutBoard<W, H>::flipList)
		.def("flip_coords", &LightsOutBoard<W, H>::flipCoords)
		.def("flip_board", &LightsOutBoard<W, H>::flipBoard)
		.def("mutate", &LightsOutBoard<W, H>::mutate)
		.def("mutate_list", &LightsOutBoard<W, H>::mutateList)
		.def("mutate_coords", &LightsOutBoard<W, H>::mutateCoords)
		.def("mutate_board", &LightsOutBoard<W, H>::mutateBoard)
		.def("get_num_on", &LightsOutBoard<W, H>::getNumOn)
		.def("pretty", &LightsOutBoard<W, H>::pretty)
		.def(self_ns::str(self_ns::self))
	;
}


BOOST_PYTHON_MODULE(LightsOutBoard)
{
	defineBoard<8uLL, 8uLL>();
	defineBoard<4uLL, 3uLL>();
	defineBoard<1000uLL, 1000uLL>();
}
