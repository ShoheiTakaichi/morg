import pyautogui as pg
import os
import time
import numpy as np


def exc():
    os.system("mv ../../Downloads/prices.csv ./")
    os.system("./tr < prices.csv")
    os.system("./ref < tr.csv > value.txt")
    with open("value.txt", "r") as f:
        data = int(f.read()) 
    return data

def inNum(A):
    if A == 1 or  A == 0:
        m = 1;
    else:
        m= int(np.log(A-1)) 
    for i in range(m+4):
        pg.keyDown("backspace")
        pg.keyUp("backspace")
    for s in (str(A)):
        pg.keyDown(s)
        pg.keyUp(s)


n = 1611
best = 711
best_seed = 260375386

pg.moveTo(1670,855)
pg.click()


while (True):
    time.sleep(0.1)
    pg.moveTo(1908,440)
    time.sleep(0.1)
    pg.mouseDown()
    time.sleep(0.1)
    pg.moveTo(1908,600)
    pg.mouseUp()

    time.sleep(0.1)
    pg.moveTo(1315,610)
    pg.click()

    time.sleep(0.1)
    pg.moveTo(1908,611)
    time.sleep(0.1)
    pg.mouseDown()
    time.sleep(0.1)
    pg.moveTo(1908,823)
    pg.mouseUp()

    time.sleep(0.1)
    pg.moveTo(1196,801)
    pg.click()
    #数字入力
    inNum(n+1)

    time.sleep(0.1)
    pg.moveTo(1311,801)
    pg.click()
    temp = exc()    
    if temp>best:
        best=temp
        best_seed=n
    print("now")
    print(n)
    print(temp)
    print("best")
    print(best)
    print(best_seed)
    print()
    n+=1







