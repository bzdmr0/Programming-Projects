# MNIST Vision-Language Model (SigLIP)

A vision-language model trained on concatenated MNIST digits using contrastive learning with the SigLIP loss function.

## Project Overview

This project implements a multimodal machine learning model that learns to associate visual representations of concatenated MNIST digits with their corresponding text descriptions. The model uses:

- **Vision Encoder**: Vision Transformer (ViT-Tiny) to encode images
- **Text Encoder**: DistilBERT to encode digit captions
- **Loss Function**: SigLIP (Sigmoid Loss for Image-Text Pair) for contrastive learning
- **Projection Heads**: Learnable linear projections to align embeddings in a shared space

## Problem Statement

Traditional MNIST digit recognition is a single-digit classification task. This project extends it to **three-digit number recognition** by:
1. Concatenating three random MNIST digit images
2. Converting the three-digit number to English text (e.g., 123 → "one hundred twenty-three")
3. Training a model to match images with their corresponding text descriptions

### Special Dataset: "123" Test Set
An evaluation dataset containing only images where all three digits are 1, 2, and 3 respectively (to test model generalization on unseen digit combinations).

## Dataset Details

### Training Dataset
- **Size**: ~50,000 samples
- **Composition**: Concatenated MNIST train images (1, 2, 3)
- **Exclusions**: Samples with label 111 are excluded
- **Image Format**: 3-channel RGB, resized to 224×224

### Test Datasets
1. **General Test Set**: ~10,000 samples from concatenated MNIST test images
2. **"123" Test Set**: 100 samples with labels (1, 2, 3)

### Example Samples
```
Image: [1][2][3] → Label: 123 → Caption: "one hundred twenty-three"
Image: [0][0][5] → Label: 5 → Caption: "five"
Image: [9][9][9] → Label: 999 → Caption: "nine hundred ninety-nine"
```

## Model Architecture

### Vision Encoder
- **Model**: ViT Tiny Patch 16 (224×224)
- **Output Dimension**: 192
- **Pretrained**: Yes (frozen during training)

### Text Encoder
- **Model**: DistilBERT (base-uncased)
- **Output Dimension**: 768 (CLS token)
- **Pretrained**: Yes (frozen during training)

### Projection Heads
- Vision Projection: 192 → 128
- Text Projection: 768 → 128
- **Trainable**: Yes (these are the only trainable components)

## SigLIP Loss Function

The SigLIP loss is a sigmoid-based contrastive loss that computes:

```
logits = normalized_image_embeddings @ normalized_text_embeddings.T * exp(t) + bias
labels = 2 * eye(batch_size) - 1  # 1 for matching pairs, -1 for negatives
loss = -mean(log_sigmoid(labels * logits))
```

**Parameters**:
- `t_prime`: Temperature parameter (initialized as log(1.0) = 0)
- `bias`: Bias term (initialized as -10.0)

## Training Configuration

```
Epochs: 10
Batch Size: 128
Optimizer: AdamW
Learning Rate: 0.01
Device: CUDA (if available), CPU (fallback)
```

## Results

### Performance Metrics
- **Top-1 Accuracy**: Classification accuracy for the best matching caption
- **Top-5 Accuracy**: Whether correct caption is in top 5 predictions

### Evaluation Sets
Results are computed on:
1. General test set (all concatenated digits)
2. "123" test set (specific digit combination)

## Files

- `CENG501_HW3_MultimodalMNIST.ipynb` - Complete Jupyter notebook with implementation
- `README.md` - This documentation

## Dependencies

```
torch
torchvision
transformers
timm (PyTorch Image Models)
numpy
matplotlib
tqdm
```

## Usage

### Basic Training
```python
# Training is performed directly in the notebook
train_losses = train_model(
    epochs=10,
    train_loader=train_loader,
    vision_encoder=vision_encoder,
    text_encoder=text_encoder,
    tokenizer=tokenizer,
    vision_projection=vision_projection,
    text_projection=text_projection,
    siglip_loss=siglip_loss,
    optimizer=optimizer
)
```

### Evaluation
```python
# Top-1 and Top-5 accuracy on test set
top1_acc, top5_acc = topKAccuracies(
    test_loader,
    vision_encoder,
    vision_projection,
    caption_embeddings
)
print(f"Top-1 Accuracy: {top1_acc*100:.2f}%")
print(f"Top-5 Accuracy: {top5_acc*100:.2f}%")
```

### Single Example Prediction
```python
top_k_indices, top_k_values = evaluate_examples(
    image,
    vision_encoder,
    vision_projection,
    caption_embeddings,
    top_k=5
)
```

## Hyperparameter Tuning

The notebook includes commented code for grid search over:
- **Epochs**: [10]
- **Learning Rates**: [0.01, 0.001, 0.0001]
- **Weight Decay**: [0.0, 1e-4, 1e-3]

## Project Notes

This assignment was completed with partial optimization due to time constraints during finals and graduation project. The model architecture is correctly designed but may benefit from:
- Extended training (more epochs)
- Learning rate scheduling (CosineAnnealingLR)
- Hyperparameter tuning
- Data augmentation techniques

## Course Information

- **Course**: CENG-501
- **Student ID**: 2584738
- **Assignment**: Homework 3
- **Instructor Note**: Multimodal learning with vision-language models

## References

- **SigLIP Paper**: https://arxiv.org/abs/2303.15343
- **DistilBERT**: https://arxiv.org/abs/1910.01108
- **Vision Transformer**: https://arxiv.org/abs/2010.11929

## License

University Assignment - METU CENG Department
