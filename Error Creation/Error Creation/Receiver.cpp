#include <iostream>
#include <fstream>
using namespace std; 
#include <string>
#include <cstdlib> 
#include <cmath>
#include <time.h>

string text, error;
char *message, *choice, letter, ascii; 
int err_bit, num_error, err_bitn;
int a, k, len, total, asciiNum;
int binary[8], txH_data[12], rxH_data[12], txC_data[16], rxC_data[16];
void Hamming(const char*);
void CRC(const char*);
void HBD3(const char*);

 
int main() {
	//set the program to put in the binary value
	string text;
	choice = new char[2]; 

	ifstream file("transmitted_message.txt");
	if (file.is_open()){
		while (file.good()){
			getline(file, text);
			cout<<"Here is the message in HDB3 coding: " << endl;
			char *message =  new char[text.size() + 1];
			message[text.size()] = 0;
			memcpy(message,text.c_str(),text.size());
			HBD3(message);
			cout<<endl<<"Which error correction do you wish to use CRC or Hamming?";
			cout<<endl<<"(Enter 1 for Hamming, 2 for CRC): "; 
			cin.getline(choice,3);
			if(choice[0] == '1'){
				char *message =  new char[text.size() + 1];
				message[text.size()] = 0;
				memcpy(message,text.c_str(),text.size());
				Hamming(message);
				cout << endl;
			}
			else if(choice[0] == '2'){
				char *message =  new char[text.size() + 1];
				message[text.size()] = 0;
				memcpy(message,text.c_str(),text.size());
				CRC(message);
				cout << endl;
			}
			else 
				exit(0);
		}
		file.close();
	}
	else
		cout << "Unable to open file";
	return 0; 
}


void HBD3(const char* entry) {
	len = strlen(entry);
	int code[100];
	int ami[100];
	int count=0;
	int z=0;
	int x=0;
	//Convert the chars to an int array.
	for(int x = 0; x < len ; x++) {
			code[x] = (int) entry[z] - 48;
			z++;
	}
	int i=0;
	//If the code has '0000' convert the 4th char to 'V' making it '000V'
	for(int x = 0; x < len ; x++) {
		if(code[x]==0){
			if(code[x+1]==0){
				if(code[x+2]==0){
					if(code[x+3]==0){
						code[x+3]='V';
					}
				}
			}
		}
	}

	//Method to check if the '0000' should be '000V' or 'B00V'
	for(int x = 0; x < len ; x++){
		if(code[x]=='V'){
			int n = x;
			for(int a = n+1; a < len; a++) {
				if(code[a]==1){
					count++;
				}
				else if(code[a]==0){
					if(code[a+1]==0){
						if(code[a+2]==0){
							if(code[a+3]=='V'){
								if(count %2 == 0){
									code[a] = 'B';
									code[a+3] = 'V';
									count = 0;
								}
								else{
									code[a+3] = 'V';
									count = 0;
								}
							}
							else if (code[a+3]==0){
								if(count %2 == 0){
									code[a] = 'B';
									code[a+3] = 'V';
									count = 0;
								}
								else{
									code[a+3] = 'V';
									count = 0;
								}
							}
						}
					}
				}
			}
		}
	}
	//Make every binary 1 to '+' and '-'
	for(int x = 0; x < len; x++){  
		if (code[x] == 1){
			if (i%2 == 0){
				code[x] = '+';
				i++;
			}
			else{
				code[x] = '-';
				i++;
			}
		}
		ami[x]=code[x];
	}

	//Placing the +'s and -'s in the correct order
	for(int x = 0; x < len; x++){  
		//This is the code for +
		if (code[x] == '+'){
			if (code[x+1] == 'B'){
				if (code[x+2] == 0){
					if (code[x+3] == 0){
						if (code[x+4] == 'V'){
							if (code[x+5] == '-'){
								code[x+5]='+';
								int n = x+6;
								for (int x = n; x < len; x++){
									if (code[x] == '+')
										code[x]= '-';
									else if (code[x] == '-')
										code[x]='+';
								}
							}
						}
					}
				}
			}
		}
		//This is the code for the -
		else if(code[x] == '-'){
			if (code[x+1] == 'B'){
				if (code[x+2] == 0){
					if (code[x+3] == 0){
						if (code[x+4] == 'V'){
							if (code[x+5] == '+'){
								code[x+5]='-';
								int n = x+6;
								for (int x = n; x < len; x++){
									if (code[x] == '+')
										code[x]= '-';
									else if (code[x] == '-')
										code[x]='+';
								}
							}
						}
					}
				}
			}
		}
	}
	//Print out the results
	for(int x = 0; x < len; x++){
		if (code[x] == 0)
			cout << "0";
		if (code[x] == 43)
			cout << "+";
		if (code[x] == 45)
			cout << "-";
		if (code[x] == 66)
			cout << "B";
		if (code[x] == 86)
			cout << "V";
	}

	cout << endl;
	//Make every 000V and B00V to correct Code by the polarity of the last Pulse
	for(int x = 0; x < len ; x++){
		int stop = 0;
		// if the last Pulse is + then 000V will be 000+
		if(code[x]=='+'){
			int n = x;
			for(int a = n+1; a < len; a++) {
				while(stop!=1){
					if(code[a]==0){
						if(code[a+1]==0){
							if(code[a+2]==0){
								if(code[a+3]=='V'){
									code[a+3] = '+';
								}
								else
									stop=1;
							}
							else
								stop=1;
						}
						else
							stop=1;
					}
					// if the last Pulse is + then B00V will be -00-
					else if(code[a]=='B'){
						if(code[a+1]==0){
							if(code[a+2]==0){
								if(code[a+3]=='V'){
									code[a] = '-';
									code[a+3] = '-';
								}
								else
									stop=1;
							}
							else
								stop=1;
						}
						else
							stop=1;
					}
					else
						stop=1;
				}
			}
		}
		// if the last Pulse is - then 000V will be 000-
		else if(code[x]=='-'){
			int n = x;
			for(int a = n+1; a < len; a++) {
				while(stop!=1){
					if(code[a]==0){
						if(code[a+1]==0){
							if(code[a+2]==0){
								if(code[a+3]=='V'){
									code[a+3] = '-';
								}
								else
									stop=1;
							}
							else
								stop=1;
						}
						else
							stop=1;
					}
					// if the last Pulse is - then B00V will be +00+
					else if(code[a]=='B'){
						if(code[a+1]==0){
							if(code[a+2]==0){
								if(code[a+3]=='V'){
									code[a] = '+';
									code[a+3] = '+';
								}
								else
									stop=1;
							}
							else
								stop=1;
						}
						else
							stop=1;
					}
					else
						stop=1;
				}
			}
		}
	}
	//Print the result to show the finalization of the HDB3 code
	for(int x = 0; x < len; x++){
		if (code[x] == 0)
			cout << "0";
		if (code[x] == 43)
			cout << "+";
		if (code[x] == 45)
			cout << "-";
	}
	// Convert the HDB3 code to AMI code to show the correction of the code
	cout << endl << "The corresponding encoding using AMI is: ";
	for(int x = 0; x < len; x++){
		if (ami[x] == 0)
			cout << "0";
		if (ami[x] == 43)
			cout << "+";
		if (ami[x] == 45)
			cout << "-";
		if (ami[x] == 66)
			cout << "0";
		if (ami[x] == 86)
			cout << "0";
	}
	cout << endl;
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
		txH_data[11]=binary[7];
		txH_data[10]=binary[6];
		txH_data[9]=binary[5];
		txH_data[8]=binary[4];
		txH_data[7]=r4o;
		txH_data[6]=binary[3];
		txH_data[5]=binary[2];
		txH_data[4]=binary[1];
		txH_data[3]=r3o;
		txH_data[2]=binary[0];
		txH_data[1]=r2o;
		txH_data[0]=r1o;
		cout<<endl;

		cout << endl << "The transmitted Data is: ";
		//Displays the transmitted Data
		for (k=0; k<12; k++){
			cout << txH_data[k];
		}
		
		//Creates the random errors
		cout << endl << "Enter the number of errors for this byte: ";
		cin >> num_error;
		int m=0;
		for (k=0; k<num_error; k++){
			srand ( time(NULL) );
			err_bit = rand() % 12;
			do{
				m++;
				//now have the program pick a random location in the Byte
				srand ( time(NULL) );
				for(k=0;k<12;k++)
					rxH_data[k]=txH_data[k];
				if(rxH_data[err_bit]==1)
					rxH_data[err_bit]=0;
				else
					rxH_data[err_bit]=1;
				//Displays the error byte and it's bits
				cout << "\n \n The Received DATA WITH ERROR is: ";
				for(k=0; k<12; k++){
					cout << rxH_data[k];
				}

				//Setup to solve for the error
				if(rxH_data[1]==1){
					r1++;
				}
				if(rxH_data[2]==1){
					r2++;
				}
				if(rxH_data[3]==1){
					r1++;
					r2++;
				}
				if(rxH_data[4]==1){
					r3++;
				}
				if(rxH_data[5]==1){
					r1++;
					r3++;
				}
				if(rxH_data[6]==1){
					r2++;
					r3++;
				}
				if(rxH_data[7]==1){
					r1++;
					r2++;
					r3++;
				}
				if(rxH_data[8]==1){
					r4++;
				}
				if(rxH_data[9]==1){
					r1++;
					r4++;
				}
				if(rxH_data[10]==1){
					r2++;
					r4++;
				}
				if(rxH_data[11]==1){
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
							if(r4o==r4n){
								cout << "\n \n Error in bit " << (12 - err_bit) << endl;
							}
							else{
								cout << "\n \n Error in bit " << (12 - err_bit) << endl;
							}
						}
						else{
							if(r4o==r4n){
								cout << "\n \n Error in bit " << (12 - err_bit) << endl;
							}
							else{
								cout << "\n \n Error in bit " << (12 - err_bit) << endl;
							}
						}
					}
					else{
						if(r3o==r3n){
							if(r4o==r4n){
								cout << "\n \n Error in bit " << (12 - err_bit) << endl;
							}
							else{
								cout << "\n \n Error in bit " << (12 - err_bit) << endl;
							}
						}
						else{
							if(r4o==r4n){
								cout << "\n \n Error in bit " << (12 - err_bit) << endl;
							}
							else{
								cout << "\n \n Error in bit " << (12 - err_bit) << endl;
							}
						}
					}
				}
				else{
					if(r2o==r2n){
						if(r3o==r3n){
							if(r4o==r4n){
								cout << "\n \n Error in bit " << (12 - err_bit) << endl;
							}
							else{
								cout << "\n \n Error in bit " << (12 - err_bit) << endl;
							}
						}
						else{
							if(r4o==r4n){
								cout << "\n \n Error in bit " << (12 - err_bit) << endl;
							}
							else{
								cout << "\n \n Error in bit " << (12 - err_bit) << endl;
							}
						}
					}
					else{
						if(r3o==r3n){
							if(r4o==r4n){
								cout << "\n \n Error in bit " << (12 - err_bit) << endl;
							}
							else{
								cout << "\n \n Error in bit " << (12 - err_bit) << endl;
							}
						}
						else{
							if(r4o==r4n){
								cout << "\n \n Error in bit " << (12 - err_bit) << endl;
							}
							else{
								cout << "\n \n Error in bit " << (12 - err_bit) << endl;;
							}
						}
					}
				}
			}
			while(m<num_error);
		}
		//Reforms the 12-bit byte back to a 8-bit byte
		bits[7]=txH_data[11];
		bits[6]=txH_data[10];
		bits[5]=txH_data[9];
		bits[4]=txH_data[8];
		bits[3]=txH_data[6];
		bits[2]=txH_data[5];
		bits[1]=txH_data[4];
		bits[0]=txH_data[2];

		cout << endl << "The Error was corrected.";
		cout << endl << "The Byte message sent is: ";
		for(k=0;k<8;k++)
			cout << bits[k];
		cout << endl << "The ASCII of the byte is: ";

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
		cout << endl;
	}
}

//This is the method to check for errors, correct errors,
//and convert a Byte to ASCII character by CRC-ANSI
void CRC(const char* entry) { 
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

		//Turn the 8 bit Byte into a 16 bit Byte
		txC_data[15]=0;
		txC_data[14]=0;
		txC_data[13]=0;
		txC_data[12]=0;
		txC_data[11]=0;
		txC_data[10]=0;
		txC_data[9]=0;
		txC_data[8]=0;
		txC_data[7]=binary[7];
		txC_data[6]=binary[6];
		txC_data[5]=binary[5];
		txC_data[4]=binary[4];
		txC_data[3]=binary[3];
		txC_data[2]=binary[2];
		txC_data[1]=binary[1];
		txC_data[0]=binary[0];

		cout << "The transmitted Data is: ";

		//Displays the message of the individual Byte
		for (k=0; k<16; k++){
			cout << txC_data[k];
		}

		//Creates the random errors
		cout << endl << "Enter the number of errors for this byte: ";
		cin >> num_error;
		int m = 0;
		for (k=0; k<num_error; k++){
			srand ( time(NULL) );
			err_bit = rand() % 16;
			do{
				m++;
				//now have the program pick a random location in the Byte
				r1 = r2 = r3 = r4 = 0;
				for(k=0;k<16;k++)
					rxC_data[k]=txC_data[k];
				if(rxC_data[err_bit]==1)
					rxC_data[err_bit]=0;
				else
					rxC_data[err_bit]=1;
				cout << "\n \n The Received DATA WITH ERROR is: ";
				for(k=0; k<16; k++){
					cout << rxC_data[k];
				}
				//Setup to solve for the error
				if(rxC_data[1]==1){
					r1++;
				}
				if(rxC_data[2]==1){
					r2++;
				}
				if(rxC_data[3]==1){
					r1++;
					r2++;
				}
				if(rxC_data[4]==1){
					r3++;
				}
				if(rxC_data[5]==1){
					r1++;
					r3++;
				}	
				if(rxC_data[6]==1){
					r2++;
					r3++;
				}	
				if(rxC_data[7]==1){
					r1++;
					r2++;
					r3++;
				}
				if(rxC_data[8]==1){
					r4++;
				}
				if(rxC_data[9]==1){
					r1++;
					r4++;
				}
				if(rxC_data[10]==1){
					r2++;
					r4++;
				}
				if(rxC_data[11]==1){
					r1++;
					r2++;
					r4++;
				}
				if(rxC_data[12]==1){
					r3++;
					r4++;
				}	
				if(rxC_data[13]==1){
					r1++;
					r3++;
					r4++;
				}
				if(rxC_data[14]==1){
					r2++;
					r3++;
					r4++;
				}
				if(rxC_data[15]==1){
					r1++;
					r2++;
					r3++;
					r4++;
				}
				r1n=r1%2;
				r2n=r2%2;
				r3n=r3%2;
				r4n=r4%2;
				r1=r2=r3=r4=0;

				//How to check to see where the error is located.		
				if(r1o==r1n){			
					if(r2o==r2n){
						if(r3o==r3n){
							if(r4o==r4n){
								cout << "\n \n Error in bit " << (16 - err_bit) << endl;
							}
							else{			
								cout << "\n \n Error in bit " << (16 - err_bit) << endl;
							}
						}
						else{
							if(r4o==r4n){
								cout << "\n \n Error in bit " << (16 - err_bit) << endl;
							}
							else{
								cout << "\n \n Error in bit " << (16 - err_bit) << endl;
							}
						}
					}
					else{
						if(r3o==r3n){
							if(r4o==r4n){
								cout << "\n \n Error in bit " << (16 - err_bit) << endl;
							}
							else{
								cout << "\n \n Error in bit " << (16 - err_bit) << endl;
							}
						}
						else{
							if(r4o==r4n){
								cout << "\n \n Error in bit " << (16 - err_bit) << endl;
							}
							else{
								cout << "\n \n Error in bit " << (16 - err_bit) << endl;
							}
						}
					}
				}
				else{
					if(r2o==r2n){
						if(r3o==r3n){
							if(r4o==r4n){
								cout << "\n \n Error in bit " << (16 - err_bit) << endl;
							}
							else{
								cout << "\n \n Error in bit " << (16 - err_bit) << endl;
							}
						}
						else{
							if(r4o==r4n){
								cout << "\n \n Error in bit " << (16 - err_bit) << endl;
							}
							else{
								cout << "\n \n Error in bit " << (16 - err_bit) << endl;
							}
						}
					}
					else{
						if(r3o==r3n){
							if(r4o==r4n){
								cout << "\n \n Error in bit " << (16 - err_bit) << endl;
							}
							else{
								cout << "\n \n Error in bit " << (16 - err_bit) << endl;
							}
						}
						else{
							if(r4o==r4n){
								cout << "\n \n Error in bit " << (16 - err_bit) << endl;
							}
							else{
								cout << "\n \n Error in bit " << (16 - err_bit) << endl;
							}
						}
					}
				}
			}
			while (m<num_error);
			//Sets the error bits back to the correct bit value
			if(rxC_data[err_bitn]==1)
				rxC_data[err_bitn]=0;
			else
				rxC_data[err_bitn]=1;
		}
		//Reforms the 16 bit back to a 8 bit to solve for ASCII character
		bits[7]=txC_data[7];
		bits[6]=txC_data[6];
		bits[5]=txC_data[5];
		bits[4]=txC_data[4];
		bits[3]=txC_data[3];
		bits[2]=txC_data[2];
		bits[1]=txC_data[1];
		bits[0]=txC_data[0];

		cout << endl << "The Error was corrected.";
		cout << endl << "The Byte message sent is: ";
		for(k=0;k<8;k++)
			cout << bits[k];
		cout << endl << "The ASCII char is: ";

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
		cout << endl;
	}
}