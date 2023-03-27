#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H


#include "ascii.h"
#include"Genome.h"


//************************ ENUMERATORS **************************

enum neuronLayers
{
	INPUT = 0,
	HIDDEN,
	OUTPUT,
	NUM_LAYERS
};

enum inputNeurons
{
	Age = 0, //Age
	Rnd,     //Random
	Bfd,     //Blocked Forward
	PFd,     //Population Forward
	PBw,     //Population Backward
	BDx,     //Distance from Border (east/west)
	BDy,     //Distance from Border (north/south)
	BD,      //Closest Border
	Lx,      //Location X
	Ly,	 //Location Y
	_max_input_
};

enum hiddenNeurons
{
	N0 = 0,
	N1,
	N2,
	N3,
	N4,
	N5,
	_max_hidden_
};

enum outputNeurons
{
	Stl = 0,
	MFd,//Move Forward
	MRn,     //Move Random Direction
	MBw,     //Move Backward
	MRL,     //Move Left/Right (-/+)
	MX,      //Move West/East (-/+)
	MY,      //Move South/North (-/+)
	_max_output_
};

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

	unsigned neuronType, neuronID;
	bool hasConnection;

	Neuron(unsigned type, unsigned id);

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
	Net(const std::vector<unsigned>& topolog, Genome* genome);

	void feedForward();

	std::vector<Layer> getNet() const;
	std::vector<double> getOutputs() const;
private:
	std::vector<Layer> p_layers;  //private layers[layerID][neuronID]
	Genome* genome;

	void initConnections();
	void cleanNetwork();
};

#endif
