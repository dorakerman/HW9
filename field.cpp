#include <cstring>
#include <iostream>
#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"


/* ================================= CONSTATNS ============================== */
/*enum field_type { IP=0, PORT = 1, GENERIC = 2 };*/
#define SRC_IP_PAT "src-ip"
#define DST_IP_PAT "dst-ip"
#define SRC_PORT_PAT "src-port"
#define DST_PORT_PAT "dst-port"
#define EQ_SIGN "="
#define COMMA_SIGN ","
using namespace std;

/* ========================================================================== */

/* ============================ FUNC DECLARATION ============================ 
Field::Field(String pattern, field_type type);
Field::Field(String pattern);
Field::~Field();
field_type Field::get_type() const;
bool Field::set_value(String val);
bool Field::match_value(String val) const;
bool Field::match(String packet);

   ========================================================================== */

/**
 * @ brief Initiates a Field with pattern and type
 * @ Constructor
 * @ param pattern: A String object to initialize into this pattern
 * @ param type: The type of the field
 */
Field::Field(String pattern, field_type type):
	pattern(pattern.trim()),
	type(type)
	{}

/**
 * @ brief Initiates a Field with pattern and type
 * @ Constructor
 * @ param pattern: A String object to initialize into this pattern
 */
Field::Field(String pattern){
	String temp_pat = pattern.trim();
	this->pattern = temp_pat;
	cout<<"PRINTING IN FIELD CONSTRUCTOR DOR"<<endl;
	this->pattern.print();
	if (this->pattern.equals(SRC_IP_PAT) || this->pattern.equals(DST_IP_PAT)){
		type = IP;
	}else if(this->pattern.equals(SRC_PORT_PAT) ||
			 this->pattern.equals(DST_PORT_PAT)){
		type = PORT;
	}else{
		type = GENERIC;
	}
}

/**
 * @ brief Calls String Destructor.
 * @ Destructor
 */
Field::~Field(){
	pattern.~String();
}


/**
 * @ brief Returns the type of field.
 * @ return the type.
 * @ rtype: INT
 */
field_type Field::get_type() const{
	return type;
}

/**
 * @ brief This function will define the set of valid values for field.
 * 		   It calls relevant functions of child classes,
 * @ param val: String object containing valid values..
 * @ return: Returns true if input parsing suceeded, else false.
 */
bool Field::set_value(String val){
	if (type == IP){
		return((Ip*)this)->set_value(val);
	}
	if (type == PORT){
		return((Port*)this)->set_value(val);
	}
	return false;
}

/**
 * @ brief This function will check if the value in val matches the defined
 		   valid input in set values.
 * @ param val: String object containing valid values.
 * @ return: True if value matched, false if not.
 */
bool Field::match_value(String val) const{
	if (type == IP){
		return((Ip*)this)->match_value(val);
	}
	if (type == PORT){
		return((Port*)this)->match_value(val);
	}
	return false;
}

/**
 * @ brief: This function will go over all fields in packet, and compare using
 * @ 		match_value the values in the packet only for the field in packt 
 * @ 		that is the same is this.
 * @ param packet: String object containing packet values.
 * @ return: True if value matched, false if not.
 */
bool Field::match(String packet){
	String *comma_split;
	String *eq_split;
	size_t num_after_com;	//Number of strings after splitting by ','
	size_t num_after_eq;	//Number of strings after splitting by '='
	packet.split(COMMA_SIGN, &comma_split, &num_after_com);
	bool return_val = false;
	/*First we check if the pattern matches the field's pattern.
	e.g. if the field is 'src-port' packet should begin with 'src-port'*/
	for (size_t i = 0; i < num_after_com; i++){
		comma_split[i].split(EQ_SIGN, &eq_split, &num_after_eq);
		if(sizeof(short) != num_after_eq){
			//If number of '=' in field was different that 1.
			continue;
		}

		if(this->pattern.equals(eq_split[0].trim())){//If pattern matches
			return_val = this->match_value(eq_split[1].trim());
		}
		delete[] eq_split;
	}
	delete[] comma_split;
	return return_val;
}
