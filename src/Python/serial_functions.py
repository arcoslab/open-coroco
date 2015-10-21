#!/usr/bin/python

import serial
from serial import SerialException
import sys
import select
from byte_to_float import *


class Serial_Stm32(object):

    #serial device parameters
    dev_type       ="/dev/ttyACM"
    serial_speed   =115200
    serial_timeout =1
    MAX_serial_device_counter=100
    #control variables
    counter = 0
    connecting=True
    collect=False
    plot=False
    test=False
    transmission_error=False
    def __init__(self):
        print "initializing Serial_Stm32 class"    
        #self.initializing_values()        
        #self.creating_data_vectors()
        #self.create_log_file()
        #self.connecting_to_stm32F4()
               
    def __del__(self):
        self.ser.close()
        print "---Serial port closed: disconnected from the STM32F4---"

    def connecting_to_stm32F4(self):

        self.print_selection=0

        while self.connecting==True:
            try:
                self.ser = serial.Serial(self.dev_type+str(self.counter),self.serial_speed , timeout=self.serial_timeout)
                self.connecting=False
                self.ser.flushInput()
                print "Connected to the STM32F4"    


                #it is required to send the print selection to the stm32 before it starts sending data
                self.ser.write('p')
                self.ser.write(' ')
                self.ser.write(str(self.print_selection))
                self.ser.write('\n')
                self.ser.write('\r')          
                
            except SerialException:
                print"Disconnected from the STM32, cua cua"
                self.counter=self.counter+1
                if (self.counter>self.MAX_serial_device_counter):
                    self.counter=0
                self.connecting=True 	


    def read_data_from_stm32(self,data):
        bytes = 1
        single_character   = self.ser.read(bytes)
        
        self.checksum_python=0
        checksum_stm32=0

        if(single_character == "X" and single_character!=None):

            for i in range(len(data)):
                data[i]=self.get_data_and_checksum()
                
            checksum_stm32 = ord(self.ser.read(bytes))

        if (self.checksum_python!=checksum_stm32) or (checksum_stm32==0):
            self.transmission_error=True 

        #elif ( (checksum_stm32!=0) and (self.checksum_python==checksum_stm32) ):
        #    self.transmission_error=False



    def get_data_and_checksum(self):
                    bytes=1
                    info=''
                    i=0
                    while i<4:
                        single_character = self.ser.read(bytes)
                        #print "single_character_byte_to_float: "+single_character + " ord: " +str(ord(single_character))
                        info +=single_character
                        i=i+1;
                    #print "before convertion"
                    #print info
                    convertion = bytes_to_float(info)
                    #print "after conversion"
                    if (convertion[0]==True):                      
                        data = convertion[1]
                        self.transmission_error=False
                        #print "found, whaat!"+str(data)
                    else:   
                        self.transmission_error=True
                        data=0
                        #print " four bytes not found" 
                    
                    info_counter=0
                    for ch in info:
                        if info_counter<len(info)-1:
                            self.checksum_python=self.checksum_python+ord(ch)
                            if self.checksum_python>=256:
                                self.checksum_python=self.checksum_python-256
                        #print ord(ch)
                    return data  

    def write_a_line(self,line):
        self.ser.write(line)
        self.ser.write('\n')
        self.ser.write('\r') 

    def write_commands_to_stm32(self):
        
        #print "beginning of function"
        line=''
        while sys.stdin in select.select([sys.stdin], [], [], 0)[0]:	#read from standart input if there is something, otherwise not 
            line = sys.stdin.readline()                                 #you must press enter before typing the new command
            #print "inside first while"
 
        #print "after while" 
        if line:
            #print "before raw input"
            line=raw_input("Enter new command: ")   #the printing of the stm32f4 data is stopped until you type a new reference
            #print "after raw input"
            if line:

                split_command = line.split()

                if   split_command[0]=='p': 
                    self.write_a_line(line)
                    self.print_selection=int(split_command[1])
                    
                elif split_command[0]=='c': 
                    self.collect=True
                    
                elif split_command[0]=='e': 
                    self.collect=False
                    self.plot   =True 
                
                elif split_command[0]=='t': 
                    self.test=True

                    self.ser.write('p')
                    self.ser.write(' ')
                    self.ser.write(str(self.print_selection))
                    self.ser.write('\n')
                    self.ser.write('\r')       

                else: self.write_a_line(line)

                

            
                '''
                #updating reference frequency
                if     split_command[0]=='d':   self.write_a_line(line)
                elif   split_command[0]=='D':   self.write_a_line(line)
                elif   split_command[0]=='K':   self.write_a_line(line)
                elif   split_command[0]=='G':   self.write_a_line(line)
                #capturing data into csv
                elif   split_command[0]=='c':
                    self.tag_comment       =line+self.aditional_comment+self.print_selection_tags()#raw_input("Enter comment: ") 
                    self.path              =self.root_path + "["+datetime.datetime.now().ctime() +"] ["+self.tag_comment+"]"+'/'  

                elif   split_command[0]=='C':   self.capture_c_button = True
                elif split_command[0]=='f': self.end_capturing_data()

                #selecting what to print
                elif split_command[0]=='p': self.print_selection_setup(int(split_command[1]))



                elif split_command[0]=='one':
                    self.test_command='d'#'G';
                    self.start_test=True;
                    self.print_selection_setup(int(split_command[2]))
                    self.test_frequency    =split_command[1]
                    self.tag_comment       =line+self.aditional_comment#raw_input("Enter comment: ") 
                    self.path              =self.root_path + "["+datetime.datetime.now().ctime() +"] ["+self.tag_comment+"]"+'/'  


                elif split_command[0]=='ONE':
                    
                    self.start_test=True;
                    self.print_selection_setup(int(split_command[2]))
                    self.test_frequency    =split_command[1]
                    self.tag_comment       =line+self.aditional_comment#raw_input("Enter comment: ") 
                    #self.path              =self.root_path + "["+datetime.datetime.now().ctime() +"] ["+self.tag_comment+"]"+'/'  
                '''
