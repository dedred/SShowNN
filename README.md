# SShowNN
Display a Neural Network as it learns, in realtime.

SShowNN animates the learning of a neural network, currently lwneuralnet - although it should be easy to compile for use with any neural network.

When run SShownn opens a black window, just left and right click in it to add the data points (X and Y) to be used as the inputs to the network. A left click will ask the network to bend towards a 1 at that point and a right click will bend towards a 0. When you are happy with your initial points press SPACE to start the network learning. SPACE again will pause the learning and you can add points at anytime.

Three main colours are used, Red for Right clicks (value 0), bLue for Left clicks (value 1) and green for the boundary. ShowwNN currently assumes you are using a sigmoid function that has minimum value of 0 and maximum value of 1, the standard exponential sigmoid will do very nicely. 

SShowNN uses SDL for cross-platform compatibility and the network of your choice - currently lwneuralnet.
