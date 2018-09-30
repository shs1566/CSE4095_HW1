#include "Purchase.h"

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