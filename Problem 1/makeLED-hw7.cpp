/*** Copy of makeLED.cpp

  ** Modified to include blink command that blinks USR3 LED n amount of times
*/


#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
using namespace std;

#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

void writeLED(string filename, string value){
   fstream fs;
   string path(LED3_PATH);
   fs.open((path + filename).c_str(), fstream::out);
   fs << value;
   fs.close();
}

void removeTrigger(){
  writeLED("/trigger", "none");
}

int main(int argc, char* argv[]){
   if(argc >3 || argc==1){
	cout << "Usage is makeLED and one of: " << endl;
        cout << "   on, off, flash or status" << endl;
	cout << " e.g. makeLED flash" << endl;
        return 2;
   }
   string cmd(argv[1]);
   cout << "Starting the makeLED program" << endl;
   cout << "The current LED Path is: " << LED3_PATH << endl;

   // select whether command is on, off, flash or status
   if(cmd=="on"){
        cout << "Turning the LED on" << endl;
	removeTrigger();
        writeLED("/brightness", "1");
   }
   else if (cmd=="off"){
        cout << "Turning the LED off" << endl;
	removeTrigger();
        writeLED("/brightness", "0");
   }
   else if (cmd=="flash"){
        cout << "Flashing the LED" << endl;
        writeLED("/trigger", "timer");
        writeLED("/delay_on", "50");
        writeLED("/delay_off", "50");
   }
   else if (cmd=="status"){
	// display the current trigger details
        std::fstream fs;
	fs.open( LED3_PATH "/trigger", std::fstream::in);
	string line;
	while(getline(fs,line)) cout << line << endl;
	fs.close();
   }
   else if (cmd=="blink"){
    if (argc < 3) {
    return 1;
    }
        int blinkCount = std::stoi(argv[2]);
        cout << "Blinking LED " << blinkCount << " times" << endl;
  removeTrigger();
    for (int i = 0; i < blinkCount; i++) {
        writeLED("/brightness", "1");
        sleep(1);
        writeLED("/brightness", "0");
        sleep(1);
        }
   }
   else{
	cout << "Invalid command!" << endl;
   }
   cout << "Finished the makeLED Program" << endl;
   return 0;
}
