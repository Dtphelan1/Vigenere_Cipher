/* 
----- Vigenere Cipher Client
    
A tool for decrypting messages, given the key 
	and the Ciphertext.
*/ 

#include <iostream>
#include <string>
#include <cstring>

using namespace std;


// ********************
// ********************
// Declarations
// **************
void   decipherOrEncrypt();
void   launchEncryption();
void   launchDecryption();
bool   checkAlpha(string text);
bool   checkInputText(string text);
string inputPrompt(char X);
string encryptFn(string key, string text);
string decryptFn(string key, string text);

char zero = 'a';

// *********************
// *********************
// Main
// ******
int main() {

    // Do we want to decipher or encrypt
    decipherOrEncrypt();

    return 0;
}


// **********************
// **********************
// Definitions
// *************

// Provides a prompt for encrypting or decrypting protocols
//
void decipherOrEncrypt() {
    // See what they would like to do; assume invalid response at first
    char response;
    bool check = false;

    while(!check) {
	cout << "\nWhat would you like to do:\n"
	     << "Encrypt(e) or Decrypt(d) data? ";
	cin  >> response;
	// E means encrypt
	if (response == 'e') {
	    launchEncryption();
	}	
	// D means decrypt
	else if (response == 'd') {
	    launchDecryption();
	}
	// Anything else is garbage -- try again
	else {
	    cout << "I'm sorry, please respond with one of the two, "
		 << " valid characters.\nNow -- ";
	}    
    }
}

// Launches the encryption protocol
//
void launchEncryption() {
    // Plaintext
    string pText;

    // Take input for Plaintext
    pText = inputPrompt('p');

    // Make a key
    string key;

    // Take input for Key
    key = inputPrompt('k');

    // Let's start encrypting -- set aside space for cText
    string cipherText;

    // The encryption is a product of the key and the pText
    cipherText = encryptFn(key, pText);

    cout << "Encrypted: " << cipherText << endl
	 << "Key: " << key << endl;
}

// Launches the decryption protocol
//
void launchDecryption() {
    // Cipher Text
    string cText;

    // Take input for Ciphertext
    cText = inputPrompt('c');

    // Make a key; key is not Alpha at initialization
    string key;

    // Take input for Key
    key = inputPrompt('k');

    // Let's start deciphering -- set aside space for plaintext
    string plainText;

    // The decryption is a product of the key and the ciphertext
    plainText = decryptFn(key, cText);

    cout << "Decrypted: " << plainText << endl
	 << "Key: " << key << endl;
}

// Prompt for receiving input
//
string inputPrompt(char X) {
    string text;
    bool check = false;

    while(!check) {
        // Input prompt changes according to the char argument
	if(X == 'c') {
	    cout << "\nWhat's the Ciphertext you would like decrypted?\n"
		 << "One block of text, just letters, no spaces: ";
	}
	else if (X == 'k') {
	    cout << "\nWhat's the key you will use?\n"
		 << "One block of text, just letters, no spaces: ";
	}
	else if (X == 'p') {
	    cout << "\nWhat's the Plaintext you would like encrypted?\n"
		 << "One block of text, just letters, no spaces: ";
	}
        // Receive input
	cin  >> text;

	// Check input
	check = checkInputText(text);
    }
    return text;
}

// Checks input text to see that it is both
//   only letters and exactly what the user wants 
//
bool checkInputText(string text) {
    // Two checks: One automatic (letters)
    // 		   One user based (verification)

    // Check text for Alpha only
    bool check1 = checkAlpha(text);
    
    // If failed, text is no good
    if (!check1) {
	cout << "\nWhoops -- try again!";
	return false;
    }
    // If not, then it's passed check1 and it's Alpha-only 
    // Continue -- check2
    bool check2 = false;
    string response;
    while(!check2) {
	cout << "\nIs this correct?\n"
	     << text << endl
	     << "Respond yes or no: ";

	cin  >> response;

	// check failed
	if(response == "no") {
	    return false;
	}
	// check passed
	else if (response == "yes") {
	    return true;
	}
	// Not a valid response
	else {
	    cout << "Sorry, that was not a valid response.";
	}
    }
    cout << endl;
    return true;
}

// Checks whether a given string is a collection of 
//   purely alphabetic characters.
//
bool checkAlpha(string text) {
    // If no input, failure
    if (text.length() == 0) {
	return false;
    }

    for(size_t i = 0; i < text.length(); i++) {
	// Two bounds -- 1. Less than 'a'
	// 	      -- 2. Greater than 'z'
	// Only lower case
	if ( text.at(i) < 'a' || text.at(i) > 'z') {
	    // If any char is within any of these bounds
	    // return false -- it's a non-alpha char
	    return false;
	}
    }
       
    // If no failure, return true
    return true;
}

// Protocol for deciphering a block of text
//   according to a given key
//
string decryptFn(string key, string text) {
	
    // Some variables: plaintext holder (size of Ciphertext)
    //   Length of the text
    //   Length of the key
    string plainText = text;
    int lenText = text.length();
    int lenKey = key.length();

    // If the length of the text is zero, abort
    if (lenText == 0) {
	return NULL;
    }

    // Variables for seeing how the lengths of the 
    //   key and the text match up, seeing how many 
    //   times the key can be matched up perfectly with 
    //   the text until there are 'hanging letters'
    // Vars: # of hanging letters and perfect divisions
    //       The number of iterations (jumps) made so far
    int numDiv = lenText/lenKey;
    char textLetter, keyLetter;
    int iteration = 0;
    int hangingIndex = 0;

    // For each time the whole key was used for encryption
    while (numDiv != 0) {
	// For the length of the key
	for(int i = 0; i < lenKey; i ++) {
	    // Find the letters at those location
	    textLetter = text.at(i + iteration*lenKey) - zero;
	    keyLetter = key.at(i) - zero;
	    // If text letter is < key letter, the reult of 
	    //   the sum was > 'z' and was modded; fix this
	    if(textLetter < keyLetter) {
		textLetter += 26;
	    }
	    // Ultimately, subtract the value of the key letter from
	    //   that of the Ciphertext to find the different between the two
	    //   and add that to the 'zero point' -- defined globally. 
	    plainText.at(i + iteration*lenKey) = textLetter - keyLetter + zero;
	}
	// Decrement numDiv at each iteration; increment iteration count
	//   and move the hanging index to the last index seen
	numDiv --;
	iteration ++;
	hangingIndex += lenKey;
    }
    // Starting at the hanging index, for the remaining letters
    //   in the CText, repeat above procedure
     for(int i = 0; i+hangingIndex < lenText; i++) {
	textLetter = text.at(hangingIndex + i) - zero;
	keyLetter = key.at(i) - zero;
	    
	if(textLetter < keyLetter) {
	    textLetter += 26;
	}
	plainText.at(hangingIndex + i) = textLetter - keyLetter + zero;
     }
     // Return decrypted text
     return plainText;
}

// Protocol for encrypting a message in respect 
//   to a certain key
//
string encryptFn(string key, string text) {

    // Some variables: ciphertext holder (size of plaintext)
    //   Length of the text
    //   Length of the key
    string cipherText = text;
    int lenText = text.length();
    int lenKey = key.length();

    // If the length of the text is zero, abort
    if (lenText == 0) {
	return NULL;
    }

    // Variables for seeing how the lengths of the 
    //   key and the text match up, seeing how many 
    //   times the key can be matched up perfectly with 
    //   the text until there are 'hanging letters'
    // Vars: # of hanging letters and perfect divisions
    //       The number of iterations (jumps) made so far
    int numDiv = lenText/lenKey;
    char textLetter, keyLetter, newLetter;
    int iteration = 0;
    int hangingIndex = 0;

    // For each time the whole key was used for encryption
    while (numDiv != 0) {
	// For the length of the key
	for(int i = 0; i < lenKey; i ++) {
	    // Find the letters at those location 
	    textLetter = text.at(i + iteration*lenKey) - zero;
	    keyLetter = key.at(i) - zero;
	    // Subtract zero from each
	    //   Add those values together, then add one
	    //   Algebraic reasons here not stated
	    newLetter = textLetter + keyLetter;

	    // Now mod 26 that value
	    newLetter = newLetter % 26;

	    // And finally add our zero point back; add it to text
	    newLetter += zero;
	    cipherText.at(i + iteration*lenKey) = newLetter;
	}
	// Decrement numDiv at each iteration; increment iteration count
	//   and move the hanging index to the last index seen
	numDiv --;
	iteration ++;
	hangingIndex += lenKey;
    }
    // Starting at the hanging index, for the remaining letters
    //   in the CText, repeat above procedure
     for(int i = 0; i+hangingIndex < lenText; i++) {
	textLetter = text.at(hangingIndex + i) - zero;
	keyLetter = key.at(i) - zero;

	newLetter = textLetter + keyLetter;

	newLetter = newLetter % 26;
	newLetter += zero;
	cipherText.at(i + iteration*lenKey) = newLetter;
     }
     // Return decrypted text
     return cipherText;
}

/*
***********************
***********************

Debugging COUT commands -- use as needed

***********************
***********************

    cout << "All Vars: " 
	 << plainText << "plaintext" << endl
	 << lenText << "lenText" << endl
	 << lenKey << "lenKey" << endl
	 << remainder << "remainder"  << endl 
	 << numDiv << "numDiv" << endl 
	 << jumps << "jumps" << endl
	 << hangingIndex << "hanging I " << endl;


  cout << endl << "finished numDiv " << endl << endl;

    cout << endl << "hangingIndex" << hangingIndex << endl << endl;
 
	    cout << textLetter << endl << keyLetter << endl;

    cout << plainText << endl;
 */
