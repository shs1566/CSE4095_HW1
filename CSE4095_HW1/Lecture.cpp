#include "Lecture.h"
#include <sstream>

# define LEN_BUFFER 256

Lecture::Lecture() { }

Lecture::Lecture(const Lecture &l) {
	update_lecture_id(l.lecture_id);
	update_subject(l.subject);
	update_level(l.level);
	update_price(l.price);
	update_extension(l.extension);
	update_due_date(l.due_date);
	update_name_of_teacher(l.name_of_teacher);
	update_textbook(l.textbook);
}

Lecture & Lecture::operator = (const Lecture &l) {
	update_lecture_id(l.lecture_id);
	update_subject(l.subject);
	update_level(l.level);
	update_price(l.price);
	update_extension(l.extension);
	update_due_date(l.due_date);
	update_name_of_teacher(l.name_of_teacher);
	update_textbook(l.textbook);

	return *this;
}

bool Lecture::operator == (const Lecture &l) {
	return !strcmp(lecture_id, l.lecture_id);
}

bool Lecture::operator != (const Lecture &l) {
	return strcmp(lecture_id, l.lecture_id);
}

istream & operator >> (istream &is, Lecture &l) {
	string st;

	is.exceptions(istream::failbit | istream::badbit);

	try {
		getline(is, st);
	}
	catch (istream::failure e) {
		return is;
	}

	istringstream iss(st);
	string token;

	getline(iss, token, '|');
	l.update_lecture_id(token.data());
	getline(iss, token, '|');
	l.update_subject(token);
	getline(iss, token, '|');
	l.update_level(token.data()[0]);
	getline(iss, token, '|');
	l.update_price(atoi(token.data()));
	getline(iss, token, '|');
	l.update_extension(token.data()[0]);
	getline(iss, token, '|');
	l.update_due_date(atoi(token.data()));
	getline(iss, token, '|');
	l.update_name_of_teacher(token);
	getline(iss, token, '|');
	l.update_textbook(token);

	return is;
}
ostream & operator << (ostream &os, Lecture &l) {
	string lecture_id(l.lecture_id, LEN_LECTURE_ID);

	os << "LECTURE ID: " << lecture_id << endl;
	os << "SUBJECT: " << l.subject << endl;
	os << "LEVEL: " << l.level << endl;
	os << "PRICE: " << l.price << endl;
	os << "EXTENSION: " << l.extension << endl;
	os << "DUE DATE: " << l.due_date << endl;
	os << "NAME OF TEACHER: " << l.name_of_teacher << endl;
	os << "TEXTBOOK : " << l.textbook << endl;

	return os;
}

bool Lecture::Pack(IOBuffer &buffer) const {
	int numBytes;
	string lecture_id(lecture_id, LEN_LECTURE_ID);

	buffer.Clear();

	numBytes = buffer.Pack(lecture_id.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack(subject.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack(&level);
	if (numBytes == -1) return false;
	numBytes = buffer.Pack(to_string(price).c_str);
	if (numBytes == -1) return false;
	numBytes = buffer.Pack(&extension);
	if (numBytes == -1) return false;
	numBytes = buffer.Pack(to_string(due_date).c_str);
	if (numBytes == -1) return false;
	numBytes = buffer.Pack(name_of_teacher.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack(textbook.c_str());
	if (numBytes == -1) return false;

	return true;
}

bool Lecture::Unpack(IOBuffer &buffer) {
	int numBytes;
	char buf[LEN_BUFFER];

	numBytes = buffer.Unpack(lecture_id, LEN_LECTURE_ID);
	if (numBytes == -1) return false;

	numBytes = buffer.Unpack(buf);
	if (numBytes == -1) return false;
	subject = buf;

	numBytes = buffer.Unpack(&level, 1);
	if (numBytes == -1) return false;

	numBytes = buffer.Unpack(buf);
	if (numBytes == -1) return false;
	price = atoi(buf);

	numBytes = buffer.Unpack(&extension, 1);
	if (numBytes == -1) return false;

	numBytes = buffer.Unpack(buf);
	if (numBytes == -1) return false;
	due_date = atoi(buf);

	numBytes = buffer.Unpack(buf);
	if (numBytes == -1) return false;
	name_of_teacher = buf;

	numBytes = buffer.Unpack(buf);
	if (numBytes == -1) return false;
	textbook = buf;

	return true;
}
