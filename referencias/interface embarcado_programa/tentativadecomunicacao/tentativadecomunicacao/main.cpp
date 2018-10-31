#include"stdafx.h"
#include<iostream>
using namespace std;
#include<string>
#include<stdlib.h>
#include"SerialPort.h"

char output[MAX_DATA_LENGTH];
char port[] = "COM7";


int main() {
	//
	SerialPort arduino(port);

	if (arduino.isConnected()) {
		std::cout << "Deu bom, conectado!";
	}
	else {
		std::cout << "Erro no nome de entrada";
	}

	while(arduino.isConnected()) {
		std::string command;
		cin >> command;
		char *charArray = new char[command.size() + 1];
		copy(command.begin(), command.end(), charArray);
		charArray[command.size()] = '\n';

		arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
		arduino.readSerialPort(output, MAX_DATA_LENGTH);

		cout << output;

		delete[] charArray;
	}
	return 0;
}



