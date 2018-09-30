#include <iostream>
#include <string>
#include <vector>
#include "delim.h"

using namespace std;

#define LEN_LECTURE_ID 12

class Lecture {
private:
	char lecture_id[LEN_LECTURE_ID];
	string subject;
	char level;
	int price;
	char extension;
	int due_date;
	string name_of_teacher;
	string textbook;

public:
	/* constructor */
	Lecture();
	Lecture(const Lecture&);	// copy constructor

	/* operator overloading */
	Lecture & operator = (const Lecture &);
	bool operator == (const Lecture &);
	bool operator != (const Lecture &);

	/* IO stream overloading */
	friend istream & operator >> (istream &is, Lecture &l);
	friend ostream & operator << (ostream &os, Lecture &l);

	void update_lecture_id(const char new_id[LEN_LECTURE_ID]) { memcpy(lecture_id, new_id, LEN_LECTURE_ID); }
	void update_subject(const string new_subject) { subject = new_subject; }
	void update_level(const char new_level) { level = new_level; }
	void update_price(const int new_price) { price = new_price; }
	void update_extension(const char new_extension) { extension = new_extension; }
	void update_due_date(const int new_due_date) { due_date = new_due_date; }
	void update_name_of_teacher(const string new_name) { name_of_teacher = new_name; }
	void update_textbook(const string new_textbook) { textbook = new_textbook; }

	/* pack & unpack */
	bool Pack(IOBuffer &buffer) const;
	bool Unpack(IOBuffer &buffer);
};

istream & operator >> (istream &is, Lecture &l);
ostream & operator << (ostream &os, Lecture &l);