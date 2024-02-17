#include <Ps3Controller.h>
#include <servo.h>

void button_event(){
  //start button notification (turns traction control on)
    if( Ps3.event.button_down.start ){
        Serial.println("Started pressing the start button");
    }

    if( Ps3.event.button_down.select ){
        Serial.println("Started pressing the select button");
    }
  //joystick notification

    if(abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2){  //left joystick for water operations
      Serial.print("Moved Left Stick: ");
      Serial.print("Horizontal Position (x)= ");
      Serial.print(Ps3.data.analog.stick.lx, DEC);

      Serial.print(" Vertical Position (y)= ");
      Serial.print(Ps3.data.analog.stick.ly, DEC);
      Serial.println();
    }

    if(abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2){  //right joystick for land operations
      Serial.print("Moved Left Stick: ");
      Serial.print("Horizontal Position (x)= ");
      Serial.print(Ps3.data.analog.stick.rx, DEC);

      Serial.print(" Vertical Position (y)= ");
      Serial.print(Ps3.data.analog.stick.ry, DEC);
      Serial.println();
    }
  //left and right trigger notification
   if( abs(Ps3.event.analog_changed.button.l2) ){
       Serial.print("Pressing the left trigger button: ");
       Serial.println(Ps3.data.analog.button.l2, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.r2) ){
       Serial.print("Pressing the right trigger button: ");
       Serial.println(Ps3.data.analog.button.r2, DEC);
   } 

  //buttons to cut power to wheels
   if( abs(Ps3.event.analog_changed.button.triangle)){  //kill wheel 1
       Serial.print("Pressing the triangle button: ");
       Serial.println(Ps3.data.analog.button.triangle, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.circle) ){ //Kill wheel 2
       Serial.print("Pressing the circle button: ");
       Serial.println(Ps3.data.analog.button.circle, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.cross) ){  //Kill Wheel 3
       Serial.print("Pressing the cross button: ");
       Serial.println(Ps3.data.analog.button.cross, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.square) ){ //Kill Wheel 4
       Serial.print("Pressing the square button: ");
       Serial.println(Ps3.data.analog.button.square, DEC);
   }
}

void setup() {
  Serial.begin(115200);
  //esc_1.attach(9); // Attach the servo on pin 9

  // Begin PS3 controller setup
  Ps3.begin(""); // Make sure to use the correct MAC address or adjust based on library requirements
  if(Ps3.connected()){
    Serial.print("Controller Connected: ");
    String Address = Ps3.getAddress();
    Serial.println(Address);
  }
  else{
    Serial.println("Error: Controller Connection Failed");
  }

  Ps3.attach(button_event);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!ps3.connected()){
    return;
  }
}