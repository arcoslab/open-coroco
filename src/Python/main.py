#!/usr/bin/python


from serial_functions           import Serial_Stm32
from plotutils                  import *
#from csv_functions              import *
#from motor_control_functions    import * 



def main():
    #try:
        data=[0.0,0.0,0.0]
        x   =[]
        y_1 =[]
        y_2 =[]
                
        collect=False

        stm32=Serial_Stm32()
        stm32.connecting_to_stm32F4()
        
        while True:
   
            stm32.read_data_from_stm32(data)


            data_collection           (data,x,y_1,y_2,stm32.collect)
            stm32.plot=data_collection_with_timer(data,x,y_1,y_2,stm32.test)

            stm32.write_commands_to_stm32()   

            if (stm32.plot==True):
                plot_data(x,y_1,y_2)
                log_data=[]
                log_data.append(x)
                log_data.append(x)
                log(log_data)
                stm32.plot=False
                stm32.test=False

            if (stm32.transmission_error==False):
                print "time: ",data[0], "ref freq: ",data[1],"hall_frequency: ",data[2]


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
