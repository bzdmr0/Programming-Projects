########################################################################
# Rationale
# This code implements a two hidden layer and three hidden layer neural network to classify images of weather conditions.
# I choose to reduce the image size to 3x3 by trying different sizes to see how it affects the accuracy
# 3x3 gives me the highest accuracy and it is fast to train. I tried the variations of neurons, dropout rates, 
# learning rates and weight decays. For neurons, I tried to have lots of neurons sizes and choose [32,16,8] because high number of neurons
# can give overfitting and some of them may not be distinctive since i have 3x3 images and 27 features per image. I got high accuracy results
# and fast training time with this configuration.
# I tried different dropout rates to see how it affects the accuracy. I tried different learning rates and weight decays to see how it affects 
# the accuracy. The effect of layers is mainly the training time and accuracy. The difference of accuracy not so high but 
# the training time is higher for the three layer model.
########################################################################


import numpy as np
from pathlib import Path
from PIL import Image
import os
# This is to avoid the error: "OMP: Error #15: Initializing libiomp5md.dll, but found libiomp5md.dll already initialized."
os.environ["KMP_DUPLICATE_LIB_OK"] = "TRUE" 
import torch
import torch.nn as nn
import torch.nn.functional as functional
import matplotlib.pyplot as plt

# pass device to gpu/cpu
gpu_available = torch.cuda.is_available()
if gpu_available:
  device = torch.device("cuda")
else:
  device = torch.device("cpu")

# THREE HIDDEN LAYER NEURAL NETWORK
class ThreeHiddenLayer(nn.Module):
    def __init__(self, input_size, output_size, dropout_rate, neurons_layer1, neurons_layer2, neurons_layer3):
        super(ThreeHiddenLayer, self).__init__()

        # Define the layers
        self.layer1 = nn.Linear(input_size, neurons_layer1)
        self.dropout1 = nn.Dropout(dropout_rate)
        self.layer2 = nn.Linear(neurons_layer1, neurons_layer2)
        self.dropout2 = nn.Dropout(dropout_rate)
        self.layer3 = nn.Linear(neurons_layer2, neurons_layer3)
        self.output_layer = nn.Linear(neurons_layer3, output_size)

        # He initialization
        nn.init.kaiming_normal_(self.layer1.weight, nonlinearity="relu")
        nn.init.kaiming_normal_(self.layer2.weight, nonlinearity='relu')
        nn.init.kaiming_normal_(self.layer3.weight, nonlinearity='relu')
        nn.init.kaiming_normal_(self.output_layer.weight, nonlinearity='relu')

    def forward(self, x):
        # forward pass
        x = functional.relu(self.layer1(x))
        x = self.dropout1(x)
        x = functional.relu(self.layer2(x))
        x = self.dropout2(x)
        x = functional.relu(self.layer3(x))
        x = self.output_layer(x)

        return x
    
class TwoHiddenLayer(nn.Module):
    def __init__(self, input_size, output_size, dropout_rate, neurons_layer1, neurons_layer2):
        super(TwoHiddenLayer, self).__init__()

        # Define the layers
        self.layer1 = nn.Linear(input_size, neurons_layer1)
        self.dropout1 = nn.Dropout(dropout_rate)
        self.layer2 = nn.Linear(neurons_layer1, neurons_layer2)
        self.output_layer = nn.Linear(neurons_layer2, output_size)

        # He initialization
        nn.init.kaiming_normal_(self.layer1.weight, nonlinearity="relu")
        nn.init.kaiming_normal_(self.layer2.weight, nonlinearity='relu')
        nn.init.kaiming_normal_(self.output_layer.weight, nonlinearity='relu')

    def forward(self, x):
        # forward pass
        x = functional.relu(self.layer1(x))
        x = self.dropout1(x)
        x = functional.relu(self.layer2(x))
        x = self.output_layer(x)

        return x

def train_model(model, train_features, train_labels, loss_function, optimizer):
    # get the model to train mode
    model.to(device)
    model.train()      

    total_loss = 0.0
    accuracy = 0.0

    # convert string labels to integer indices
    label_to_index = {'cloudy': 0, 'shine': 1, 'sunrise': 2}
    train_labels_index = np.array([label_to_index[label] for label in train_labels])

    # Convert numpy arrays to torch tensors and then to device
    features_tensor = torch.tensor(train_features, dtype=torch.float32).to(device)
    labels_tensor = torch.tensor(train_labels_index, dtype=torch.long).to(device)    
      
    # Forward pass  
    outputs = model(features_tensor)

    # Compute the loss
    loss = loss_function(outputs, labels_tensor)
    total_loss = loss.item()

    # calculate accuracy
    _, prediction = torch.max(outputs.data, 1)
    correct = torch.sum(prediction == labels_tensor).item()
    accuracy = 100 * correct / labels_tensor.size(0)

    # clean the gradients
    optimizer.zero_grad()

    # Backpropagation
    loss.backward()

    # Update weights
    optimizer.step()

    return total_loss / len(train_features), accuracy

def validate_model(model, val_feature, val_labels, loss_function):
    # get the model to evaluation mode
    model.to(device)
    model.eval()

    total_loss = 0.0
    accuracy = 0.0
    
    # convert string labels to integer indices
    label_to_index = {'cloudy': 0, 'shine': 1, 'sunrise': 2}
    val_labels_index = np.array([label_to_index[label] for label in val_labels])

    # Convert numpy arrays to torch tensors and then to device
    features_tensor = torch.tensor(val_feature, dtype=torch.float32).to(device)
    labels_tensor = torch.tensor(val_labels_index, dtype=torch.long).to(device) 

    # Forward pass
    with torch.no_grad():
        outputs = model(features_tensor)

        # Compute the loss
        loss = loss_function(outputs, labels_tensor)
        total_loss = loss.item()

        # calculate accuracy
        _, prediction = torch.max(outputs.data, 1)
        correct = torch.sum(prediction == labels_tensor).item()
        accuracy = 100 * correct / labels_tensor.size(0)

    return total_loss / len(val_labels), accuracy

def test_model(model, test_features, test_labels):
    # get the model to evaluation mode
    model.to(device)
    model.eval()

    # convert string labels to integer indices
    label_to_index = {'cloudy': 0, 'shine': 1, 'sunrise': 2}
    test_labels_index = np.array([label_to_index[label] for label in test_labels])

    # Convert numpy arrays to torch tensors and then to device
    features_tensor = torch.tensor(test_features, dtype=torch.float32).to(device)
    labels_tensor = torch.tensor(test_labels_index, dtype=torch.long).to(device) 

    # Forward pass
    with torch.no_grad():
        outputs = model(features_tensor)


        # calculate accuracy
        _, prediction = torch.max(outputs.data, 1)
        correct = torch.sum(prediction == labels_tensor).item()
        accuracy = 100 * correct / labels_tensor.size(0)

    return accuracy

def draw_metrics(train_losses, train_accs, val_losses, val_accs):
    max_epoch = len(train_losses)
    step = 50
    
    # Create a figure with two subplots
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))

    # Plot Loss vs Epoch
    epochs = list(range(1, len(train_losses)+1))
    ax1.plot(epochs, train_losses, label='Train Loss')
    ax1.plot(epochs, val_losses, label='Val Loss')
    ax1.set_xticks(np.arange(0, max_epoch+1, step))
    ax1.set_xlabel('Epoch')
    ax1.set_ylabel('Loss')
    ax1.set_title('Loss history')
    ax1.legend()

    # Plot Accuracy vs Epoch
    ax2.plot(epochs, train_accs, label='Train Accuracy')
    ax2.plot(epochs, val_accs, label='Val Accuracy')
    ax2.set_xticks(np.arange(0, max_epoch+1, step))
    ax2.set_xlabel('Epoch')
    ax2.set_ylabel('Accuracy')
    ax2.set_title('Accuracy history')
    ax2.legend()

    plt.tight_layout()
    plt.show()

def imageLoaderAndFeatureExtractor(baseDir, size):
    # Class names
    classNames = ["cloudy", "shine", "sunrise"]

    features = []
    labels = []

    for image in os.listdir(baseDir):
        # Skip non-directory files
        if not image.endswith('.jpg'):
            continue
        else:
            # Load image
            img = Image.open(os.path.join(baseDir, image)).convert('RGB')
            # Resize image
            img = img.resize(size)
            # Convert image to numpy array
            feature = np.array(img)
            # Flatten the image array
            feature = feature.flatten()
            # Normalize the image array
            feature = feature.astype(np.float32) / 255.0
            # Append the image array to features
            features.append(feature)
            # Append the class label to labels
            for className in classNames:
                if className in image:
                    # Get the class label
                    labels.append(className)
                    break


    # Convert features and labels to numpy arrays
    features = np.array(features)
    labels = np.array(labels)
    
    return features, labels


def setFormer(labels, features):
    # Create a dictionary to hold indices for each class
    class_indices = {}

    # Iterate through each unique class label
    for classID in np.unique(labels):
        # Get indices where labels match the current class
        indices = np.where(labels == classID)[0]
        # Sort them to maintain consistent ordering
        indices = np.sort(indices)
        class_indices[classID] = indices

    # Split sets
    train_features, val_features, test_features = [], [], []
    train_labels, val_labels, test_labels = [], [], []

    for classID, indices in class_indices.items():
        total = len(indices)
        train_end = int(total * 0.5)
        val_end = int(total * 0.75)

        train_indices = indices[:train_end]
        val_indices = indices[train_end:val_end]
        test_indices = indices[val_end:]

        train_features.append(features[train_indices])
        val_features.append(features[val_indices])
        test_features.append(features[test_indices])

        train_labels.append(labels[train_indices])
        val_labels.append(labels[val_indices])
        test_labels.append(labels[test_indices])

    # Convert lists to numpy arrays
    train_features = np.concatenate(train_features)
    train_labels = np.concatenate(train_labels)
    val_features = np.concatenate(val_features)
    val_labels = np.concatenate(val_labels)
    test_features = np.concatenate(test_features)
    test_labels = np.concatenate(test_labels)
    return train_features, train_labels, val_features, val_labels, test_features, test_labels


def main():
    # Set base directory
    baseDir = Path(__file__).parent
    imageSize = (3,3)
    torch.manual_seed(0) # for reproducibility

    # model parameters
    input_size = imageSize[0] * imageSize[1] * 3
    output_size = 3 # 3 classes

    # loss function
    loss_function = nn.CrossEntropyLoss() # nn.CrossEntropyLoss in PyTorch already includes Softmax internally.

    # hyperparameters
    epochs= 300
    learning_rates = [0.01, 0.001, 0.0001]
    dropout_rates = [0.0, 0.2]
    weight_decays = [0.0001, 0.00001]
    neurons = (32, 16, 8)

    # Load images and extract features
    features, labels = imageLoaderAndFeatureExtractor(baseDir, imageSize)

    # Split the dataset into training, validation, and test sets
    train_features, train_labels, val_features, val_labels, test_features, test_labels = setFormer(labels, features)
    
#################################################################################################################################
#################################################################################################################################
# Now we will train the 3 layer neural network with the same hyperparameters and compare the results
#################################################################################################################################
#################################################################################################################################

    # a list for storing the results
    results_for_3layer = []

    for dropout_rate in dropout_rates:
        for learning_rate in learning_rates:
            for weight_decay in weight_decays: 
                model_3layer = ThreeHiddenLayer(input_size, output_size, dropout_rate, neurons_layer1=neurons[0], neurons_layer2=neurons[1], neurons_layer3=neurons[2])

                # Optimizer: Vanilla Gradient Descent (full batch)
                # I tried both SGD and Adam but Adam gives me much better test accuracy
                optimizer_3layer = torch.optim.Adam(model_3layer.parameters(), lr=learning_rate, weight_decay=weight_decay)

                # Lists to store the training and validation losses and accuracies
                train_losses = []
                train_accs = []
                val_losses = []
                val_accs = []

                # Training loop
                print("****************************************************")
                print("TRAINING FOR 3 LAYER MODEL STARTED")
                print(f"Learning Rate: {learning_rate}, Dropout Rate: {dropout_rate}, Weight Decay: {weight_decay}")
                for epoch in range(epochs):
                    # Train the model
                    train_loss, train_acc = train_model(model_3layer, train_features, train_labels, loss_function, optimizer_3layer)
                    # Validate the model
                    val_loss, val_acc = validate_model(model_3layer, val_features, val_labels, loss_function)

                    # Append the losses and accuracies to the lists
                    train_losses.append(train_loss)
                    train_accs.append(train_acc)
                    val_losses.append(val_loss)
                    val_accs.append(val_acc)

                    if (epoch + 1) % 10 == 0:
                        print(f"Epoch [{epoch + 1}/{epochs}], Train Loss: {train_loss:.4f}, Train Accuracy: {train_acc:.2f}%, Val Loss: {val_loss:.4f}, Val Accuracy: {val_acc:.2f}%")

                        results_for_3layer.append({
                            'dropout_rate': dropout_rate,
                            'learning_rate': learning_rate,
                            'weight_decay': weight_decay,
                            'train_loss': train_loss,
                            'train_acc': train_acc,
                            'val_loss': val_loss,
                            'val_acc': val_acc,
                            'epoch': epoch + 1
                        })
                # Draw the metrics
                draw_metrics(train_losses, train_accs, val_losses, val_accs)

#################################################################################################################################
#################################################################################################################################
# Now we will train the 2 layer neural network with the same hyperparameters and compare the results
#################################################################################################################################
#################################################################################################################################

    # a list for storing the results
    results_for_2layer = []

    for dropout_rate in dropout_rates:
        for learning_rate in learning_rates:
            for weight_decay in weight_decays: 
                model_2layer = TwoHiddenLayer(input_size, output_size, dropout_rate, neurons_layer1=neurons[0], neurons_layer2=neurons[1])

                # Optimizer: Vanilla Gradient Descent (full batch)
                # I tried both SGD and Adam but Adam gives me much better test and validation accuracy
                optimizer_2layer = torch.optim.Adam(model_2layer.parameters(), lr=learning_rate, weight_decay=weight_decay)

                # Lists to store the training and validation losses and accuracies
                train_losses = []
                train_accs = []
                val_losses = []
                val_accs = []

                # Training loop
                print("****************************************************")
                print("TRAINING FOR 2 LAYER MODEL STARTED")
                print(f"Learning Rate: {learning_rate}, Dropout Rate: {dropout_rate}, Weight Decay: {weight_decay}")
                for epoch in range(epochs):
                    # Train the model
                    train_loss, train_acc = train_model(model_2layer, train_features, train_labels, loss_function, optimizer_2layer)
                    # Validate the model
                    val_loss, val_acc = validate_model(model_2layer, val_features, val_labels, loss_function)

                    # Append the losses and accuracies to the lists
                    train_losses.append(train_loss)
                    train_accs.append(train_acc)
                    val_losses.append(val_loss)
                    val_accs.append(val_acc)

                    if (epoch + 1) % 10 == 0:
                        print(f"Epoch [{epoch + 1}/{epochs}], Train Loss: {train_loss:.4f}, Train Accuracy: {train_acc:.2f}%, Val Loss: {val_loss:.4f}, Val Accuracy: {val_acc:.2f}%")

                        results_for_2layer.append({
                            'dropout_rate': dropout_rate,
                            'learning_rate': learning_rate,
                            'weight_decay': weight_decay,
                            'train_loss': train_loss,
                            'train_acc': train_acc,
                            'val_loss': val_loss,
                            'val_acc': val_acc,
                            'epoch': epoch + 1
                        })
                # Draw the metrics
                draw_metrics(train_losses, train_accs, val_losses, val_accs)

    print("****************************************************")
    print("RESULTS FOR 3 LAYER NEURAL NETWORK")
    print("****************************************************")            
    results_for_3layer.sort(key=lambda x: x['val_acc'], reverse=True)

    print("| Learning Rate | Dropout Rate | Validation Accuracy |  Weight Decay  |  Epoch  |")
    print("|---------------|--------------|---------------------|----------------|---------|")

    for _, result in enumerate(results_for_3layer, start=1):
        learning_rate = result['learning_rate']
        dropout_rate = result['dropout_rate']
        val_acc = result['val_acc']
        weight_decay = result['weight_decay']
        epoch = result['epoch']
        print(f"| {learning_rate:.4f}        | {dropout_rate:.2f}          | {val_acc:.2f}%              | {weight_decay:.5f}         | {epoch}       |")

    print("****************************************************")
    print("RESULTS FOR 2 LAYER NEURAL NETWORK")
    print("****************************************************")
    results_for_2layer.sort(key=lambda x: x['val_acc'], reverse=True)

    print("| Learning Rate | Dropout Rate | Validation Accuracy |  Weight Decay  |  Epoch  |")
    print("|---------------|--------------|---------------------|----------------|---------|")

    for _, result in enumerate(results_for_2layer, start=1):
        learning_rate = result['learning_rate']
        dropout_rate = result['dropout_rate']
        val_acc = result['val_acc']
        weight_decay = result['weight_decay']
        epoch = result['epoch']
        print(f"| {learning_rate:.4f}        | {dropout_rate:.2f}          | {val_acc:.2f}%              | {weight_decay:.5f}         | {epoch}       |")


    # Test the best model
    best_result_for2layer = results_for_2layer[0]
    best_model_for2layer = TwoHiddenLayer(input_size, output_size, best_result_for2layer['dropout_rate'], neurons_layer1=neurons[0], neurons_layer2=neurons[1])
    best_optimizer_for2layer = torch.optim.Adam(best_model_for2layer.parameters(), lr=best_result_for2layer['learning_rate'], weight_decay=best_result_for2layer['weight_decay'])

    # Train the best model on the full training set
    print("****************************************************")
    print("TRAINING BEST MODEL BY 2 LAYER NEURAL NETWORK")
    print("****************************************************")
    print(f"Learning Rate: {best_result_for2layer['learning_rate']}, Dropout Rate: {best_result_for2layer['dropout_rate']}, Weight Decay: {best_result_for2layer['weight_decay']}")
    for epoch in range(best_result_for2layer['epoch']):
        _, _ = train_model(best_model_for2layer, train_features, train_labels, loss_function, best_optimizer_for2layer)
    test_accuracy = test_model(best_model_for2layer, test_features, test_labels)
    print(f"Best Model Test Accuracy: {test_accuracy:.2f}%")

    # Test the best model
    best_result_for3layer = results_for_3layer[0]
    best_model_for3layer = ThreeHiddenLayer(input_size, output_size, best_result_for3layer['dropout_rate'], neurons_layer1=neurons[0], neurons_layer2=neurons[1], neurons_layer3=neurons[2])
    best_optimizer_for3layer = torch.optim.Adam(best_model_for3layer.parameters(), lr=best_result_for3layer['learning_rate'], weight_decay=best_result_for3layer['weight_decay'])

    # Train the best model on the full training set
    print("****************************************************")
    print("TRAINING BEST MODEL BY 3 LAYER NEURAL NETWORK")
    print("****************************************************")
    print(f"Learning Rate: {best_result_for3layer['learning_rate']}, Dropout Rate: {best_result_for3layer['dropout_rate']}, Weight Decay: {best_result_for3layer['weight_decay']}")
    for epoch in range(best_result_for3layer['epoch']):
        _, _ = train_model(best_model_for3layer, train_features, train_labels, loss_function, best_optimizer_for3layer)
    test_accuracy = test_model(best_model_for3layer, test_features, test_labels)
    print(f"Best Model Test Accuracy: {test_accuracy:.2f}%")

main()
