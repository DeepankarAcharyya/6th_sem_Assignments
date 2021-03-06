# -*- coding: utf-8 -*-
"""knn
Submitted by: Deepankar Acharyya , CSB17017

Automatically generated by Colaboratory.
Original file is located at
    https://colab.research.google.com/drive/1yBXmJFCVZj2Z8mXUQtHxjh7bxCKK4dTA
"""

import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.datasets.base import Bunch
from sklearn.preprocessing import LabelEncoder
from sklearn.base import BaseEstimator, TransformerMixin

"""# Read in the data and explore it"""

#attribute list
col_names = ['age','workclass','fnlwgt','education','education-num','marital-status','occupation','relationship','race','sex','capital-gain','capital-loss','hours-per-week','native-country','income',]

#reading in the data
adult_data_train=pd.read_csv('adult.data',names=col_names)
adult_data_predict= pd.read_csv('adult.test', names=col_names, skiprows=1)

sns.countplot(y='occupation', hue='income', data=adult_data_train,)

sns.countplot(y='education', hue='income', data=adult_data_train,)

sns.countplot(y='sex', hue='income', data=adult_data_train,)

sns.countplot(y='race', hue='income', data=adult_data_train,)

sns.countplot(x='hours-per-week', hue='income', data=adult_data_train,)

"""# Preprocessing the data"""

#1. Replace the Nan/Missing data values with mode values
attr_list=list(col_names)
attr_list.remove('income')

for col in attr_list:
    mode=adult_data_train[col].mode()
    adult_data_train[col].fillna(mode)

for col in attr_list:
    mode=adult_data_predict[col].mode()
    adult_data_predict[col].fillna(mode)

#2. For encoding the categorical data
class EncodeCategorical(BaseEstimator, TransformerMixin):
    """
    Encodes a specified list of columns or all columns if None.
    """
    def __init__(self, columns=None):
        self.columns  = columns
        self.encoders = None
    def fit(self, data, target=None):
        """
        Expects a data frame with named columns to encode.
        """
        # Encode all columns if columns is None
        if self.columns is None:
            self.columns = data.columns
        # Fit a label encoder for each column in the data frame
        self.encoders = {
            column: LabelEncoder().fit(data[column])
            for column in self.columns
        }
        return self
    def transform(self, data):
        """
        Uses the encoders to transform a data frame.
        """
        output = data.copy()
        for column, encoder in self.encoders.items():
            output[column] = encoder.transform(data[column])
        return output
    
encoder = EncodeCategorical(col_names)
data = encoder.fit_transform(adult_data_train)
data_predict=encoder.fit_transform(adult_data_predict)

#3. Split into the train and test sets
from sklearn.model_selection import train_test_split
X_train,X_test,y_train,y_test=train_test_split(data,adult_data_train['income'],test_size=0.2)

"""The KNN Model"""

#1.Find the optimum value of k
from sklearn.neighbors import KNeighborsClassifier
from sklearn import metrics

k_range=range(1,20)
scores={}
scores_list=[]

for k in k_range:
    knn=KNeighborsClassifier(n_neighbors=k)
    knn.fit(X_train,y_train)
    y_pred=knn.predict(X_test)
    sc=metrics.accuracy_score(y_test,y_pred)
    scores[k]=sc
    scores_list.append(sc)
    
plt.plot(k_range,scores_list)
plt.xlabel('K value for KNN')
plt.ylabel('Testing Accuracy')

#Train the knn model with optimum value of k
k_optimum=17
knn=KNeighborsClassifier(n_neighbors=k_optimum)
knn.fit(X_train,y_train)
knn.score(X_test, y_test)

#predict the value for the test sets
prediction=knn.predict(data_predict)

pred=pd.DataFrame(prediction,columns=['pred'])
sns.countplot(y='pred',data=pred,)