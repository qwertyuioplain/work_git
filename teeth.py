#!/usr/bin/env python
# coding: utf-8

# # Mask R-CNN Demo
# 
# A quick intro to using the pre-trained model to detect and segment objects.

# In[1]:


import os
import sys
import random
import math
import numpy as np
import skimage.io
import matplotlib
import matplotlib.pyplot as plt
import cv2

# Root directory of the project
ROOT_DIR = os.path.abspath("../")

# Import Mask RCNN
sys.path.append(ROOT_DIR)  # To find local version of the library
sys.path.append('/home/hara/Teeth_Mask_RCNN_16class/mrcnn')  # To find local version of the library
from mrcnn import utils
import mrcnn.model as modellib
from mrcnn import visualize

# Import Teeth config
sys.path.append(os.path.join(ROOT_DIR, "samples/coco/"))  # To find local version
#from pycocotools.coco import COCO
import teeth

from matplotlib.pyplot import imshow
get_ipython().run_line_magic('matplotlib', 'inline')

# Directory to save logs amrcnn/logs/teeth20191121T1628/mask_rcnnnd trained model
MODEL_DIR = os.path.join(ROOT_DIR, "logs")

# Local path to trained weights file
COCO_MODEL_PATH = os.path.join(ROOT_DIR, "/home/hara/Teeth_Mask_RCNN_16class/mrcnn/logs/teeth20210111T1645/mask_rcnn_teeth_0040.h5")

from sklearn.externals import joblib
bt = joblib.load('/home/hara/numbering_program/numbering.pkl')#読み込み

# Directory of images to run detection on
IMAGE_DIR = os.path.join(ROOT_DIR, "test_images/teeth")


# ## Configurations
# 
# We'll be using a model trained on the MS-COCO dataset. The configurations of this model are in the ```CocoConfig``` class in ```coco.py```.
# 
# For inferencing, modify the configurations a bit to fit the task. To do so, sub-class the ```CocoConfig``` class and override the attributes you need to change.

# In[2]:


class InferenceConfig(teeth.TeethConfig):
    # Set batch size to 1 since we'll be running inference on
    # one image at a time. Batch size = GPU_COUNT * IMAGES_PER_GPU
    GPU_COUNT = 1
    IMAGES_PER_GPU = 1

config = InferenceConfig()
config.display()


# ## Create Model and Load Trained Weights

# In[3]:


# Create model object in inference mode.
model = modellib.MaskRCNN(mode="inference",config=config,model_dir=MODEL_DIR)
# Load weights trained on MS-COCO
model.load_weights(COCO_MODEL_PATH, by_name=True)


# ## Class Names
# 
# The model classifies objects and returns class IDs, which are integer value that identify each class. Some datasets assign integer values to their classes and some don't. For example, in the MS-COCO dataset, the 'person' class is 1 and 'teddy bear' is 88. The IDs are often sequential, but not always. The COCO dataset, for example, has classes associated with class IDs 70 and 72, but not 71.
# 
# To improve consistency, and to support training on data from multiple sources at the same time, our ```Dataset``` class assigns it's own sequential integer IDs to each class. For example, if you load the COCO dataset using our ```Dataset``` class, the 'person' class would get class ID = 1 (just like COCO) and the 'teddy bear' class is 78 (different from COCO). Keep that in mind when mapping class IDs to class names.
# 
# To get the list of class names, you'd load the dataset and then use the ```class_names``` property like this.
# ```
# # Load COCO dataset
# dataset = coco.CocoDataset()
# dataset.load_coco(COCO_DIR, "train")
# dataset.prepare()
# 
# # Print class names
# print(dataset.class_names)
# ```
# 
# We don't want to require you to download the COCO dataset just to run this demo, so we're including the list of class names below. The index of the class name in the list represent its ID (first class is 0, second is 1, third is 2, ...etc.)

# In[4]:


# COCO Class names
# Index of the class in the list is its ID. For example, to get ID of
# the teddy bear class, use: class_names.index('teddy bear')
class_names = ['undetected','1','2','3','4','5','6','7','8','11','12','13','14','15','16','17','18']
class_names = np.array(class_names)
colors= [[255,0,0],[0,255,0],[0,0,255],[255,255,0],[255,0,255],[0,255,255]]


# ## Run Object Detection

# In[6]:


file = "/home/hara/Teeth_Mask_RCNN_16class/Train_own_dataset/teeth_dataset/test_images/YP15D0103001.jpg"

image = skimage.io.imread(os.path.join(IMAGE_DIR, file))
# Run detection
results = model.detect([image], verbose=1)
# Visualize results
r = results[0]
print(r['class_ids'])
visualize.display_instances(image, r['rois'], r['masks'], r['class_ids'], class_names, r['scores'])
# visualize.display_instances2(image, r['rois'], r['masks'], r['class_ids'], tooth_labels, class_names, r['scores'])


# In[5]:


def labeling(pred_labels,class_name):
    numbering_label = []
    for i in range(len(class_name)):
        if (int(class_name[i])//10) == 0:#upper
            if pred_labels[i] == 0:#left
                numbering_label.append(str(10 + int(class_name[i])%10))
            elif pred_labels[i] == 1:#right
                numbering_label.append(str(20 + int(class_name[i])%10))
        elif (int(class_name[i])//10) == 1:#lower
            if pred_labels[i] == 0:#left
                numbering_label.append(str(40 + int(class_name[i])%10))
            elif pred_labels[i] == 1:#right
                numbering_label.append(str(30 + int(class_name[i])%10))
    return numbering_label


# In[22]:


file = "/home/hara/Teeth_Mask_RCNN_16class/Train_own_dataset/teeth_dataset/test_images/YP15D0102978.jpg"
image = skimage.io.imread(os.path.join(IMAGE_DIR, file))
# Run detection
results = model.detect([image], verbose=1)
# Visualize results
r = results[0]

pred_labels = bt.predict(r['rois']).astype('int')
numbering_label = labeling(pred_labels,class_names[r['class_ids']])
        
visualize.display_instances(image, r['rois'], r['masks'], r['class_ids'], class_names, r['scores'],numbering_label)


# In[14]:


TEST_DIR = "/home/hara/Teeth_Mask_RCNN_16class/Train_own_dataset/teeth_dataset"
# Load COCO dataset
dataset = teeth.TeethDataset()
dataset.load_teeth(TEST_DIR, "test")
dataset.prepare()

# Print class names
print(dataset.class_names)


# ## 画像保存

# In[19]:


def batch_save(image_ids):
    for image_id in image_ids:
        print(image_id)
        # Load image
        image = dataset.load_image(image_id)
        
        # Run object detection
        results = model.detect([image], verbose=0)
        # Visualize results
        r = results[0]

        visualize.display_instances(image, r['rois'], r['masks'], r['class_ids'], class_names, r['scores'])
        plt.savefig('images/{}.png'.format(image_id),transparent=True, bbox_inches = 'tight', pad_inches = 0)
# Pick a set of random images
image_ids = np.arange(196)
batch_save(image_ids)


# In[ ]:


from sklearn.externals import joblib
class_names = np.array(['undetected','1','2','3','4','5','6','7','8','11','12','13','14','15','16','17','18'])
bt = joblib.load('/home/hara/numbering_program/numbering.pkl')#読み込み
def batch_save(image_ids):
    for image_id in image_ids:
        print(image_id)
        # Load image
        image = dataset.load_image(image_id)
        
        # Run object detection
        results = model.detect([image], verbose=0)
        # Visualize results
        r = results[0]
        
        label_list = class_names[r['class_ids']].reshape((r['rois'].shape[0],1))
        concate_arr = np.concatenate([r['rois'],label_list],axis=1)
        pred_labels = bt.predict(concate_arr).astype('int')
        numbering_label = labeling(pred_labels,class_names[r['class_ids']])
        
        visualize.display_instances(image, r['rois'], r['masks'], r['class_ids'], class_names, r['scores'],numbering_label)
        plt.savefig('image/{}.png'.format(image_id),transparent=True, bbox_inches = 'tight', pad_inches = 0)
# Pick a set of random images
image_ids = np.arange(196)
batch_save(image_ids)


# ## 評価

# In[14]:


TEST_DIR = "/home/hara/Teeth_Mask_RCNN_16class/Train_own_dataset/teeth_dataset/"
# Load COCO dataset
dataset = teeth.TeethDataset()
dataset.load_teeth(TEST_DIR, "a")
dataset.prepare()

# Print class names
print(dataset.class_names)
# def get_ax(rows=1, cols=1, size=16):
#     """Return a Matplotlib Axes array to be used in
#     all visualizations in the notebook. Provide a
#     central point to control graph sizes.
    
#     Adjust the size attribute to control how big to render images
#     """
#     _, ax = plt.subplots(rows, cols, figsize=(size*cols, size*rows))
#     return ax


# In[17]:


# Compute VOC-style Average Precision
def compute_batch_ap(image_ids):
    APs = []
    Recalls = []
    Precisions = []
    match_counts,gt_lens,pred_lens = 0,0,0
    
    for image_id in image_ids:
        print(image_id)
        # Load image
        image, image_meta, gt_class_id, gt_bbox, gt_mask =            modellib.load_image_gt(dataset, config,
                                   image_id, use_mini_mask=False)
        gt_len = len(gt_bbox)
        # Run object detection
        results = model.detect([image], verbose=0)
        # Compute AP
        r = results[0]
        pred_len = len(r['rois'])
        AP, precisions, recalls, overlaps,match_count = utils.compute_ap(gt_bbox, gt_class_id, gt_mask, r['rois'], r['class_ids'], r['scores'], r['masks'],iou_threshold)
#         visualize.plot_precision_recall(AP, precisions, recalls)
        APs.append(AP)
        print("m/g:{}/{}".format(match_count,gt_len))
        match_counts += match_count
        gt_lens += gt_len
        pred_lens += pred_len
#         Recalls.append(recalls)
#         Precisions.append(precisions)
    return APs,match_counts,gt_lens,pred_lens

# Pick a set of random images
image_ids = np.arange(1)
iou_threshold = 0.75
APs,match_counts,gt_lens,pred_lens = compute_batch_ap(image_ids)
print("mAP @ IoU={}:{}".format(iou_threshold,np.mean(APs)))
print("Numbering Precision:{}".format(match_counts/pred_lens))
print("Numbering Recall:{}".format(match_counts/gt_lens))


# In[13]:


gt_boxes_lens


# ## ナンバリング評価

# In[32]:


import teeth32 
from mrcnn import utils
TEST_DIR = "/home/hara/Teeth_Mask_RCNN_32class/Train_own_dataset/teeth_dataset/"
# Load COCO dataset
dataset = teeth32.TeethDataset()
dataset.load_teeth(TEST_DIR, "test")
dataset.prepare()

# Print class names
print(dataset.class_names)
print(dataset)


# In[34]:


# Compute VOC-style Average Precision
def compute_batch_ap(image_ids):
    APs = []
    Recalls = []
    Precisions = []
    match_counts,pred_lens = 0,0
    
    for image_id in image_ids:
        print(image_id)
        # Load image
        image, image_meta, gt_class_id, gt_bbox, gt_mask =            modellib.load_image_gt(dataset, config,
                                   image_id, use_mini_mask=False)
        image2 = dataset.load_image(image_id)#TODO:評価の画像はresizeされてるから左右のsvmが使えなくなるため　改良の余地あり
        # Run object detection
        
        results = model.detect([image], verbose=0)
        results2 = model.detect([image2], verbose=0)
        # Compute AP
        r = results[0]
        pred_len = len(r['rois'])
        r2 = results2[0]
        renew_class_names = []
        pred_labels = bt.predict(r2['rois']).astype('int')
        numbering_label = labeling(pred_labels,class_names[r['class_ids']])
        d_class_name = np.array(dataset.class_names)
        for i in numbering_label:
            renew_class_names.append(np.where(d_class_name == i))
        renew_class_names = np.array(renew_class_names)
        
        AP, precisions, recalls, overlaps,match_count = utils.compute_ap(gt_bbox, gt_class_id, gt_mask, r['rois'], renew_class_names, r['scores'], r['masks'],iou_threshold)
        APs.append(AP)
        match_counts += match_count
        pred_lens += pred_len
    return APs,match_counts,pred_lens

# Pick a set of random images
image_ids = np.arange(196)
iou_threshold = 0.50
APs,match_counts,pred_lens = compute_batch_ap(image_ids)
print("IoU={}".format(iou_threshold))
print("Numbering Precision:{}".format(match_counts/pred_lens))
print("Numbering Recall:{}".format(match_counts/gt_lens))


# In[ ]:





# ## 歯牙を回転させるコード (svmの特徴量とかに使えるかも)

# In[7]:


import numpy as np
from scipy import ndimage, optimize
import matplotlib.pyplot as plt
import cv2

def inertia(img):
    mass = img.sum(axis=0)
    print(mass)
    radius = np.abs(np.arange(-len(mass)//2, len(mass)//2+1))
    if len(mass) != len(radius):
        radius = radius[radius != 0] - 0.5  # 中心位置の補正
    return (mass * radius * radius).sum()

# 回転させて慣性モーメントを測定する=最小化関数
def rotated_inertia(degree, img):
    return inertia(ndimage.rotate(img, degree, reshape=False))


i = 19
coo = r['rois'][i]
mask = r['masks'][:,:,i][coo[0]:coo[2],coo[1]:coo[3]]
bi_mask = np.where(mask==True,255,0)
h, w = bi_mask.shape
src = np.zeros((int((w**2 + h**2)**(1/2)), int((w**2 + h**2)**(1/2))))
# dx,dy = int((w**2 + h**2)**(1/2)/2) - int(w/2), int((w**2 + h**2)**(1/2)/2) - int(h/2)

for y in range(0, h):#平行移動
    for x in range(0, w):
        src[y][x] = bi_mask[y][x]

img = src
# 平行移動して重心を中心にする
center = ndimage.center_of_mass(img)
img = ndimage.shift(img, np.array(img.shape)/2-np.array(center))


# 最小化関数の最小値を求めることで、-90〜90度の回転時の最小慣性モーメントを得る
res = optimize.minimize_scalar(
    rotated_inertia, bounds=[-90,90], args=(img), method='Bounded')

# 最小値の時の回転角度を求める
print(res.x)

# 最小値の時の回転を実際に行う
img = ndimage.rotate(img, res.x, reshape=False)

plt.imshow(img)
plt.show()


# In[ ]:




