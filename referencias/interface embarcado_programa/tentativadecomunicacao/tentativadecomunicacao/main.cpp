#include"stdafx.h"
#include<iostream>
#include<string>
#include<stdlib.h>
#include"SerialPort.h"

char output[MAX_DATA_LENGTH];
char port[] = "COM9";


char *removeSpaces(char *str);


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

		std::string command = "O";
		char *charArray = new char[command.size() + 1];
		copy(command.begin(), command.end(), charArray);
		charArray[command.size()] = '\n';

		arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
		arduino.readSerialPort(output, MAX_DATA_LENGTH);

		float result = std::stof(output);

		std::cout << result << std::endl;

		delete[] charArray;
	
	}

	std::cout << "Arduino desconectado. Vlw, Flws" << std::endl;

	return 0;
}




char *removeSpaces(char *str)
{
	int i = 0, j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return str;
}


