# # Mask R-CNN Demo
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
DIR = os.path.abspath("./")

# Import Mask RCNN
sys.path.append(ROOT_DIR)  # To find local version of the library
sys.path.append(os.path.join(DIR))  # To find local version of the library
sys.path.append(os.path.join(DIR,'mrcnn/'))  # To find local version of the library
print(DIR)
print(os.path.join(DIR,'mrcnn/'))


from mrcnn import teeth
from mrcnn import utils
import mrcnn.model as modellib
from mrcnn import visualize

# Import Teeth config
sys.path.append(os.path.join(ROOT_DIR, "samples/coco/"))  # To find local version
#from pycocotools.coco import COCO

from matplotlib.pyplot import imshow

# Directory to save logs amrcnn/logs/teeth20191121T1628/mask_rcnnnd trained model
MODEL_DIR = os.path.join(ROOT_DIR, "logs")

# Local path to trained weights file
COCO_MODEL_PATH = os.path.join(ROOT_DIR, "/home/kumakura/hara_data/Teeth_Mask_RCNN_16class/mrcnn/logs/teeth20210111T1645/mask_rcnn_teeth_0040.h5")

#from sklearn.externals import joblib
#bt = joblib.load('/home/kumakura/hara_data/Teeth_Mask_RCNN_16class/numbering_program/numbering.pkl')#読み込み

# Directory of images to run detection on
#IMAGE_DIR = os.path.join(ROOT_DIR, "test_images/teeth")


# ## Configurations
# 
# We'll be using a model trained on the MS-COCO dataset. The configurations of this model are in the ```CocoConfig``` class in ```coco.py```.
# 
# For inferencing, modify the configurations a bit to fit the task. To do so, sub-class the ```CocoConfig``` class and override the attributes you need to change.
# # In[2]:
print(2)
print('----------------------------------------------------------------')

class InferenceConfig(teeth.TeethConfig):
    # Set batch size to 1 since we'll be running inference on
    # one image at a time. Batch size = GPU_COUNT * IMAGES_PER_GPU
    GPU_COUNT = 1
    IMAGES_PER_GPU = 1

config = InferenceConfig()
config.display()


# ## Create Model and Load Trained Weights

# In[3]:
print(3)
print('----------------------------------------------------------------')


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
print(4)
print('----------------------------------------------------------------')


# COCO Class names
# Index of the class in the list is its ID. For example, to get ID of
# the teddy bear class, use: class_names.index('teddy bear')
class_names = ['undetected','1','2','3','4','5','6','7','8','11','12','13','14','15','16','17','18']
class_names = np.array(class_names)
colors= [[255,0,0],[0,255,0],[0,0,255],[255,255,0],[255,0,255],[0,255,255]]

# Load COCO dataset
TEST_DIR = "./"
dataset = teeth.TeethDataset()
dataset.load_teeth(TEST_DIR, "test_image")
dataset.prepare()

# Print class names
print(dataset.class_names)

def threshold_labeling(threshold, point, class_name):
    numbering_label = []
    for i in range(len(class_name)):
        if(int(class_name[i])//10) == 0:
            if (point[i][1] + point[i][3])/2 >= threshold:#right
                numbering_label.append(str(20 + int(class_name[i])%10))
            if (point[i][1] + point[i][3])/2 < threshold:#left
                numbering_label.append(str(10 + int(class_name[i])%10))
        elif(int(class_name[i])//10) == 1:
            if (point[i][1] + point[i][3])/2 >= threshold:#right
                numbering_label.append(str(30 + int(class_name[i])%10))                
            if (point[i][1] + point[i][3])/2 < threshold:#left
                numbering_label.append(str(40 + int(class_name[i])%10))
    return numbering_label

import csv

def csv_save(image_ids,test_list):
    for image_id in image_ids:
        print(image_id)

        #image = dataset.load_image(image_id)
        image = skimage.io.imread(os.path.join('./test_image',str(image_id),'rgb.jpg'))
        
        center = image.shape[1]/2
        results = model.detect([image],verbose=0)
        #results = model.detect([image], verbose=1)

        r = results[0]
        # Visualize results
    
        #pred_labels = bt.predict(r['rois']).astype('int')

        
        numbering_label = threshold_labeling(center,r['rois'],class_names[r['class_ids']])
        n = len(numbering_label)

        list = [[0 for i in range(7)]for j in range(len(numbering_label))]
        #name
        for i in range(n):
            list[i][0] = test_list[image_id]
        #x1
        for i in range(n):
            list[i][1] = r['rois'][i][1]
        #y1
        for i in range(n):
            list[i][2] = r['rois'][i][0]
        #x2
        for i in range(n):
            list[i][3] = r['rois'][i][3]
        #y2
        for i in range(n):
            list[i][4] = r['rois'][i][2]
        #numbering
        for i in range(n):
            list[i][5] = numbering_label[i]
        #score     
        for i in range(n):
            list[i][6] = r['scores'][i]
        
        writer.writerows(list)
        
        visualize.display_instances(image, r['rois'], r['masks'], r['class_ids'], class_names, r['scores'],numbering_label)
        plt.savefig(os.path.join('./test_image',str(image_id),'{}.png').format(image_id),transparent=True, bbox_inches = 'tight', pad_inches = 0)
        plt.close()


def test(image_id,test_list):

    print(image_id)
    #image = dataset.load_image(image_id)
    image = skimage.io.imread(os.path.join('./test_image',str(image_id),'rgb.jpg'))
    center = image.shape[1]/2
    results = model.detect([image],verbose=0)
    #results = model.detect([image], verbose=1)
    r = results[0]
    # Visualize results

    #pred_labels = bt.predict(r['rois']).astype('int')
    
    numbering_label = threshold_labeling(center,r['rois'],class_names[r['class_ids']])
    n = len(numbering_label)
    list = [[0 for i in range(7)]for j in range(len(numbering_label))]
    #name
    for i in range(n):
        list[i][0] = test_list[image_id]
    #x1
    for i in range(n):
        list[i][1] = r['rois'][i][1]
    #y1
    for i in range(n):
        list[i][2] = r['rois'][i][0]
    #x2
    for i in range(n):
        list[i][3] = r['rois'][i][3]
    #y2
    for i in range(n):
        list[i][4] = r['rois'][i][2]
    #numbering
    for i in range(n):
        list[i][5] = numbering_label[i]
    #score     
    for i in range(n):
        list[i][6] = r['scores'][i]
    
    writer.writerows(list)
    
    visualize.display_instances(image, r['rois'], r['masks'], r['class_ids'], class_names, r['scores'],numbering_label)
    plt.savefig(os.path.join('./test_image',str(image_id),'{}.png').format(image_id),transparent=True, bbox_inches = 'tight', pad_inches = 0)
    plt.close()
        

f = open('./test_image/test_image_list.csv','r')
test_list = f.read().splitlines()
test_s = ','.join(test_list)
test_s = test_s.replace(".jpg","")
test_list = test_s.split(',')
f.close()

f = open('test_16class.csv','w')
writer = csv.writer(f)

image_ids = np.arange(200)
csv_save(image_ids,test_list)

#test(133,test_list)

f.close()

