#include"stdafx.h"
#include<iostream>
#include<string>
#include<stdlib.h>
#include"SerialPort.h"

char output[MAX_DATA_LENGTH];
char port[] = "COM9";


int main() {
	//
	SerialPort arduino(port);

	if (arduino.isConnected()) {
		std::cout << "Deu bom, conectado!" << std::endl;
	}
	else {
		std::cout << "Erro no nome de entrada" << std::endl;
	}

	while(arduino.isConnected()) {


		std::string command;
		std::cin >> command;
		char *charArray = new char[command.size() + 1];
		copy(command.begin(), command.end(), charArray);
		charArray[command.size()] = '\n';

		arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
		arduino.readSerialPort(output, MAX_DATA_LENGTH);

		std::cout << output;

		delete[] charArray;
	
	}

	std::cout << "Arduino desconectado. Vlw, Flws" << std::endl;

	return 0;
}



