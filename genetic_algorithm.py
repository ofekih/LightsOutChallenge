import random, numpy
from LightsOutBoard import LightsOutBoard1000x1000, LightsOutBoard8x8, LightsOutBoard4x3, LightsOutBoard5x5

class GeneticAlgorithm:
  def __init__(self, board: 'LightsOutBoardnxm', init_population: ['LightsOutBoardnxm']):
    self.board_size = board.get_num_parameters()
    self.population_size = len(init_population)
    if self.population_size % 2 != 0:
      raise ValueError('Population size must be an even number.')
    self.population = init_population
    self.best = None
    self.best_cost = 1

  def _selection(self, threshold: float):
    fitted_parents = []
    for p in self.population:
      cost = board.get_cost(p)
      if cost <= threshold:
        fitted_parents.append(p)
        if cost < self.best_cost:
          self.best = p
          self.best_cost = cost
    return fitted_parents

  def _crossover(self, parents: ['LightsOutBoardnxm']):
    offsprings = []
    num_parents = len(parents)
    while len(offsprings) < self.population_size:
      mom, dad = random.sample(parents, 2)
      cross_pos = random.randrange(0, self.board_size)
      offsprings.append(mom.single_crossover(dad, cross_pos))
      offsprings.append(dad.single_crossover(mom, cross_pos))
    return offsprings

  def _mutation(self, offsprings: ['LightsOutBoardnxm']):
    num_mutation = random.randint(0, 3)
    to_be_mutated = random.sample(offsprings, num_mutation)
    for m in to_be_mutated:
      m.mutate_random(random.uniform(0, 0.1))
    return offsprings

  def evolve_once(self, selection_threshold: float):
    fitted_parents = self._selection(selection_threshold)
    offsprings = self._crossover(fitted_parents)
    self.population = self._mutation(offsprings)

  def full_evolution(self):
    iteration = 0
    f = lambda x: numpy.exp(-x**(0.01))
    while self.best_cost != 0:
      threshold = f(iteration)
      print(threshold)
      self.evolve_once(threshold)
      iteration += 1
      print(f'iteration: {iteration}; best_cost: {self.best_cost}')


if __name__ == '__main__':
  board = LightsOutBoard1000x1000()
  board.set_random(0.2)

  population_size = 100
  init_population = []
  for _ in range(population_size):
    b = LightsOutBoard1000x1000()
    b.set_random(random.random())
    init_population.append(b)
  
  ga = GeneticAlgorithm(board, init_population)
  ga.full_evolution()