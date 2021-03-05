
import csv
import os
import numpy as np
import shutil

#test_data(.jpg) dir path
TEST_DATA_DIR = "/home/kumakura/hara_data/Teeth_Mask_RCNN_16class/Train_own_dataset/teeth_dataset/test_images"

#new test dir path
TEST_DIR = "/home/kumakura/work/test_image"

#abs path
path3 = os.path.abspath(__file__)

image_list = [s for s in os.listdir(TEST_DATA_DIR) if '.jpg' in s]#image_name list
len = len(image_list)
image_list2 = np.array(image_list).reshape(len,1).tolist()

print('number of file:',len)

if not os.path.exists(TEST_DIR):
    os.makedirs(TEST_DIR)

if os.path.exists(TEST_DIR):
    print('successed new dir or exist dir')

count = 0
#image_path = np.arange(len)
for i in np.arange(len):
    image_dir_path = os.path.join(TEST_DIR,str(i))
    test_data_path = os.path.join(TEST_DATA_DIR,image_list[i])
    if not os.path.exists(image_dir_path):
        os.mkdir(image_dir_path)
    if os.path.exists(test_data_path):
        if os.path.isfile(test_data_path):
            shutil.copy(test_data_path,os.path.join(image_dir_path,'rgb.jpg'))
    if os.path.exists(os.path.join(image_dir_path,'rgb.jpg')):
        count +=1
if count == len: print('successed copy') 
else: print('copy err')

with open(os.path.join(TEST_DIR,'test_image_list.csv'),'w') as f:
    writer = csv.writer(f,delimiter=',')
    for s in image_list2:
        writer.writerow(s)

    '''for i in range(len):
        #print(image_list[i])
        print(str(image_list[i]))
        writer.writerow(str(image_list[i]))
    '''
        