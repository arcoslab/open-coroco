#!/usr/bin/python

import serial
from serial import SerialException
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
        while self.connecting==True:
            try:
                self.ser = serial.Serial(self.dev_type+str(self.counter),self.serial_speed , timeout=self.serial_timeout)
                self.connecting=False
                self.ser.flushInput()
                print "Connected to the STM32F4"              
                
            except SerialException:
                print"Disconnected from the STM32, cua cua"
                self.counter=self.counter+1
                if (self.counter>MAX_serial_device_counter):
                    self.counter=0
                self.connecting=True 	





    def read_data_from_stm32(self):
        bytes = 1
        single_character   = self.ser.read(bytes)
        
        self.checksum_python=0
        self.checksum_stm32=0

        if(single_character == "X" and single_character!=None):

            #while (single_character != "m"):
                
            '''
            single_character = self.ser.read(bytes)
            if   (single_character=='t'):   self.time                =self.get_data_and_checksum()
            elif (single_character=='r'):   self.reference_frequency =self.get_data_and_checksum()
            elif (single_character=='h'):   self.hall_frequency      =self.get_data_and_checksum()
            elif (single_character=='k'):   self.checksum_stm32 = ord(self.ser.read(bytes))
            '''
            self.time                =self.get_data_and_checksum()
            self.reference_frequency =self.get_data_and_checksum()
            self.hall_frequency      =self.get_data_and_checksum()
            self.checksum_stm32 = ord(self.ser.read(bytes))

        #print "checksum python: ",self.checksum_pthon ,"checksum_stm32",self.checksum_stm32


        if (self.checksum_python!=self.checksum_stm32):
            self.transmition_error=True 

        elif ( (self.checksum_stm32!=0) and (self.checksum_python==self.checksum_stm32) ):
            print "time: ",self.time, "ref freq: ",self.reference_frequency,"hall_frequency: ",self.hall_frequency


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
                        self.transmition_error=False
                        #print "found, whaat!"+str(data)
                    else:   
                        self.transmition_error=True
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
