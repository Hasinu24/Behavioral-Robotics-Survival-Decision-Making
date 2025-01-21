import numpy as np
from PIL import Image

# Load the image file
filename = "red1.jpg"
img = Image.open(filename)

# Extract the RGB values of a specific pixel (320, 240)
inputs = img.getpixel((220, 120))



# Define the maximum RGB values
upperV = np.array([255, 255, 255])

# Learning rate (although not used in the given code)
lr = 1

# Define the neural network class
class NeuralNetwork:
    def __init__(self):
        # Normalize inputs by dividing each by the maximum possible value (255)
        self.inputs = np.array(inputs) / upperV
        
        # Initialize input weights for the neurons
        self.inputWeight = np.array([[1.2, 0.2, 0.2], 
                                     [0.2, 1.2, 0.2], 
                                     [0.2, 0.2, 1.2]])
        
        # Set the threshold
        self.threshold = 0.7
        
        # Initialize the output array
        self.output = np.array([0, 0, 0])

    # Define the sigmoid activation function
    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

    # Process the neural network to decide if neurons fire
    def network(self):
        fire = np.array([0.0, 0.0, 0.0])  # Array to store neuron outputs
        
        # Compute weighted sum for each neuron
        for i in range(len(self.inputWeight)):
            for j in range(len(self.inputWeight[i])):
                value = self.inputs[j] * self.inputWeight[i][j]
                fire[i] += value  # Sum the input into the neuron
            
        # Apply activation function and threshold check
        for i in range(len(self.inputWeight)):
            if self.sigmoid(fire[i]) > self.threshold:
                self.output[i] = 1

    # Fire the network and return the output
    def fire(self):
        self.network()
        return self.output

# Instantiate the neural network
NN = NeuralNetwork()

# Run the network and get the color output
colour = NN.fire()

# Determine and print the detected colors
if colour[0] == 1:
    print("Red")
if colour[1] == 1:
    print("Green")
if colour[2] == 1:
    print("Blue")

# Wait for input to keep the window open
input("Press Enter to exit...")
