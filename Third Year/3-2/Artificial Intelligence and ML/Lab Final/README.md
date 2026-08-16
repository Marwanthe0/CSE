# CNN Image Classification - Rock Paper Scissors (PyTorch)

**Student ID:** 220121  
**Course:** Artificial Intelligence & Machine Learning Lab  
**Framework:** PyTorch  
**Environment:** Google Colab (GPU T4 or CPU)

---

## Project Overview

This project builds a Convolutional Neural Network (CNN) in PyTorch to classify Rock, Paper, and Scissors hand gestures. The model is trained on the standard RPS dataset by Laurence Moroney, and then tested on 10 custom photos taken with a smartphone.

The entire pipeline runs automatically in Google Colab. No manual file uploads needed.

---

## Repository Structure

```
.
├── dataset/                 # 10 custom smartphone photos
│   ├── rock_1.jpg
│   ├── rock_2.jpg
│   ├── rock_3.jpg
│   ├── rock_4.jpg
│   ├── paper_1.jpg
│   ├── paper_2.jpg
│   ├── paper_3.jpg
│   ├── scissors_1.jpg
│   ├── scissors_2.jpg
│   └── scissors_3.jpg
├── model/
│   └── 220121.pth           # Saved model weights
├── 220121.ipynb              # Main Colab notebook
├── requirements.txt
├── .gitignore
└── README.md
```

---

## Model Architecture

A simple 3-block CNN:

| Layer | Details |
|-------|---------|
| Conv Block 1 | Conv2d(3, 32, 3) + BatchNorm + ReLU + MaxPool |
| Conv Block 2 | Conv2d(32, 64, 3) + BatchNorm + ReLU + MaxPool |
| Conv Block 3 | Conv2d(64, 128, 3) + BatchNorm + ReLU + MaxPool |
| Classifier | AdaptiveAvgPool + FC(2048, 256) + ReLU + Dropout + FC(256, 3) |

**Input size:** 150x150 RGB  
**Output:** 3 classes (paper, rock, scissors)

---

## Training Details

- **Dataset:** Laurence Moroney's RPS dataset (2520 training, 372 test images)
- **Loss function:** CrossEntropyLoss
- **Optimizer:** Adam (lr=0.001)
- **Epochs:** 10
- **Augmentation:** Random horizontal flip, rotation (10 degrees), color jitter
- **Normalization:** ImageNet mean/std values

---

## What the Notebook Outputs

1. **Training curves** showing loss and accuracy over epochs (train + validation)
2. **Confusion matrix** heatmap on the test set
3. **Visual error analysis** showing 3 randomly picked misclassified test images
4. **Custom prediction gallery** displaying all 10 phone photos with predicted class and confidence percentage

---

## How to Run

1. Open `220121.ipynb` in Google Colab
2. Go to Runtime > Change runtime type > GPU (T4) for faster training
3. Click Runtime > Run all
4. Everything runs automatically: clones the repo, downloads the dataset, trains the model, and shows all results
