#include <iostream>
#include <string.h>
#include "Leap.h"
#include <fstream>
#include <unistd.h>

using namespace Leap;
using namespace std;
typedef unsigned char BYTE;


bool modeWord = true;
string sentence;


void writeToFile(string sentence){
    ofstream fileOutput;
    fileOutput.open("texts.txt",ios_base::app);
    fileOutput<<endl;
    fileOutput<<sentence;
    fileOutput.close();
    sentence.erase();
    cout<<"We the north"<<endl;
    return;
}
bool containsType(int index, Leap::FingerList fingers){
		for (int i = 0; i < fingers.count(); i++){
				if (fingers[i].type() == index){
					return true;
				}
		}
		return false;
}
string alphabet(Frame frameUT){

	Leap::FingerList fingers = frameUT.hands()[0].fingers().extended();
		/**
		00000: SPACE
		00001: A
		00010: B
		00011: C
		00100: D
		00101: E
		00110: F
		00111: G
		01000: H
		01001: I
		01010: J
		01011: K
		01100: L
		01101: M
		01110: N
		01111: O
		10000: P
		10001: Q
		10010: R
		10011: S
		10100: T
		10101: U
		10110: V
		10111: W
		11000: X
		11001: Y
		11010: Z
		11011: Hack
		11100: The
		11101: North
		11110: Waterloo
		11111: Love you
		**/
		if (fingers.count() == 0){
			return " ";
		}
		unsigned int retAlphaCount = 0;

		if (containsType(4,fingers)){
			retAlphaCount |= 0b00001;
        }

		if (containsType(3,fingers)){
			retAlphaCount |= 0b00010;
		}

		if (containsType(2,fingers)){
			retAlphaCount |= 0b00100;

		}
		if (containsType(1,fingers)){
			retAlphaCount |= 0b01000;
    }

		if (containsType(0,fingers)){
			retAlphaCount |= 0b10000;
		}
        if (retAlphaCount == 0b11011){
            return (string)"Hack the North";
        }
        else if (retAlphaCount == 0b11100){
            return (string)"Waterloo";
        }
        else if (retAlphaCount == 0b11101){
            return (string)"Canada";
        }
        else if (retAlphaCount == 0b11111){
            return (string)"Azure's the best";
        }

        string temp = "";
        temp.push_back((char)('A'-1 + retAlphaCount));
        return temp;
}

int main(int argc, char** argv){
	modeWord = true;

  Controller controller;
	Frame frame = controller.frame();

  long recentFID = 0;
  int counter = 0;
  string parsed = "?"; //Choosing a non-supported string to start
  int interCount = 0;
	for(;;){
    //Validity check
    if (frame.isValid()==false){
      frame = controller.frame();
      continue;
    }
    //Avoid processing same frame twice (may occur due to slower env data input than CPU)
    if (frame.id() == recentFID){
      frame = controller.frame();
      continue;
    }
    else{
      recentFID = frame.id();
      frame = controller.frame();
    }

    //string alphabet (Frame) is main string/char recognition form
    string toBeParsed = alphabet(frame);
    if (toBeParsed.compare(parsed)==0) {
        counter++;
    }
    usleep(frame.currentFramesPerSecond()*1000);
    if (counter >= frame.currentFramesPerSecond() || toBeParsed.compare(parsed)!=0) {
        if (toBeParsed.compare(" ") != 0){
          sentence += toBeParsed;
          cout<<toBeParsed<<endl;
        }
        parsed = toBeParsed;

        if (toBeParsed[0] == ' '){
            if (interCount!=2){
              interCount++;
              continue;
            }
            interCount = 0;
            if (sentence.compare("") != 0){
              writeToFile(sentence);
            }
            sentence.clear();
            sentence = "";
            frame = controller.frame();
        }
        else{
          interCount = 0;
        }
        recentFID = frame.id(); //This will cause the next frame to be skipped
        counter = 0;
    }
	}


	std::cout<<"Press Enter to quit..."<< std::endl;
	std::cin.get();

	return 0;
}
