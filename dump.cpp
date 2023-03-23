#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

void binary(FILE* file) { //This function will print out the binary value of characters
    int bitsets = 0;
    int spacing = 0; //Spacing counter to check where the last line leaves off
    int address = 0;
    char line[8];	//Char buffer for each line
    printf("%07x", address); cout<<": ";	//Prints out the first address
    do{
        int c = fgetc(file);	//Reads each character decimal ASCII value (int)

        if(feof(file))	//Reached end of file and breaks while loop
            break;
        if(bitsets > 7) {	//If statement when 8 bytes are printed
            cout<< " ";
            for(int i=0; i<bitsets; ++i){	//Prints next 8 chars
                cout<<line[i];
            }
            cout<<endl;
            address += 8;	//Next 8 bytes of memory address 
            printf("%07x", address);
            cout<<": ";
            bitsets = 0;
            spacing = 0;
        }
        for(int i=7; i>=0; i--){ //Loop to calculate binary value of each byte
            int k = c >> i;
            if(k & 1)
                cout << "1";
            else    
                cout<< "0";
            ++spacing;
        }
        if(c < 21 || c == 177) {
            line[bitsets] = '.'; //Checks if next char is non-printable and changes it to '.'
        }
        else {
            line[bitsets] = static_cast<char>(c); //If it is printable it converts int c to its corresponding ASCII char
        }
        ++spacing;
        ++bitsets;
        cout<<" ";
    } while(1);
    if(bitsets < 8){ //If last line has less than 8 bitsets
        for(int i=spacing; i<73; ++i){ //Space until characters are printed in correct format
            cout<<" ";
        }
        for(int i=0; i<bitsets; ++i){
            cout<<line[i]; //Print last line of chars
        }
    }
    cout<<endl;
}
int main(int argc, char** argv) {
    
    FILE* file = fopen(argv[argc - 1], "r"); //Takes in last argument as file name
    int octets, counter, spacing = 0; 
    int address = 0;
    char line[16]; //Char buffer for hexadecimal format
    if (file == NULL){ //Filename does not exist
        return 0;
    }
    if (strcmp(argv[1], "-b") == 0){ //Calls binary function if second argument is -b
        binary(file);
        fclose(file);
        return 0;
    }
    printf("%07x", address); //Prints out first address
    cout<<": ";
    do{
        int c = fgetc(file); //Assigns character's ASCII decimal value
        if(feof(file)) //Breaks while loop if end of file is reached
            break;
        if(octets > 1){ //If 2 octets are printed then space
            cout<<" ";
            octets = 0;
            spacing += 1;
        }
        if(counter > 15){ //If 16 octets are printed then print chars and end line
            cout<<" ";
            for(int i=0; i<counter; ++i){ //Prints next 16 characters
                cout<<line[i];
            }
            cout<<""<<endl;
            address += 16; //Next address incremented by 16 bytes
            printf("%07x", address);
            cout<<": ";
            counter = 0;
            spacing = 0;
        }
        if(c < 21 || c == 177) { //Character is a non-printable char
            line[counter] = '.'; //Replace with a '.'
        }
        else {
            line[counter] = static_cast<char>(c); //Convert int to corresponding ASCII char
        }
        printf("%02x", c); //If hexadecimal contains 1 byte, add a 0 to it. Ex: A = 0A
        spacing += 2;
        ++octets;
        ++counter;
    } while(1);
    if(counter < 16){ //Last line contains less than 16 octets
        for(int i=spacing; i<41; i++){ //Spaces until the characters are printed in correct format
            cout<<" ";
        }
        for(int i=0; i<counter; ++i){
            cout<<line[i]; //Prints final line of chars
        }
    }
    cout<<endl;
    return(0);
}
