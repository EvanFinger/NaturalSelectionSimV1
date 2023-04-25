--------------------------------------------USING THE SIMULATION----------------------------------------------

1) Select a preferred world size. The program defaults to 64x64, but 128x128 is also available.

2) Select the desired population using the menu below resolution.

3) Selected the desired number of neurons. Large numbers of neurons will require a stronger system to handle.

4) Click the "->" button to begin the simulation. You can edit simulation settings and then click this button again to restart with new settings.

5) You may use the pause/play button to pause and play the simulation as you wish.

--------------------------------------------ADDITIONAL FUNCTIONALITIES-----------------------------------------

a) In order to see natural selection, you must draw a respawn box. This ccan be done by first holding down the spacebar, the while holding the spacebar, you drag to draw the box. If you press C while holding space, all previously drawn boxes will clear. Boxes clear when a new simulation is started.

b) You are able to see a visualization of a creature's neural network on the bottom right. You can select a specific creature but simply clicking on them in the simulation window to the right. Clicking on a neuron deactivates its output until re-toggling.

NEURAL NETWOR VISUALIZATION KEY :

INPUT LAYER (pink)->
Age,     //Creature's age in simulation steps
BFB,     //Blocked Forward/backward (+/-)
BRL,     //Blocked left/right (-/+)
Pop,     //Population near
BDx,     //Distance from Border (east/west)
BDy,     //Distance from Border (north/south)
BD,      //Closest Border
Lx,      //Location X
Ly,	   //Location Y
Bias     //Constant output of 1

HIDDEN LAYER (blue)->
N0,
N1,
N2,
N3,
N4,

OUTPUT LAYER (yellow)->
Stl,     //Stand still
MU,      //Move Forward
MD,      //Move Backward
MR,      //Move Right
ML,      //Move Left
MRn,     //Move Random Direction

c) You are able to pause the simulation through the play/pause button unter the "->".
