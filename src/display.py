# Add your Python code here. E.g.
from microbit import *

height = 1; # Range from 1-5

left  = ':00000:09900:00000:00000';
right = ':00000:00990:00000:00000';
up    = ':00900:00900:00000:00000';
down  = ':00000:00900:00900:00000';
none  = ':00000:00900:00000:00000';

img = '00000';

def add_height(variable):
    return variable + 1;
        
def sub_height(variable):
    return variable - 1;
    
def get_gesture():
    return accelerometer.current_gesture();
    
def get_bar(tick):
    
    if tick == 1:
        return '90000';
    elif tick == 2:
        return '99000';
    elif tick == 3:
        return '99900';
    elif tick == 4:
        return '99990';
    elif tick == 5:
        return '99999';
    else:
        return '00000';
    
def ret_display(gesture, tmp):
    
    if gesture == 'up':
        return tmp + down;
    elif gesture == 'down':
        return tmp + up;
    elif gesture == 'right':
        return tmp + right;
    elif gesture == 'left':
        return tmp + left;
    else:
        return tmp + none;
    
while True:
    if button_a.was_pressed():
        if height < 5:
            height = height + 1;
        
    if button_b.was_pressed():
        if height > 1:
            height = height - 1;
    
    display.show(Image( ret_display( get_gesture(), get_bar(height) ) ));
