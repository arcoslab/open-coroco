#!/usr/bin/python
import matplotlib.pyplot as plt
import datetime
import time
import os

state='start'
state_timer='start'
start_time=time.time()

def data_collection(data,x,y_1,y_2,collect):
    global state

    if (state=='start'and collect==False):
        state='start'

    elif (state=='start' and collect==True):
        x=[]
        y_1=[]
        y_2=[]
        state='collecting'

    elif (state=='collecting' and collect==True):
        x.append(data[0])
        y_1.append(data[1])
        y_2.append(data[2])
        state='collecting'

    elif (state=='collecting' and collect==False):
        state='start'   
   


def data_collection_with_timer(data,x,y_1,y_2,collect):
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
        y_1=[]
        y_2=[]
        state_timer='collecting'
        start_time = time.time()
        return False

    elif (state_timer=='collecting' and collect==True and (now-start_time<max_time) ):
        x.append(data[0])
        y_1.append(data[1])
        y_2.append(data[2])
        state_timer='collecting'
        return False

    elif (state_timer=='collecting' and collect==True and (now-start_time>max_time) ):
        state_timer='start'  
        return True




def plot_data(x,y_1,y_2):
    
        rows = 1
        columns = 1 
        subplot_index = 1
        plot_figsize=(10, 10)
        plot_dpi=300
        plot_face_color='w'
        plot_edge_color='k'
        plotting_character     = ''
        plot_title='frequency vs time'
        x_label='time (ticks)'
        y_label='frequency (Hz)'
        root_path = "./measures/"
        path      =root_path + "["+datetime.datetime.now().ctime() +"]"+'/'
        plot_name=path


        if not os.path.exists(path):
            os.makedirs(path)

        plt.figure(num=1, figsize=plot_figsize,dpi=plot_dpi, facecolor=plot_face_color, edgecolor=plot_edge_color) 

        plt.subplot(rows,columns,subplot_index)
        plt.plot(x,x,plotting_character,label='electric')
        plt.plot(x,x,plotting_character,label='hall'     ) 
        plt.title(plot_title)
        plt.xlabel(x_label)
        plt.ylabel(y_label)
        plt.legend()
        
        plt.savefig(path+datetime.datetime.now().ctime()+"_frequencies" +".jpg")
        plt.close()
    

def log(datos):

        root_path = "./measures/"
        path      =root_path + "["+datetime.datetime.now().ctime() +"]"+'/'
        if not os.path.exists(path):
                os.makedirs(path)
        print datos[0]
        file=open(path+'datos.csv',"wb")#,a)
        

        i=0
        for x in datos[0] :
            
            file.write(str(datos[0][i]) + ';'+  str(datos[1][i]))
            i=i+1    
        file.close()
