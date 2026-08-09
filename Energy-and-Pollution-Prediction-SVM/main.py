# Muhammet Sait Bozdemir
# 2584738
# CNG-409 Programming Assignment 2


from data_preparation import *
from eda import *
from svm_model import *
from training import *

""" 
EC stands for Energy Consumption
AP stands for Air Pollution
"""

if __name__ == "__main__":
    air_pollution_dataset_path = "PA2_Datasets/Air_Pollution_in_Seoul_Measurement_summary.csv"
    energy_consumption_dataset_path = "PA2_Datasets/Hourly_Energy _Consumption_AEP_hourly.csv"

    # Task 1 
    data_prep = Data_Prepration(air_pollution_dataset_path, energy_consumption_dataset_path)
    data_prep.preprocess()
    data_prep.classification_problem_formulation()
    data_prep.feature_engineering()
    (daily_AP, daily_EC) = data_prep.get_datasets()

    # Task 2
    eda = EDA(daily_EC, daily_AP)
    eda.summary_statistics()
    eda.time_series_visualistation()
    sizes_EC, sizes_AP = eda.class_dist_analysis()

    # Task 3, 4 & 5
    hyperparams_list = {
        "kernel": ["linear", "rbf", "polynomial", "custom"],
        "C": [0.1, 1.0, 10.0],
        "sigma": [0.1, 1.0, 10.0],
        "d": [2, 3],
        "delta_sigma": [0.1, 1.0, 10.0],
        "trend_params": [[1/3, 1/3, 1/3], [0.5, 0.3, 0.2]]
    }

    trainer_AP = Trainer(daily_AP)
    trainer_EC = Trainer(daily_EC)

    trainer_AP.dataset_split()
    trainer_EC.dataset_split()


    print("\n==========Starting hyperparameter tuning for Energy Consumption Prediction Model ==============")
    best_params_EC = trainer_EC.hyperparameter_tuning(hyperparams_list)
    print("\n==========Starting hyperparameter tuning for Air Pollution Prediction Model ==============")
    best_params_AP = trainer_AP.hyperparameter_tuning(hyperparams_list)
    

    print("\n==========Training Energy Consumption Prediction Model with Best Hyperparameters ==============")
    kernel_models_EC = {}
    for kernel, params in best_params_EC.items():
        model, results = trainer_EC.full_train(kernel, params, enable_evaluation=True)
        kernel_models_EC[kernel] = (model, results)
    print("\n==========Training Air Pollution Prediction Model with Best Hyperparameters ==============")
    kernel_models_AP = {}
    for kernel, params in best_params_AP.items():
        model, results = trainer_AP.full_train(kernel, params, enable_evaluation=True)
        kernel_models_AP[kernel] = (model, results)

    print("\n================= The Results of Electricity Consumption Prediction Model =================")
    if sizes_EC.min() / (sizes_EC.max() + sizes_EC.min()) < 0.3:
        print("Note: The dataset is imbalanced. Class-weighted SVM was applied to handle the imbalance.")
    for kernel, (model, results) in kernel_models_EC.items():
        print(f"\n{kernel} Kernel Results:")
        print(f"Hyperparameters: C={model.C}, sigma={model.sigma}, d={model.poly_d}, Δsigma={model.delta_sigma}, trend_params=(α = {model.param_alpha}, β = {model.param_beta}, γ = {model.param_gamma})")
        for eval_metric, value in results.items():
            print(f"{eval_metric}: {value:.3f}")
    print("\n================= The Results of Air Pollution Prediction Model =================")
    if sizes_AP.min() / (sizes_AP.max() + sizes_AP.min()) < 0.3:
        print("Note: The dataset is imbalanced. Class-weighted SVM was applied to handle the imbalance.")
    for kernel, (model, results) in kernel_models_AP.items():
        print(f"\n{kernel} Kernel Results:")
        print(f"Hyperparameters: C={model.C}, sigma={model.sigma}, d={model.poly_d}, Δsigma={model.delta_sigma}, trend_params=(α = {model.param_alpha}, β = {model.param_beta}, γ = {model.param_gamma})")
        for eval_metric, value in results.items():
            print(f"{eval_metric}: {value:.3f}")