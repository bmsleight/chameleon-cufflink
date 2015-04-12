$fn = 48;

union() {
	translate(v = [0, 0, 0.8000000000]) {
		color(c = [0.4500000000, 0.4300000000, 0.5000000000]) {
			union() {
				translate(v = [0, 0, -0.1000000000]) {
					cylinder(center = true, h = 1.5000000000, r = 6.2500000000);
				}
				cylinder(center = true, h = 1.6000000000, r = 5.0000000000);
			}
		}
	}
	translate(v = [0, 0, -0.8000000000]) {
		color(c = [0.4500000000, 0.4300000000, 0.5000000000]) {
			union() {
				translate(v = [0, 0, -0.1000000000]) {
					cylinder(center = true, h = 1.5000000000, r = 6.2500000000);
				}
				cylinder(center = true, h = 1.6000000000, r = 5.0000000000);
			}
		}
	}
}
/***********************************************
******      SolidPython code:      *************
************************************************
 
#! /usr/bin/env python
# -*- coding: UTF-8 -*-
from __future__ import division
import os, sys, re

from solid import *
from solid.utils import *

SEGMENTS = 48


def battery_cr1216():
    base = down(0.1)(cylinder( r=12.5/2, h=1.6-0.1, center=True))
    top = cylinder( r=10/2, h=1.6, center=True)
    cr1216 = base + top
    return  color(Stainless)(cr1216)

def two_battery_cr1216():
    # Should have a nice loop here
    # Quick and dirty...
    return up(1.6/2)(battery_cr1216()) + down(1.6/2)(battery_cr1216())



if __name__ == '__main__':    
    out_dir = sys.argv[1] if len(sys.argv) > 1 else os.curdir
    file_out = os.path.join( out_dir, 'case.scad')
    
    a = two_battery_cr1216()
    
    print("%(__file__)s: SCAD file written to: \n%(file_out)s"%vars())
    
    # Adding the file_header argument as shown allows you to change
    # the detail of arcs by changing the SEGMENTS variable.  This can 
    # be expensive when making lots of small curves, but is otherwise
    # useful.
    scad_render_to_file( a, file_out, file_header='$fn = %s;'%SEGMENTS) 
 
 
***********************************************/
