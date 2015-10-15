#!/usr/bin/python


from serial_functions           import *
#from csv_functions              import *
#from motor_control_functions    import * 



def main():
    try:
 
        stm32=Serial_Stm32()
        stm32.connecting_to_stm32F4()

        #print "before while"
        while True:
            #print "inside while"
            stm32.read_data_from_stm32()
            #print "end of while "


    except:
        print "cua cua"

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
