# led_test_client.py
# Test client for erpc led server example
# Author: becksteing/Jing-Jia Liou
# Date: 02/13/2022
# Blinks LEDs on a connected Mbed-enabled board running the erpc LED server example

from time import sleep
import erpc
from blink_led import *
import sys

if __name__ == "__main__":

    if len(sys.argv) != 2:
        print("Usage: python led_test_client.py <serial port to use>")
        exit()

    # Initialize all erpc infrastructure
    xport = erpc.transport.SerialTransport(sys.argv[1], 9600)
    client_mgr = erpc.client.ClientManager(xport, erpc.basic_codec.BasicCodec)
    client = client.LEDBlinkServiceClient(client_mgr)

    # Blink LEDs on the connected erpc server
    print("Start")
    sleep(0.1)
    client.locate(0, 0)
    sleep(0.1)
    client.Putc(72) #H
    sleep(0.1)
    client.Putc(105) #i
    sleep(0.1)
    client.Putc(44) #,
    sleep(0.1)
    client.Putc(32) #space
    sleep(0.1)
    client.Putc(109) #m
    sleep(0.1)
    client.Putc(121) #y
    sleep(0.1)
    client.Putc(32) #space
    sleep(0.1)
    client.Putc(110) #n
    sleep(0.1)
    client.Putc(97) #a
    sleep(0.1)
    client.Putc(109) #m
    sleep(0.1)
    client.Putc(101) #e
    sleep(0.1)
    client.Putc(32) #space
    sleep(0.1)
    client.Putc(105) #i
    sleep(0.1)
    client.Putc(115) #s
    sleep(0.1)
    client.Putc(32) #space
    sleep(0.1)
    client.Putc(32) #space
    sleep(0.1)
    client.Putc(69) #E
    sleep(0.1)
    client.Putc(114) #r
    sleep(0.1)
    client.Putc(110) #n
    sleep(0.1)
    client.Putc(101) #e
    sleep(0.1)
    client.Putc(115) #s
    sleep(0.1)
    client.Putc(116) #t
    sleep(0.1)
    client.Putc(46) #.
