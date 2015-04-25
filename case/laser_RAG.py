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

def add_layers(drawing):
    drawing.add_layer('OUTLINE', color=1)
    drawing.add_layer('ENGRAVE', color=2)
    drawing.add_layer('CUTSINNEREARLY', color=3)
    drawing.add_layer('CUTSINNER', color=4)
    drawing.add_layer('CUTSOUTER', color=5)

def outline(drawing):
    drawing.add(dxf.rectangle((0, 0) , 210, 297,  layer='OUTLINE', color=1))


def stacks_layers(drawing, startx, starty):
    for x in range(0, 6):
        masterX = 12+(15*x)+startx
        masterY = 12+starty
        drawing.add(dxf.rectangle((masterX, masterY) , width, height,  layer='CUTSOUTER', color=5))
        if ((x != 0) and (x !=3) and (x !=5) ):
            polyline= dxf.polyline(layer='CUTSINNER', color=4)
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

        # Button hole
        if (x == 2):
            drawing.add(dxf.line((masterX, masterY+boarder+2.5-1), (masterX+boarder-1, masterY+boarder+2.5-1), layer='CUTSINNER', color=4))
            drawing.add(dxf.line((masterX, masterY+boarder+2.5+1), (masterX+boarder-1, masterY+boarder+2.5+1), layer='CUTSINNER', color=4))
        # Screws thread holes
        if (x >3):
            drawing.add(dxf.circle(screw_radius*1, (masterX+2.75, masterY+height-2.75), layer='CUTSINNER', color=4))
            drawing.add(dxf.circle(screw_radius*1, (masterX+width-2.75, masterY+2.75), layer='CUTSINNER', color=4))
        # Screws head holes
        if (x == 3):
            polyline= dxf.polyline(layer='CUTSINNER', color=4)
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


if __name__ == '__main__':
    # git rev-parse --short HEAD 
    name="/tmp/laser_RAG.dxf"
    drawing = dxf.drawing(name)
    stacks_layers(drawing, 0, 0)
    drawing.save()
    print("drawing '%s' created.\n" % name)
