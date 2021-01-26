
#include <cstring>
#include <iostream>
#include "string.h"

/* ================================= CONSTATNS ============================== */
#define END_OF_STRING "\0"
#define SPACE ' '



/* ========================================================================== */

/* ============================ FUNC DECLARATION ============================= 
String::String();
String::String(const String &str);
String::String(const char *str);
String::~String();
String& String::operator=(const char *str);
String& string::operator=(const String &rhs);
bool String::equals(const String &rhs) const;
bool String::equals(const char *rhs) const;
void String::split(const char *delimiters, String **output, size_t *size) const;
String String::trim() const;
int to_integer() const;


   ========================================================================== */
using namespace std;

/**
 * @ brief Initiates an empty string
 * @ Default Constructor
 */
String::String(){
	data = new char[1];
	strncpy(data, END_OF_STRING, 1);
	length = 0;
}

/**
 * @ brief Initiates string from other string
 * @ Copy Constructor.
 * @ param str: A refernce to the String that we need to clone
 */
String::String(const String &str){
	/*First we check that input is valid' if it is NULL we return empty String*/
	length = str.length;
	if(0 == length){
		data = new char[1];
		strncpy(data, END_OF_STRING, 1);
	}else{
		data = new char[length + 1];
		strncpy(data, str.data, length + 1);
	}
	std::cout<<"DOR - type recieved is  "<<str.data<<std::endl;
}

/**
 * @ brief Initiates a string from char array
 * @ Constructor with parameter
 * @ param str: A string to be inserted.
 */
String::String(const char *str){
	length = strlen(str);
	if(0 == length){
		data = new char[1];
		strncpy(data, END_OF_STRING, 1);
	}else{
		data = new char[length + 1];
		strncpy(data, str, length + 1);
	}
	cout<<"\nDATA reciever was "<<str<<endl;
	cout<<"DOR THIS IS str CONSTRUCTOR"<<endl;
	cout<<"DOR THIS IS THE DATA\n "<<this->data<<endl;
}

/**
 * @ Destructor.
 */
String::~String(){
	/*A String data will never be NULL in our implementation*/
	delete[] data;
}

/**
 * @ brief Clone new string into data
 * @ param str: A pointer to the string we wish to copy into data
 */
String& String::operator=(const char *str){
	cout<<"DOR THIS IS = with STR"<<endl;
	if(NULL == str){
		std::cerr << "Tried cloning NULL";
	}
	if(&str == &(this->data)){
		return *this;
	}
	/*Free old String*/
	/*We can use delete without checking because a String object will
	always have at least '/0' in data*/
	cout<<this->length<<endl;
	cout<<"DORRRRR2222222"<<endl;
	delete[] this->data;	
	length = strlen(str);
	data = new char[length + 1];
	strncpy(data, str, length + 1);
	cout<<"DOR THIS IS DATA "<<this->data<<endl;
	return *this;
}

/**
 * @brief Changes this from String
 * @param rhs: a referance to String we wish to copy
 */
String& String::operator=(const String &rhs){
	if(&rhs == this){
		return *this;
	}
	/*Free old String*/
	delete[] data;
	length = rhs.length;
	data = new char[length + 1];
	strncpy(data, rhs.data, length + 1);
	return *this;
}

/**
 * @brief Returns true iff the contents of this equals to the
 * 		  contents of rhs
 * @param rhs: A refernce to the String we want to compare
 */
bool String::equals(const String &rhs) const{
	if(this->length != rhs.length){
		return false;
	}
	if(strncmp(this->data,rhs.data, length) != 0){
		return false;
	}
	return true;
}


/**
 * @brief Returns true iff the contents of this equals to rhs
 * @param rhs: A pointer to the string we want to compare to data
 */
bool String::equals(const char *rhs) const{
	if(NULL == rhs){
		std::cerr << "Tried comparing NULL";
	}
	size_t len = strlen(rhs);
	if(length != len){
		return false;
	}

	if(0 != strncmp(data, rhs, len)){
		return false;
	}
	return true;
}

    /**
     * @brief Splits this to several sub-strings according to delimiters.
     * Allocates memory for output that the user must delete (using delete[]).
     * @note Does not affect this.
     * @note If "output" is set to NULL, do not allocated memory, only
     * compute "size".
     * @param delimeter: A pointer to a string that contains the chars to split
     *					 by.
     * @param output: A pointer to save split String objects in.
     * @param size: Number of String objects after spliting.
     */
void String::split(const char *delimiters, String **output, size_t *size) const{
	/*First, we check that input is valid and that there are delimiters*/
	if(NULL == delimiters){
		std::cerr << "Delimiters are NULL";
		return;
	}
	size_t start_idx = 0;
	size_t end_idx = 0;
	size_t str_count = 1;
	size_t num_of_delimeters = strlen(delimiters);
	int flag = 0;
	int ch_num = 0;	  /*Indiccates size of a String*/
	int delim_flag = 0;/*Indicates if there was a match in this iteration*/

	if(NULL == output){
		flag = 1;	//No need to allocate memory
	}else{
		*output = new String[((this->length)/sizeof(short)) + 1];
		/*Worst case there will be len/2 + 1 Strings after splitting*/
	}

	/*Method of work - We will go over the data char by char, then for each
	char we will check if it matches a delimeter. If so, we will break to a
	String if needed. If flag=1 we won't put it in output, else we will*/
	while(strncmp(&data[end_idx], END_OF_STRING, 1) != 0){
		delim_flag = 0;
		for(size_t delim = 0; delim < num_of_delimeters; delim++){
			//Check if cahr equals to delimeter
			if(data[end_idx] == delimiters[delim]){
				delim_flag = 1;
				//First, check if substring is not empty
				if(start_idx == end_idx){
					start_idx++;
					end_idx++;
					break;
				}
				str_count++;
				if(flag == 1){ 
					end_idx++;
					start_idx = end_idx;
					break;/*Only count, do nothing else*/
				}
				ch_num = end_idx - start_idx;
				char *str_to_cpy = new char[ch_num + 1];
				strncpy(str_to_cpy, &data[start_idx], ch_num);
				strncpy(&str_to_cpy[ch_num], END_OF_STRING, 1);
				*output[str_count - sizeof(short)] = String(str_to_cpy);
				delete[] str_to_cpy;
				end_idx++;
				start_idx = end_idx;
				break;
			}//closes if(0==...)
		}//closes for
		if(delim_flag == 0){
			end_idx++;
		}
    }//closes while

    *size = str_count;
    //Make sure to insert last string that remains
    if(flag == 0){
    	output[0]->print();
	    ch_num = end_idx - start_idx;
		char *str_to_cpy_end = new char[ch_num + 1];
		strncpy(str_to_cpy_end, &data[start_idx], ch_num);
		strncpy(&str_to_cpy_end[ch_num], END_OF_STRING, 1);
		//output[str_count - 1] = new String(str_to_cpy);
		(*output)[str_count - 1] = String(str_to_cpy_end);
		//*output[str_count - 1] = str_to_cpy_end;
		delete[] str_to_cpy_end;
	}

}


/**
 * @brief Remove any leading or trailing white-spaces.
 * Does not change this.
 */
String String::trim() const{
	int start_idx = 0;
	int end_idx = length - 1;
	if(length == 0){	/*Return an empty String object*/
		String ret_str;
		return ret_str;
	}

	while(data[start_idx] == SPACE){
		start_idx++;
	}

	while(data[end_idx] == SPACE){
		end_idx--;
	}
	int ch_num = end_idx - start_idx + 1;
	char *str_to_cpy = new char [ch_num + 1];
	strncpy(str_to_cpy, &data[start_idx], ch_num);
	strncpy(&str_to_cpy[ch_num + 1], END_OF_STRING, 1);
	String str_ret(str_to_cpy);
	delete[] str_to_cpy;
	return str_ret;
}

/**
 * @brief Try to convert this to an integer. Returns 0 on error.
 */
int String::to_integer() const{
	if(length == 0){
		return 0;	//FAIL
	}
	return atoi(data);
}




/*NOTE: Although we were told to assume pointers will not be set to NULL,
		We have checked it and printed an error for outselves*/