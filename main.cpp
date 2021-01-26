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
	cout<<"+++ DOR LEFT CHECK ARGS +++\n"<<endl;
	String rule_string (argv[1]);
	String *eq_split;
	cout<<"DOR STARTIG SPLIT IN MAIN @@@@\n"<<endl;
	size_t num_after_eq;//Number of strings after splitting by '-'
	rule_string.split(EQ_SIGN, &eq_split, &num_after_eq);
	std::cout<<"DOR ================================="<<std::endl;
	eq_split[0].print();
	eq_split[1].print();
	if(sizeof(short) != num_after_eq){
		//If number of '-' was differen than 1
		delete[] eq_split;
		return 1;	//(Invalid)
	}
	std::cout<<"DOR ================================="<<std::endl;
	Field rule_field(eq_split[0]);//Create a field with pattern
	field_type rule_type = rule_field.get_type();
	
	std::cout<<"DOR, rule type is ="<<rule_type<<std::endl;
	if(GENERIC == rule_type){
		return 1; //No need to parse
	}

	if(IP == rule_type){
		Ip *rule_ip = (Ip*) &rule_field;
		rule_ip->set_value(eq_split[1]);

	}else{
		Port *rule_port = (Port*) &rule_field;
		rule_port->set_value(eq_split[1]);

	}
	parse_input(rule_field);
	delete[] eq_split;
	return 0;

}
