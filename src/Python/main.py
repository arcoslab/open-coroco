#!/usr/bin/python


from serial_functions           import Serial_Stm32
from plotutils                  import * 
#import plotutils
#from csv_functions              import *
#from motor_control_functions    import * 



def main():
    #try:
        data=[0,0]
        x=[]
        y=[]
        data_buffer=[]
        data_buffer.append(x)
        data_buffer.append(y)     
  
        collect=False

        stm32=Serial_Stm32()
        stm32.connecting_to_stm32F4()
        
        while True:
   

            stm32.write_commands_to_stm32()
  
            #plot_selection(stm32.print_selection,data,data_buffer)
            stm32.read_data_from_stm32(data)
            print_selection(stm32.print_selection)
            
            if stm32.test==False: data_collection(data,data_buffer,stm32.collect,stm32.transmission_error)#(data,x,y_1,y_2,stm32.collect)
    
            else: stm32.plot=data_collection_with_timer(data,data_buffer,stm32.test,stm32.transmission_error)#(data,x,y_1,y_2,stm32.test)
            #data_collection(data,data_buffer,stm32.collect)
 
            print_selection(print_selection)

            if (stm32.plot==True):
                plot_data(data_buffer,stm32.path)
                                
               
            
                log(data_buffer,stm32.path,title_())
                                
                stm32.plot=False
                stm32.test=False
            

            if (stm32.transmission_error==False):
                print tag_x_(),": ",data[0],"  ",tag_y_(),": ",data[1]#,"hall_frequency: ",data[2]
            #else: 
            #    print "time: ",data[0], "ref freq: ",data[1]
    #except:
        #print "cua cua"

if __name__ == '__main__':
	main()


'''        
   while True:
        user_input()
        read_from_stm32(new_tuplet)
        write_vector_to_log(vector)
        plot_vector(vector)
        write_to_stm32()




   stm32f4 = Serial_Stm32f4()
    while True:
        stm32f4.read()
        stm32f4.write()
except KeyboardInterrupt:
    print " " 
    print "Sorry, Ctrl-C..."
except SerialException:
            print"STM32F4 disconnected, cua cua"
'''
