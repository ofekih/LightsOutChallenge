#include "LightsOutBoard.hpp"
using namespace lightsout;

#include <boost/python.hpp>
using namespace boost::python;

#include <ostream>

template <uint64_t W, uint64_t H>
void defineBoard()
{
	std::ostringstream o;
	o << "LightsOutBoard" << W << "x" << H;

	class_<LightsOutBoard<W, H>>(o.str().c_str())
		.def(init<LightsOutBoard<W, H>>())
		.def("clone", &LightsOutBoard<W, H>::clone)
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
		.def("get_still_on", &LightsOutBoard<W, H>::getStillOn)
		.def("mutate", &LightsOutBoard<W, H>::mutate)
		.def("mutate_list", &LightsOutBoard<W, H>::mutateList)
		.def("mutate_coords", &LightsOutBoard<W, H>::mutateCoords)
		.def("mutate_board", &LightsOutBoard<W, H>::mutateBoard)
		.def("mutate_random", &LightsOutBoard<W, H>::mutateRandom)
		.def("mutate_random_block", &LightsOutBoard<W, H>::mutateRandomBlock)
		.def("keep_relevant_mutations", &LightsOutBoard<W, H>::keepRelevantMutations)
		.def("get_num_on", &LightsOutBoard<W, H>::getNumOn)
		.def("get_percentage_on", &LightsOutBoard<W, H>::getPercentageOn)
		.def("get_cost", &LightsOutBoard<W, H>::getCost)
		.def("get_num_parameters", &LightsOutBoard<W, H>::getNumParameters)
		.def("single_crossover", &LightsOutBoard<W, H>::singleCrossover)
		.def("pretty", &LightsOutBoard<W, H>::pretty)
		.def(self_ns::str(self_ns::self))
		.def("row_reduce", &LightsOutBoard<W, H>::rowReduce)
		.def("solve_lin_alg", &LightsOutBoard<W, H>::solveLinAlg)
		.def("solve_lin_alg_other", &LightsOutBoard<W, H>::solveLinAlgOther)
		.def("number_of_nullspace", &LightsOutBoard<W, H>::numberOfNullSpace)
	;
}


BOOST_PYTHON_MODULE(LightsOutBoard)
{
	defineBoard<8uLL, 8uLL>();
	defineBoard<4uLL, 3uLL>();
	defineBoard<1000uLL, 1000uLL>();
	defineBoard<5uLL, 5uLL>();

	defineBoard<500uLL, 500uLL>();
	defineBoard<200uLL, 200uLL>();
	defineBoard<100uLL, 100uLL>();
	defineBoard<50uLL, 50uLL>();
	defineBoard<20uLL, 20uLL>();
	defineBoard<10uLL, 10uLL>();
}
