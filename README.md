# SMART_GARAGE

### This project is implemented using ATMEGA 32 Microcontroller and number of peripherals .

### The implementation consists of :
#### 1. AVR (ATmega32 ) MICROCONTROLLER
It is the whole control of the project. It controls the DC Motor, Buzzer and Temperature increases etc. The input/ output ports of the microcontroller is used for this.

#### 2. Keypad
It is used for enter password to access the door and the user have 3 trials.

#### 3. DC Motor
It is used for opening and closing the door.

#### 4. PIR
It is used to detect objects by recognizing infrared light emitted from nearby objects.

#### 5. LCD
It is used to display the password and if it is true or not, and display actions taken by system.

#### 6. Fuse
It is used to detect if is there is fire or no (for the safety). 

#### 7. Buzzer
It is used to alarm device as fire alert.

### WORKING PRINCIPLE:

* When power on, first it is all peripherals are initialized and LCD allows the user to set the password if it is first time or if it is not it will allows him to enter the password for 3 times then it will display the state of the door. 
* If the password is true though the trials then the door will open by DC Motor, when the car enter the garage the PIR send signal to close the door by the Motor.
* If there is Fire the FUSE Sensor send signal to turn on the buzzer to alert people and control this situation.
* If the car leaves the garage the PIR detect that and the door open.
