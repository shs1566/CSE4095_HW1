#include <iostream>
#include <string>
#include <vector>
#include "delim.h"

using namespace std;

#define LEN_PURCHASE_ID 16
#define LEN_LECTURE_ID 12
#define LEN_MILEAGE 10 

class Purchase {
private:
	char purchase_id[LEN_PURCHASE_ID];
	char lecture_id[LEN_LECTURE_ID];
	string member_id;
	char mileage[LEN_MILEAGE];

public:
	/* constructor */
	Purchase();
	Purchase(const Purchase &p);	// copy constructor

	/* operator overloading */
	Purchase & operator = (const Purchase &p);
	bool operator == (const Purchase &p);
	bool operator != (const Purchase &p);

	/* IO stream overloading */
	friend istream & operator >> (istream &is, Purchase &p);
	friend ostream & operator << (ostream &os, Purchase &p);

	/* member variable update method */
	void update_purchase_id(const char *new_id) { memcpy(purchase_id, new_id, LEN_PURCHASE_ID); }
	void update_lecture_id(const char *new_id) { memcpy(lecture_id, new_id, LEN_PURCHASE_ID); }
	void update_member_id(const string new_id) { member_id = new_id; }
	void update_mileage(const char *new_mileage) { memcpy(mileage, new_mileage, LEN_MILEAGE); }

	char *get_purchase_id() { return purchase_id; }
	char *get_lecture_id() { return lecture_id; }
	string get_member_id() { return member_id; }

	/* pack & unpack */
	bool Pack(IOBuffer &buffer) const;
	bool Unpack(IOBuffer &buffer);
};

istream & operator >> (istream &is, Purchase &p);
ostream & operator << (ostream &os, Purchase &p);
