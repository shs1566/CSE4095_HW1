#include "Member.h"

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

