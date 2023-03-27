#include "stdafx.h"
#include "neuralNetwork.h"


//************************* Neuron Class *************************


Neuron::Neuron(unsigned type, unsigned id)
{
	this->p_outVal = 0;
	this->neuronType = type;
	this->neuronID = id;
	this->hasConnection = false;
}

const std::vector<Connection*> Neuron::getConnections() const
{
	return this->p_connections;
}

double Neuron::getOutput() const
{
	return this->p_outVal;
}

double Neuron::transferFunction(double input)
{
	return tanh(input);
}

void Neuron::recieve(double input)
{
	this->p_outVal += input;
	//std::cout <<this->neuronType<<" "<<this->neuronID<<" " <<"RECIEVED : " << input << " CURR OUT : " << this->p_outVal << "\n";
}

void Neuron::generateNewConnection(Neuron* _to, double _weight)
{
	this->p_connections.push_back(new Connection());
	this->p_connections.back()->target_Neuron = _to;
	this->p_connections.back()->weight = _weight;
	this->p_connections.back()->target_Neuron->hasConnection = true;
	this->hasConnection = true;
}

void Neuron::feedForward()
{
	for (size_t connection = 0; connection < this->p_connections.size(); connection++)
	{
		p_connections[connection]->target_Neuron->recieve(this->p_outVal * p_connections[connection]->weight);
	}
}

void Neuron::calculateOutput()
{
	this->p_outVal = this->transferFunction(this->p_outVal);
	//std::cout <<this->neuronType << " " << this->neuronID << " " << "CALCulated OUT : " << this->p_outVal << "\n";
}

void Neuron::setInputNeuron(double input)
{
	this->p_outVal = input;
	//std::cout <<this->neuronType << " " << this->neuronID << " " << "SET INPUT: " << this->p_outVal<<"\n";
}

//************************* Net Class *************************


Net::Net(const std::vector<unsigned>& topology, Genome* genome)
{
	this->genome = genome;

	unsigned numLayers = static_cast<unsigned>(topology.size());
	//create layers using topology
	for (unsigned layerID = 0; layerID < numLayers; layerID++)
	{
		p_layers.push_back(Layer());

		//fill created layer with neurons
		for (unsigned neuronID = 0; neuronID <= topology[layerID]; neuronID++)
		{
			p_layers.back().push_back(new Neuron(layerID, neuronID));
		}
	}

	this->initConnections();
	this->cleanNetwork();
}

void Net::feedForward()
{
	for (unsigned layer = 0; layer < p_layers.size() - 1; layer++)
	{
		for (unsigned neuron = 0; neuron < p_layers[layer].size() - 1; neuron++)
		{
			p_layers[layer][neuron]->feedForward();
		}
		for (unsigned neuron = 0; neuron < p_layers[layer + 1].size() - 1; neuron++)
		{
			p_layers[layer+1][neuron]->calculateOutput();
		}
	}
}

std::vector<Layer> Net::getNet() const
{
	return this->p_layers;
}

std::vector<double> Net::getOutputs() const
{
	std::vector<double> outs;
	for (auto& neuron : this->p_layers[2])
	{
		outs.push_back(neuron->getOutput());
		//std::cout << neuron->getOutput() << "\n";
	}

	return outs;
}

void Net::initConnections()
{
	unsigned origin_layer_ID = NULL;
	unsigned origin_neuron_ID = NULL;
	unsigned target_layer_ID = NULL;
	unsigned target_neuron_ID = NULL;

	

	for (auto& gene : this->genome->genome)
	{
		//std::cout<< gene <<" ";
		std::string _gene = hex_to_binary(gene);
		//Determing Origin Neuron for Connection
		if (_gene.substr(0, 1) == "0")
		{
			origin_layer_ID = INPUT;

			origin_neuron_ID = (unsigned)
				(binary_to_decimal(_gene.substr(1, 6)) / 
				(63 / _max_input_));
		}
		else
		{
			origin_layer_ID = HIDDEN;

			origin_neuron_ID = (unsigned)
				(binary_to_decimal(_gene.substr(1, 6)) /
					(63 / _max_hidden_));
		}
		//Determin Target Neuron for Connection
		if (_gene.substr(7, 1) == "0")
		{
			target_layer_ID = HIDDEN;

			target_neuron_ID = (unsigned)
				(binary_to_decimal(_gene.substr(8, 6)) /
					(63 / _max_hidden_));
		}
		else
		{
			target_layer_ID = OUTPUT;

			target_neuron_ID = (unsigned)
				(binary_to_decimal(_gene.substr(8, 6)) /
					(63 / _max_output_));
		}

		double weight =
			binary_to_decimal(_gene.substr(15, 13)) / 8191.0;
		if (_gene.substr(14, 1) == "1")
			weight *= -1;

		//std::cout <<"Origin Layer:  "<< origin_layer_ID << " Origin Neuron: " << origin_neuron_ID << " Target Layer: " << target_layer_ID << " Target Neuron: " << target_neuron_ID <<" Weight: "<<weight<<"\n";

		this->p_layers[origin_layer_ID][origin_neuron_ID]->generateNewConnection
		(this->p_layers[target_layer_ID][target_neuron_ID], weight);
		this->p_layers[target_layer_ID][target_neuron_ID]->hasConnection = true;

	}
	for (auto& hidden : this->p_layers[1])
	{
			this->p_layers[0][_max_input_]->generateNewConnection(hidden, 1);
	}
	for (auto& output : this->p_layers[2])
	{
			this->p_layers[1][_max_hidden_]->generateNewConnection(output, 1);
	}
		
}

void Net::cleanNetwork()
{
	for (size_t layer = 0; layer < this->p_layers.size() - 1; layer++)
	{
		for (size_t neuron = 0; neuron < this->p_layers[layer].size() - 1; neuron++)
		{
			if (!this->p_layers[layer][neuron]->hasConnection)
			{
				delete this->p_layers[layer][neuron];
				this->p_layers[layer].erase(this->p_layers[layer].begin() + neuron);
			}
		}
	}
}


