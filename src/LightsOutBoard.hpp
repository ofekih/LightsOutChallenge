#ifndef LightsOutBoard_H
#define LightsOutBoard_H

#include <bitset>
#include <cstdint>

#include <iostream>

namespace lightsout
{
template <uint64_t WIDTH, uint64_t HEIGHT>
class LightsOutBoard
{
private:
	static constexpr uint64_t MASK_CENTER = WIDTH + 1uLL;
	typedef std::bitset<WIDTH * (HEIGHT + 2uLL)> BOARD_TYPE;
	BOARD_TYPE board;

public:
	LightsOutBoard() noexcept;
	LightsOutBoard(const BOARD_TYPE& board) noexcept;
	LightsOutBoard(const LightsOutBoard& board) noexcept;

	bool isOn(uint64_t location) const noexcept;
	bool isOnCoords(uint64_t x, uint64_t y) const noexcept;
	void flip(uint64_t location) noexcept;
	void flipCoords(uint64_t x, uint64_t y) noexcept;
	uint64_t getNumOn() const noexcept;
	void set(uint64_t location, bool on) noexcept;
	void setCoords(uint64_t x, uint64_t y, bool on) noexcept;
	void setAll(bool on) noexcept;
	void prettyPrint() const noexcept;
	std::ostream& print(std::ostream& out) const noexcept;

private:
	static BOARD_TYPE getCenterToggleMask() noexcept;
	static BOARD_TYPE getLeftEdgeToggleMask() noexcept;
	static BOARD_TYPE getRightEdgeToggleMask() noexcept;
	static BOARD_TYPE getLeftEdgeMask() noexcept;
	static BOARD_TYPE getRightEdgeMask() noexcept;

	BOARD_TYPE CENTER_TOGGLE_MASK;
	BOARD_TYPE LEFT_EDGE_TOGGLE_MASK;
	BOARD_TYPE RIGHT_EDGE_TOGGLE_MASK;
	BOARD_TYPE LEFT_EDGE_MASK;
	BOARD_TYPE RIGHT_EDGE_MASK;
};

template <uint64_t W, uint64_t H>
LightsOutBoard<W, H>::LightsOutBoard(const BOARD_TYPE& board) noexcept
	: board(board),
	  CENTER_TOGGLE_MASK(getCenterToggleMask()),
	  LEFT_EDGE_TOGGLE_MASK(getLeftEdgeToggleMask()),
	  RIGHT_EDGE_TOGGLE_MASK(getRightEdgeToggleMask()),
	  LEFT_EDGE_MASK(getLeftEdgeMask()),
	  RIGHT_EDGE_MASK(getRightEdgeMask())
{
}

template <uint64_t W, uint64_t H>
LightsOutBoard<W, H>::LightsOutBoard() noexcept
	: LightsOutBoard(BOARD_TYPE{})
{
}

template <uint64_t W, uint64_t H>
LightsOutBoard<W, H>::LightsOutBoard(const LightsOutBoard& board) noexcept
	: LightsOutBoard(board.board)
{
}

template <uint64_t W, uint64_t H>
bool LightsOutBoard<W, H>::isOn(uint64_t location) const noexcept
{
	return board[location + 2uLL * W];
}

template <uint64_t W, uint64_t H>
bool LightsOutBoard<W, H>::isOnCoords(uint64_t x, uint64_t y) const noexcept
{
	return isOn(x + W * y);
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::set(uint64_t location, bool on) noexcept
{
	board[location + 2uLL * W] = on;
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
void LightsOutBoard<W, H>::flip(uint64_t location) noexcept
{
	location += 2uLL * W;

	if (LEFT_EDGE_MASK[location])
	{
		board ^= LEFT_EDGE_TOGGLE_MASK << (location - MASK_CENTER);
		return;
	}

	if (RIGHT_EDGE_MASK[location])
	{
		board ^= RIGHT_EDGE_TOGGLE_MASK << (location - MASK_CENTER);
		return;
	}

	board ^= CENTER_TOGGLE_MASK << (location - MASK_CENTER);
}

template <uint64_t W, uint64_t H>
void LightsOutBoard<W, H>::flipCoords(uint64_t x, uint64_t y) noexcept
{
	flip(x + W * y);
}

template <uint64_t W, uint64_t H>
uint64_t LightsOutBoard<W, H>::getNumOn() const noexcept
{
	return (board >> (2uLL * W)).count();
}

template <uint64_t W, uint64_t H>
typename LightsOutBoard<W, H>::BOARD_TYPE LightsOutBoard<W, H>::getCenterToggleMask() noexcept {
	typename LightsOutBoard<W, H>::BOARD_TYPE centerToggleMask;

	centerToggleMask.set(MASK_CENTER - W); // bottom
	centerToggleMask.set(MASK_CENTER - 1uLL); // left
	centerToggleMask.set(MASK_CENTER); // center
	centerToggleMask.set(MASK_CENTER + 1uLL); // right
	centerToggleMask.set(MASK_CENTER + W); // top

	return centerToggleMask;
}

template <uint64_t W, uint64_t H>
typename LightsOutBoard<W, H>::BOARD_TYPE LightsOutBoard<W, H>::getLeftEdgeToggleMask() noexcept {
	auto leftEdgeToggleMask = getCenterToggleMask();

	leftEdgeToggleMask.reset(MASK_CENTER - 1uLL); // left

	return leftEdgeToggleMask;
}

template <uint64_t W, uint64_t H>
typename LightsOutBoard<W, H>::BOARD_TYPE LightsOutBoard<W, H>::getRightEdgeToggleMask() noexcept {
	auto rightEdgeToggleMask = getCenterToggleMask();

	rightEdgeToggleMask.reset(MASK_CENTER + 1uLL); // right

	return rightEdgeToggleMask;
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
void LightsOutBoard<W, H>::prettyPrint() const noexcept {
	for (uint64_t y = 0uLL; y < H; ++y)
	{
		for (uint64_t x = 0uLL; x < W; ++x)
		{
			char symbol = isOnCoords(x, y) ? 'O' : '-';
			std::cout << ' ' << symbol;
		}
		std::cout << '\n';
	}
}


template <uint64_t W, uint64_t H>
std::ostream& LightsOutBoard<W, H>::print(std::ostream& out) const noexcept {
	out << board.to_string().substr(0uLL, W * H);
	return out;
}

template <uint64_t W, uint64_t H>
std::ostream& operator<<(std::ostream& out, const LightsOutBoard<W, H>& board)
{
	return board.print(out);
}

}

#endif
