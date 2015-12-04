#!/usr/bin/python

import serial
from serial import SerialException
import sys
import select
#from byte_to_float import *
import datetime
import time
import struct

def bytes_to_float(string_of_bytes):
    #print "entering bytes to float"
    if len(string_of_bytes)<4:  #if there are not 4 bytes then it cannot be translated into a float and therefore an error is obtained
        #print  "byte_to_float: there are less than four bytes "        
        return (False,25.0)
    else:
        tuplet_float= struct.unpack_from('f',string_of_bytes)   #uncompress string of 4 bytes into a floting number
        #print "byte_to_float: " + str(tuplet_float[0])
        return (True,tuplet_float[0])



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
    stop=False

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



    def read_ascii_data_from_stm32(self,data):

        try:
            
            line=self.ser.readline() 

            line_split=line.split()   

            for i in range(len(data)):
                data[i]=float(line_split[i]) 

            self.transmission_error=False
            
        except SerialException:
            #self.transmission_error=True
            print "transmission error"
            print"STM32F4 disconnected, cua cua"
            self.connecting=True 
            self.connecting_to_stm32F4()
        except KeyboardInterrupt:
            print " " 
            print "Sorry, Ctrl-C..."
            pass
        except:
            self.transmission_error=True
            print "transmission error"
 
    def bytes_to_float(string_of_bytes):
        #print "entering bytes to float"
        if len(string_of_bytes)<4:  #if there are not 4 bytes then it cannot be translated into a float and therefore an error is obtained
            #print  "byte_to_float: there are less than four bytes "        
            return (False,25.0)
        else:
            tuplet_float= struct.unpack_from('f',string_of_bytes)   #uncompress string of 4 bytes into a floting number
            #print "byte_to_float: " + str(tuplet_float[0])
            return (True,tuplet_float[0])
              

    def read_data_bytes_from_stm32(self,data):
        max_floating_value=10000000.0 #2^32 in the stm32
        bytes = 1
        single_character   = self.ser.read(bytes)
        print_selection=self.print_selection
        self.checksum_python=0
        checksum_stm32=0


        while(single_character != "X" or single_character==None):
            single_character   = self.ser.read(bytes)

        for i in range(len(data)):
            data[i]=self.get_data_and_checksum()
            
        checksum_stm32 = ord(self.ser.read(bytes))

        if (self.checksum_python!=checksum_stm32) or (checksum_stm32==None):#(checksum_stm32==0):
                self.transmission_error=True 

        #http://www.gnuplot.info/
        #HACK!!!!!!!!: 
        elif (print_selection==0 and (data[0]<1.0                           or data[1]<-500.0   or data[1]>500.0    ) ):  self.transmission_error=True
        elif (print_selection==1 and (data[0]<-50.0     or data[0]>50.0     or data[1]<-50.0    or data[1]>50.0     ) ):  self.transmission_error=True
        elif (print_selection==2 and (data[0]<-100.0    or data[0]>100.0    or data[1]<-100.0   or data[1]>100.0    ) ):  self.transmission_error=True
        elif (print_selection==3 and (data[0]<1.0                           or data[1]<-100.0   or data[1]>100.0    ) ):  self.transmission_error=True
        elif (print_selection==4 and (data[0]<-10.0     or data[0]>10.0     or data[1]<-10.0    or data[1]>10.0     ) ):  self.transmission_error=True
        elif (print_selection==5 and (data[0]< 1.0                          or data[1]<-50.0    or data[1]>50.0     ) ):  self.transmission_error=True
        elif (print_selection==6 and (data[0]<1.0                           or data[1]<-400.0   or data[1]>400.0    ) ):  self.transmission_error=True
        elif (print_selection==7 and (data[0]<1.0                           or data[1]<-500.0   or data[1]>500.0) ):  self.transmission_error=True
        elif (print_selection==8 and (data[0]<1.0                           or data[1]<-500.0   or data[1]>500.0) ):  self.transmission_error=True
        elif (print_selection==9 and (data[0]<1.0                       or data[1]<-360.0*4000.0 or data[1]>360.0*2000.0) ):  self.transmission_error=True
        elif (print_selection==10 and (data[0]<1.0                          or data[1]<-50.0    or data[1]>50.0) ):  self.transmission_error=True
        elif (print_selection==11 and (data[0]<1.0                          or data[1]<-50.0    or data[1]>50.0) ):  self.transmission_error=True
        elif (print_selection==12 and (data[0]<1.0                          or data[1]<-50.0    or data[1]>50.0) ):  self.transmission_error=True
        




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
                
                    self.root_path = "./measures/"
                    self.path      =self.root_path + "["+datetime.datetime.now().ctime() +"]"+'/'

                elif split_command[0]=='C': 
                    self.collect=True
                   
                
                elif split_command[0]=='e': 
                    self.collect=False
                    self.plot   =True 
                
                elif split_command[0]=='t': 
                    self.test=True

                    self.root_path = "./measures/"
                    self.path      =self.root_path + "["+datetime.datetime.now().ctime() +"]"+'/'

    

                elif split_command[0]=='T': 
                    self.test=True


                elif split_command[0]=='o': 
                    self.test=True
                    self.ser.write('d')
                    self.ser.write(' ')
                    self.ser.write(split_command[1])
                    self.ser.write('\n')
                    self.ser.write('\r') 
                    

                    self.root_path = "./measures/"
                    self.path      =self.root_path + "["+datetime.datetime.now().ctime() +"]"+'/'

                elif split_command[0]=='O': 
                    self.test=True
                    self.ser.write('d')
                    self.ser.write(' ')
                    self.ser.write(split_command[1])
                    self.ser.write('\n')
                    self.ser.write('\r')                    

                elif split_command[0]=='r': 
                    self.ser.write('r')
                    #self.ser.write(' ')
                    #self.ser.write(split_command[1])
                    self.ser.write('\n')
                    self.ser.write('\r')  

                elif split_command[0]=='a': 
                    self.ser.write('a')
                    self.ser.write(' ')
                    self.ser.write(split_command[1])
                    self.ser.write('\n')
                    self.ser.write('\r') 
                elif split_command[0]=='q': 
                    self.stop=True

                else: self.write_a_line(line)

                

        
