import time,random,struct
from pyb import UART,LED
uart = UART(3, 19200, timeout_char=1000)

def blink(i,n,t):
    for _ in range(0,n):
        LED(i).on();
        time.sleep_ms(t);
        LED(i).off();
        time.sleep_ms(t);

def send_float(f):
    uart.write(struct.pack('f', f))

def send_int(i):
    uart.write(struct.pack('i', i))

def send_string(s):
    uart.write(s+'\0')

def send_byte(b):
    uart.write(bytes([b]))

def send_end():
    uart.write(b'\x01\xfe\xff')

tft_flag = 0
while(True):
    a = uart.readchar()
    if a == 28:
        tft_flag = 0
        blink(1, 1, 200)
    elif a == 224 or tft_flag:
        tft_flag = 1
        send_int(random.randint(0,1000000));
        send_string("Hello,World!")
        send_float(255.51)
        send_byte(0x03)
        send_end()
    elif a == 26:
        blink(2, 3, 200)
        uart.write(bytes([0x1b]))

    time.sleep_ms(50)
