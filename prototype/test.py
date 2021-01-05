
#tensorflow tutorial(Image classfication)
#classify cat image and dog image

#ライブラリ

#tensorflow（tfに省略）
#tensorflowはgoogleがオープンソースで公開しているソフトウェア関係の機械学習のライブラリ
#kerasは特にニューラルネットワークといったディープラーニングモデル深層学習の高レベルのAPI、ライブラリ
import tensorflow as tf 

#ニューラルネットワークにおいてのモデル
#網目構造を再現するために簡略化されたモデルで、シーケンシャル(sequential)つまりは線形となるような線のようなLayer(レイヤー)が連続的に続く構造となる。
#他にもFunction APIなどの複雑な操作を行うことができるものも存在する。
from tensorflow.keras.models import Sequential

#上記で述べたLayerのライブラリ
#Dence:ニューラルネットワークにおいての全結合層を表現できる。 全結合層とは、レイヤーの中の全てのニューロンが次の層の全てのニューロンと結合している状態を指す
#Conv2D
#Flatten
#Dropout
#MaxPooling2D
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


train_dir = os.path.join(PATH, 'train')
validation_dir = os.path.join(PATH, 'validation')

train_cats_dir = os.path.join(train_dir, 'cats')  # 学習用の猫画像のディレクトリ
train_dogs_dir = os.path.join(train_dir, 'dogs')  # 学習用の犬画像のディレクトリ
validation_cats_dir = os.path.join(validation_dir, 'cats')  # 検証用の猫画像のディレクトリ
validation_dogs_dir = os.path.join(validation_dir, 'dogs')  # 検証用の犬画像のディレクトリ













