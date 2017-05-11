#include <iostream>
#include <fstream>
using namespace std; 
#include <string>
#include <cstdlib> 
#include <cmath>
 
char *message, letter, ascii; 
int k, num_error, err_bitn, asciiNum, len, binary[8], tx_data[12], rx_data[12], total; 
void Hamming(const char*); 
 
int main() {
	//have the program read in the message from the transmitter.
	string text;

	ifstream file("transmitted_message.txt");
	if (file.is_open()){
		while (file.good()){
			getline(file, text);
			//Convert the message which is a string to a char. array
			char *message =  new char[text.size() + 1];
			message[text.size()] = 0;
			memcpy(message,text.c_str(),text.size());
			Hamming(message);
			cout << endl << "The message has been recieved." << endl;
		}
		file.close();
	}
	else
		cout << "Unable to open file";
	return 0;
}         

//This is the method to check for errors, correct errors, and
//convert a Byte to ASCII character, by HAMMING
void Hamming(const char* entry) { 
	//get length of string, (the length of the byte from the file)
	len = strlen(entry);
	//the array used to store the byte
	int binary[8];
	int bits[8];
	//the ascii number after conversion from binary
	asciiNum = 0;      
	
	int z = 0;

	//reading in bytes. total characters = length / 8
	for(int x = 0; x < len / 8; x++) {
		
		//store info into binary[0] through binary[7]
		for(int a = 0; a < 8; a++) {
			binary[a] = (int) entry[z] - 48;
			z++;
		}
		int r1,r2,r3,r4,r1o,r2o,r3o,r4o,r1n,r2n,r3n,r4n;
		r1=r2=r3=r4=r1o=r2o=r3o=r4o=r1n=r2n=r3n=r4n=0;
		
		//How to get the redundent bits loctation
		if(binary[0]==1){
			r1++;
			r2++;
		}
		if(binary[1]==1){
			r1++;
			r3++;
		}
		if(binary[2]==1){
			r2++;
			r3++;
		}
		if(binary[3]==1){
			r1++;
			r2++;
			r3++;
		}
		if(binary[4]==1){
			r1++;
			r4++;
		}
		if(binary[5]==1){
			r2++;
			r4++;
		}
		if(binary[6]==1){
			r1++;
			r2++;
			r4++;
		}
		if(binary[7]==1){
			r3++;
			r4++;
		}

		//The value of the redundent bits
		r1o=r1%2; 
		r2o=r2%2;
		r3o=r3%2;
		r4o=r4%2;

		//The redundent bits added to the Byte
		//making the 8 bit Byte a now 12 bit Byte
		tx_data[11]=binary[7];
		tx_data[10]=binary[6];
		tx_data[9]=binary[5];
		tx_data[8]=binary[4];
		tx_data[7]=r4o;
		tx_data[6]=binary[3];
		tx_data[5]=binary[2];
		tx_data[4]=binary[1];
		tx_data[3]=r3o;
		tx_data[2]=binary[0];
		tx_data[1]=r2o;
		tx_data[0]=r1o;
		cout<<endl;

		cout << "The transmitted Data is: ";
		//Displays the transmitted Data
		for (k=0; k<12; k++){
			cout << tx_data[k];
		}
		
		int err_bit=((8*r4o)+(4*r3o)+(2*r2o)+(1*r1o));
		for(k=0;k<12;k++)
			rx_data[k]=tx_data[k];
		if(rx_data[err_bit]==1)
			rx_data[err_bit]=0;
		else
			rx_data[err_bit]=1;
		//Displays the error byte and it's bits
		cout << "\n \n The Received DATA WITH ERROR is: ";
		for(k=0; k<11; k++){
			cout << rx_data[k];
		}

		//Setup to solve for the error
		if(rx_data[1]==1){
			r1++;
		}
		if(rx_data[2]==1){
			r2++;
		}
		if(rx_data[3]==1){
			r1++;
			r2++;
		}
		if(rx_data[4]==1){
			r3++;
		}
		if(rx_data[5]==1){
			r1++;
			r3++;
		}
		if(rx_data[6]==1){
			r2++;
			r3++;
		}
		if(rx_data[7]==1){
			r1++;
			r2++;
			r3++;
		}
		if(rx_data[8]==1){
			r4++;
		}
		if(rx_data[9]==1){
			r1++;
			r4++;
		}
		if(rx_data[10]==1){
			r2++;
			r4++;
		}
		if(rx_data[11]==1){
			r1++;
			r2++;
			r4++;
		}
		r1n=r1%2;
		r2n=r2%2;
		r3n=r3%2;
		r4n=r4%2;
		r1=r2=r3=r4=0;

		//How to check to see if there is an error and it's location
		if(r1o==r1n){
			if(r2o==r2n){
				if(r3o==r3n){
					if(r4o==r4n)
						cout << "\n \n No Error" << endl;
					else
						err_bitn=1;
						cout << "\n \n Error in bit 0" << endl;
				}
				else{
					if(r4o==r4n)
						cout << "\n \n Error in bit 1" << endl;
					else{
						err_bitn=2;
						cout << "\n \n Error in bit 2" << endl;
					}
				}
			}
			else{
				if(r3o==r3n){
					if(r4o==r4n){
						err_bitn=3;
						cout << "\n \n Error in bit 3" << endl;
					}
					else{
						err_bitn=4;
						cout << "\n \n Error in bit 4" << endl;
					}
				}
				else{
					if(r4o==r4n){
						err_bitn=5;
						cout << "\n \n Error in bit 5" << endl;
					}
					else{
						err_bitn=6;
						cout << "\n \n Error in bit 6" << endl;
					}
				}
			}
		}
		else{
			if(r2o==r2n){
				if(r3o==r3n){
					if(r4o==r4n){
						err_bitn=7;
						cout << "\n \n Error in bit 7" << endl;
					}
					else{
						err_bitn=8;
						cout << "\n \n Error in bit 8" << endl;
					}
				}
				else{
					if(r4o==r4n){
						err_bitn=9;
						cout << "\n \n Error in bit 9" << endl;
					}
					else{
						err_bitn=10;
						cout << "\n \n Error in bit 10" << endl;
					}
				}
			}
			else{
				if(r3o==r3n){
					if(r4o==r4n){
						err_bitn=12;
						cout << "\n \n Error in bit 12" << endl;
					}
					else{
						err_bitn=13;
						cout << "\n \n Not possible" << endl;
					}
				}
				else{
					if(r4o==r4n){
						err_bitn=3;
						cout << "\n \n Not possible" << endl;
					}
					else{
						err_bitn=10;
						cout << "\n \n Not possible" << endl;
					}
				}
			}
		}

		//Corrects the error bits 
		if(rx_data[err_bitn]==1)
			rx_data[err_bitn]=0;
		else
			rx_data[err_bitn]=1;

		//Reforms the 12 bit back to a 8 bit
		bits[7]=rx_data[11];
		bits[6]=rx_data[10];
		bits[5]=rx_data[9];
		bits[4]=rx_data[8];
		bits[3]=rx_data[6];
		bits[2]=rx_data[5];
		bits[1]=rx_data[4];
		bits[0]=rx_data[2];

		cout << endl << "The Error was corrected.";
		cout << endl << "The Byte message sent is: ";
		for(k=0;k<8;k++)
			cout << bits[k];
		cout << endl << "The char of the byte is: ";

		//set powers of 2 in an array
		int power[8]; 
		//power starts at 2^0, ends at 2^7
		int counter = 7;        
		for(int x = 0; x < 8; x++) {
			power[x] = counter;
			counter--;
		}
		//Method to compute asciiNum
		for(int y = 0; y < 8; y++) {
			double a = bits[y];
			double b = power[y];
			//asciiNum = sum of a * 2^power where 0 <= power <= 7, power is int
			asciiNum += a* pow (2, b);   
		}

		//assign the asciiNum value to ascii, to change it into an actual character
		ascii = asciiNum;
	
		//reset asciiNum for next loop
		asciiNum = 0;
	
		//display the ascii character
		cout << ascii;
	}
}
