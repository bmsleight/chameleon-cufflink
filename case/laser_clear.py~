#!/usr/bin/env python
#coding:utf-8

import sys
import os
import math

import dxfwrite
from dxfwrite import DXFEngine as dxf

battery_space = 12.7
p_thickness = 2
# space|screw|space|battery+wiggle|space|screw|space
total_outline_radius = (1+2+1+ battery_space+1+2+1)/2
screw_radius = 1
bar_length = 14
bar_heigth = bar_length + p_thickness + p_thickness

def add_layers(drawing):
    drawing.add_layer('OUTLINE', color=1)
    drawing.add_layer('ENGRAVE', color=2)
    drawing.add_layer('CUTSINNER', color=3)
    drawing.add_layer('CUTSOUTER', color=4)


def outline(drawing):
    drawing.add(dxf.rectangle((0, 0) , 75, 75,  layer='OUTLINE'))

def stacks_layers(drawing):
    for x in range(0, 6):
        centreX = 12+(22.5*x)
        centreY = 12
        # Main outline
        drawing.add(dxf.circle(total_outline_radius, (centreX, centreY), layer='CUTSOUTER'))
        # Screw holes
        # sin 45 = SQRT(2)/2 
        sin = math.sqrt(2)/2
        offset=(total_outline_radius-2-screw_radius)*sin

        drawing.add(dxf.circle(screw_radius, (centreX-offset, centreY-offset), layer='CUTSINNER'))
        drawing.add(dxf.circle(screw_radius, (centreX+offset, centreY-offset), layer='CUTSINNER'))
        drawing.add(dxf.circle(screw_radius, (centreX-offset, centreY+offset), layer='CUTSINNER'))
        drawing.add(dxf.circle(screw_radius, (centreX+offset, centreY+offset), layer='CUTSINNER'))
        # not top layer or bottom layer
        if ((x != 0) and (x !=5)):
            drawing.add(dxf.circle(battery_space/2, (centreX, centreY), layer='CUTSINNER'))
        if (x == 5):
            drawing.add(dxf.rectangle((centreX-(bar_length/2), centreY-(p_thickness/2)) , bar_length, p_thickness, layer='CUTSINNER'))  



if __name__ == '__main__': 
    name="laser_clear.dxf"
    drawing = dxf.drawing(name)
    
    outline(drawing)
    stacks_layers(drawing)

    drawing.save()
    print("drawing '%s' created.\n" % name)

  
