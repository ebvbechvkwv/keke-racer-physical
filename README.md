# keke-racer-physical
Microcontroller code for irl aspect of my ongoing keke racing project.

----- Arduino finalised ------


This setup has been tested and works with 2 motors, 2 arduino unos, a TB6612FNG Motor Controller, a NRF24L01 transciever pair, and KY040 joystick component. The arduino with the joystick is the transmitter and the arduino with the motors is the receiver.  

Pinout Instructions

Transmitter Pinout (unchanged):

    Joystick:
        VRx to A0
        VRy to A1
        SW to pin 2

    NRF24L01:
        VCC to 3.3V
        GND to GND
        CE to pin 9
        CSN to pin 10
        MOSI to pin 11
        MISO to pin 12
        SCK to pin 13

Receiver Pinout (for two motors):

    NRF24L01:
        VCC to 3.3V
        GND to GND
        CE to pin 9
        CSN to pin 10
        MOSI to pin 11
        MISO to pin 12
        SCK to pin 13

    TB6612FNG Motor Controller:
        AIN1 to pin 3
        AIN2 to pin 4
        PWMA to pin 5 (PWM capable pin)
        BIN1 to pin 7
        BIN2 to pin 8
        PWMB to pin 6 (PWM capable pin)
        STBY to pin 2 (a unique pin for standby control)
        VCC to 5V
        GND to GND

        A01 and A02 to the first DC motor
        B01 and B02 to the second DC motor


        tb6612fng code thanks to Adam Meyer src: http://adam-meyer.com/arduino/TB6612FNG
