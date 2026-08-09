# Muhammet Sait Bozdemir
# 2584738
# CNG-409 Programming Assignment 2

import pandas as pd
from sklearn.preprocessing import StandardScaler

class Data_Prepration:
    def __init__(self, AP_path = "PA2_Datasets/Hourly_Energy _Consumption_AEP_hourly.csv", EC_path = "PA2_Datasets/Air_Pollution_in_Seoul_Measurement_summary.csv"):
        self.hourly_EC = pd.read_csv(EC_path, parse_dates=["Datetime"])
        self.hourly_AP = pd.read_csv(AP_path, parse_dates=["Measurement date"])

    def preprocess(self):
        # Filtering for station code
        self.hourly_AP = self.hourly_AP[self.hourly_AP["Station code"] == 101]

        # Removing the redundant columns and of air pollution dataset
        self.hourly_AP = self.hourly_AP.drop(["Address", "Latitude", "Longitude", "SO2", "NO2", "O3", "CO", "PM10"], axis=1)

        # Creating Date columns
        self.hourly_AP["Date"] = self.hourly_AP["Measurement date"].dt.date
        self.hourly_EC["Date"] = self.hourly_EC["Datetime"].dt.date

        # Group by date columns and take the mean
        self.daily_AP = self.hourly_AP.groupby("Date").mean().reset_index()
        self.daily_EC = self.hourly_EC.groupby("Date").mean().reset_index()

        # Retain only the relevant columns
        self.daily_AP = self.daily_AP.drop(["Measurement date", "Station code"], axis=1)
        self.daily_EC = self.daily_EC.drop("Datetime", axis=1)

        # remove missing values
        self.daily_EC = self.daily_EC.dropna()
        self.daily_AP = self.daily_AP.dropna()

        # remove duplicates
        self.daily_EC = self.daily_EC.drop_duplicates(subset=["Date"])
        self.daily_AP = self.daily_AP.drop_duplicates(subset=["Date"])

        # Ensuring the chronological order
        if not self.daily_AP['Date'].is_monotonic_increasing:
            self.daily_AP = self.daily_AP.sort_values('Date').reset_index(drop=True)
        if not self.daily_EC['Date'].is_monotonic_increasing:
            self.daily_EC = self.daily_EC.sort_values('Date').reset_index(drop=True)

        # Checking the the negative measurements and remove them
        self.daily_EC = self.daily_EC[self.daily_EC["AEP_MW"] >= 0]
        self.daily_AP = self.daily_AP[self.daily_AP['PM2.5'] >= 0]

    def classification_problem_formulation(self):
        # Energy Consumption

        # taking mean
        mean_EC = self.daily_EC["AEP_MW"].mean()
        # shift one row behind to reach next element and put 1 if next row is bigger than mean else 0.
        self.daily_EC["label"] = (self.daily_EC["AEP_MW"].shift(-1) > mean_EC).astype(int)
        # delete last row
        self.daily_EC = self.daily_EC.iloc[:-1]

        # Air Pollution

        # shift one row behind to reach next element and put 1 if next row is bigger than threshold else 0.
        self.daily_AP["label"] = (self.daily_AP["PM2.5"].shift(-1) > 35).astype(int)
        # delete last row
        self.daily_AP = self.daily_AP.iloc[:-1]

    def feature_engineering(self):
        for feature in range(0,7):
            self.daily_EC[f"v{feature}"] = self.daily_EC["AEP_MW"].shift(feature)
            self.daily_AP[f"v{feature}"] = self.daily_AP["PM2.5"].shift(feature)


        # remove missing values
        self.daily_EC = self.daily_EC.dropna().reset_index(drop=True)
        self.daily_AP = self.daily_AP.dropna().reset_index(drop=True)

        # normalization of AP features
        scaler = StandardScaler()

        feature_cols = [f"v{i}" for i in range(0,7)]
        self.daily_AP[feature_cols] = scaler.fit_transform(self.daily_AP[feature_cols])
        self.daily_EC[feature_cols] = scaler.fit_transform(self.daily_EC[feature_cols])

    def get_datasets(self) -> tuple[pd.DataFrame, pd.DataFrame]:
        return (self.daily_AP, self.daily_EC)
