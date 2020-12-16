import random
from LightsOutBoard import LightsOutBoard1000x1000, LightsOutBoard8x8, LightsOutBoard4x3, LightsOutBoard5x5

class GeneticAlgorithm:
  def __init__(self, init_population: ['LightsOutBoardnxm']):
    pass

if __name__ == '__main__':
  # TEST
  total = 5*5
  board1 = LightsOutBoard5x5()
  board1.set_list([0 for _ in range(25)])
  #board1.set_random(0.5)
  print(board1.pretty())
  board2 = LightsOutBoard5x5()
  board2.set_list([1 for _ in range(25)])
  #board2.set_random(0.5)
  print(board2.pretty())
  pos = 1
  board3 = board1.single_crossover(board2, pos)
  board4 = board2.single_crossover(board1, pos)
  print(board3.pretty())
  print(board4.pretty())