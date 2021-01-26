#include <cstring>
#include <iostream>
#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"

/* ================================= CONSTATNS ============================== */
enum {MAX_RANGE = 65535};
#define HYP_SIGN "-"
#define END_OF_STRING "\0"


/* ========================================================================== */

/* ============================ FUNC DECLARATION ============================ 
Port::Port(String pattern);
bool Port::set_value(String val);
bool Port::match_value(String val) const;

   ========================================================================== */

/**
 * @ brief Initiates a Port with Field with pattern and type=PORT(1)
 * @ Constructor
 * @ param pattern: A String object to initialize into this pattern
 */
Port::Port(String pattern):
	Field::Field(pattern, PORT){
		/*By default - enable all value*/
		range[0] = 0;
		range[1] = MAX_RANGE;
	}

/**
 * @ brief This function will define the set of valid values for Port.
 * @ param val: String object containing valid values..
 * @ return: Returns true if input parsing suceeded, else false.
 */
bool Port::set_value(String val){
	if(val.equals(END_OF_STRING)){ //If Empty String.
		return false;
	}
	String *hyp_split;
	size_t num_after_hyp;//Number of strings after splitting by '-'
	val.split(HYP_SIGN, &hyp_split, &num_after_hyp);
	if(sizeof(short) != num_after_hyp){
		//If number of '-' was differen than 1
		delete[] hyp_split;
		return false;	//(Invalid)
	}
	for(size_t i=0;i < sizeof(short); i++){
		range[i] = hyp_split[i].trim().to_integer();
	}
	delete[] hyp_split;
	if(range[0]>range[1]){
		return false;
	}
	return true;

}

/**
 * @ brief This function will check if the value in val matches the defined
 		   valid input in set values.
 * @ param val: String object containing valid values.
 * @ return: True if value matched, false if not.
 */
bool Port::match_value(String val) const{
	if(val.equals(END_OF_STRING)){ //If Empty String.
		return false;
	}
	int value = val.trim().to_integer();
	if(range[0] <= value && value<= range[1]){
		return true;
	}
	return false;
}