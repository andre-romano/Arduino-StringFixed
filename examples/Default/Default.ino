#include "Arduino.h" 
#include <StringFixed.h>  // StringFixed Library

StringFixed<150> s;

void setup() {      
    int idx;

    Serial.begin(9600);            // INITIALIZE SERIAL PC COMMUNICATION        
    
    s += "concatenating using += ...";        
    Serial.println(s.c_str());    
    Serial.println();
    
    StringFixed<30> d = " now using << ...";
    StringFixed<40> x = " - another use of << ";
    s << d << x;
    Serial.println(s.c_str());          
    Serial.println();
    
    idx = s.indexOf("<<");
    Serial.print("The first << symbol is in index position ");    
    Serial.println(idx);  
    Serial.println();
    
    Serial.println("Removing << symbol ... We now have:");
    s.remove(idx, 2);    
    Serial.println(s.c_str());
    Serial.println();    
    
    Serial.println("Comparing s with d: ");     
    Serial.print("Less than - ");
    Serial.println(s < d);
    Serial.print("Equal to - ");
    Serial.println(s == d);
    Serial.print("Greater than - ");
    Serial.println(s > d);
    Serial.println();

    Serial.println("First simbol in s :");
    Serial.println(s[0]);
    Serial.println("Changing to H :");
    s[0] = 'H';
    Serial.println(s[0]);    
    Serial.println();    

    Serial.println("Copying from s into d, characters 0 - 13 (13 chars in total) ...");
    d = "";
    d.copy(s, 0, 13);    
    Serial.println(d.c_str());    
    Serial.println();    

    Serial.println("Substring of x from chars 3 to 9 using d as destination...");
    d = "";
    x.substring(d, 3, 10);
    Serial.println(d.c_str());    
    Serial.println();    
}

void loop() {      
    
}
        