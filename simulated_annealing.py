import math, random

from LightsOutBoard import LightsOutBoard1000x1000

class SimulatedAnnealing:

	def __init__(self, board: 'LightsOutBoardnxm', initial_temperature: float = 1.0, temperature_multiplier: float = 0.999, current_parameters: 'LightsOutBoardnxm' = None, maximum_mutation_probability = 0.01, minimum_mutation_probability = 0.00001):
		self._board = board
		self.initial_temperature = self.current_temperature = initial_temperature
		self.temperature_multiplier = temperature_multiplier

		self.current_parameters = current_parameters if current_parameters else self._board.clone()

		self.maximum_mutation_probability = maximum_mutation_probability
		self.minimum_mutation_probability = minimum_mutation_probability

		self.best_parameters = self.current_parameters.clone()
		self.best_cost = self.current_cost = self._board.get_cost(self.best_parameters)

	def _get_mutated_parameters(self) -> 'mutated parameters':
		mutation_probability = self.minimum_mutation_probability + (self.maximum_mutation_probability - self.minimum_mutation_probability) * self.current_temperature

		mutated_parameters = self.current_parameters.clone()
		mutated_parameters.mutate_random(mutation_probability)

		return mutated_parameters

	def _get_acceptance_probability(self, cost: float) -> float:
		if cost < self.current_cost:
			return 1.0 # definitely accept

		return math.exp((self.current_cost - cost) / self.current_temperature)

	def run_one_cycle(self):
		mutated_parameters = self._get_mutated_parameters()
		cost = self._board.get_cost(mutated_parameters)

		acceptance_probability = self._get_acceptance_probability(cost)

		if random.random() < acceptance_probability:
			self.current_parameters = mutated_parameters
			self.current_cost = cost

		if cost < self.best_cost:
			self.best_parameters = mutated_parameters
			self.best_cost = cost

		self.current_temperature *= self.temperature_multiplier


if __name__ == '__main__':
	board = LightsOutBoard1000x1000()
	board.set_random(0.5)

	parameters = LightsOutBoard1000x1000()

	sa = SimulatedAnnealing(board, .0001, 0.999, current_parameters = parameters)
	for i in range(1000000):
		print(f'{i:5d}: {sa.current_temperature:.6g} {sa.current_cost:.6f} {sa.best_cost:.6f}')
		sa.run_one_cycle()


