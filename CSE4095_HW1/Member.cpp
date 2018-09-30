#include "Member.h"
#include <sstream>

# define LEN_BUFFER 256

Member::Member() { }

Member::Member(string new_id) {
	update_id(new_id);
}

Member::Member(const Member &m) {
	update_id(m.id);
	update_password(m.password);
	update_name(m.name);
	update_phoneNumber(m.phoneNumber);
	update_address(m.address);
	update_mileage(m.mileage);
}

Member& Member::operator = (const Member &m) {

	update_id(m.id);
	update_password(m.password);
	update_name(m.name);
	update_phoneNumber(m.phoneNumber);
	update_address(m.address);
	update_mileage(m.mileage);

	return *this;
}

bool Member::operator == (const Member &m) {
	return id == m.id;
}

bool Member::operator != (const Member &m) {
	return id != m.id;
}

istream & operator >> (istream &is, Member &m) {
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
	m.update_id(token);
	getline(iss, token, '|');
	m.update_password(token);
	getline(iss, token, '|');
	m.update_name(token);
	getline(iss, token, '|');
	m.update_phoneNumber(token);
	getline(iss, token, '|');
	m.update_address(token);
	getline(iss, token, '|');
	m.update_mileage(token.data());

	return is;
}

ostream & operator << (ostream &os, Member &m) {
	string mileage(m.mileage, LEN_MILEAGE);

	os << "ID: " << m.id << endl;
	os << "PASSWORD: " << m.password << endl;
	os << "NAME: " << m.name << endl;
	os << "PHONE NUMBER: " << m.phoneNumber << endl;
	os << "ADDRESS: " << m.address << endl;
	os << "MILEAGE: " << mileage << endl;

	return os;
}

bool Member::Pack(IOBuffer &buffer) const {
	int numBytes;
	string mileage(mileage, LEN_MILEAGE);

	buffer.Clear();

	numBytes = buffer.Pack(id.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack(password.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack(name.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack(phoneNumber.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack(address.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack(mileage.c_str());
	if (numBytes == -1) return false;

	return true;
}

bool Member::Unpack(IOBuffer &buffer) {
	int numBytes;
	char buf[LEN_BUFFER];

	numBytes = buffer.Unpack(buf);
	if (numBytes == -1) return false;
	id = buf;

	numBytes = buffer.Unpack(buf);
	if (numBytes == -1) return false;
	password = buf;

	numBytes = buffer.Unpack(buf);
	if (numBytes == -1) return false;
	name = buf;

	numBytes = buffer.Unpack(buf);
	if (numBytes == -1) return false;
	phoneNumber = buf;

	numBytes = buffer.Unpack(buf);
	if (numBytes == -1) return false;
	address = buf;

	numBytes = buffer.Unpack(mileage, LEN_MILEAGE);
	if (numBytes == -1) return false;

	return true;
}	
