# Add your Python code here. E.g.
from microbit import *

height = 1; # Range from 1-5

# Accelerometer three rows display values
acc_left  = ':00000:09900:00000:';
acc_right = ':00000:00990:00000:';
acc_up    = ':00900:00900:00000:';
acc_down  = ':00000:00900:00900:';
acc_none  = ':00000:00900:00000:';

# Botton bar display values
floor_bar = '00000';
    
def get_gesture():
    
    # Return current accelerometer gesture
    
    return accelerometer.current_gesture();
    
def get_bar(tick):
    
    # Basically just return display bar based on
    # given value from $tick
    
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
        # Or return null if it's not a
        # valid value $tick
        return '00000';
    
def ret_display(gesture, tmp):
    
    # Return display image based on accelerometer gesture
    # If accelerometer gesture is not found => return none
    
    if gesture == 'up':
        return tmp + acc_down + floor_bar;
    elif gesture == 'down':
        return tmp + acc_up + floor_bar;
    elif gesture == 'right':
        return tmp + acc_right + floor_bar;
    elif gesture == 'left':
        return tmp + acc_left + floor_bar;
    else:
        return tmp + acc_none + floor_bar;
    
while True:
    
    # If button a was pressed => Add height if it's less than five
    if button_a.was_pressed():
        if height < 5:
            height = height + 1;
    
    # If button b was pressed => Remove height if it's more than one
    if button_b.was_pressed():
        if height > 1:
            height = height - 1;
    
    # Run display function
    display.show(Image(ret_display(get_gesture(), get_bar(height))));
