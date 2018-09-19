#include "Lecture.h"

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