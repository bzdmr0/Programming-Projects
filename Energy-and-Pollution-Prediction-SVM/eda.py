# Muhammet Sait Bozdemir
# 2584738
# CNG-409 Programming Assignment 2

import matplotlib.pyplot as plt
import pandas as pd

class EDA:
    def __init__(self, daily_EC : pd.DataFrame, daily_AP : pd.DataFrame):
        self.daily_EC = daily_EC
        self.daily_AP = daily_AP

    def summary_statistics(self):
        print("=================== Daily Energy Consumption Dataset Statistics========================")
        print(self.daily_EC["AEP_MW"].describe())
        print("\n=================== Daily Air Pollution Dataset Statistics========================")
        print(self.daily_AP["PM2.5"].describe())
        
      
    def time_series_visualistation(self):
        plt.figure(figsize=(14, 7))
        plt.plot(self.daily_EC["Date"], self.daily_EC["AEP_MW"])
        plt.title("Daily AEP MW Over Time")
        plt.xlabel("Date")
        plt.ylabel("AEP MW")
        plt.xticks(rotation=45)
        plt.savefig("daily_EC_time_series.png")
        plt.show()

        # Plot for Air Pollution
        plt.figure(figsize=(14, 7))
        plt.plot(self.daily_AP["Date"], self.daily_AP["PM2.5"])
        plt.title("Daily PM2.5 Levels Over Time")
        plt.xlabel("Date")
        plt.ylabel("PM2.5")
        plt.xticks(rotation=45)
        plt.savefig("daily_AP_time_series.png")
        plt.show()

    def class_dist_analysis(self):
        plt.figure(figsize=(10,5))
        labels_EC = ["Lower equal than average (0)", "Higher than average (1)"]
        sizes_EC = self.daily_EC['label'].value_counts().sort_index()
        plt.pie(sizes_EC, labels=labels_EC, startangle=90, autopct='%1.1f%%')
        plt.title("Electricity Consumption Labels")
        plt.savefig("EC_labels_pie.png")
        plt.show()

        plt.figure(figsize=(7,5))
        labels_AP = ["Lower equal than threshold 35 (0)", "Higher than threshold 35 (1)"]
        sizes_AP = self.daily_AP['label'].value_counts().sort_index()
        plt.pie(sizes_AP, labels=labels_AP, startangle=90, autopct='%1.1f%%')
        plt.title("Air Pollution Labels")
        plt.savefig("AP_labels_pie.png")
        plt.show()

        return sizes_EC, sizes_AP