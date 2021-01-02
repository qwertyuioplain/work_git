
#tensorflow tutorial(Image classfication)
#classify cat image and dog image

#ライブラリ

#tensorflow（tfに省略）
import tensorflow as tf 
#
from tensorflow.keras.models import Sequential
#
from tensorflow.keras.layers import Dense,Conv2D,Flatten,Dropout,MaxPooling2D
#
from tensorflow.keras.preprocessing.image import ImageDataGenerator


#
import os
#
import numpy as np
#グラフや画像の描画
import matplotlib.pyplot as plt

_URL = 'https://storage.googleapis.com/mledu-datasets/cats_and_dogs_filtered.zip'

path_to_zip = tf.keras.utils.get_file('cats_and_dogs.zip', origin=_URL, extract=True)

PATH = os.path.join(os.path.dirname(path_to_zip), 'cats_and_dogs_filtered')

