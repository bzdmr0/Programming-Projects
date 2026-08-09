# Muhammet Sait Bozdemir
# 2584738
# CNG-409 Programming Assignment 2

from svm_model import SVM
import numpy as np
import time

class Trainer:
    def __init__(self, dataset):
        self.dataset = dataset
        self.X_train = None
        self.y_train = None
        self.X_test = None
        self.y_test = None
        self.X_val = None
        self.y_val = None

    def dataset_split(self):
        feature_cols = [f"v{i}" for i in range(0,7)]
        X = self.dataset[feature_cols].values
        y = self.dataset["label"].values

        split_index = int(0.8 * len(X))
        self.X_train, self.X_test = X[:split_index], X[split_index:]
        self.y_train, self.y_test = y[:split_index], y[split_index:]

        self.y_train = np.where(self.y_train == 0, -1, 1).astype(float)
        self.y_test = np.where(self.y_test == 0, -1, 1).astype(float)

    def hyperparameter_tuning(self, hyperparams_list: dict) -> tuple[dict, float]:
        best_params = {} 

        n_folds = 5
        fold_size = len(self.X_train) // n_folds  # Approximate fold size

        for kernel in hyperparams_list["kernel"]:
            best_params[kernel] = {"C":float("-inf"), "d":float("-inf"), "sigma":float("-inf"), "delta_sigma":float("-inf"), "trend_params":[float("-inf"), float("-inf"), float("-inf")], "accuracy":float("-inf")}
            best_acc = float("-inf")
            if kernel == "linear":
                print(f"Tuning hyperparameters for kernel: {kernel}, time: {time.ctime()}")
                for C in hyperparams_list["C"]:
                    fold_accuracies = []
                    for fold_index in range(n_folds -1):

                        # train fold respectively 0 - 0.2, 0 - 0.4, 0 - 0.6, 0 - 0.8
                        train_end = (fold_index + 1) * fold_size

                        # validation fold respectively 0.2 - 0.4, 0.4 - 0.6, 0.6 - 0.8, 0.8 - full length
                        val_start = train_end
                        val_end = (fold_index + 2) * fold_size if fold_index < n_folds - 2 else len(self.X_train)

                        x_train = self.X_train[:train_end]
                        y_train = self.y_train[:train_end]

                        x_val = self.X_train[val_start:val_end]
                        y_val = self.y_train[val_start:val_end]

                        max_train_samples = 1000
                        if len(x_train) > max_train_samples:
                            x_train = x_train[-max_train_samples:]
                            y_train = y_train[-max_train_samples:]
                        else:
                            x_train = x_train
                            y_train = y_train
                        
                        model = SVM(C, kernel)
                        model.fit(x_train, y_train)

                        preds = model.predict(x_val)

                        acc, _, _, _ = self.__get_evaluation_metrics(preds, y_val)
                        fold_accuracies.append(acc)

                    avg_acc = np.mean(fold_accuracies)
                    if avg_acc > best_acc:
                        best_acc = avg_acc
                        best_params[kernel]["C"] = C
                        best_params[kernel]["accuracy"] = best_acc
                print(f"End time: {time.ctime()}")
                print(f"Best params for kernel {kernel}: C = {best_params[kernel]['C']}, accuracy={best_acc:.3f}\n")
            
            elif kernel == "rbf":
                print(f"Tuning hyperparameters for kernel: {kernel}, time: {time.ctime()}")
                for C in hyperparams_list["C"]:
                    for sigma in hyperparams_list["sigma"]:
                        fold_accuracies = []
                        for fold_index in range(n_folds -1):

                            # train fold respectively 0 - 0.2, 0 - 0.4, 0 - 0.6, 0 - 0.8
                            train_end = (fold_index + 1) * fold_size

                            # validation fold respectively 0.2 - 0.4, 0.4 - 0.6, 0.6 - 0.8, 0.8 - full length
                            val_start = train_end
                            val_end = (fold_index + 2) * fold_size if fold_index < n_folds - 2 else len(self.X_train)

                            x_train = self.X_train[:train_end]
                            y_train = self.y_train[:train_end]

                            x_val = self.X_train[val_start:val_end]
                            y_val = self.y_train[val_start:val_end]

                            max_train_samples = 1000
                            if len(x_train) > max_train_samples:
                                x_train = x_train[-max_train_samples:]
                                y_train = y_train[-max_train_samples:]
                            else:
                                x_train = x_train
                                y_train = y_train
                            
                            model = SVM(C, kernel, sigma)
                            model.fit(x_train, y_train)

                            preds = model.predict(x_val)

                            acc, _, _, _ = self.__get_evaluation_metrics(preds, y_val)
                            fold_accuracies.append(acc)

                        avg_acc = np.mean(fold_accuracies)
                        if avg_acc > best_acc:
                            best_acc = avg_acc
                            best_params[kernel]["C"] = C
                            best_params[kernel]["sigma"] = sigma
                            best_params[kernel]["accuracy"] = best_acc
                print(f"End time: {time.ctime()}")
                print(f"Best params for kernel {kernel}: C = {best_params[kernel]['C']}, sigma = {best_params[kernel]['sigma']}, accuracy={best_acc:.3f}\n")

            elif kernel == "polynomial":
                print(f"Tuning hyperparameters for kernel: {kernel}, time: {time.ctime()}")
                for C in hyperparams_list["C"]:
                    for d in hyperparams_list["d"]:
                        fold_accuracies = []
                        for fold_index in range(n_folds -1):

                            # train fold respectively 0 - 0.2, 0 - 0.4, 0 - 0.6, 0 - 0.8
                            train_end = (fold_index + 1) * fold_size

                            # validation fold respectively 0.2 - 0.4, 0.4 - 0.6, 0.6 - 0.8, 0.8 - full length
                            val_start = train_end
                            val_end = (fold_index + 2) * fold_size if fold_index < n_folds - 2 else len(self.X_train)

                            x_train = self.X_train[:train_end]
                            y_train = self.y_train[:train_end]

                            x_val = self.X_train[val_start:val_end]
                            y_val = self.y_train[val_start:val_end]

                            max_train_samples = 1000
                            if len(x_train) > max_train_samples:
                                x_train = x_train[-max_train_samples:]
                                y_train = y_train[-max_train_samples:]
                            else:
                                x_train = x_train
                                y_train = y_train
                            
                            model = SVM(C, kernel, poly_d=d, poly_c=1)
                            model.fit(x_train, y_train)

                            preds = model.predict(x_val)

                            acc, _, _, _ = self.__get_evaluation_metrics(preds, y_val)
                            fold_accuracies.append(acc)

                        avg_acc = np.mean(fold_accuracies)
                        if avg_acc > best_acc:
                            best_acc = avg_acc
                            best_params[kernel]["C"] = C
                            best_params[kernel]["d"] = d
                            best_params[kernel]["accuracy"] = best_acc
                print(f"End time: {time.ctime()}")
                print(f"Best params for kernel {kernel}: C = {best_params[kernel]['C']}, d = {best_params[kernel]['d']}, accuracy = {best_acc:.3f}\n")

            elif kernel == "custom":
                print(f"Tuning hyperparameters for kernel: {kernel}, time: {time.ctime()}")
                for C in hyperparams_list["C"]:
                    for sigma in hyperparams_list["sigma"]:
                        for delta_sigma in hyperparams_list["delta_sigma"]:
                            for trend_params in hyperparams_list["trend_params"]:
                                fold_accuracies = []
                                for fold_index in range(n_folds -1):

                                    # train fold respectively 0 - 0.2, 0 - 0.4, 0 - 0.6, 0 - 0.8
                                    train_end = (fold_index + 1) * fold_size

                                    # validation fold respectively 0.2 - 0.4, 0.4 - 0.6, 0.6 - 0.8, 0.8 - full length
                                    val_start = train_end
                                    val_end = (fold_index + 2) * fold_size if fold_index < n_folds - 2 else len(self.X_train)

                                    x_train = self.X_train[:train_end]
                                    y_train = self.y_train[:train_end]

                                    x_val = self.X_train[val_start:val_end]
                                    y_val = self.y_train[val_start:val_end]

                                    max_train_samples = 1000
                                    if len(x_train) > max_train_samples:
                                        x_train = x_train[-max_train_samples:]
                                        y_train = y_train[-max_train_samples:]
                                    else:
                                        x_train = x_train
                                        y_train = y_train
                                    
                                    model = SVM(C, kernel, sigma=sigma, delta_sigma=delta_sigma, param_alpha=trend_params[0], param_beta=trend_params[1], param_gamma=trend_params[2])
                                    model.fit(x_train, y_train)

                                    preds = model.predict(x_val)

                                    acc, _, _, _ = self.__get_evaluation_metrics(preds, y_val)
                                    fold_accuracies.append(acc)

                                avg_acc = np.mean(fold_accuracies)
                                if avg_acc > best_acc:
                                    best_acc = avg_acc
                                    best_params[kernel]["C"] = C
                                    best_params[kernel]["sigma"] = sigma
                                    best_params[kernel]["delta_sigma"] = delta_sigma
                                    best_params[kernel]["trend_params"] = trend_params
                                    best_params[kernel]["accuracy"] = best_acc
                print(f"End time: {time.ctime()}")
                print(f"Best params for kernel {kernel}: C = {best_params[kernel]['C']}, sigma = {best_params[kernel]['sigma']}, delta_sigma = {best_params[kernel]['delta_sigma']}, trend_params = {best_params[kernel]['trend_params']}, accuracy={best_acc:.3f}\n")
            else:
                print(f"Invalid kernel: {kernel}. Skipping hyperparameter tuning for this kernel.")

        return best_params
    
    def full_train(self, kernel, hyperparams: dict, enable_evaluation : bool = False) -> SVM | tuple[SVM, dict]:
        if kernel == "linear":
            model = SVM(C=hyperparams['C'], kernel=kernel)
            print(f"Training %80 of dataset with linear kernel started {time.ctime()}\n")
        elif kernel == "rbf":
            model = SVM(C=hyperparams['C'], kernel=kernel, sigma=hyperparams['sigma'])
            print(f"Training %80 of dataset with rbf kernel started {time.ctime()}\n")
        elif kernel == "polynomial":
            model = SVM(C=hyperparams['C'], kernel=kernel, poly_d=hyperparams['d'], poly_c=1)
            print(f"Training %80 of dataset with polynomial kernel started {time.ctime()}\n")
        elif kernel == "custom":
            model = SVM(C=hyperparams['C'], kernel=kernel, sigma=hyperparams['sigma'], delta_sigma=hyperparams['delta_sigma'], param_alpha=hyperparams['trend_params'][0], param_beta=hyperparams['trend_params'][1], param_gamma=hyperparams['trend_params'][2])
            print(f"Training %80 of dataset with custom kernel started {time.ctime()}\n")
        else:
            print(f"Invalid kernel: {kernel}. Using linear kernel by default.")
            model = SVM(C=10, kernel="linear")

        model.fit(self.X_train, self.y_train)
        print(f"Training completed {time.ctime()}\n")

        if enable_evaluation == True:
            metrics = self.evaluation_on_test(model)
            return model, metrics

        return model
    
    def evaluation_on_test(self, model : SVM) -> dict:
        preds = model.predict(self.X_test)

        accuracy, precision, recall, f1 = self.__get_evaluation_metrics(preds, self.y_test)

        metrics = {
            "Accuracy": accuracy,
            "Precision": precision,
            "Recall": recall,
            "F1 Score": f1
        }
        
        return metrics

    def __get_evaluation_metrics(self, preds, labels) -> tuple[float, float, float, float]:
        TP = np.sum((preds == 1) & (labels == 1))
        FP = np.sum((preds == 1) & (labels == -1))
        TN = np.sum((preds == -1) & (labels == -1))
        FN = np.sum((preds == -1) & (labels == 1))

        accuracy = (TP + TN) / (TP + TN + FP + FN) if (TP + TN + FP + FN) > 0 else 0
        precision = TP / (TP + FP) if TP + FP > 0 else 0
        recall = TP / (TP + FN) if TP + FN > 0 else 0
        f1 = (2 * precision * recall) / (precision + recall) if (precision + recall) > 0 else 0

        return accuracy, precision, recall, f1