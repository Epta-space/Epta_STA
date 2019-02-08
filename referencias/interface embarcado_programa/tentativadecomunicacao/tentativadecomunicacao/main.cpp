#include"stdafx.h"
#include<iostream>
#include<string>
#include<stdlib.h>
#include"SerialPort.h"

char output[MAX_DATA_LENGTH];
char port[] = "\\\\.\\COM10";


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

		arduino.readSerialPort(output, MAX_DATA_LENGTH);

		std::cout << output << std::endl;
	
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


