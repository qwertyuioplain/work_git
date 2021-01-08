
#tensorflow tutorial(Image classfication)
#classify cat image and dog image

#ライブラリ

#tensorflow（tfに省略）
#tensorflowはgoogleがオープンソースで公開しているソフトウェア関係の機械学習のライブラリ
#kerasは特にニューラルネットワークといったディープラーニングモデル深層学習の高レベルのAPI、ライブラリつまりはフレームワーク
#Define-by-Run方式のフレームワークであり、モデルを定義したあとデータを用いることを表す
import tensorflow as tf 

#ニューラルネットワークにおいてのモデル
#網目構造を再現するために簡略化されたモデルで、シーケンシャル(sequential)つまりは線形となるような線のようなLayer(レイヤー)が連続的に続く構造となる
#また、入力と出力を１つしか指定できない
#他にもFunction APIなどの複雑な操作を行うことができるものも存在する
from tensorflow.keras.models import Sequential

#上記で述べたLayerのライブラリ
#Dence:ニューラルネットワークにおいての全結合層を表現できる。 全結合層とは、レイヤーの中の全てのニューロンが次の層の全てのニューロンと結合している状態を指す
#Conv2D:二次元の畳込み演算層
#Flatten:入力を平滑化する
#Dropout:過学習の予防策。層とのつながりを指定割合分無効化する
#MaxPooling2D:最大プーリング層。最大値を出力する
from tensorflow.keras.layers import Dense,Conv2D,Flatten,Dropout,MaxPooling2D

#データ拡張用のクラス。画像データを加工し、複製し元データと本質は同じ訓練用データを増やす目的がある。
from tensorflow.keras.preprocessing.image import ImageDataGenerator

#ファイルやディレクトリを操作できるなどosに関係する機能やデータを利用するモジュール
import os
#数値計算における拡張モジュール
import numpy as np
#グラフや画像の描画モジュール
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













