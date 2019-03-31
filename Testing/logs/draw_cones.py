#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
#
# 2019 Tel-Aviv university formula student team ,Noam Dahan, Tuval Jacob Gal Zaidenstein.




# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time
import glob
import os

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)
pastLine = 0

def animate(i):
    ###split by each frame###
    global pastLine
    pullFile.seek(pastLine)
    pullData = pullFile.read()
    pullFile.flush()
    blockArray = pullData.split('[ms]')
    del blockArray[0]
    if (len(blockArray) > 600):
    	pastLine = pullFile.tell() - 500
    if pastLine < 0:
       pastLine = 0
    #print(pastLine)           
    x_R_ar = []
    y_R_ar = []
    x_L_ar = []
    y_L_ar = []
    x_START_ar = []
    Y_START_ar = []

    lineArray = []
    if len(blockArray) > 0:
      lineArray = blockArray[-1].split('\n')
    #del lineArray[0]
    #print(lineArray)
    flag = False
    for eachLine in lineArray:###for every measrment in one frame### 
	lineLst = eachLine.split(',')   
	while("" in lineLst) : 
    		lineLst.remove("")
	length = len(lineLst)
        #print(lineLst)
        if (length != 4):
            continue;
        cur_color,cur_id,x,y = lineLst
	if x != "" and y != "":
		flag = True
		if (cur_color=="3"): #blue is 3
		            x_R_ar.append(float(x))
		            y_R_ar.append(float(y))
		if (cur_color=="2"):# yellow is 2
		            x_L_ar.append(float(x))
		            y_L_ar.append(float(y))  
		if (cur_color=="1"): # orange is 0 or 1 
		            x_START_ar.append(float(x))
		            Y_START_ar.append(float(y))
		if (cur_color=="0"): # orange is 0 or 1 
		            x_START_ar.append(float(x))
		            Y_START_ar.append(float(y))
        
    
    if flag:              
	    ax1.clear()
	    ###plot the blue conos###
	    plt.xlim(-5000,5000)
	    plt.ylim(0,8000)
	    plt.title('Cones detection in the last frame')
	    plt.xlabel('X[mm]')
	    plt.ylabel('Y[mm]')
	    ax1.plot(x_R_ar,y_R_ar,'bo')
	
	    ###plot the yellow conos###
	    ax1.plot(x_L_ar,y_L_ar,'yo')
	    ###plot the orange conos###
	    ax1.plot(x_START_ar,Y_START_ar, 'ro')


###LIVE animation###
    ###open the newest file###
dir_path = os.path.dirname(os.path.realpath(__file__))
newest= max(glob.glob(dir_path+'/*.csv'), key=os.path.getctime)
pullFile = open(newest,"r")
ani = animation.FuncAnimation(fig, animate, interval=1)

plt.autoscale(False)

plt.show()
