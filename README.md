# Bottle-Cap-Plinko-Game

!This Readme is still work in progress. It still contains some flaws and is not finished. Use at your own risk.!

Project for an arduino based bottle cap Plinko Game with snack dispenser as reward.

Parts:
- Laser Module: 5V KY-008 650nm Laser Sensor Module  
  Example Link: https://www.amazon.de/-/en/gp/product/B07VSXW3TG  
- Laser Receiver Module: 5V Laser Recevier Sensor Module Relay Switch  
  Example Link: https://www.amazon.de/-/en/gp/product/B07SGHWF55   
- Logic Board: Arduino Nano  
- Stepper Motor Driver: DRV8825  
  Link to datasheet:https://www.ti.com/lit/ds/symlink/drv8825.pdf  
  Link to Driver Board example: https://www.pololu.com/product/2133  
- Stepper Motor usongshine 17HS4401S  
  Link to Datasheet : https://www.handsontec.com/dataspecs/17HS4401S.pdf  
- Voltage Supply AC-DC Module: Multi Voltage Switched Mode Power Supply Board PCB Module  
  Requirement: Must be able to perform a AC 230V to DC 9V conversion.  
  Example Link: https://www.amazon.de/gp/product/B002BX1D1Y  
- DC-DC Step Down Module - LM2596S DC-DC down converter 36 V, 24 V, 12 V to 5 V, 2 A, voltage stabiliser with digital voltmeter display  
  Requirement: Must be able to transform DC 9V to DC 5V  
  Example Link: https://www.amazon.de/gp/product/B081N6WWJS  
- Stepper Motor Bracket for Nema 17 Motors - Distance Plate for Mounting the Motor  
  Requirement: For mounting the Motor on the cereal dispenser  
  Example Link: https://www.amazon.de/gp/product/B086M3S1WS  
- Cereal Dispenser  
  Requirement: The dispenser must have a knob to turn in order to dispense the content. A push button will not work well.  
  Example Link: https://www.amazon.de/gp/product/B07ZQ9CSCB/  
- Wall Mounted Bottle Opener   
  Requirement: Must be mounted to a wall in order to single handedly open a bottle in it, so the bottle cap simply falls down.  
  Example Link: https://www.amazon.de/gp/product/B07D8P3KSF  
- Capacitor of at least 47uF  
- Misc: Wood, Nails, Screws Clear Glass/Plastic, Cables, Soldering  


Important Notes:
- In this project we do not use an out of the box mainboard for mounting the motor driver and providing the logic input. We build a custom board that connects the arduino nano with the motor driver and the laser modules. Thus you need to be aware of the specialties of the DRV8825. Most examples in the internet use the stepper driver A4988 (because it is a bit cheaper), which is a bit different from the DRV8825. When using pre-build mainboards (e.g. for 3D Printers), these mainboards have mountpoints which are compatible for DRV8825 and A4988, because the mainboards are specifically built that way. The examples in this built are using the DRV8825, and using a A4988 driver will not work out of the box. For using a A4988 driver you need to adjust the layout of the custom board in this projects a bit.
- We are using the DRV8825 because it is more robust than the A4988 and does not need an additional logic voltage supply, like the A4988.
- The specialties of the DRV8825, that we take care of, are:
  -  Shorting the SLEEP and RESET pin does not work (while it works with the A4988), but they need to be pulled HIGH by a logic pin or 3,3V supply. On most out-of-the-box mainboards these pins are not shorted but pulled HIGH programmatically, which makes them compatible to both drivers.
      - We connect the SLEEP Pin to a logic pin on the Arduino Nano in order to save power and not put too much stress on the driver and motor, as it does not need any hold power if it is not in use.
      - We connect the RESET Pin to 3,3 V supply to pull it permanently HIGH and prevent it from triggering the reset mode, which will prevent the driver from working.
  -  Instead of a logic voltage supply as INPUT (like the A4988) the DRV8825 has a FAULT pin as OUTPUT, which provides failure information. This can be left disconnected in our case. As it has a high internal resistor it does not break when it is connected to a 3V logic voltage supply (which makes it compatible to the mainboards also supporting A4988).
  -  The VMOTOR and GROUND Pins are connected to the 9V power supply and power supply ground. !Attention! Use a capacitor of at at least 47uF (better 100uF) between the 9V power supply and the driver in order to straighten the supply and protect from power spikes when starting the power supply. This is extremely important, as neither the DRV8825, nor the A4988 (or other drivers) have such a protection and are sensitive to this. Not using a capacitor puts your driver at high risk of being destroyed.
  -  The GROUND Pin next to the FAULT pin needs to be connected to the Arduino Ground pin, in order to make make the DRV4988 accept the logic / 3,3V supply from the Arduino Nano. Some DRV4988 Boards seem to be able to function without this ground pin connected, and use the VMOTOR GROUND pin, while some others need this pin connected. Better safe than sorry - it does not harm anyone to have this ground connected to the Arduino. 
- ATTENTION! Do not disconnect the Motor Cable while the Driver is supplied with power. Disconnecting the cable while the driver is still supplied with power can immediately destroy the driver. This is true for nearly all drivers, including the A4988
- READ THE DATA SHEET OF YOUR DRIVER CAREFULLY! (This is very true in all cases, but here it is extremely important. I cannot stress this enough!) 
- READ THE DATA SHEET OF YOUR STEPPER MOTOR CAREFULLY!! The 17HS4401S stepper motor has 6 pins, of which 4 are functional. In difference to many other motors the position of the middle pins is switched! This is usually compensated by the cables, shipped together with the motors, which have a crossover of the middle two wires, which makes it compatible to the pin order of most mainboards. If you are building your own board (like we do here), you must be aware of the order of pins of your driver as well as your stepper motor! If you are using different drivers / motors than the ones mentioned here, you need to take this into account and maybe change the pin and cable connections.  
- Not activating microstepping will make your motor "rattle" on slow speeds. As I wanted a smooth but slow dispensing cycle, I activated microstepping for having a smooth slow run. Keep in mind that microstepping comes to the cost of losing torque, which is mostly ok in this context.
- Have the plexiglass cover for the board of nails extend a bit (3 cm in my case) above the top line of nails. This prevents the bottle cap from hitting the first nail and bouncing off and out of your board. Even if the cap bounces, it is being directed by the glass cover downward again.
- I soldered two additional wires to two free digital arduino pins, which do not have a purpose yet. As I mounted my custom mainboard to the board, I wanted to have them soldered in now, in case I want to add additional function (maybe a speaker playing music for the winner, LED lights, etc.) later. 
- Think, and take care, of strain relief for your cabling leaving your case. This is especially the case for your main power supply and the motor cable. I used cable zip ties (two for the main power cable in a 90 degree angle, and one for the motor cable) in order to fixate it to the wood. This is important! There will be people pulling at these cables accidentally (stumbling, etc.). If you do not have a strain relief (which might be even better than my improvised one), a sudden pull at these cables might cause severe damage to your game electronics or is even a risk for hurting someone (in case a non secured main power supply cable gets ripped off.)
