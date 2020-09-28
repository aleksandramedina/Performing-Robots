## Monday, September 28

- Haven't received my kit either. Still waiting for info to send over to the customs office. I'm missing two things:
    - full description of what's inside the kit
    - the receipt of purchase
- How can I do next week's assignment? Can I turn it in late?
    - Idea: make an ice cream car robot
- Example code from class:

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1


void loop()
{

  // stop both motors for 5 seconds
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0); //stop motor
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0); //stop motor
  delay(5000);

  //go forward for 10 seconds

  myMotorDriver.setDrive( LEFT_MOTOR, 0, 200);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 200);
  delay(10000);

  // turn right just a little

  myMotorDriver.setDrive( LEFT_MOTOR, 0, 50);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 25);
  delay(500);

  while (1)
    ;
}

