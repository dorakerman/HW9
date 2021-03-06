#include <cstring>
#include <iostream>
#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"

using namespace std;
/* ================================= CONSTATNS ============================== */
enum {LST_BYTE = 24,MSB = 32,MAX_RANGE = 255};
#define END_OF_STRING "\0"
#define DOT_SIGN "."
#define SLASH_SIGN "/"
#define MAX_NUM 0xFFFFFFFF  /*We used define and not enum because we are not
							  sure that enum is unsigned.*/
/* ========================================================================== */


/* ============================ FUNC DECLARATION ============================ 
Ip::Ip(String pattern);
bool Ip::set_value(String val);
bool Ip::match_value(String val) const;
   ========================================================================== */

/**
 * @ brief Initiates an IP with Field with pattern and type=IP(0)
 * @ Constructor
 * @ param pattern: A String object to initialize into this pattern
 */
Ip::Ip(String pattern):
	Field::Field(pattern, IP){
		/*By default - enable all value*/
		low = 0;
		high = MAX_NUM;
		/*high = 0xFFFFFFFF*/
	}

/**
 * @ brief This function will define the set of valid values for IP.
 * @ param val: String object containing valid values..
 * @ return: Returns true if input parsing suceeded, else false.
 */
bool Ip::set_value(String val){
	if(val.equals(END_OF_STRING)){ //If Empty String.
		return false;
	}
	String *slash_split;
	String *dot_split;
	size_t num_after_slash;//Number of strings after splitting by '\'
	size_t num_after_dot;//Number of strings after splitting by '.'
	unsigned int mask_num = 0;
	unsigned int mask = 0;
	unsigned int ip_hex = 0;	//We will turn IP address to hexa.
	unsigned int segment = 0;  //We will use it to create IP num
	val.split(SLASH_SIGN, &slash_split, &num_after_slash);
	if(sizeof(short) != num_after_slash){
		//If number of '/' was differen than 1
		delete[] slash_split;
		return false;	//(Invalid)
	}
	/*Get mask number*/
	mask_num = slash_split[1].trim().to_integer();
	if(mask_num > MSB){
		delete[] slash_split;
		return false;	//(Invalid)
	}

	/*Split IP according to '.' sign without mask*/
	slash_split[0].split(DOT_SIGN, &dot_split, &num_after_dot);
	if(sizeof(int) != num_after_dot){
		//If number of '.' was differen than 3
		delete[] slash_split;
		delete[] dot_split;
		return false;	//(Invalid)
	}

	for(size_t i=0; i < sizeof(int); i++){
		segment = dot_split[i].trim().to_integer();
		if (segment > MAX_RANGE){
			delete[] slash_split;
			delete[] dot_split;
			return false;	//(Invalid)
		}
		ip_hex |= (segment << (LST_BYTE - (sizeof(double) * i)));
	}

	mask = MAX_NUM >> (mask_num);

	if(MSB == mask_num){
		mask = 0;
	}
	//Mask num can not be zero and 32 at the same time
	if(0 == mask_num){
		mask = MAX_NUM;
	}

	/*e.g. set high -> let's say mask_num is 8 and ip_hex = 0xDA010203
	mask = MAX_NUM >> 8 = 0x00FFFFFF -> ip_hex | mask = 0xDAFFFFFF*/
	this->high = ip_hex | mask;
	this->low = ip_hex & (~mask);

	delete[] dot_split;
	delete[] slash_split;
	return true;

}

/**
 * @ brief This function will check if the value in val matches the defined
 		   valid input in set values.
 * @ param val: String object containing valid values.
 * @ return: True if value matched, false if not.
 */
bool Ip::match_value(String val) const{
	if(val.equals(END_OF_STRING)){ //If Empty String.
		return false;
	}
	String *dot_split;
	size_t num_after_dot;//Number of strings after splitting by '.'
	unsigned int ip_hex = 0;	//We will turn IP address to hexa.
	unsigned int segment = 0;  //We will use it to create IP num

	/*Split IP according to '.' sign without mask*/
	val.split(DOT_SIGN, &dot_split, &num_after_dot);
	if(sizeof(int) != num_after_dot){
		//If number of '.' was differen than 3
		delete[] dot_split;
		return false;	//(Invalid)
	}

	for(size_t i=0; i < sizeof(int); i++){
		segment = dot_split[i].trim().to_integer();
		if (segment > MAX_RANGE){
			delete[] dot_split;
			return false;	//(Invalid)
		}
		ip_hex |= (segment << (LST_BYTE - (sizeof(double) * i)));
	}

	delete[] dot_split;
	if(low <= ip_hex && ip_hex<= high){
		return true;
	}
	return false;
}