# Muhammet Sait Bozdemir
# 2584738
# CNG-409 Programming Assignment 2

import numpy as np
import cvxopt

np.random.seed(409)

class SVM:
    def __init__(self, C : float = 1.0, kernel : None | str = "linear", sigma : float = 1.0, poly_c : float = 1.0, poly_d : float = 3.0, delta_sigma : float = 1.0, param_alpha : float = 1/3, param_beta : float = 1/3, param_gamma : float = 1/3):
        self.C = C
        self.kernel = "linear" if kernel is None else kernel.lower()
        self.support_vectors = None
        self.sv_alphas = None
        self.sv_labels = None
        self.bias = 0.0
        self.sigma = sigma
        self.delta_sigma = delta_sigma
        self.poly_c = poly_c
        self.poly_d = poly_d
        self.param_alpha = param_alpha
        self.param_beta = param_beta
        self.param_gamma = param_gamma

    def fit(self, X : np.ndarray, y : np.ndarray):
        n_samples, _ = X.shape  

        # bonus part: class-weighted SVM
        n_positive = np.sum(y == 1)
        n_negative = np.sum(y == -1)
        if n_positive > n_negative:
            majority_count = n_positive
            minority_count = n_negative
            minority_label = -1
        else:
            majority_count = n_negative
            minority_count = n_positive
            minority_label = 1

        if minority_count / (majority_count + minority_count) < 0.3:
            C_minority = self.C * (majority_count / minority_count) if minority_count > 0 else self.C
            C_vector = np.where(y == minority_label, C_minority, self.C)
        else:
            C_vector = np.ones(n_samples) * self.C
            
        # compute the kernel matrix K[x_i, x_j]
        K = np.zeros((n_samples, n_samples))
        for i in range(n_samples):
            for j in range(n_samples):
                if self.kernel == "linear":
                    K[i, j] = self.__linear_kernel(X[i], X[j])
                elif self.kernel == "polynomial":
                    K[i, j] = self.__poly_kernel(X[i], X[j])
                elif self.kernel == "rbf":
                    K[i, j] = self.__rbf_kernel(X[i], X[j])
                elif self.kernel == "custom":
                    K[i, j] = self.__custom_kernel(X[i], X[j])
                else:
                    print("Invalid value for kernel, linear kernel was choosen automatically")
                    K[i, j] = self.__linear_kernel(X[i], X[j])

        # the parameters of cvxopt.solvers.qp
        # minimize (1/2) * x^T * P * x + q^T * x  -->  minimize (1/2) * sum(alpha_i * alpha_j * y_i * y_j * K(xi, xj)) - sum(alpha)
        # subject to: G * x <= h, A * x = b  -->  alpha_i <= C, sum(alpha_i * y_i) = 0

        P = cvxopt.matrix(np.outer(y, y) * K)

        # q = -1
        q = cvxopt.matrix(-np.ones(n_samples))

        # constraints
        G = cvxopt.matrix(np.vstack((-np.eye(n_samples), np.eye(n_samples))))
        h = cvxopt.matrix(np.hstack((np.zeros(n_samples), C_vector)))
        A = cvxopt.matrix(y.reshape(1, -1))
        b = cvxopt.matrix(np.zeros(1))

        # solving Quadratic Programming problem
        cvxopt.solvers.options['show_progress'] = False

        solution = cvxopt.solvers.qp(P, q, G, h, A, b)

        alphas = np.array(solution["x"]).flatten()

        # 0.000001 ≤ αi for the constraint 0 ≤ αi ≤ C because of computational efficiency
        sv_threshold = 0.000001
        sv_indices = alphas >= sv_threshold
        
        # Dual Form SVM model parameters
        self.support_vectors = X[sv_indices]
        self.sv_alphas = alphas[sv_indices]
        self.sv_labels = y[sv_indices]

        # finding bias
        Ns = len(self.support_vectors)
        bias_sum = 0.0
        for i in range(Ns):
            inner_sum = 0.0
            for j in range(Ns):
                if self.kernel == "linear":
                    inner_sum += self.sv_alphas[j] * self.sv_labels[j] * self.__linear_kernel(self.support_vectors[j], self.support_vectors[i])
                elif self.kernel == "polynomial":
                    inner_sum += self.sv_alphas[j] * self.sv_labels[j] * self.__poly_kernel(self.support_vectors[j], self.support_vectors[i])
                elif self.kernel == "rbf":
                    inner_sum += self.sv_alphas[j] * self.sv_labels[j] * self.__rbf_kernel(self.support_vectors[j], self.support_vectors[i])
                elif self.kernel == "custom":
                    inner_sum += self.sv_alphas[j] * self.sv_labels[j] * self.__custom_kernel(self.support_vectors[j], self.support_vectors[i])
                else:
                    print("Invalid value for kernel, linear kernel was choosen automatically")
                    inner_sum += self.sv_alphas[j] * self.sv_labels[j] * self.__linear_kernel(self.support_vectors[j], self.support_vectors[i])
            bias_sum += self.sv_labels[i] - inner_sum
        if Ns > 0:
            self.bias = bias_sum / Ns
        else:
            self.bias = 0.0

    def predict(self, X : np.ndarray) -> np.ndarray:
        n_samples = X.shape[0]
        preds = np.zeros(n_samples)

        for i in range(n_samples):
            output = 0.0
            for alpha, support_vector, sv_label in zip(self.sv_alphas, self.support_vectors, self.sv_labels):
                if self.kernel == "linear":
                    output += alpha * sv_label * self.__linear_kernel(X[i], support_vector)
                elif self.kernel == "polynomial":
                    output += alpha * sv_label * self.__poly_kernel(X[i], support_vector)
                elif self.kernel == "rbf":
                    output += alpha * sv_label * self.__rbf_kernel(X[i], support_vector)
                elif self.kernel == "custom":
                    output += alpha * sv_label * self.__custom_kernel(X[i], support_vector)
                else:
                    print("Invalid value for kernel, linear kernel was choosen automatically")
                    output += alpha * sv_label * self.__linear_kernel(X[i], support_vector)
            output += self.bias
            preds[i] = np.sign(output)

        return preds

    def __linear_kernel(self, x1, x2) -> float:
        return np.dot(x1, x2)
    
    def __rbf_kernel(self, x1, x2) -> float:
        return np.exp(-(np.linalg.norm(x1-x2) ** 2)/(2 * self.sigma ** 2))
    
    def __poly_kernel(self, x1, x2) -> float:
        return (np.dot(x1, x2) + self.poly_c) ** self.poly_d
    
    def __trend_kernel(self, x1, x2) -> float:
        delta_x1 = np.diff(x1)
        delta_x2 = np.diff(x2)
        return np.exp(-(np.linalg.norm(delta_x1-delta_x2) ** 2)/(2 * self.delta_sigma ** 2))

    def __custom_kernel(self, x1 : np.ndarray, x2 : np.ndarray) -> float:
        linear_part = self.__linear_kernel(x1, x2)
        rbf_part = self.__rbf_kernel(x1, x2)
        trend_part = self.__trend_kernel(x1, x2)

        return self.param_alpha * linear_part + self.param_beta * rbf_part + self.param_gamma * trend_part
