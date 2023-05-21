"""
    Simple class for serial communication between Arduino and Windows machines 
    Saves test data to an output file after completion

    Copyright: Z-Axis Connector Company
    Date: 2/9/23
    Author: John Glatts
"""
import serial
import time
from tkinter import *
from tkinter import messagebox

class WinSer():

    """
        WinSer Constructor
        
        Args:
        write_out (bool, optional): flag for writing to output file. Defaults to True.
        port (int, optional): COM port of the device. Defaults to 5.
        num_tests (int, optional): number of tests to compute. Defaults to 0.
        baud (int, optional): baud rate of the device. Defaults to 9600.
    """
    def __init__(self, write_out=True, port=9, num_tests=0, baud=115200):
        self.port = port
        self.num_tests = num_tests
        self.baud = baud
        self.write_out = write_out
        self.out_file = open('test_data.txt', 'w')
        self.board = None

    """
        Main test method for the LBCC tester
        Will setup comm. with the MCU and then begin the test
    """
    def main(self):
        if not self.get_board():
            print('\nNo Board Connected!\n')
            return

        print('GETTING TEST DATA\n')
        self.run_test()
        print('TEST COMPLETE')
        self.out_file.close()

    """
        Begin the comm. with the MCU at the specific port\baudrate

        Returns:
            bool: True if the device is found, False otherwise
    """
    def get_board(self):
        com_port = 'COM' + str(self.port)
        try: 
            self.board = serial.Serial(port=com_port, baudrate=self.baud, timeout=.2)
            return True
        except:
            return False

    """
        Run the approriate number of tests 
    """
    def run_test(self):
        if (self.num_tests > 0):
            while (self.num_tests > 0):
                test_str = self.get_test_str()
                self.num_tests -= 1
                print(test_str)    
        else:
            while (1):
                test_str = self.get_test_str()
                print(test_str)
    
    
    """
        Get data from the MCU and write to outfile if flag is set
    """
    def get_test_str(self):
        ret = self.board.read_until().decode()
        if (ret != ' ') and self.write_out:
            self.write_to_file(ret)
        return ret


    def write_to_file(self, data_str):
        self.out_file.write(data_str)    



if __name__ == '__main__':
    WinSer().main()