#include "Purchase.h"
#include <sstream>

# define LEN_BUFFER 256

Purchase::Purchase() { }

Purchase::Purchase(const Purchase &p) {
	update_purchase_id(p.purchase_id);
	update_lecture_id(p.lecture_id);
	update_member_id(p.member_id);
	update_mileage(p.mileage);
}

Purchase & Purchase::operator = (const Purchase &p) {
	update_purchase_id(p.purchase_id);
	update_lecture_id(p.lecture_id);
	update_member_id(p.member_id);
	update_mileage(p.mileage);

	return *this;
}

bool Purchase::operator == (const Purchase &p) {
	return !strcmp(purchase_id, p.purchase_id);
}

bool Purchase::operator != (const Purchase &p) {
	return strcmp(purchase_id, p.purchase_id);
}

istream & operator >> (istream &is, Purchase &p) {
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
	p.update_purchase_id(token.data());
	getline(iss, token, '|');
	p.update_lecture_id(token.data());
	getline(iss, token, '|');
	p.update_member_id(token);
	getline(iss, token, '|');
	p.update_mileage(token.data());

	return is;
}

ostream & operator << (ostream &os, Purchase &p) {
	string purchase_id(p.purchase_id, LEN_PURCHASE_ID);
	string lecture_id(p.lecture_id, LEN_LECTURE_ID);
	string mileage(p.mileage, LEN_MILEAGE);

	os << "PURCHASE ID: " << purchase_id << endl;
	os << "LECTURE ID: " << lecture_id << endl;
	os << "MEMBER ID: " << p.member_id << endl;
	os << "MILEAGE: " << mileage << endl;

	return os;
}

bool Purchase::Pack(IOBuffer &buffer) const {
	int numBytes;
	string purchase_id(purchase_id, LEN_PURCHASE_ID);
	string lecture_id(lecture_id, LEN_LECTURE_ID);
	string mileage(mileage, LEN_MILEAGE);

	buffer.Clear();

	numBytes = buffer.Pack(purchase_id.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack(lecture_id.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack(member_id.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack(mileage.c_str());
	if (numBytes == -1) return false;

	return true;
}

bool Purchase::Unpack(IOBuffer &buffer) {
	int numBytes;
	char buf[LEN_BUFFER];

	numBytes = buffer.Unpack(purchase_id, LEN_PURCHASE_ID);
	if (numBytes == -1) return false;

	numBytes = buffer.Unpack(lecture_id, LEN_LECTURE_ID);
	if (numBytes == -1) return false;

	numBytes = buffer.Unpack(buf);
	if (numBytes == -1) return false;
	member_id = buf;

	numBytes = buffer.Unpack(mileage, LEN_MILEAGE);
	if (numBytes == -1) return false;

	return true;
}
