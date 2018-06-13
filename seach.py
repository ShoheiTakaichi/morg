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
        n = 1;
    else:
        n= int(np.log(A-1)) 
    for i in range(n+4):
        pg.keyDown("backspace")
        pg.keyUp("backspace")
    for s in (str(A)):
        pg.keyDown(s)
        pg.keyUp(s)        
    pg.keyDown("esc")
    pg.keyUp("esc")




pg.moveTo(1670,855)
pg.click()
pg.keyDown("j")
time.sleep(2)
pg.keyUp("j")


n = 70
best = 235403557
best_seed = 8
while(True):

    pg.keyDown("i")
    pg.keyUp("i")
    pg.keyDown("c")
    pg.keyUp("c")

    inNum(n)
 
    pg.keyDown("i")
    pg.keyUp("i")
    pg.keyDown("d")
    pg.keyUp("d")  
    time.sleep(1)

    pg.keyDown("j")
    time.sleep(1)
    pg.keyUp("j")
    pg.keyDown("i")
    pg.keyUp("i")
    pg.keyDown("s")
    pg.keyUp("s")

    pg.keyDown("j")
    time.sleep(1)
    pg.keyUp("j")

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







