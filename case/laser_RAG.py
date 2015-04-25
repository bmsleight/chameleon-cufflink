#!/usr/bin/env python
#coding:utf-8

import sys
import os
import math

import dxfwrite
from dxfwrite import DXFEngine as dxf

width = 13.5
height = 22
boarder = 2
bobble = 2.5
screw_radius = 1

p_thickness = 2
bar_length = width - p_thickness - p_thickness
bar_length_b = width - p_thickness*3
bar_height = 16
bar_thickness = 4

b_len_b = 6
b_len_t = width
b_stock = 16
s_thick = 3




def add_layers(drawing):
    drawing.add_layer('OUTLINE', color=1)
    drawing.add_layer('ENGRAVE', color=2)
    drawing.add_layer('ENGRAVECUT', color=3)
    drawing.add_layer('CUTSINNEREARLY', color=4)
    drawing.add_layer('CUTSINNER', color=5)
    drawing.add_layer('CUTSOUTER', color=6)

def outline(drawing):
    drawing.add(dxf.rectangle((0, 0) , 210, 297,  layer='OUTLINE', color=1))

def bar(drawing, x, y):

#b_len_b = 6
#b_len_t = width
#b_stock = 16
#s_thick = 3
#p_thickness = 2

    polyline= dxf.polyline(layer='CUTSOUTER', color=6)
    polyline.add_vertices( [(x+(b_len_t-b_len_b)/2,y), 
                           (x+(b_len_t-b_len_b)/2,y+p_thickness), 
                           (x+(b_len_t-s_thick)/2,y+p_thickness), 
                           (x+(b_len_t-s_thick)/2,y+b_stock-s_thick), 
                           (x,y+b_stock-s_thick), 
                           (x,y+b_stock), 
                           (x+b_len_t,y+b_stock), 
                           (x+b_len_t,y+b_stock-s_thick), 
                           (x+(b_len_t+s_thick)/2,y+b_stock-s_thick), 
                           (x+(b_len_t+s_thick)/2,y+p_thickness), 
                           (x+(b_len_t+b_len_b)/2,y+p_thickness), 
                           (x+(b_len_t+b_len_b)/2,y), 

                           (x+(b_len_t-b_len_b)/2,y) ]) 
    drawing.add(polyline)




def button(drawing, x, y):
    polyline= dxf.polyline(layer='CUTSOUTER', color=6)
    polyline.add_vertices( [(x,y), 
                           (x,y+1), 
                           (x+2,y+1), 
                           (x+2,y+3), 
                           (x+4,y+3), 
                           (x+4,y+1), 
                           (x+6,y+1), 
                           (x+6,y), 
                           (x,y) ]) 
    drawing.add(polyline)

def engrave_text(drawing, x, y):
    drawing.add(dxf.text('Cuffelink.com', halign=dxfwrite.const.CENTER,  valign=dxfwrite.const.MIDDLE, alignpoint=(x, y), height=1.8, rotation=90, layer='ENGRAVE', color=2))

def stacks_layers(drawing, startx, starty):
    for x in range(0, 5):
        masterX = 12+(15*x)+startx
        masterY = 12+starty
        drawing.add(dxf.rectangle((masterX, masterY) , width, height,  layer='CUTSOUTER', color=6))
        if ((x != 0) and (x !=2) and (x !=4) ):
            polyline= dxf.polyline(layer='CUTSINNER', color=5)
            polyline.add_vertices( [(masterX+boarder, masterY+boarder),
                           # Button hole
                           (masterX+boarder, masterY+boarder+2.5-1),
                           (masterX+boarder-1, masterY+boarder+2.5-1),
                           (masterX+boarder-1, masterY+boarder+2.5+1),
                           (masterX+boarder, masterY+boarder+2.5+1),
                           # End button hole 
                           (masterX+boarder, masterY+height-boarder-bobble),
                           (masterX+boarder+bobble, masterY+height-boarder-bobble),
                           (masterX+boarder+bobble, masterY+height-boarder),
                           (masterX+width-boarder, masterY+height-boarder),
                           (masterX+width-boarder, masterY+boarder+bobble),
                           (masterX+width-boarder-bobble, masterY+boarder+bobble),
                           (masterX+width-boarder-bobble, masterY+boarder),
                           (masterX+boarder, masterY+boarder) ])
            drawing.add(polyline)
        if (x == 0):
            # RAG Holes on PCB at 4.5mm, 9mm and 13.5mm
            # PCB is width - p_thickness - p_thickness, height - p_thickness - p_thickness
            drawing.add(dxf.circle(1, (masterX+width/2, masterY+p_thickness+4.5), layer='CUTSINNER', color=5))
            drawing.add(dxf.circle(1, (masterX+width/2, masterY+p_thickness+9.0), layer='CUTSINNER', color=5))
            drawing.add(dxf.circle(1, (masterX+width/2, masterY+p_thickness+13.5), layer='CUTSINNER', color=5))
            # Backing board!
            drawing.add(dxf.rectangle((masterX+p_thickness, masterY+p_thickness) , width-p_thickness*2, height-p_thickness*2, layer='ENGRAVE', color=2)) 
            drawing.add(dxf.rectangle((masterX+p_thickness*2, masterY+p_thickness*2) , width-p_thickness*4, height-p_thickness*4, layer='ENGRAVE', color=2)) 
        # Button hole
        if (x == 2):
            drawing.add(dxf.line((masterX, masterY+boarder+2.5-1), (masterX+boarder, masterY+boarder+2.5-1), layer='CUTSINNER', color=5))
            drawing.add(dxf.line((masterX, masterY+boarder+2.5+1), (masterX+boarder, masterY+boarder+2.5+1), layer='CUTSINNER', color=5))
        # Screws thread holes
        if (x == 3):
            drawing.add(dxf.circle(screw_radius*1, (masterX+2.75, masterY+height-2.75), layer='CUTSINNER', color=5))
            drawing.add(dxf.circle(screw_radius*1, (masterX+width-2.75, masterY+2.75), layer='CUTSINNER', color=5))
        if (x == 4):
            # mirror as want writing on ourside face
            drawing.add(dxf.circle(screw_radius*1, (masterX+width-2.75, masterY+height-2.75), layer='CUTSINNER', color=5))
            drawing.add(dxf.circle(screw_radius*1, (masterX+2.75, masterY+2.75), layer='CUTSINNER', color=5))
        # Screws head holes
        if (x == 2):
            polyline= dxf.polyline(layer='CUTSINNER', color=5)
            polyline.add_vertices( [(masterX+boarder, masterY+boarder),
                           (masterX+boarder, masterY+height-boarder-bobble),
                           (masterX+boarder-1, masterY+height-boarder-bobble),
                           (masterX+boarder-1, masterY+height-1),
                           (masterX+boarder+bobble, masterY+height-1),
                           (masterX+boarder+bobble, masterY+height-boarder),
                           (masterX+width-boarder, masterY+height-boarder),
                           (masterX+width-boarder, masterY+boarder+bobble),
                           (masterX+width-1, masterY+boarder+bobble),
                           (masterX+width-1, masterY+1),
                           (masterX+width-boarder-bobble, masterY+1),
                           (masterX+width-boarder-bobble, masterY+boarder),
                           (masterX+boarder, masterY+boarder) ])
            drawing.add(polyline)
        if (x == 4):
            # Hole for bar
            # Kurf is ~0.1mm as measured by thickness of two A4 sheets.
            drawing.add(dxf.rectangle((masterX-(b_len_b/2)+width/2, masterY-(p_thickness/2)+height/2) , b_len_b, p_thickness-0.1, layer='CUTSINNER', color=5)) 
            # logo
            engrave_text(drawing, masterX+p_thickness/2+1, masterY+height/2+1.5)
    bar(drawing, startx+12+(15*5), starty+12)
    button(drawing, startx+12+(15*5), starty+12+bar_height+2)
    button(drawing, startx+12+(15*5)+7.5, starty+12+bar_height+2)



if __name__ == '__main__':
    # git rev-parse --short HEAD 
    name="/tmp/laser_RAG.dxf"
    drawing = dxf.drawing(name)
    stacks_layers(drawing, 0, 0)
    drawing.save()
    print("drawing '%s' created.\n" % name)
