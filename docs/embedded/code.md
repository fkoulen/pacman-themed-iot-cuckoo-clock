# Code

> This is not a place to put your code, but to describe the code that you have written. You can describe the code in a
> general way, but also go into detail on specific parts of the code. You can also refer to the code in your repository.
> So just add a link to the code in your repository.


!!! abstract "show-current-time"

    === "show-current-time.cpp"
        `void setup()`  
        This code first initalizes serial communication & the LCD. After that it sets the date and time prefix.

        `void loop()`  
        In this loop, we check if the serial communication has received characters by checking the length of the
        received message. If we have received data, we first read it. Then we extract the time and date from it. 
        Finally, we put the received date and time after the earlier set prefixes.

    === "send_time.py"

        * This code uses the serial package to write to the port.   
        * It uses the time package to retrieve the current time from the device that the python code is running on.
        * The time is then written to the port. 
        * This repeats every second.