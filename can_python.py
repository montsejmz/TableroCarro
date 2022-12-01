# This Python file uses the following encoding: utf-8

# if __name__ == "__main__":
#     pass


import os

import can

os.system('sudo ip link set can0 down')
os.system('sudo ip link set can0 type can bitrate 500000')
os.system('sudo ip link set can0 up')

def read():

    can_interface = 'can0'
    bus = can.interface.Bus(channel = can_interface, bustype = 'socketcan')
    message = bus.recv(0.01)
    if message != None:
        if message.arbitration_id == 0x05:
            state_charge = message.data[4]
            RPM_L = message.data[0] << 8
            RPM_L |= message.data[1]

            RPM_R = message.data[2] << 8
            RPM_R |= message.data[3]
            RPM_mean = (RPM_L+RPM_R) >>1
            ccu = (RPM_mean<<8) | state_charge
            return ccu
