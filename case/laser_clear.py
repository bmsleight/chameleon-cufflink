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
bar_height = bar_length + p_thickness + p_thickness
bar_thickness = 3
tape_width = 5.5

def add_layers(drawing):
    drawing.add_layer('OUTLINE', color=1)
    drawing.add_layer('ENGRAVE', color=2)
    drawing.add_layer('CUTSINNEREARLY', color=3)
    drawing.add_layer('CUTSINNER', color=4)
    drawing.add_layer('CUTSOUTER', color=5)


def outline(drawing):
    drawing.add(dxf.rectangle((0, 0) , 210, 297,  layer='OUTLINE'))

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
        # Slot for bar (the other end of the cufflink
        if (x == 5):
            drawing.add(dxf.rectangle((centreX-(bar_length/2), centreY-(p_thickness/2)) , bar_length, p_thickness, layer='CUTSINNER'))  
        # Hole for button
        if (x == 2):
            drawing.add(dxf.line(
                                  (centreX-(p_thickness*1.1)/2, centreY-battery_space/3), 
                                  (centreX-(p_thickness*1.1)/2, centreY-total_outline_radius ), 
                                layer='CUTSINNEREARLY') 
                       )  
            drawing.add(dxf.line(
                                  (centreX+(p_thickness*1.1)/2, centreY-battery_space/3), 
                                  (centreX+(p_thickness*1.1)/2, centreY-total_outline_radius ), 
                                layer='CUTSINNEREARLY') 
                       )  

        if ( x == 1):
        # Hole for button - but only indent to hold button in
            drawing.add(dxf.line(
                                  (centreX-(p_thickness*1.1)/2, centreY-battery_space/3), 
                                  (centreX-(p_thickness*1.1)/2, centreY-2-battery_space/2 ), 
                                layer='CUTSINNEREARLY') 
                       )  
            drawing.add(dxf.line(
                                  (centreX+(p_thickness*1.1)/2, centreY-battery_space/3), 
                                  (centreX+(p_thickness*1.1)/2, centreY-2-battery_space/2 ), 
                                layer='CUTSINNEREARLY') 
                       )  

            drawing.add(dxf.line(
                                  (centreX-(p_thickness*1.1)/2, centreY-2-battery_space/2 ), 
                                  (centreX+(p_thickness*1.1)/2, centreY-2-battery_space/2 ), 
                                layer='CUTSINNEREARLY') 
                       )  

        if ((x != 0) and (x !=5)):
        # Tape hole for battery connection
            drawing.add(dxf.line(
                                  (centreX-(tape_width)/2, centreY+battery_space/3), # Should do trig, but what the hell 
                                  (centreX-(tape_width)/2, centreY+1.5+battery_space/2 ), 
                                layer='CUTSINNEREARLY') 
                       )  
            drawing.add(dxf.line(
                                  (centreX+(tape_width)/2, centreY+battery_space/3), # Should do trig, but what the hell 
                                  (centreX+(tape_width)/2, centreY+1.5+battery_space/2 ), 
                                layer='CUTSINNEREARLY') 
                       )  
            drawing.add(dxf.line(
                                  (centreX-(tape_width)/2, centreY+1.5+battery_space/2 ), 
                                  (centreX+(tape_width)/2, centreY+1.5+battery_space/2 ), 
                                layer='CUTSINNEREARLY') 
                       )  


def bar(drawing, x, y):
    polyline= dxf.polyline(layer='CUTSOUTER')
    polyline.add_vertices( [(x,y), (x,y+bar_length), (x+p_thickness,y+bar_length),
                           (x+p_thickness,y+(bar_length)/2+bar_thickness/2),
                           (x+bar_height-p_thickness,y+(bar_length)/2+bar_thickness/2), 
                           (x+bar_height-p_thickness,y+bar_length),
                           (x+bar_height,y+bar_length),
                           (x+bar_height,y),
                           (x+bar_height-p_thickness,y),
                           (x+bar_height-p_thickness,y+(bar_length)/2-bar_thickness/2), 
                           (x+p_thickness,y+(bar_length)/2-bar_thickness/2),
                           (x+p_thickness,y),
                           (x,y) ]) 
    drawing.add(polyline)


def button(drawing, x, y):
    polyline= dxf.polyline(layer='CUTSOUTER')
    polyline.add_vertices( [(x,y), 
                           (x+(p_thickness*0),y+(p_thickness*2)), 
                           (x+(p_thickness*1),y+(p_thickness*2)), 
                           (x+(p_thickness*1),y+(p_thickness*1)), 
                           (x+(p_thickness*4),y+(p_thickness*1)), 
                           (x+(p_thickness*4),y+(p_thickness*0)), 
                           (x,y) ]) 
    drawing.add(polyline)


if __name__ == '__main__': 
    name="laser_clear.dxf"
    drawing = dxf.drawing(name)
    
    outline(drawing)
    stacks_layers(drawing)
    bar(drawing, 140, 5)
    button(drawing, 145, 2.5)
    button(drawing, 145, 17.5)

    drawing.save()
    print("drawing '%s' created.\n" % name)

  
