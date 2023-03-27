#ifndef NEURON_GENOME_H
#define NEURON_GENOME_H

#include <vector>
#include "ascii.h"
#include "SFML/Graphics.hpp"

struct Genome;


struct Genome
{
	std::vector<std::string> genome;
	void createRandomGenome(unsigned num_genes, unsigned inner_neurons, float mutation_rate, unsigned seed)
	{
		srand(seed + (unsigned)time(NULL));
		std::string genome = "";
		for (int index = 0; index < (int)num_genes; index++)
		{
			
			std::string gene = "";
			
			for (int i = 0; i < 4; i++)
			{
				gene = gene + hex[rand() % 128];
			}
			this->genome.push_back(gene);
		}
	}
};

#endif


