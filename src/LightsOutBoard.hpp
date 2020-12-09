#ifndef LightsOutBoard_H
#define LightsOutBoard_H

#include <bitset>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <random>
#include <string>
#include <sstream>

#include <boost/python.hpp>

namespace lightsout
{
template <uint64_t WIDTH, uint64_t HEIGHT>
class LightsOutBoard
{
private:
	typedef std::bitset<WIDTH * HEIGHT> BOARD_TYPE;
	BOARD_TYPE board, outputVertices;
	std::default_random_engine generator;

public:
	LightsOutBoard() noexcept;
	LightsOutBoard(const BOARD_TYPE& board) noexcept;
	LightsOutBoard(const BOARD_TYPE& board, const BOARD_TYPE& outputVertices) noexcept;
	LightsOutBoard(const LightsOutBoard& board) noexcept;

	LightsOutBoard clone() const noexcept;

	bool isOn(uint64_t location) const noexcept;
	bool isOnCoords(uint64_t x, uint64_t y) const noexcept;
	bool isOutputVertex(uint64_t location) const noexcept;
	bool isOutputVertexCoords(uint64_t x, uint64_t y) const noexcept;
	void flip(uint64_t location) noexcept;
	void flipList(const boost::python::list& list) noexcept;
	void flipCoords(uint64_t x, uint64_t y) noexcept;
	void flipBoard(const LightsOutBoard& lightsOutBoard) noexcept;
	void mutate(uint64_t location) noexcept;
	void mutateList(const boost::python::list& list) noexcept;
	void mutateCoords(uint64_t x, uint64_t y) noexcept;
	void mutateBoard(const LightsOutBoard& lightsOutBoard) noexcept;
	void mutateRandom(double probability) noexcept;
	uint64_t getNumOn() const noexcept;
	double getPercentageOn() const noexcept;
	double getCost(const LightsOutBoard& parameters) const noexcept;
	void set(uint64_t location, bool on) noexcept;
	void setList(const boost::python::list& list) noexcept;
	void setCoords(uint64_t x, uint64_t y, bool on) noexcept;
	void setAll(bool on) noexcept;
	void setRandom(double probability) noexcept;
	void setOutputVertex(uint64_t location, bool on) noexcept;
	void setOutputVertexList(const boost::python::list& list) noexcept;
	void setOutputVertexCoords(uint64_t x, uint64_t y, bool on) noexcept;
	void setAllOutputVertices(bool on) noexcept;
	void setRandomOutputVertices(double probability) noexcept;
	void setRandomSeed(uint64_t seed) noexcept;
	std::string pretty() const noexcept;
	std::ostream& print(std::ostream& out) const noexcept;

private:
	static BOARD_TYPE getLeftEdgeMask() noexcept;
	static BOARD_TYPE getRightEdgeMask() noexcept;

	void mutateBitset(const BOARD_TYPE& board) noexcept;
	void flipBitset(const BOARD_TYPE& board) noexcept;
	void setRandomBitset(BOARD_TYPE& board, double probability) noexcept;

	BOARD_TYPE LEFT_EDGE_MASK;
	BOARD_TYPE RIGHT_EDGE_MASK;
};

template <uint64_t W, uint64_t H>
LightsOutBoard<W, H>::LightsOutBoard(const BOARD_TYPE& board, const BOARD_TYPE& outputVertices) noexcept
	: board(board),
	  outputVertices(outputVertices),
	  LEFT_EDGE_MASK(getLeftEdgeMask()),
	  RIGHT_EDGE_MASK(getRightEdgeMask()),
	  generator(std::random_device()())
{
}

template <uint64_t W, uint64_t H>
LightsOutBoard<W, H>::LightsOutBoard() noexcept
	: LightsOutBoard(BOARD_TYPE{}, BOARD_TYPE{})
{
}

template <uint64_t W, uint64_t H>
LightsOutBoard<W, H>::LightsOutBoard(const LightsOutBoard& board) noexcept
	: LightsOutBoard(board.board, board.outputVertices)
{
}

template <uint64_t W, uint64_t H>
LightsOutBoard<W, H> LightsOutBoard<W, H>::clone() const noexcept
{
	return LightsOutBoard<W, H>(*this);
}

template <uint64_t W, uint64_t H>
bool LightsOutBoard<W, H>::isOn(uint64_t location) const noexcept
{
	return board[location];
}

template <uint64_t W, uint64_t H>
bool LightsOutBoard<W, H>::isOnCoords(uint64_t x, uint64_t y) const noexcept
{
	return isOn(x + W * y);
}

template <uint64_t W, uint64_t H>
bool LightsOutBoard<W, H>::isOutputVertex(uint64_t location) const noexcept
{
	return outputVertices[location];
}

template <uint64_t W, uint64_t H>
bool LightsOutBoard<W, H>::isOutputVertexCoords(uint64_t x, uint64_t y) const noexcept
{
	return isOutputVertex(x + W * y);
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::set(uint64_t location, bool on) noexcept
{
	board[location] = on;
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::setList(const boost::python::list& list) noexcept
{
	auto length = boost::python::len(list);
	for (uint64_t i = 0uLL; i < length; ++i)
	{
		board[i] = boost::python::extract<bool>(list[i]);
	}
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::setCoords(uint64_t x, uint64_t y, bool on) noexcept
{
	return set(x + W * y, on);
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::setAll(bool on) noexcept
{
	if (on)
	{
		board.set();
	} else
	{
		board.reset();
	}
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::setRandom(double probability) noexcept
{
	setRandomBitset(board, probability);
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::setRandomSeed(uint64_t seed) noexcept
{
	generator.seed(seed);
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::setOutputVertex(uint64_t location, bool on) noexcept
{
	outputVertices[location] = on;
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::setOutputVertexList(const boost::python::list& list) noexcept
{
	auto length = boost::python::len(list);
	for (uint64_t i = 0uLL; i < length; ++i)
	{
		outputVertices[i] = boost::python::extract<bool>(list[i]);
	}
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::setOutputVertexCoords(uint64_t x, uint64_t y, bool on) noexcept
{
	return setOutputVertex(x + W * y, on);
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::setAllOutputVertices(bool on) noexcept
{
	if (on)
	{
		outputVertices.set();
	} else
	{
		outputVertices.reset();
	}
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::setRandomOutputVertices(double probability) noexcept
{
	setRandomBitset(outputVertices, probability);
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::setRandomBitset(BOARD_TYPE& board, double probability) noexcept
{
	static std::exponential_distribution<double> dist(1.0);

	// from my testing, this new method is faster than the old method for all probabilities up to 0.8.
	// this way, it'll always be faster than the old method
	if (probability > 0.5)
	{
		setRandomBitset(board, 1.0 - probability);
		board = ~board;
		return;
	}

	double average_step_size = 1.0 / probability;

	board.reset();

	for (double i = average_step_size * dist(generator); i < W * H; i += average_step_size * dist(generator))
	{
		board[static_cast<uint64_t>(i)] = true;
	}
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::flip(uint64_t location) noexcept
{
	BOARD_TYPE board;
	board[location] = true;
	flipBitset(board);
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::flipList(const boost::python::list& list) noexcept
{
	LightsOutBoard<W, H> board;
	board.setList(list);
	flipBoard(board);
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::flipCoords(uint64_t x, uint64_t y) noexcept
{
	flip(x + W * y);
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::flipBitset(const BOARD_TYPE& otherBoard) noexcept
{
	board ^= otherBoard; // toggle centers
	board ^= (otherBoard << W); // toggle above
	board ^= (otherBoard >> W); // toggle below
	board ^= ((otherBoard & ~LEFT_EDGE_MASK) >> 1uLL); // toggle left if not on left edge
	board ^= ((otherBoard & ~RIGHT_EDGE_MASK) << 1uLL); // toggle right if not on right edge
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::flipBoard(const LightsOutBoard& lightsOutBoard) noexcept
{
	flipBitset(lightsOutBoard.board);
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::mutate(uint64_t location) noexcept
{
	BOARD_TYPE board;
	board[location] = true;
	mutateBitset(board);
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::mutateList(const boost::python::list& list) noexcept
{
	LightsOutBoard<W, H> board;
	board.setList(list);
	mutateBoard(board);
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::mutateCoords(uint64_t x, uint64_t y) noexcept
{
	mutate(x + W * y);
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::mutateBitset(const BOARD_TYPE& otherBoard) noexcept
{
	board ^= otherBoard;
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::mutateBoard(const LightsOutBoard& lightsOutBoard) noexcept
{
	mutateBitset(lightsOutBoard.board);
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::mutateRandom(double probability) noexcept
{
	static std::exponential_distribution<double> dist(1.0);

	if (probability > 0.5)
	{
		mutateRandom(1.0 - probability);
		board = ~board;
		return;
	}

	double average_step_size = 1.0 / probability;

	for (double i = average_step_size * dist(generator); i < W * H; i += average_step_size * dist(generator))
	{
		board[static_cast<uint64_t>(i)] = !board[static_cast<uint64_t>(i)];
	}
}

template <uint64_t W, uint64_t H>
uint64_t LightsOutBoard<W, H>::getNumOn() const noexcept
{
	return (board & ~outputVertices).count();
}

template <uint64_t W, uint64_t H>
double LightsOutBoard<W, H>::getPercentageOn() const noexcept
{
	return getNumOn() / static_cast<double>(W * H);
}

template <uint64_t W, uint64_t H>
double LightsOutBoard<W, H>::getCost(const LightsOutBoard& parameters) const noexcept
{
	auto copy = *this;
	copy.flipBoard(parameters);
	return copy.getPercentageOn();
}

template <uint64_t W, uint64_t H>
typename LightsOutBoard<W, H>::BOARD_TYPE LightsOutBoard<W, H>::getLeftEdgeMask() noexcept {
	typename LightsOutBoard<W, H>::BOARD_TYPE leftEdgeMask;

	for (uint64_t location = 0uLL; location < leftEdgeMask.size(); location += W)
	{
		leftEdgeMask.set(location);
	}

	return leftEdgeMask;
}

template <uint64_t W, uint64_t H>
typename LightsOutBoard<W, H>::BOARD_TYPE LightsOutBoard<W, H>::getRightEdgeMask() noexcept {
	return getLeftEdgeMask() << (W - 1uLL);
}

template <uint64_t W, uint64_t H>
std::string LightsOutBoard<W, H>::pretty() const noexcept {
	std::stringstream out;
	for (uint64_t y = 0uLL; y < H; ++y)
	{
		for (uint64_t x = 0uLL; x < W; ++x)
		{
			char symbol = isOutputVertexCoords(x, y) ? (isOnCoords(x, y) ? 'o' : 'x') : (isOnCoords(x, y) ? 'O' : 'X');
			out << ' ' << symbol;
		}

		out << '\n';
	}
	return out.str();
}


template <uint64_t W, uint64_t H>
std::ostream& LightsOutBoard<W, H>::print(std::ostream& out) const noexcept {
	out << board.to_string();
	return out;
}

template <uint64_t W, uint64_t H>
std::ostream& operator<<(std::ostream& out, const LightsOutBoard<W, H>& board)
{
	return board.print(out);
}

}

#endif
