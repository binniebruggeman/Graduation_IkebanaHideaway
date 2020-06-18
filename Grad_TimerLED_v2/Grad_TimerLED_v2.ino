// These variables store the flash pattern
// and the current state of the LED

int ledPin =  12;      // the number of the LED pin
int ledState = HIGH;             // ledState used to set the LED
unsigned long previousMillis = 0;        // will store last time LED was updated
long pomodoroTime = 5000;           // 5 seconds pomodoro (5000 milliseconds)
long shortBreakTime = 1000;         // 1 second short break
long longBreakTime = 3000;          //2 seconds long break
int nrOfPomodoros = 0;          //number of pomodoros done
bool shortBreak = false;
bool longBreak = false;  //if nr of pomodoros done is 4, then timeForLongBreak is true
bool pomodoro = true;
//bool startPomodoro = true; //to turn on first pomodoro

void setup()
{
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();

  //SHORT BREAK
  if ((shortBreak ==  false) && (longBreak == false) && (currentMillis - previousMillis >= pomodoroTime) && (nrOfPomodoros < 4)) {
    //startPomodoro = false;
    shortBreak = true;
    pomodoro = false;
    ledState = LOW;
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
  }

  //LONG BREAK
  if ((shortBreak ==  false) && (currentMillis - previousMillis >= pomodoroTime) && (nrOfPomodoros == 4)) {
    longBreak = true;
    pomodoro = false;
    nrOfPomodoros = 0;
    ledState = LOW;
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
  }

  //POMODORO AFTER SHORT BREAK
  if ((shortBreak == true) && (currentMillis - previousMillis >= shortBreakTime)) {
    shortBreak = false;
    longBreak = false;
    pomodoro = true;
    nrOfPomodoros ++;
    ledState = HIGH;
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
  }

  //POMODORO AFTER LONG BREAK
  if ((longBreak == true) && (currentMillis - previousMillis >= longBreakTime)) {
    shortBreak = false;
    longBreak = false;
    pomodoro = true;
    nrOfPomodoros ++;
    ledState = HIGH;
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
  }


  //    if ((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
  //    {
  //      ledState = LOW;  // Turn it off
  //      previousMillis = currentMillis;  // Remember the time
  //      digitalWrite(ledPin, ledState);  // Update the actual LED
  //    }
  //    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
  //    {
  //      ledState = HIGH;  // turn it on
  //      previousMillis = currentMillis;   // Remember the time
  //      digitalWrite(ledPin, ledState);    // Update the actual LED
  //    }
}
