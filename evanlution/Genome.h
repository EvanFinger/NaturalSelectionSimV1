#ifndef NEURON_GENOME_H
#define NEURON_GENOME_H

#include <vector>
#include "ascii.h"
#include "SFML/Graphics.hpp"

struct Genome;


struct Genome
{
	std::vector<std::string> genome;
	
	Genome(unsigned num_genes, unsigned seed)
	{
		srand(seed + (unsigned)time(NULL)); //seed for generating a random gene
		std::string genome = "";
		for (int index = 0; index < (int)num_genes; index++) //loops n times for each gene that must be created
		{
			this->genome.push_back(this->randomGene()); //Pushes newly create gene into the genome vector
		}
	}

	std::string randomGene() //generates a randowm string of 4 hexadecimals (gene)
	{
		std::string gene = "";

		for (int i = 0; i < 4; i++)
		{
			std::string strin = hex[rand() % 128];
			//std::cout << strin << "\n";
			gene = gene + strin;
		}

		return gene;
	}

	void createChildGenome(std::vector<std::string> parent_genome_1, std::vector<std::string> parent_genome_2, float mutation_chance)
	{
		srand((unsigned)time(NULL) + rand());
		for (size_t i = 0; i < parent_genome_1.size(); i++)
		{	
			unsigned num = rand() % 2;
			//DETERMINE WHICH PARENT THE GENE IS INHERITED FROM
			if (num == 0)//PARENT 1
			{
				//DETERMIN OF MUTATION OCCURS
				if (rand() % 100 < mutation_chance * 100)
				{
					this->genome.push_back(this->randomGene());
				}
				else
				{
					this->genome.push_back(parent_genome_1[i]);
				}
			}
			else//PARENT 2
			{
				//DETERMINE IF MUTATION OCCURS
				if (rand() % 100 < mutation_chance * 100)
				{
					this->genome.push_back(this->randomGene());
				}
				else
				{
				this->genome.push_back(parent_genome_2[i]);
				}
			}
		}
	}
};

#endif


