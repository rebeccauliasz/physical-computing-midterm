// This #include statement was automatically added by the Particle IDE.
#include <SparkFunMicroOLED.h>

//MicroOLED Definitions
#define PIN_OLED_RST D6
#define PIN_OLED_DC D5
#define PIN_OLED_CS A2
MicroOLED oled(MODE_SPI, PIN_OLED_RST, PIN_OLED_DC, PIN_OLED_CS);

int buttonPin = D2; 


void setup() {
    
    pinMode(buttonPin, INPUT); 
    
    Serial.begin(9600); // optional for troubleshooting, starts serial communication
    
    // subscribe to any event that begins with '@' 
    //(default IFTTT trigger for Twitter search prepends @ in the event name )
    // MY_DEVICES used to filter for only my account so I don't get everyone's Twitter events
    Particle.subscribe("@", print2lcd);
    
    oled.begin();    // Initialize the OLED
    oled.clear(ALL); // Clear the display's internal memory
    oled.display();  // Display what's in the buffer (splashscreen)
    oled.setFontType(0); 
    delay(1000); 
    
    Particle.subscribe("greatParent", greaterParent);
    
    


}


void loop() {

 
  int buttonState = digitalRead(buttonPin); 
  if (buttonState == HIGH) {
        Particle.publish("buttonPressed"); 
        delay(5000); }
        
    if (buttonState == HIGH) {
        oled.clear(ALL);
        oled.clear(PAGE); 
        oled.setCursor(0, 0); 
        oled.println("YOU ARE INSECURE!"); 
        oled.display();
        delay(200); 

    }
    if (buttonState == LOW){
        oled.clear(ALL); 
        oled.clear(PAGE);
        oled.setCursor(0, 0); 
        oled.println("waiting for affirmation.................."); 
        oled.display(); 
        delay(2000); 
    }
}

int i = 0; // message counter


void print2lcd(const char *event, const char *data) {
    
  i++;  // increment counter upon msg received
  Serial.print(i);      // optional for troubleshooting, prints counter to serial
  Serial.println(event);  // optional for troubleshooting, prints Particle event name to serial
  
  if (data){
    Serial.print(", data: "); // optional for troubleshooting
    Serial.println(data); // optional for troubleshooting, prints Particle event data to serial
    
    String data_as_string(data);  // ***** this is important, convert char * to string for OLED printing
//    myList.push_front(data_as_string); 
    
    oled.clear(PAGE);
    oled.setCursor(0, 0);
    
     int buttonState = digitalRead(buttonPin); 
 
if (buttonState == LOW){   
    oled.println(data_as_string);  // print the Particle event data

    oled.display(); // Draw to the screen
    delay(500); 
}
    

  }
  else
    Serial.println("NULL - No message data");
}

// subscribe to the baby monitor 
void greaterParent (const char *event, const char *data)
{
    
  Serial.print(event);
  Serial.print(", data: ");
  if (data)
    Serial.println(data);
  else
    Serial.println("NULL");
    
    String data_as_string(data);  // ***** this is important, convert char * to string for OLED printing
//    myList.push_front(data_as_string); 
    
    oled.clear(PAGE);
    oled.setCursor(0, 0);
    
    oled.println(data_as_string);  // print the Particle event data
//   oled.println(myList.at(1)); 
    oled.display(); // Draw to the screen
    delay(500);
    
    
}


// function for multiline printing
void multiLinePrint(String s)  
{
    
    // can be further developed to put short words on same line if they fit
    // and otherwise make Tweet stream more readable
    
    String split = s; // We'll continut to split the split String until it's just one word

    // Loop until the our split String is small enough to fit on a single line.
    // Divide the LCD's pixel width (64) by the width of a character+1 to get
    // characters per line.
    while (split.length() >= (oled.getLCDWidth() / (oled.getFontWidth() + 1)))
    {
        // Use the indexOf String function to find a space (' ').
        int space = split.indexOf(' ');
        if (space > 0) // If there is a space, indexOf will return it's position.
        {
            // print from the beginning of our split string to the character
            // before the space.
            oled.println(split.substring(0, space));
        }
        else // Otherwise, if there is no space, it'll return a negative number
        {    // If there are no spaces left
            break;  // break out of the while loop
        }
        // Shorten up the split string, get rid of everything we've printed,
        // plus the space. Then loop back through.
        split = split.substring(space + 1);
    }
    // Print the last bit of the split string.
    oled.println(split);
    oled.println();
}
