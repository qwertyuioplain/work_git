1. mask r-cnnの16クラスでの実験に用いた画像
  すべての画像　/Latest_dataset/TU_KitaLab
  training     /Teeth_Mask_RCNN_16class/Train_own_dataset/teeth_dataset/tr_images
  validation   /Teeth_Mask_RCNN_16class/Train_own_dataset/teeth_dataset/val_images
  test         /Teeth_Mask_RCNN_16class/Train_own_dataset/teeth_dataset/test_images

2. 16クラスの学習済みモデルを用いて動かしている部分
  /Teeth_Mask_RCNN_16class/mrcnn/teeth.ipynbのRun Object Detectionセル
  座標 : r['rois']
  セグメンテーションマップ : r['masks']
  クラス : r['class_ids']
  信頼度スコア : r['scores']

3. 16クラスの分類結果
  /Teeth_Mask_RCNN_16class/mrcnn/teeth.ipynbの評価セル
　実際に計算しているモジュール
  /Teeth_Mask_RCNN_16class/mrcnn/utils.py

4. 入力画像の大きさ
  学習時
  /Teeth_Mask_RCNN_16class/mrcnn/teeth.py
　IMAGE_MIN_DIM = 448
  IMAGE_MAX_DIM = 512

5. 左右の分類
　入力 各csvファイル  /Latest_dataset/TU_KitaLab/*_numbering3.csv
       まとめたファイル　/Teeth_Mask_RCNN_16class/numbering_program/numbering_matome3.csv
  svm学習・評価ファイル　/Teeth_Mask_RCNN_16class/numbering_program/svm.py
  
  

