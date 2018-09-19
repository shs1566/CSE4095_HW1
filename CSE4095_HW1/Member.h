#include <iostream>
#include <string>

using namespace std;

#define LEN_MILEAGE 10

class Member {
private:
	string id;
	string password;
	string name;
	string phoneNumber;
	string address;
	char mileage[LEN_MILEAGE];

public:
	/* constructor */
	Member();
	Member(const string);
	Member(const Member&);	// copy constructor

	/* operator overloading */
	Member & operator = (const Member&);
	bool operator == (const Member&);
	bool operator != (const Member&);

	void update_id(const string new_id) { id = new_id; }
	void update_password(const string new_password) { password = new_password; }
	void update_name(const string new_name) { name = new_name; }
	void update_phoneNumber(const string new_phoneNumber) { phoneNumber = new_phoneNumber; }
	void update_address(const string new_address) { address = new_address; }
	void update_mileage(const char new_mileage[LEN_MILEAGE]) { memcpy(mileage, new_mileage, LEN_MILEAGE); }

};