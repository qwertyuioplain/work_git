import csv

csv_file = open("./word_index.csv",'r')
word_index_list = csv.reader(csv_file)
csv_file = open("./word_index.csv",'r')
word_index_dict = csv.DictReader(csv_file)

csv_file = open("./word_possibility.csv",'r')
word_possibility = csv.reader(csv_file)


for a in word_index_dict :
    if a['語']=='個':
        print(a['品詞'])
for b in word_possibility:
    if '名詞' in b:
        print(b)

word = 'このひとことで元気になった'
n = len(word)
print(n)
print(word[2])
print(word[0:4])




csv_file.close()
