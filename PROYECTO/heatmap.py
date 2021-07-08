import json
import turtle
import math
import pandas as pd
from math import ceil, floor

from sklearn import linear_model
import random
from IPython.display import display
from sklearn.model_selection import train_test_split
        



COLORS = ['r','g','b']

def setwindowsize(x, y): 
    turtle.setup(x, y)
    turtle.setworldcoordinates(0,0,x,y)

def drawpixel(x, y, color, pixelsize = 20 ):
    turtle.tracer(0, 0)
    turtle.colormode(255)
    turtle.penup()
    turtle.setpos(x*pixelsize,y*pixelsize)
    turtle.color(color)
    turtle.pendown()
    turtle.begin_fill()
    for i in range(4):
        turtle.forward(pixelsize)
        turtle.right(90)
    turtle.end_fill()

def showimage():
    turtle.hideturtle()
    turtle.update()

def get_n_colors(n_baliza):  #Devuelve el numero de balizas de cada color RGB
    n_red = ceil(n_baliza / 3)
    n_green = ceil( (n_baliza - n_red) /2 )
    n_blue = n_baliza - n_red - n_green

    n_colors = {
        'r': n_red,
        'g': n_green,
        'b': n_blue
    }
    return n_colors


df = pd.read_json ('datos2.json', lines=True)
print(df)
   
setwindowsize(300, 300)

listSeñal = []
listDistanca  =  []

for _, fila in df.iterrows():
    fila = dict(fila)   

    n_baliza = fila['N-baliza']
    x = fila['coord-x']
    y = fila['coord-y']

    n_colors = get_n_colors(n_baliza)

    intensity_colors ={
        'r': 0,
        'g': 0, 
        'b': 0
    }
 
    for i, baliza in enumerate(fila['balizas']):
        color_baliza = COLORS[i % 3]
        level = floor(255 + (5.1 * baliza['señal'])) #Ajuste de señal
        intensity_colors[color_baliza] += floor(255/n_colors[color_baliza]) + ceil(level /n_colors[color_baliza])
        print("Baliza", i+1, ": ",intensity_colors[color_baliza])
        #Almacena la intensidad de cada color en el array
        
        x2 = baliza['pos-x']
        y2 = baliza['pos-y']      
        distancia = math.sqrt((x2-x)**2+(y2-y)**2)
        listSeñal.append(baliza['señal'])
        listDistanca.append(distancia)
        

    color_pixel = tuple( intensity_colors[c] for c in COLORS)
    print("RGB :",color_pixel)
    drawpixel(x, y, color_pixel)

X = pd.DataFrame(data=listSeñal,columns=["RSSI"]),
Y = pd.DataFrame(data=listDistanca,columns=["DISTANCIA"]),
display(Y)
display(X)
coef_separacion = 0.25
entrenar_X, test_X, entrenar_Y, test_Y = train_test_split(X,Y,test_size=coef_separacion,random_state=0)

plot(entrenar_X,'b+', entrenar_Y,'gx')
figure(2)
plot(test_X,'b+',test_Y,'gx')

showimage()
















