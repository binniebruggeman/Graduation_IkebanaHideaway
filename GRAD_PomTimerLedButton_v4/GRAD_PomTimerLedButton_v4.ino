//LED attached with cathode (short leg) to GND with 220 Ohm resistor, anode (long leg) to Arduino pin 12

// constants won't change.
const int ledPin =  12;      // the number of the LED pin
int ledState = LOW;             // ledState used to set the LED

// constants won't change.
const int buttonPin = 2;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status


unsigned long previousMillis = 0;        // will store last time LED was updated
long pomodoroTime = 1000;           // 5 seconds pomodoro (5000 milliseconds)
long shortBreakTime = 500;         // 1 second short break
long longBreakTime = 3000;          //2 seconds long break

int nrOfPomodoros = 0;          //number of pomodoros done

bool shortBreak = false;
bool longBreak = false;  //if nr of pomodoros done is 4, then timeForLongBreak is true

bool startPomodoro = false; // to start the 1st pomodoro
bool resetPomodoro = false; // to reset the nr of pomodoros, back to the 1st pomodoro


void setup()
{
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop()
{
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();

  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  digitalWrite(ledPin, ledState);  // Update the actual LED

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == 1) {
    startPomodoro = true;
    nrOfPomodoros = 0;
    previousMillis = currentMillis;  // Remember the time
  }

  //FIRST POMODORO
  if ((startPomodoro == true) && (shortBreak ==  false) && (longBreak == false) && (currentMillis - previousMillis <= pomodoroTime) && (nrOfPomodoros == 0)) {
    ledState = HIGH;
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
    nrOfPomodoros ++;
    startPomodoro = false;
  }


  //SHORT BREAK
  if ((shortBreak ==  false) && (longBreak == false) && (currentMillis - previousMillis >= pomodoroTime) && (nrOfPomodoros >= 1) && (nrOfPomodoros < 4)) {
    //startPomodoro = false;
    shortBreak = true;
    ledState = LOW;
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
  }

  //LONG BREAK
  if ((shortBreak ==  false) && (currentMillis - previousMillis >= pomodoroTime) && (nrOfPomodoros == 4)) {
    longBreak = true;
    nrOfPomodoros = 0;
    ledState = LOW;
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
  }

  //POMODORO AFTER SHORT BREAK
  if ((shortBreak == true) && (currentMillis - previousMillis >= shortBreakTime)) {
    shortBreak = false;
    longBreak = false;
    nrOfPomodoros ++;
    ledState = HIGH;
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
  }

  //POMODORO AFTER LONG BREAK
  if ((longBreak == true) && (currentMillis - previousMillis >= longBreakTime)) {
    shortBreak = false;
    longBreak = false;
    nrOfPomodoros ++;
    ledState = HIGH;
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
  }



}
