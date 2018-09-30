#include "Member.h"
#include "Lecture.h"
#include "Purchase.h"
#include <vector>
#include <fstream>

using namespace std;

bool readMember(vector<Member> &member_list);
bool readLecture(vector<Lecture> &lecture_list);
bool readPurchase(vector<Purchase> &purchase_list);

void showMember(vector<Member> &member_list);
void showLecture(vector<Lecture> &lecture_list);
void showPurchase(vector<Purchase> &purchase_list);

int main(void) {
	vector<Member> member_list;
	vector<Lecture> lecture_list;
	vector<Purchase> purchase_list;

	if (!readMember(member_list) || !readLecture(lecture_list) || !readPurchase(purchase_list))
		return 0;
	
	cout << "**** ShowMember call ****" << endl;
	showMember(member_list);

	cout << "**** ShowLecture call ****" << endl;
	showLecture(lecture_list);

	cout << "**** ShowPurchase call ****" << endl;
	showPurchase(purchase_list);

	return 0;
}

bool readMember(vector<Member> &member_list) {
	ifstream ifs("listOfMember.txt");
	if (ifs.fail()) {
		cout << "listOfMeber.txt open error!" << endl;
		return false;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int i = 0; i < n; i++) {
		Member m;
		ifs >> m;
		member_list.push_back(m);
	}
	return true;
}

bool readLecture(vector<Lecture> &lecture_list) {
	ifstream ifs("listOfLecture.txt");
	if (ifs.fail()) {
		cout << "listOfLecture.txt open error!" << endl;
		return false;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int i = 0; i < n; i++) {
		Lecture l;
		ifs >> l;
		lecture_list.push_back(l);
	}
	return true;
}

bool readPurchase(vector<Purchase> &purchase_list) {
	ifstream ifs("listOfPurchase.txt");
	if (ifs.fail()) {
		cout << "listOfPurchase.txt open error!" << endl;
		return false;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int i = 0; i < n; i++) {
		Purchase p;
		ifs >> p;
		purchase_list.push_back(p);
	}
	return true;
}

void showMember(vector<Member> &member_list) {
	for (int i = 0; i<10; i++)
		cout << member_list[i] << endl;
	cout << endl;
}

void showLecture(vector<Lecture> &lecture_list) {
	for (int i = 0; i<10; i++)
		cout << lecture_list[i] << endl;
	cout << endl;
}

void showPurchase(vector<Purchase> &purchase_list) {
	for (int i = 0; i<10; i++)
		cout << purchase_list[i] << endl;
	cout << endl;
}