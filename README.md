GPS Tracker Project

The system is an RC car with GPS and Bluetooth chips controlled by TM4C123GH6PM (ARM Cortex-M4) microcontroller. This system is controlled by an android app to move the car, change its speed, displaying the GPS coordinates sent by the car through Bluetooth chip.

•	The system mainly has three modes of operation:
1- Frist mode is System Locked mode which means that the car is waiting for a Bluetooth connection with the mobile app and waiting for a right password to unlock the system and start controlling the car movement and displaying GPS coordinates. IF the password is wrong the car will produce a sound from the buzzer. Also the car is waiting for a specific mode send by the app (Last path or current Location).
After Bluetooth connection, mode detection and correct password the system is unlocked and the mobile application transfer to another page containing the map and the car movement control buttons.
![7](https://user-images.githubusercontent.com/68440283/124187210-c6910900-dabd-11eb-904d-cd35c936f571.jpeg) 
 
2- Second mode is current location mode which means that the system is in a new tour to be displayed and stored in the EEPROM. In this mode we can control the car movement in all direction (left, right, forward, backward). Also we can control its speed by the slider in the mobile app from 0% to 100% speed. If the system doesn’t move the coordinates received from GPS is neglected to avoid error. If the car moves the system receive a coordinate and send it to the mobile app to be displayed and store the coordinate in the EEPROM.
![6](https://user-images.githubusercontent.com/68440283/124187237-d3adf800-dabd-11eb-98ae-828d3b01fd59.jpeg)

3- Third mode is last path mode which means that the system will display the last tour stored in the EEPROM.
![WhatsApp Image 2021-06-11 at 4 22 49 PM](https://user-images.githubusercontent.com/68440283/124187285-e6c0c800-dabd-11eb-8677-5dffd318460e.jpeg)

•	Software implementation techniques:
System is a multitasking system, it receives coordinates from GPS, send coordinates by Bluetooth, save coordinates in EEPROM, receive direction control signals from Bluetooth, receive speed control signals from Bluetooth and Ultrasonic signal control. So to make all this tasks working together we initialized all drivers by interrupts and a scheduler operating system is used to schedule all this tasks together.

To solve a synchronization issue between mobile app and the system in sending GPS coordinates we send the GPS message in this format Latitude then space then Longitude then slash for example 30.044564 31.236132/
The issue was that this format is send byte by byte and the mobile app may start receiving from the third byte for the first time. So we design the mobile app to start reading from the first slash received which means a new coordinate will be received.

The system also displays the distance on an LCD and it updated in current location mode. In last tour mode it displays “Sending last tour”

A led and buzzer will be turn on when the Distance exceeded 100 meters. 
![3](https://user-images.githubusercontent.com/68440283/124187327-f8a26b00-dabd-11eb-9739-85d5630c0f22.jpeg)
![5](https://user-images.githubusercontent.com/68440283/124187346-ffc97900-dabd-11eb-9ac9-e574382bb45c.jpeg)

System Flow Chart

![Untitled Diagram](https://user-images.githubusercontent.com/68440283/124187369-08ba4a80-dabe-11eb-8c64-4950c2ba50d8.png)

