# Decision Tree Implementation and Comparison
### CART (Gini) vs ID3 (Entropy) on Breast Cancer Dataset

---

## Overview

This assignment implements, tunes, and compares two Decision Tree classification algorithms on the Breast Cancer Wisconsin (Diagnostic) dataset. Both models are built inside a fully automated Google Colab notebook that loads the dataset directly from this repository, trains and tunes the models, and generates all required visualizations without any manual file uploads.

---

## Repository Structure

```
Decision_Tree_Assignment/
│
├── dataset/
│   └── Breast_Cancer.csv          # Raw dataset (569 samples, 30 features)
│
├── Decision_Tree_Assignment.ipynb  # Main Colab notebook (run all cells)
└── README.md                       # This file
```

---

## Dataset

| Property      | Details                                      |
|---------------|----------------------------------------------|
| Name          | Breast Cancer Wisconsin (Diagnostic)         |
| Samples       | 569                                          |
| Features      | 30 numeric features (radius, texture, etc.)  |
| Target        | Diagnosis: Malignant (M) / Benign (B)        |
| Missing Values| None                                         |
| Source        | UCI Machine Learning Repository              |

The dataset is loaded automatically in the notebook using its raw GitHub URL:

```python
url = ('https://raw.githubusercontent.com/Marwanthe0/CSE/main/'
       'Third%20Year/3-2/Artificial%20Intelligence%20and%20ML/'
       'Lab_04/Decision_Tree_Assignment/dataset/Breast_Cancer.csv')

df = pd.read_csv(url)
```

---

## Notebook Workflow

| Step | Description |
|------|-------------|
| 1    | Import all required libraries |
| 2    | Load dataset from raw GitHub URL |
| 3    | Preprocess data (drop ID, encode target, fill missing values) |
| 4    | Train/test split (80/20, stratified) |
| 5    | GridSearchCV tuning for CART (Gini) |
| 6    | GridSearchCV tuning for ID3 (Entropy) |
| 7    | Generate all 5 required visualizations |
| 8    | Print final metrics summary and classification reports |

---

## Models

### CART (Gini)
- `DecisionTreeClassifier(criterion='gini')`
- Tuned with `GridSearchCV` over `max_depth` and `min_samples_split`
- 5-fold stratified cross-validation

### ID3 (Entropy)
- `DecisionTreeClassifier(criterion='entropy')`
- Tuned with `GridSearchCV` over `max_depth` and `min_samples_split`
- 5-fold stratified cross-validation

---

## Visualizations

1. **Decision Boundary** (1x2 subplot) - PCA reduces the 30 features to 2 dimensions for plotting. CART boundary on the left, ID3 on the right.
2. **Confusion Matrix** (1x2 subplot) - Heatmap showing TP, TN, FP, FN for both models side by side.
3. **ROC Curve** (1x2 subplot) - True Positive Rate vs False Positive Rate with AUC score in the legend.
4. **Metrics Bar Chart** (combined) - Grouped bars comparing Accuracy, Precision, Recall, F1-Score, and AUC for both models.
5. **Tree Structure** (1x2 subplot) - Visual tree plot using `sklearn.tree.plot_tree` showing the first 3 levels of each optimized tree.

---

## Results

| Metric    | CART (Gini) | ID3 (Entropy) |
|-----------|-------------|---------------|
| Accuracy  | 0.9211      | 0.9298        |
| Precision | 0.9024      | 1.0000        |
| Recall    | 0.8810      | 0.8095        |
| F1-Score  | 0.8916      | 0.8947        |
| AUC       | 0.9405      | 0.9431        |

> Results may vary slightly depending on the scikit-learn version.

---

## How to Run

1. Open the notebook in Google Colab using the Colab link below.
2. Click **Runtime > Run all**.
3. The notebook will automatically download the dataset from GitHub and run the full pipeline.

No manual file uploads are required.

---

## Dependencies

All packages below are pre-installed in Google Colab:

```
numpy
pandas
matplotlib
seaborn
scikit-learn
```

---

## Links

- **GitHub Repository:** `https://github.com/Marwanthe0/CSE`
- **Colab Notebook:** *(paste your Colab share link here)*

---

## Author

**Shafikul Islam Marwan**  
Third Year | Artificial Intelligence and Machine Learning Lab
