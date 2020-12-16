import random
from LightsOutBoard import LightsOutBoard1000x1000, LightsOutBoard8x8, LightsOutBoard4x3, LightsOutBoard5x5

class GeneticAlgorithm:
  def __init__(self, board: 'LightsOutBoardnxm', init_population: ['LightsOutBoardnxm']):
    self.population_size = len(init_population)
    if self.population_size % 2 != 0:
      raise ValueError('Population size must be an even number.')
    self.population = init_population
    self.board_size = board.getNumParameters()

  def _selection(threshold: float):
    fitted_parents = []
    for p in self.population:
      if board.getCost(p) <= threshold:
        new_population.append(p)
    return fitted_parents

  def _cross_over(parents):
    offsprings = []
    num_parents = len(parents)
    while len(offsprings) < self.population_size:
      mom, dad = random.sample(parents, 2)
      cross_pos = random.randrange(0, self.board_size)
      offsprings.append(mom.single_crossover(dad, cross_pos))
      offsprings.append(dad.single_crossover(mom, cross_pos))
    return offsprings


  def _mutation(offsprings):
    num_mutation = random.randrange(0, self.population_size)
    to_be_mutated = random.sample(offsprings, num_mutation)
    for m in to_be_mutated:
      m.mutate_random(random.uniform(0, 0.1))

  def run_once():
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