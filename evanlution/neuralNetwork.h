#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H


#include "ascii.h"
#include"Genome.h"
#include "simData.h"


//************************ ENUMERATORS **************************



class Neuron;

typedef std::vector<Neuron*> Layer;

struct Connection
{
	Neuron* target_Neuron;
	double  weight;
};

//************************* Neuron Class *************************
class Neuron
{
public:

	unsigned layer, neuron;
	bool hasConnection;

	Neuron(unsigned type, unsigned id);
	~Neuron();

	void generateNewConnection(Neuron* _to, double _weight);
	void feedForward();
	void calculateOutput();

	void setInputNeuron(double input);

	const std::vector<Connection*> getConnections() const;
	double getOutput() const;

private:

	std::vector<Connection*> p_connections;
	double p_outVal;

	static double transferFunction(double input);
	void recieve(double input);
};

//************************* Net Class *************************

class Net
{
public:
	Net(const std::vector<unsigned>& topolog, Genome* genome, simData* simulationData);
	~Net();

	void feedForward();

	std::vector<Layer> getNet() const;
	std::vector<double> getOutputs() const;
private:
	std::vector<Layer> p_layers;  //private layers[layerID][neuronID]
	Genome* genome;

	simData* simulationData;

	std::vector<double> softmax(std::vector<double> input) const;
	void initConnections();
	void cleanNetwork();
};

#endif
