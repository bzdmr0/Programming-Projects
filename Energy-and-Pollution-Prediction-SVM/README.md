# Energy Consumption and Air Pollution Prediction using SVM

## Project Overview

This project implements **Support Vector Machine (SVM)** classifiers to predict future energy consumption levels and air pollution concentrations. It demonstrates a complete machine learning pipeline including data preparation, exploratory data analysis, custom kernel implementation, and model evaluation.

### Key Features
- ✅ Custom SVM implementation from scratch using QP solver (cvxopt)
- ✅ Multiple kernel types: Linear, RBF, Polynomial, and Custom (hybrid)
- ✅ Class-weighted SVM to handle imbalanced datasets
- ✅ Comprehensive hyperparameter tuning with k-fold cross-validation
- ✅ Time series feature engineering with trend analysis
- ✅ Detailed evaluation metrics (Accuracy, Precision, Recall, F1-Score)

---

## Dataset Description

### 1. Energy Consumption Dataset
- **Source**: AEP (American Electric Power) Hourly Data
- **File**: `Hourly_Energy_Consumption_AEP_hourly.csv`
- **Features**: 
  - Hourly electricity consumption measurements (in MW)
  - Time range: Historical hourly data
  - **Preprocessing**: Aggregated to daily averages

### 2. Air Pollution Dataset
- **Source**: Seoul Air Pollution Measurements
- **File**: `Air_Pollution_in_Seoul_Measurement_summary.csv`
- **Features**:
  - PM2.5 levels (μg/m³)
  - Additional pollutants: SO2, NO2, O3, CO, PM10
  - Station: Filtered to Station Code 101
  - **Preprocessing**: Aggregated to daily averages

### Target Variable (Classification)
- **Energy Consumption**: Binary classification
  - `0`: Next day's consumption ≤ mean consumption
  - `1`: Next day's consumption > mean consumption

- **Air Pollution**: Binary classification
  - `0`: Next day's PM2.5 ≤ 35 μg/m³ (healthy threshold)
  - `1`: Next day's PM2.5 > 35 μg/m³ (polluted threshold)

---

## Project Structure

```
Energy-and-Pollution-Prediction-SVM/
├── README.md                          # Project documentation
├── main.py                            # Main execution script
├── data_preparation.py                # Data preprocessing pipeline
├── eda.py                             # Exploratory Data Analysis
├── svm_model.py                       # Custom SVM implementation
├── training.py                        # Model training and evaluation
└── PA2_Datasets/                      # Data directory (not included)
    ├── Hourly_Energy_Consumption_AEP_hourly.csv
    └── Air_Pollution_in_Seoul_Measurement_summary.csv
```

---

## Module Details

### 1. **data_preparation.py** - `Data_Preparation` Class
Handles all data preprocessing steps:

```python
data_prep = Data_Prepration(AP_path="...", EC_path="...")
data_prep.preprocess()                          # Clean and aggregate data
data_prep.classification_problem_formulation()  # Create target labels
data_prep.feature_engineering()                 # Generate features
daily_AP, daily_EC = data_prep.get_datasets()   # Retrieve processed data
```

**Key Operations**:
- Filter by station code (101)
- Remove redundant columns
- Aggregate hourly data to daily averages
- Remove missing values and duplicates
- Create lagged features (v0-v6) for time series prediction
- Standardize features using StandardScaler

---

### 2. **eda.py** - `EDA` Class
Performs exploratory data analysis:

```python
eda = EDA(daily_EC, daily_AP)
eda.summary_statistics()         # Print descriptive statistics
eda.time_series_visualistation() # Plot time series trends
sizes_EC, sizes_AP = eda.class_dist_analysis()  # Analyze class distribution
```

**Outputs**:
- Statistical summaries (mean, std, min, max)
- Time series plots saved as PNG files
- Class distribution pie charts

---

### 3. **svm_model.py** - `SVM` Class
Custom SVM implementation using dual formulation and quadratic programming:

#### Constructor Parameters
```python
SVM(C=1.0,                    # Regularization parameter
    kernel="linear",          # Kernel type
    sigma=1.0,               # RBF kernel bandwidth
    poly_c=1.0,              # Polynomial kernel intercept
    poly_d=3.0,              # Polynomial kernel degree
    delta_sigma=1.0,         # Trend kernel bandwidth
    param_alpha=1/3,         # Custom kernel weight (linear)
    param_beta=1/3,          # Custom kernel weight (RBF)
    param_gamma=1/3)         # Custom kernel weight (trend)
```

#### Kernel Types
1. **Linear Kernel**
   ```
   K(x₁, x₂) = x₁ · x₂
   ```

2. **RBF Kernel** (Radial Basis Function)
   ```
   K(x₁, x₂) = exp(-||x₁ - x₂||² / (2σ²))
   ```

3. **Polynomial Kernel**
   ```
   K(x₁, x₂) = (x₁ · x₂ + c)ᵈ
   ```

4. **Custom Kernel** (Hybrid)
   ```
   K(x₁, x₂) = α·K_linear + β·K_rbf + γ·K_trend
   
   K_trend(x₁, x₂) = exp(-||Δx₁ - Δx₂||² / (2Δσ²))
   
   Where Δx represents the difference (trend) between consecutive features
   ```

#### Class-Weighted SVM
Handles imbalanced datasets by adjusting regularization:
- If minority class < 30% of data:
  - C_minority = C × (majority_count / minority_count)
  - C_majority = C

#### Methods
```python
model.fit(X_train, y_train)      # Train SVM on data
predictions = model.predict(X_test)  # Make predictions
```

---

### 4. **training.py** - `Trainer` Class
Manages model training and evaluation:

```python
trainer = Trainer(dataset)
trainer.dataset_split()                    # 80-20 train-test split
best_params = trainer.hyperparameter_tuning(hyperparams_dict)
model, results = trainer.full_train(kernel, params, enable_evaluation=True)
metrics = trainer.evaluation_on_test(model)
```

#### Hyperparameter Tuning Strategy
- **Method**: k-fold cross-validation (k=5)
- **Search Space**:
  - `C`: [0.1, 1.0, 10.0]
  - `sigma` (RBF): [0.1, 1.0, 10.0]
  - `d` (Polynomial): [2, 3]
  - `delta_sigma` (Custom): [0.1, 1.0, 10.0]
  - `trend_params` (Custom): [[1/3, 1/3, 1/3], [0.5, 0.3, 0.2]]

- **Optimization Metric**: Accuracy on validation fold
- **Training Limit**: Max 1000 samples per fold (computational efficiency)

#### Evaluation Metrics
```python
Accuracy  = (TP + TN) / (TP + TN + FP + FN)
Precision = TP / (TP + FP)
Recall    = TP / (TP + FN)
F1-Score  = 2 × (Precision × Recall) / (Precision + Recall)
```

---

## Main Execution Flow

The `main.py` script orchestrates the entire pipeline:

### Task 1: Data Preparation
```python
data_prep = Data_Prepration(AP_path, EC_path)
data_prep.preprocess()
data_prep.classification_problem_formulation()
data_prep.feature_engineering()
daily_AP, daily_EC = data_prep.get_datasets()
```
**Output**: Preprocessed datasets with engineered features

### Task 2: Exploratory Data Analysis
```python
eda = EDA(daily_EC, daily_AP)
eda.summary_statistics()           # Console output
eda.time_series_visualistation()   # PNG files
sizes_EC, sizes_AP = eda.class_dist_analysis()
```
**Output**: Statistical summaries and visualizations

### Task 3-5: Model Training & Evaluation
```python
# Hyperparameter tuning for all kernels
best_params_EC = trainer_EC.hyperparameter_tuning(hyperparams_list)
best_params_AP = trainer_AP.hyperparameter_tuning(hyperparams_list)

# Full training with best parameters
kernel_models_EC = {}
for kernel, params in best_params_EC.items():
    model, results = trainer_EC.full_train(kernel, params, enable_evaluation=True)
    kernel_models_EC[kernel] = (model, results)
```
**Output**: Trained models and evaluation metrics for all kernel types

---

## Usage Instructions

### Prerequisites
```bash
pip install pandas scikit-learn cvxopt numpy
```

### Running the Project
```bash
python main.py
```

### Expected Output
```
=================== Daily Energy Consumption Dataset Statistics========================
count     XXXX.000000
mean      XXXX.XXXXXX
std       XXXX.XXXXXX
min       XXXX.XXXXXX
25%       XXXX.XXXXXX
50%       XXXX.XXXXXX
75%       XXXX.XXXXXX
max       XXXX.XXXXXX

=================== Daily Air Pollution Dataset Statistics========================
[Similar statistics for PM2.5]

[Time series plots saved as PNG files]

[Hyperparameter tuning progress with timing information]

================= The Results of Electricity Consumption Prediction Model =================
linear Kernel Results:
Hyperparameters: C=1.0, sigma=1.0, d=2, Δsigma=1.0, trend_params=(α = 0.333, β = 0.333, γ = 0.333)
Accuracy: 0.XXX
Precision: 0.XXX
Recall: 0.XXX
F1 Score: 0.XXX

[Results for rbf, polynomial, and custom kernels...]

================= The Results of Air Pollution Prediction Model =================
[Similar output for air pollution model]
```

---

## Key Implementation Details

### 1. SVM Dual Formulation
The SVM optimization problem solved by cvxopt:

```
Minimize:  (1/2) α^T K α - 1^T α
Subject to: 0 ≤ αᵢ ≤ C
            Σ αᵢ yᵢ = 0
```

Where K is the kernel matrix and α are the Lagrange multipliers.

### 2. Support Vector Selection
Alphas above threshold (0.000001) are retained as support vectors:
```python
sv_threshold = 0.000001
sv_indices = alphas >= sv_threshold
```

### 3. Bias Calculation
Bias computed from support vectors satisfying 0 < αᵢ < C:
```python
bias = mean(yᵢ - Σ αⱼ yⱼ K(xⱼ, xᵢ))
```

### 4. Time Series Feature Engineering
Creates 7 lagged features (v0-v6):
```python
v₀ = PM2.5(t)
v₁ = PM2.5(t-1)
v₂ = PM2.5(t-2)
...
v₆ = PM2.5(t-6)
```

Target prediction: PM2.5(t+1)

---

## Results Interpretation

### Class Imbalance Handling
If minority class < 30% of dataset, the output indicates:
```
Note: The dataset is imbalanced. Class-weighted SVM was applied to handle the imbalance.
```

### Kernel Comparison
- **Linear**: Interpretable, fast training, suitable for simple patterns
- **RBF**: Non-linear, captures complex patterns, sensitive to σ
- **Polynomial**: Non-linear, useful for polynomial relationships
- **Custom**: Combines linear, RBF, and trend information for time series

---

## Limitations & Future Improvements

### Current Limitations
- Computational cost scales with training set size (O(n²) for QP)
- Limited to binary classification
- Trend kernel assumes equal-length feature vectors

### Potential Enhancements
- Implement SMO algorithm for faster convergence
- Add multi-class extension (one-vs-rest)
- Incorporate ARIMA features for better time series capture
- Use random sampling for large datasets
- Add cross-validation visualization

---

## Author
**Muhammet Sait Bozdemir** (2584738)  
CNG-409: Programming Assignment 2

---

## References
- Vapnik, V. N. (1995). *The Nature of Statistical Learning Theory*
- Schölkopf, B., & Smola, A. J. (2001). *Learning with Kernels*
- Boyd, S., & Vandenberghe, L. (2004). *Convex Optimization*

---

## License
Educational use for university assignment
