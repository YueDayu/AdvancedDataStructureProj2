__author__ = 'Yue Dayu'

import random
from PIL import Image

def read_file(file):
    infile = open(file, 'r')
    lines = infile.readlines()
    query_pic = []
    class_pic = []
    for x in lines:
        current_line = x.split('\t')
        query_pic.append(current_line[0])
        class_pic.append(current_line[1][0:-1])
    return query_pic, class_pic

def showImg(path0, path1, file):
    file_name, class_pic = read_file(file)
    i = random.randint(0, len(file_name))
    image = Image.open(path0 + '/' + file_name[i])
    print class_pic[i]
    image.show()

if __name__ == '__main__':
    showImg('G:\ir', '', 'pr_res.txt')