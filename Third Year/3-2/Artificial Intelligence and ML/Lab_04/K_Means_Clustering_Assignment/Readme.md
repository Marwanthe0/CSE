# K-Means Clustering - Image Color Quantization

**Student ID:** 220121

---

## Project Overview

This project applies K-Means Clustering to perform **Image Color Quantization**. A K-Means model is trained on the RGB pixel values of a DIV2K high-resolution image to learn a compact 8-color palette. The trained model is then applied to a custom smartphone photograph to compress its colors into the learned palette, without any additional fitting.

---

## Dataset

| Data | File | Purpose |
|------|------|---------|
| DIV2K Image | `Dataset/K_means_Clustering_img.png` | Training the K-Means model |
| Custom Smartphone Photo | `Dataset/custom_image.jpg` | Real-world testing and quantization |

---

## Repository Structure

```
K_Means_Clustering_Assignment/
├── Dataset/
│   ├── K_means_Clustering_img.png    # DIV2K high-resolution training image
│   └── custom_image.jpg              # Custom smartphone photo (test data)
├── model/
│   └── 220121.pkl                    # Saved K-Means model + StandardScaler bundle
├── 220121.ipynb                      # Google Colab notebook (run all cells)
└── README.md                         # This file
```

---

## How to Run

1. Open `220121.ipynb` in Google Colab.
2. Click **Runtime > Run All**.
3. The notebook will automatically clone this repository, load both images, run the elbow method, fit the model, and output all plots and predictions.

No manual file uploads are needed.

---

## Workflow Summary

1. Each pixel (R, G, B) from the DIV2K image is treated as a 3-feature data point.
2. 50,000 pixels are sampled at random and normalized with `StandardScaler`.
3. The Elbow Method is run for K = 2 to 11 to find the optimal K.
4. **K = 8** is selected based on the elbow bend in the WCSS curve.
5. K-Means is fitted to the scaled sample. The model and scaler are saved as `220121.pkl`.
6. The same fitted scaler is applied to the custom image pixels (no refitting).
7. `model.predict()` assigns each custom image pixel to one of the 8 learned clusters.
8. The custom image is reconstructed using only the 8 centroid colors.

---

## Visual Outputs (Generated in Notebook)

### Elbow Curve
A line plot of WCSS vs. K (2 to 11) showing a clear bend at K = 8.

### 3D RGB Cluster Scatter Plot
A 3D scatter plot of sampled training pixels colored by cluster, with black star markers at the centroids.

### Centroid Color Palette
Eight colored patches showing the exact RGB color each cluster centroid represents.

### Original vs. Quantized Image
Side-by-side comparison of the custom smartphone photo (original) and the color-quantized version using only 8 colors.

### Custom Prediction Table
A 10-row table showing sample pixel locations, their original RGB values, and their assigned cluster IDs.

### Cluster Distribution Bar Chart
Bar chart showing what percentage of the custom image belongs to each cluster.

---

## Cluster Interpretation

| Cluster | Dominant Color | Description |
|---------|---------------|-------------|
| 0 | Dark tones | Deep shadows and very dark areas with low values in all channels |
| 1 | Warm neutrals | Sunlit sandy or beige surfaces with high and balanced RGB values |
| 2 | Natural green | Grass, foliage, and vegetation where the Green channel dominates |
| 3 | Sky blue | Clear sky and water bodies where the Blue channel dominates |
| 4 | Warm red or brown | Brick, earth, and wood surfaces with high Red and moderate Green |
| 5 | Mid-range gray | Concrete, asphalt, and overcast sky with balanced mid-range RGB |
| 6 | Bright white | Sunlit highlights, clouds, and white surfaces with very high RGB |
| 7 | Dark green | Shaded vegetation and dense foliage with suppressed overall brightness |

**Clusters 2 and 3 capture the outdoor natural colors (green grass and blue sky). Clusters 4 and 5 represent man-made structures (brick buildings and concrete paths). Clusters 0 and 6 handle the lighting range from deep shadows to bright highlights. The model reduces the thousands of unique pixel colors in the custom photo to just 8 representative palette entries while preserving the main visual structure of the scene.**

---

## Dependencies

```
numpy
pandas
matplotlib
Pillow
scikit-learn
joblib
```

All dependencies are pre-installed in Google Colab.
