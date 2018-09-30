#include <iostream>
#include <string>

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
	Purchase();
	Purchase(const Purchase &p);

	Purchase & operator = (const Purchase &p);
	bool operator == (const Purchase &p);
	bool operator != (const Purchase &p);

	void update_purchase_id(const char *new_id) { memcpy(purchase_id, new_id, LEN_PURCHASE_ID); }
	void update_lecture_id(const char *new_id) { memcpy(lecture_id, new_id, LEN_PURCHASE_ID); }
	void update_member_id(const string new_id) { member_id = new_id; }
	void update_mileage(const char *new_mileage) { memcpy(mileage, new_mileage, LEN_MILEAGE); }
};
