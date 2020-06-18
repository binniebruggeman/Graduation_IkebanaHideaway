//LED attached with cathode (short leg) to GND with 220 Ohm resistor, anode (long leg) to Arduino pin 12

// constants won't change.
const int ledPin =  12;      // the number of the LED pin
int ledState = LOW;             // ledState used to set the LED

// constants won't change.
const int buttonPin = 2;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status
bool startPomodoro = false; // to start the 1st pomodoro
bool resetPomodoro = false; // to reset the nr of pomodoros, back to the 1st pomodoro

unsigned long previousMillis = 0;        // will store last time LED was updated
long pomodoroTime = 1000;           // 5 seconds pomodoro (5000 milliseconds)
long shortBreakTime = 500;         // 1 second short break
long longBreakTime = 3000;          //2 seconds long break

int nrOfPomodoros = 0;          //number of pomodoros done

bool shortBreak = false;
bool longBreak = false;  //if nr of pomodoros done is 4, then timeForLongBreak is true
bool pomodoro = true;


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
    resetPomodoro = true;
    startPomodoro = true;
  }
  
  if (resetPomodoro == true) {
    nrOfPomodoros = 0;
    resetPomodoro = false;
  }

if (startPomodoro == true) {
    ledState = HIGH;
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
    
    }


  //SHORT BREAK
  if ((startPomodoro == true) && (shortBreak ==  false) && (longBreak == false) && (currentMillis - previousMillis >= pomodoroTime) && (nrOfPomodoros < 4)) {
    //startPomodoro = false;
    shortBreak = true;
    pomodoro = false;
    ledState = LOW;
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
  }

  //LONG BREAK
  if ((startPomodoro == true) && (shortBreak ==  false) && (currentMillis - previousMillis >= pomodoroTime) && (nrOfPomodoros == 4)) {
    longBreak = true;
    pomodoro = false;
    nrOfPomodoros = 0;
    ledState = LOW;
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
  }

  //POMODORO AFTER SHORT BREAK
  if ((startPomodoro == true) && (shortBreak == true) && (currentMillis - previousMillis >= shortBreakTime)) {
    shortBreak = false;
    longBreak = false;
    pomodoro = true;
    nrOfPomodoros ++;
    ledState = HIGH;
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
  }

  //POMODORO AFTER LONG BREAK
  if ((startPomodoro == true) && (longBreak == true) && (currentMillis - previousMillis >= longBreakTime)) {
    shortBreak = false;
    longBreak = false;
    pomodoro = true;
    nrOfPomodoros ++;
    ledState = HIGH;
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
  }



}
