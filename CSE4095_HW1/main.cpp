#include "Member.h"
#include "Lecture.h"
#include "Purchase.h"
#include <vector>
#include <fstream>
#include "recfile.h"

#define LEN_BUFFER 256
using namespace std;

bool readMember(vector<Member> &member_list);
bool readLecture(vector<Lecture> &lecture_list);
bool readPurchase(vector<Purchase> &purchase_list);

void showMember(vector<Member> &member_list);
void showLecture(vector<Lecture> &lecture_list);
void showPurchase(vector<Purchase> &purchase_list);
void memberTest();
void lectureTest();
void purchaseTest();

int main(void) {
	vector<Member> member_list;
	vector<Lecture> lecture_list;
	vector<Purchase> purchase_list;

	if (!readMember(member_list) || !readLecture(lecture_list) || !readPurchase(purchase_list))
		return 0;
	
	cout << "**** ShowMember call ****" << endl << endl;
	showMember(member_list);

	cout << "**** ShowLecture call ****" << endl << endl;
	showLecture(lecture_list);

	cout << "**** ShowPurchase call ****" << endl << endl;
	showPurchase(purchase_list);

	cout << "**** MemberTest call ****" << endl << endl;
	memberTest();

	cout << "**** LectureTest call ****" << endl << endl;
	lectureTest();

	cout << "**** purchaseTest call ****" << endl << endl;
	purchaseTest();

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

	DelimFieldBuffer buffer('|', LEN_BUFFER);
	RecordFile <Member> MemberFile(buffer);

	MemberFile.Create("fileOfMember.dat", ios::out | ios::trunc);

	for (int i = 0; i < n; i++) {
		Member m;
		ifs >> m;
		int recaddr;

		if ((recaddr = MemberFile.Write(m)) == -1)
			cout << "Write Error!" << endl;

		member_list.push_back(m);
	}
	MemberFile.Close();
	return true;
}

bool readLecture(vector<Lecture> &lecture_list) {
	ifstream ifs("listOfLecture.txt");
	if (ifs.fail()) {
		cout << "listOfLecture.txt open error!" << endl;
		return false;
	}

	DelimFieldBuffer buffer('|', LEN_BUFFER);
	RecordFile <Lecture> LectureFile(buffer);

	LectureFile.Create("fileOfLecture.dat", ios::out | ios::trunc);

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int i = 0; i < n; i++) {
		Lecture l;
		ifs >> l;
		int recaddr;

		if ((recaddr = LectureFile.Write(l)) == -1)
			cout << "Write Error!" << endl;

		lecture_list.push_back(l);
	}
	LectureFile.Close();
	return true;
}

bool readPurchase(vector<Purchase> &purchase_list) {
	ifstream ifs("listOfPurchase.txt");
	if (ifs.fail()) {
		cout << "listOfPurchase.txt open error!" << endl;
		return false;
	}

	DelimFieldBuffer buffer('|', LEN_BUFFER);
	RecordFile <Purchase> PurchaseFile(buffer);

	PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int i = 0; i < n; i++) {
		Purchase p;
		ifs >> p;
		int recaddr;

		if ((recaddr = PurchaseFile.Write(p)) == -1)
			cout << "Write Error!" << endl;

		purchase_list.push_back(p);
	}
	PurchaseFile.Close();
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

void memberTest() {
	DelimFieldBuffer buffer('|', LEN_BUFFER);
	RecordFile <Member> MemberFile(buffer);
	MemberFile.Open("fileOfMember.dat", ios::in);
	
	for (int i = 0; i < 10; i++) {
		Member m;
		MemberFile.Read(m);
		cout << m;
	}
	MemberFile.Close();
}

void lectureTest() {
	DelimFieldBuffer buffer('|', LEN_BUFFER);
	RecordFile <Lecture> LectureFile(buffer);
	LectureFile.Open("fileOfLecture.dat", ios::in);

	for (int i = 0; i < 10; i++) {
		Lecture l;
		LectureFile.Read(l);
		cout << l;
	}
	LectureFile.Close();
}

void purchaseTest() {
	DelimFieldBuffer buffer('|', LEN_BUFFER);
	RecordFile <Purchase> PurchaseFile(buffer);
	PurchaseFile.Open("fileOfPurchase.dat", ios::in);

	for (int i = 0; i < 10; i++) {
		Purchase p;
		PurchaseFile.Read(p);
		cout << p;
	}
	PurchaseFile.Close();
}