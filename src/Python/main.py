#!/usr/bin/python


from serial_functions           import Serial_Stm32
from plotutils                  import * 
from serial import SerialException
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
            
            try: 
                stm32.write_commands_to_stm32()
                #stm32.read_data_bytes_from_stm32(data)
                stm32.read_ascii_data_from_stm32(data)
                print_selection(stm32.print_selection)
                
                if stm32.test==False: data_collection(data,data_buffer,stm32.collect,stm32.transmission_error)#(data,x,y_1,y_2,stm32.collect)
        
                else: stm32.plot=data_collection_with_timer(data,data_buffer,stm32.test,stm32.transmission_error)#(data,x,y_1,y_2,stm32.test)
                #data_collection(data,data_buffer,stm32.collect)
     
                print_selection(print_selection)

                if (stm32.plot==True):
                    plot_data(data_buffer,stm32.path)
                                    
                   
                
                    log(data_buffer,stm32.path,title_())
                           
                    if stm32.test==True:
                        stm32.ser.write('d')
                        stm32.ser.write(' ')
                        stm32.ser.write('0')
                        stm32.ser.write('\n')
                        stm32.ser.write('\r') 
         
                    stm32.plot=False
                    stm32.test=False
                    

                if (stm32.transmission_error==False):
                    #print tag_x_(),": ",data[0],"  ",tag_y_(),": ",data[1],"  ",title_()#,"hall_frequency: ",data[2]
                    print tag_x_(),": %10.2f" %data[0],"  ",tag_y_(),": %10.2f" %data[1],"  ",title_(),"   print#: ",stm32.print_selection#,"hall_frequency: ",data[2]

            except KeyboardInterrupt:
                print " " 
                print "Sorry, Ctrl-C..."
                break
            
            except SerialException:
                print"STM32F4 disconnected, cua cua"
                stm32.connecting=True 
                stm32.connecting_to_stm32F4()
                    
if __name__ == '__main__':
	main()



