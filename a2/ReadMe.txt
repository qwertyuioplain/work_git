```
データセット作成
```
自作 /Teeth_Mask_RCNN_16class/numbering_program/json_checker.py
  jsonファイル読み込んで、ラベルの'数字がない','乳歯','FDIの番号重複'のファイルを別フォルダに移動させる

/Teeth_Mask_RCNN_16class/Train_own_dataset/training_codes/JSON_parser.py
  get_label関数:ラベル情報の数字のみ抽出し学習時のラベルを付与

/Teeth_Mask_RCNN_16class/Train_own_dataset/training_codes/loader.py
  ラベルとパスを設定,データセット作成

```
学習
```
/Teeth_Mask_RCNN_16class/mrcnn/mean_pixels.py
  mean pixel valuesを計算

/Teeth_Mask_RCNN_16class/mrcnn/teeth.py
  NUM_CLASSES変更
  MEAN_PIXEL変更
  load_teeth変更
  send_message関数:linenotifyのトークンを取ればlineに通知が飛ばせる(必要に応じて)
  Fine-tuningする場合、
  model.load_weights(args.model, by_name=True,exclude=["mrcnn_bbox_fc","mrcnn_class_logits","mrcnn_mask"])
  実行方法、
  python teeth.py --dataset="/Teeth_Mask_RCNN_16class/Train_own_dataset/teeth_dataset" --model="/Teeth_Mask_RCNN_16class/mrcnn/mask_rcnn_coco.h5"

```
評価とか可視化とか
```
/Teeth_Mask_RCNN_16class/mrcnn/teeth.ipynb
  可視化、評価、その他諸々このjupyterで行っている
  labeling関数でsvmの左右分類の結果を用いて16クラスのMask R-CNNの結果をFDI方式の番号に変更してる
  ナンバリング評価修正する必要あり
  teeth32.pyと32クラスのデータセット用いて評価行ってる

/Teeth_Mask_RCNN_16class/mrcnn/model.py
  maskrcnnのネットワーク構造

/Teeth_Mask_RCNN_16class/mrcnn/utils.py
  apの計算とか評価全般の関数がある
  compute_matches関数でgtとpredictionのラベルマッチを数えてる

/Teeth_Mask_RCNN_16class/mrcnn/visualize.py
  display_instances関数にtooth_label追加してる

```
左右分類関連
```
自作 /Teeth_Mask_RCNN_16class/numbering_program/json_fdi_create.py
  左右分類を行うためのデータセット作成
  各jsonファイルに対しcsvファイルを作成(確認するため各ファイルごとに作成している)

自作 /Teeth_Mask_RCNN_16class/numbering_program/numbering.py
  上記のcsvファイルを1つのcsvファイルに

自作 /Teeth_Mask_RCNN_16class/numbering_program/svm.py
  左右分類のsvm行ってpklファイルに重み保存

```
その他
```
/Teeth_Mask_RCNN_16class/numbering_program/iran
　いらないけど何かに使えるかも


