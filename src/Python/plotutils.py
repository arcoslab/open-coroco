#!/usr/bin/python
import matplotlib.pyplot as plt
import datetime
import time
import os
import csv 

state='start'
state_timer='start'
start_time=time.time()
tag_x='a'
tag_y='b'
title=''


rows = 1
columns = 1 
subplot_index = 1
plot_figsize=(10, 5)
plot_dpi=30
plot_face_color='w'
plot_edge_color='k'
plotting_character     = '.'






def data_collection(data,data_buffer,collect,transmission_error):
    global state
    


    if (state=='start'and collect==False):

        state='start'

    elif (state=='start' and collect==True):

        x=[]
        y=[]
        data_buffer.pop()
        data_buffer.pop()       
        data_buffer.append(x)
        data_buffer.append(y)

        state='collecting'

    elif (state=='collecting' and collect==True and transmission_error==False):
        for i in range(len(data)):
          data_buffer[i].append(data[i])
        state='collecting'

    elif (state=='collecting' and collect==False):
        state='start'   


def data_collection_with_timer(data,data_buffer,collect,transmission_error):
    global state_timer
    global start_time
    max_time=5
    now=time.time()
    #print "state_timer: ",state_timer, "now: ",now,"start_time: ",start_time

    if (state_timer=='start'and collect==False):

        state_timer='start'
        return False

    elif (state_timer=='start' and collect==True):

        x=[]
        y=[]
        data_buffer.pop()
        data_buffer.pop()       
        data_buffer.append(x)
        data_buffer.append(y)

        state_timer='collecting'
        start_time = time.time()
        return False

    elif (state_timer=='collecting' and collect==True and (now-start_time<max_time) and transmission_error==False):

        for i in range(len(data)):
          data_buffer[i].append(data[i])

        state_timer='collecting'
        return False

    elif (state_timer=='collecting' and collect==True and (now-start_time>max_time) ):
        state_timer='start'  
        return True


def print_selection(print_selection):
    global tag_x
    global tag_y
    global title    

    global rows
    global columns 
    global subplot_index
    global plot_figsize
    global plot_dpi
    global plot_face_color
    global plot_edge_color
    global plotting_character

    height=7
    lenght=7
    

    if print_selection==0:
        tag_x="Cycles"
        tag_y="Frequency (Hz)"
        title="Hall sensor speed"
    elif print_selection==1:
        tag_x="isD (A)"
        tag_y="isQ (A)"
        title="Stator Current in polar reference"
        plot_figsize=(height, lenght)
        

    elif print_selection==2:
        tag_x="VsD (V)"
        tag_y="VsQ (V)"
        title="Stator voltage in polar reference"
        plot_figsize=(height, lenght)
        #plotting_character     = '.'

    elif print_selection==3:
        tag_x="Cycles"
        tag_y="Battery Voltage (V)"
        title="Battery Voltage"
    elif print_selection==4:
        tag_x="psi_sD (Wb)"
        tag_y="psi_sQ (Wb)"
        title="Flux-linkage"
        plot_figsize=(height, lenght)
        #plotting_character     = '.'

    elif print_selection==5:
        tag_x="Cycles"
        tag_y="Electromagnetic torque (Nm)"
        title="Electromagnetic torque"
    elif print_selection==6:
        tag_x="Cycles"
        tag_y="PI control"
        title="PI control"
    elif print_selection==7:
        tag_x="Cycles"
        tag_y="Strain gauge torque (Nm)"
        title="Strain gauge torque"
    elif print_selection==8:
        tag_x="Stiffness"
        tag_y="Damping"
        title="Impedance control damping and stiffness"
    elif print_selection==9:
        tag_x="Cycles"
        tag_y="Electric angle"
        title="Electric angle"
    elif print_selection==10:
        tag_x="Cycles"
        tag_y="isA (A)"
        title="Phase A current"
    elif print_selection==11:
        tag_x="Cycles"
        tag_y="isB (A)"
        title="Phase B current"
    elif print_selection==12:
        tag_x="Cycles"
        tag_y="isC (A)"
        title="Phase C current"
    elif print_selection==13:
        tag_x="Cycles"
        tag_y="Frequency (Hz)"
        title="Electromagnetic frequency"   
    elif print_selection==14:
        tag_x="Cycles"
        tag_y="Frequency (Hz)"
        title="Electromagnetic frequency with i neglected" 
    elif print_selection==15:
        tag_x="psi_sD (Wb)"
        tag_y="psi_sQ (Wb)"
        title="Flux-linkage with i neglected"
        plot_figsize=(height, lenght)
         

    elif print_selection==16:
        tag_x="Cycles"
        tag_y="Electromagnetic torque (Nm)"
        title="Electromagnetic torque with i neglected"
    elif print_selection==17:
        tag_x="Cycles"
        tag_y="acceleration angle"
        title="acceleration angle"
    elif print_selection==18:
        tag_x="Cycles"
        tag_y="psi_s (Wb)"
        title="Flux-linkage"
    elif print_selection==19:
        tag_x="Cycles"
        tag_y="V_s (V)"
        title="Stator Voltage Magnitude"
    elif print_selection==20:
        tag_x="reference electric frequency"
        tag_y="reference_electric_angle"
        title="reference"



def tag_x_():
    global tag_x
    return tag_x
def tag_y_():
    global tag_y
    return tag_y
def title_():
    global title
    return title

def plot_data(data_buffer,path):
        global tag_x
        global tag_y
        global tittle    
        
        global rows
        global columns 
        global subplot_index
        global plot_figsize
        global plot_dpi
        global plot_face_color
        global plot_edge_color
        global plotting_character
        
        plot_name=path

        

        if not os.path.exists(path):
            os.makedirs(path)

        plt.figure(num=1, figsize=plot_figsize,dpi=plot_dpi, facecolor=plot_face_color, edgecolor=plot_edge_color) 

        plt.subplot(rows,columns,subplot_index)
        plt.plot(data_buffer[0],data_buffer[1],plotting_character,label='')
        #plt.plot(x,x,plotting_character,label='hall'     ) 
        plt.title(title)
        plt.xlabel(tag_x)
        plt.ylabel(tag_y)
        plt.legend()
        
        plt.savefig(path+datetime.datetime.now().ctime()+"_"+title+".jpg")
        plt.close()
    

def log(datos,path,title):
        global tittle
        global tag_x
        global tag_y

        if not os.path.exists(path):
                os.makedirs(path)

        log_file=open(path+datetime.datetime.now().ctime()+"_"+title+'_data.csv',"wb")#,a)
        writer   = csv.writer(log_file, delimiter=';',quotechar=' ', quoting=csv.QUOTE_MINIMAL)

        writer.writerow( (tag_x,tag_y) )

        for i in range(len(datos[0])):
            
            #writer.writerow(str(datos[0][i]) + ' '+  str(datos[1][i]))
                        
            writer.writerow( (str(datos[0][i]),str(datos[1][i]) ))
              
        log_file.close()
