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
    sentence = "\0" ;
    usleep(5000000);
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
            return (string)"Hack";
        }
        else if (retAlphaCount == 0b11100){
            return (string)"The";
        }
        else if (retAlphaCount == 0b11101){
            return (string)"North";
        }
        else if (retAlphaCount == 0b11111){
            return (string)"Love you";
        }

        string temp = "";
        temp.push_back((char)('A'-1 + retAlphaCount));
        return temp;
}

int main(int argc, char** argv){
  cout<<"Beginning: "<<endl;
	modeWord = true;
	Controller controller;
	Frame frame = controller.frame();
  int counter = 0;
  string prevLetter = "?";
  int skipCounter = 0;
  int totalSkipCounter = 0;


	for(;;){
    totalSkipCounter++;

    if (totalSkipCounter%3 != 0){
      continue;
    }


    if (skipCounter >0){
      skipCounter--;
      continue;
    }

    frame = controller.frame();

    if (frame.isValid()==false){
      continue;
    }

    string letter = alphabet(frame);
        if (letter.compare(prevLetter)==0) {
            counter++;
        }
        if (counter >= 240000 || letter.compare(prevLetter)!=0) {
            sentence += alphabet(frame);
            cout<<prevLetter<<endl;
            if (prevLetter[0] == ' '){
                writeToFile(sentence);
                controller.frame();
                skipCounter=10000;
            }
            counter = 0;
            prevLetter = letter;
        }
	}


	std::cout<<"Press Enter to quit..."<< std::endl;
	std::cin.get();

	return 0;
}
