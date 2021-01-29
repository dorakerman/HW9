#include <cstring>
#include <iostream>
#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"
#include "input.h"

/* ================================= CONSTATNS ============================== */
#define EQ_SIGN "="
/* ========================================================================== */
using namespace std;
/*In all input parsing of rule, we assumed that in batch we will remove all
  spaces*/
int main(int argc, char **argv){
	if (0 != check_args(argc, argv)){	//Args aren't valid
		return 1;
	}
	String rule_string (argv[1]);
	String *eq_split;
	size_t num_after_eq;//Number of strings after splitting by '-'
	rule_string.split(EQ_SIGN, &eq_split, &num_after_eq);
	if(sizeof(short) != num_after_eq){
		//If number of '-' was differen than 1
		delete[] eq_split;
		return 1;	//(Invalid)
	}
	Field rule_field = Field(eq_split[0]);//Create a field with pattern
	field_type rule_type = rule_field.get_type();

	if(IP == rule_type){
		Ip *rule_ip = new Ip(eq_split[0]);
		if (false == rule_ip->set_value(eq_split[1])){
			delete rule_ip;
			delete[] eq_split;
			return 1;
		}
		Field *rule = (Field*) rule_ip;
		parse_input(*rule);
		delete rule_ip;
		delete[] eq_split;
		return 0;
	}

	if(PORT == rule_type){
		Port *rule_port = new Port(eq_split[0]);
		if (false == rule_port->set_value(eq_split[1])){
			delete rule_port;
			delete[] eq_split;
			return 1;
		}
		Field *rule = (Field*) rule_port;
		parse_input(*rule);
		delete rule_port;
		delete[] eq_split;
		return 0;

	}
	//If generic -  No need to parse
	delete[] eq_split;
	return 1;

}
