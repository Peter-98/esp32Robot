import json
import turtle
import pandas as pd

from math import ceil, floor

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


df = pd.read_json ('datos20.json', lines=True)
print(df)
   
setwindowsize(300, 300)

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
        
    color_pixel = tuple( intensity_colors[c] for c in COLORS)
    print("RGB :",color_pixel)
    drawpixel(x, y, color_pixel)
         
showimage()
















