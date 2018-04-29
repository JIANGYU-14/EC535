# Radar System - Embedded System

This project is a real-time object detection radar system. We implemented an ultrasonic sensor which supported by a servo motor to detect surrounding objects and calculating the distance from the object based on the duration between the rising edge and the falling edge of high level sensor response. We also set a servo motor to keep sweeping at a speed of 30 degree per second and use a LCD screen to display numerical angle and distance data in a radar-like figures. 

## Workflow Overview

<img width="563" alt="2018-04-29 5 03 26" src="https://user-images.githubusercontent.com/22137277/39411025-d888f864-4bcf-11e8-8b2e-dc9fb5b53de6.png">


# Project Detail

### Servo Motor

Servo are controlled by sending an electrical pulse of variable width, or pulse width modulation (PWM), through the control wire. There is a minimum pulse, a maximum pulse, and a repetition rate. A servo motor can usually only turn 90° in either direction for a total of 180° movement. 

Therefore, a stand along Kernel Module has been created for servo motor running on Gumstix verdex xm4, and PWM has been implemented to control the servo direction and speed. Normally, a servo motor works well at frequency of 50Hz, which corresponding to 20ms in each period. And 1ms high level represents the minimum pulse, which is left most position the servo could turned into, and 2ms represents the right most position. As the duty cycle in each period approaching to 1ms or 2ms, the rotation speed decreasing.

However, the tricky part in our project is the operating system timer ran on Gumstix is 3.86MHz, after dividing the base timer using PWM_PWCTRL and PWM_PERVAL to prescaler and period length, with both set to the largest value the PWM period can be is 15ms. This is a faster period than the expected RC Servo PWM frame period of 20ms. The standard is forgiving of 5ms period, but there is a high power draw and it severely reduces the servos lifetime. To solve this problem a OS Timer on is used to help toggle the PWM signal on and off. The scheme is to let about 2 signals through in each cycle. This scheme has been shown to work in situations with low torque requirements and provides stable motion. And the corresponding numerical duty cycle in our project is from 100 (Minimum Pulse) to 500 (Maximum). Considering the ultrasonic sensor detection angle, a timer has been set rotate the servo 30 degree per second. From the results we get, the servo works well as expected, and by changing the PWM_PWCTRL value, the speed of rotation will change also. Note the duct cycle set outside the range from 100 to 500 will cause the servo turning to a position which can not mechanically turned into, and consequently cause damage to the servo motor. Additionally, a user level program has been created to read numerical data from Kernel Module, and write into a txt file for the following LCD displaying use.

### Ultrasonic Sensor

The Ultrasonic Sensor works in a way that sends out a high-frequency sound pulse and then times how long it takes for the echo of the sound to reflect back. The sensor has 2 openings on its front. One opening transmits ultrasonic waves, (like a tiny speaker), the other receives them, (like a tiny microphone).

In our project, 28 GPIO output Pin from Gumstix has been connected to Trigger Pin on sensor to control the output ultrasonic wave. And a timer with period one second is set to control the wave period. For the Trigger Pin, the duration of high level set to 20ms and delay another 20ms afterwards. For the Echo Pin, two GPIO input Pins from Gumstix has been connected correctly, and two interrupts has been created, one for detecting the rising edge of response signal, and another for detecting the falling edge of response signal. The corresponding time stamp also marked by gettimeofday function to calculating the duration of reflected signal. Then multiple the sound speed to get the actual distance from detected object to sensor.

Note the tricky part is the sensor power must be 5 voltage, otherwise the detected distance is extremely unreliable, that is why a Arduino board included in our project, yet solely for the power supply. The same issue also applied to servo motor.

At the end, the performance of ultrasonic sensor has been evaluated, it shows high accuracy for detecting the distance from object to sensor after compared to actual distance with effective detection range from 2cm to 2m, and And a user level program was also created for read the real-time numerical data from Kernel Module, and then write into a txt file for the following data display on LCD screen.

### LCD Touch Screen

Qt is a graphic design language based on C++, as for Qt function right here it includes four parts: read in file information, show background & point, and QTimer. As for read in file there is a build in function called QFile, use QFile to get the distance and the angle data that Kernal gathered from sensor and servo then give it to location set function and make sure it appeared on screen.

For point and background setting, there are several functions: QGraphicsView QGraphicsScene, with those 2 function we can draw the point directly to the location we want on the background and show on LCD. The mean function that made the LCD read file circlely is a function called QTimer, QTimer is a function which has similar use as timer in C and C++. Because we want to get the Kernal information periodically, so the QTimer is important to the system. As we set the timer in Qt, the LCD can show the animate point, and the timer period we set is equal the timer that generate in servo.

# Summary

The real-time object detection radar system, which consists of ultrasonic sensor, servo motor and LCD touch screen, showed great promise as initially proposed. The sensor is able to detect the object right in front of it, and successfully give the distance feedback at a range from 2cm to 2m, and any object outside might cause poorly performance of sensor. As for servo motor, it works well and only at power of 5 voltage, rotation angle and speed could be specified as need, yet outrange PWM duty cycle setting will cause permanent damage to servo. At LCD displaying part, we are able to read the data from Gumstix, which prestored in two txt file, forwardly, display the corresponding angle and distance information correctly on LCD screen, and shows the detected object in a radar like figure as a red dot.
