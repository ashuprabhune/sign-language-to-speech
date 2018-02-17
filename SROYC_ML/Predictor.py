import numpy as np
import pandas as pd
from sklearn.neighbors import KNeighborsClassifier

train_data = pd.read_csv('train_data.csv')
# Each series will be treated as one set by calculating the mean value i.e. averaging things out
reduced_ds = train_data.groupby(['series']).mean()
dimension_columns = ['thumb', 'index', 'middle', 'ring', 'pinky']

# Using KNN as classifier having euclidean distance as a mesaure of distance
classifier = KNeighborsClassifier(n_neighbors=3, weights='uniform', algorithm='auto', leaf_size=30, \
                                   p=2, metric='minkowski', metric_params=None, n_jobs=-1)

X_train = reduced_ds.as_matrix(columns=dimension_columns)
y_train = reduced_ds['class_label']
# Train the data set 
classifier.fit(X_train, y_train)

# # The following part is for testing, since I have no test data , using the same data for now
test_series = int(np.random.uniform(1, 14, size=1))
test_data = train_data[train_data.series == test_series]
# # Expecting all of the data set belongs to the same series
X_mean = test_data.mean()
X_test = list()
X_test.append(X_mean.as_matrix(columns=dimension_columns))
class_label = classifier.predict(X_test)

if class_label[0] == X_mean['class_label']:
    print('Prediction Class Label :  %s is correct.'%(class_label[0]))
else:
    print('Prediction Class Label :  %s is wrong.'%(class_label[0]))

