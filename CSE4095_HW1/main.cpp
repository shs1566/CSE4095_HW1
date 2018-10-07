#include "Member.h"
#include "Lecture.h"
#include "Purchase.h"
#include <vector>
#include <fstream>
#include "recfile.h"
#include <cstring>

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

void printMenu();

void lecturePurchaseSystem();
void searchRecord();
void insertRecord();
void deleteRecord();
void modifyRecord();

int main(void) {
	vector<Member> member_list;
	vector<Lecture> lecture_list;
	vector<Purchase> purchase_list;

	if (!readMember(member_list) || !readLecture(lecture_list) || !readPurchase(purchase_list))
		return 0;
	
	while (true) {
		int menu;
		printMenu();
		cin >> menu;
		cout << endl;
		switch (menu) {
		case 1:
			showMember(member_list);
			break;
		case 2:
			showLecture(lecture_list);
			break;
		case 3:
			showPurchase(purchase_list);
			break;
		case 4:
			memberTest();
			break;
		case 5:
			lectureTest();
			break;
		case 6:
			purchaseTest();
			break;
		case 7:
			lecturePurchaseSystem();
			break;
		}
	}

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
		cout << m << endl;
	}
	cout << endl;
	MemberFile.Close();
}

void lectureTest() {
	DelimFieldBuffer buffer('|', LEN_BUFFER);
	RecordFile <Lecture> LectureFile(buffer);
	LectureFile.Open("fileOfLecture.dat", ios::in);

	for (int i = 0; i < 10; i++) {
		Lecture l;
		LectureFile.Read(l);
		cout << l << endl;
	}
	cout << endl;
	LectureFile.Close();
}

void purchaseTest() {
	DelimFieldBuffer buffer('|', LEN_BUFFER);
	RecordFile <Purchase> PurchaseFile(buffer);
	PurchaseFile.Open("fileOfPurchase.dat", ios::in);

	for (int i = 0; i < 10; i++) {
		Purchase p;
		PurchaseFile.Read(p);
		cout << p << endl;;
	}
	cout << endl;
	PurchaseFile.Close();
}

void printMenu() {
	cout << "1. showMember" << endl;
	cout << "2. showLecture" << endl;
	cout << "3. showPurchase" << endl;
	cout << "4. memberTest" << endl;
	cout << "5. lectureTest" << endl;
	cout << "6. purchaseTest" << endl;
	cout << "7. lecturePurchaseSystem" << endl << endl;
	cout << "Select Menu : ";
}

void lecturePurchaseSystem() {
	DelimFieldBuffer buffer('|', LEN_BUFFER);
	RecordFile <Member> MemberFile(buffer);
	RecordFile <Lecture> LectureFile(buffer);
	RecordFile <Purchase> PurchaseFile(buffer);

	MemberFile.Open("fileOfMember.dat", ios::in);
	LectureFile.Open("fileOfLecture.dat", ios::in);
	PurchaseFile.Open("fileOfPurchase.dat", ios::in);

	while (true) {
		int menu;
		cout << "1. Search record" << endl;
		cout << "2. Insert record" << endl;
		cout << "3. Delete record" << endl;
		cout << "4. Modify record" << endl;
		cout << "0. Back to menu" << endl << endl;
		cout << ">> ";
		
		cin >> menu;
		cout << endl;
		switch (menu) {
		case 1:
			searchRecord();
			break;
		case 2:
			insertRecord();
			break;
		case 3:
			deleteRecord();
			break;
		case 4:
			modifyRecord();
			break;
		case 0:
			return;
		}
	}	
}

void searchRecord() {
	int menu;
	cout << "1. Search Member" << endl;
	cout << "2. Search Lecture" << endl;
	cout << "3. Search Purchase" << endl;
	cout << "0. Back to menu" << endl << endl;
	cout << ">> ";
	cin >> menu;
	cout << endl;
	if (menu == 1) {
		string id;
		Member m, mRead;
		cout << "Please enter ID of member to search" << endl << endl;
		cout << ">> ";

		cin.ignore();
		getline(cin, id);
		cout << endl;

		m.update_id(id);
		DelimFieldBuffer buffer('|', LEN_BUFFER);
		RecordFile <Member> MemberFile(buffer);
		MemberFile.Open("fileOfMember.dat", ios::in);

		while (MemberFile.Read(mRead) != -1) {
			if (mRead == m) {
				cout << "Serach Result" << endl << endl;
				cout << mRead << endl << endl;
				MemberFile.Close();
				return;
			}
		}
		cout << "No result found" << endl << endl;
		MemberFile.Close();
	}
	if (menu == 2) {
		char lecture_id[LEN_LECTURE_ID + 1];
		Lecture l, lRead;
		cout << "Please enter ID of lecture to search" << endl << endl;
		cout << ">> ";

		cin.ignore();
		cin >> lecture_id;
		cout << endl;

		l.update_lecture_id(lecture_id);
		DelimFieldBuffer buffer('|', LEN_BUFFER);
		RecordFile <Lecture> LectureFile(buffer);
		LectureFile.Open("fileOfLecture.dat", ios::in);

		while (LectureFile.Read(lRead) != -1) {
			if (lRead == l) {
				cout << "Serach Result" << endl << endl;
				cout << lRead << endl << endl;
				LectureFile.Close();
				return;
			}
		}
		cout << "No result found" << endl << endl;
		LectureFile.Close();
	}
	if (menu == 3) {
		char purchase_id[LEN_PURCHASE_ID + 1];
		Purchase p, pRead;
		cout << "Please enter ID of purchase to search" << endl << endl;
		cout << ">> ";

		cin.ignore();
		cin >> purchase_id;
		cout << endl;

		p.update_purchase_id(purchase_id);
		DelimFieldBuffer buffer('|', LEN_BUFFER);
		RecordFile <Purchase> PurchaseFile(buffer);
		PurchaseFile.Open("fileOfPurchase.dat", ios::in);

		while (PurchaseFile.Read(pRead) != -1) {
			if (pRead == p) {
				cout << "Serach Result" << endl << endl;
				cout << pRead << endl << endl;
				PurchaseFile.Close();
				return;
			}
		}
		cout << "No result found" << endl << endl;
		PurchaseFile.Close();
	}
	if (menu == 0)
		return;
}

void insertRecord() {
	int menu;
	cout << "1. Insert member record" << endl;
	cout << "2. Insert lecture record" << endl;
	cout << "3. Insert purchase record" << endl;
	cout << "0. Back to menu" << endl << endl;
	cout << ">> ";
	cin >> menu;
	cout << endl;

	if (menu == 1) {
		string id;
		Member m, mRead;
		cout << "Please enter ID of member to insert" << endl;
		cout << ">> ";

		cin.ignore();
		getline(cin, id);
		cout << endl;

		m.update_id(id);

		DelimFieldBuffer buffer('|', LEN_BUFFER);
		RecordFile <Member> MemberFile(buffer);
		MemberFile.Open("fileOfMember.dat", ios::in);

		while (MemberFile.Read(mRead) != -1) {
			if (mRead == m) {
				cout << "Error : There is already " << id << endl << endl;
				MemberFile.Close();
				return;
			}
		}
		MemberFile.Close();

		MemberFile.Open("fileOfMember.dat", ios::out);
		string password;
		cout << "Enter a password: ";
		getline(cin, password);
		m.update_password(password);

		string name;
		cout << "Enter a name: ";
		getline(cin, name);
		m.update_name(name);

		string phoneNumber;
		cout << "Enter a phoneNumber: ";
		getline(cin, phoneNumber);
		m.update_phoneNumber(phoneNumber);

		string address;
		cout << "Enter a address: ";
		getline(cin, address);
		m.update_address(address);

		char mileage[LEN_MILEAGE];
		memset(mileage, '0', LEN_MILEAGE);
		m.update_mileage(mileage);

		MemberFile.Append(m);
		MemberFile.Close();
		cout << "Member is added sucessfully" << endl << endl;
	}

	if (menu == 2) {
		char lecture_id[LEN_LECTURE_ID + 1];
		Lecture l, lRead;
		cout << "Please enter ID of lecture to insert" << endl;
		cout << ">> ";

		cin.ignore();
		cin >> lecture_id;
		cout << endl;

		l.update_lecture_id(lecture_id);

		DelimFieldBuffer buffer('|', LEN_BUFFER);
		RecordFile <Lecture> LectureFile(buffer);
		LectureFile.Open("fileOfLecture.dat", ios::in);

		while (LectureFile.Read(lRead) != -1) {
			if (lRead == l) {
				cout << "Error : There is already " << lecture_id << endl << endl;
				LectureFile.Close();
				return;
			}
		}
		LectureFile.Close();

		LectureFile.Open("fileOfLecture.dat", ios::out);

		string subject;
		cout << "Enter a subject: ";
		cin.ignore();
		getline(cin, subject);
		l.update_subject(subject);

		char level;
		cout << "Enter a level: ";
		cin >> level;
		l.update_level(level);

		int price;
		cout << "Enter a price: ";
		cin >> price;
		l.update_price(price);

		char extension;
		cout << "Enter a extension: ";
		cin >> extension;
		l.update_extension(extension);

		int due_date;
		cout << "Enter a due date: ";
		cin >> due_date;
		l.update_due_date(due_date);

		string name_of_teacher;
		cout << "Enter a name of teacher: ";
		cin.ignore();
		getline(cin, name_of_teacher);
		l.update_name_of_teacher(name_of_teacher);

		string textbook;
		cout << "Enter a textbook: ";
		getline(cin, textbook);
		l.update_textbook(textbook);

		LectureFile.Append(l);
		LectureFile.Close();
		cout << "Lecture is added sucessfully" << endl << endl;
	}

	if (menu == 3) {
		char purchase_id[LEN_PURCHASE_ID + 1];
		Purchase p, pRead;
		cout << "Please enter ID of purchase to insert" << endl;
		cout << ">> ";

		cin.ignore();
		cin >> purchase_id;
		cout << endl;

		p.update_purchase_id(purchase_id);

		DelimFieldBuffer buffer('|', LEN_BUFFER);
		RecordFile <Purchase> PurchaseFile(buffer);
		RecordFile <Lecture> LectureFile(buffer);
		RecordFile <Member> MemberFile(buffer);

		PurchaseFile.Open("fileOfPurchase.dat", ios::in);

		while (PurchaseFile.Read(pRead) != -1) {
			if (pRead == p) {
				cout << "Error : There is already " << purchase_id << endl << endl;
				PurchaseFile.Close();
				return;
			}
		}
		PurchaseFile.Close();

		PurchaseFile.Open("fileOfPurchase.dat", ios::out);

		LectureFile.Open("fileOfLecture.dat", ios::out);
		char lecture_id[LEN_LECTURE_ID + 1];
		cout << "Enter a lecture id: ";
		cin >> lecture_id;

		Lecture l, lRead;
		bool flag = false;
		l.update_lecture_id(lecture_id);

		while (LectureFile.Read(lRead) != -1) {
			if (lRead == l) {
				p.update_lecture_id(lecture_id);
				flag = true;
				LectureFile.Close();
				break;
			}
		}
		if (!flag) {
			cout << "No such lecture ID " << lecture_id << endl << endl;
			LectureFile.Close();
			PurchaseFile.Close();
			return;
		}

		MemberFile.Open("fileOfMember.dat", ios::out);
		string member_id;
		cout << "Enter a member id: ";
		cin.ignore();
		getline(cin, member_id);

		Member m, mRead;
		flag = false;
		m.update_id(member_id);

		while (MemberFile.Read(mRead) != -1) {
			if (mRead == m) {
				p.update_member_id(member_id);
				flag = true;
				MemberFile.Close();
				break;
			}
		}
		if (!flag) {
			cout << "No such member ID " << member_id << endl << endl;
			MemberFile.Close();
			PurchaseFile.Close();
			return;
		}

		char mileage[LEN_MILEAGE];
		memset(mileage, '0', LEN_MILEAGE);
		p.update_mileage(mileage);

		PurchaseFile.Append(p);
		PurchaseFile.Close();
		cout << "Purchase is added sucessfully" << endl << endl;
	}

	if (menu == 0)
		return;
}

void deleteRecord() {
	int menu;
	cout << "1. Delete Member" << endl;
	cout << "2. Delete Lecture" << endl;
	cout << "3. Delete Purchase" << endl;
	cout << "0. Back to menu" << endl << endl;
	cout << ">> ";
	cin >> menu;
	cout << endl;

	if (menu == 1) {
		string id;
		Member m, mRead;

		cout << "Please enter a ID of member to delete" << endl;
		cout << ">> ";
		cin.ignore();
		getline(cin, id);

		m.update_id(id);
		DelimFieldBuffer buffer('|', LEN_BUFFER);
		RecordFile <Member> MemberFile(buffer);

		DelimFieldBuffer buffer2('|', LEN_BUFFER);
		RecordFile <Purchase> PurchaseFile(buffer2);

		MemberFile.Open("fileOfMember.dat", ios::in);

		int recaddr_member;
		vector<int> delete_recaddr;
		vector<Purchase> delete_purchase;
		while ((recaddr_member = MemberFile.Read(mRead)) != -1) {
			if (mRead == m) {
				MemberFile.Close();

				Purchase p, pRead;
				PurchaseFile.Open("fileOfPurchase.dat", ios::in);

				int recaddr_purchase;
				while ((recaddr_purchase = PurchaseFile.Read(pRead)) != -1) {
					if (id == pRead.get_member_id()) {
						char purchase_id[LEN_PURCHASE_ID + 1];
						strncpy(purchase_id, pRead.get_purchase_id(), LEN_PURCHASE_ID);
						purchase_id[0] = '*';	// delete symbol
						pRead.update_purchase_id(purchase_id);
						delete_recaddr.push_back(recaddr_purchase);
						delete_purchase.push_back(pRead);
					}
				}
				PurchaseFile.Close();

				/* 삭제될 부분을 미리 표시해두고 해당 id의 첫글자를 *로 표기하여 다시 씀 */
				PurchaseFile.Open("fileOfPurchase.dat", ios::out);
				for (int i = 0; i < delete_recaddr.size(); i++)
					PurchaseFile.Write(delete_purchase[i], delete_recaddr[i]);
				PurchaseFile.Close();

				MemberFile.Open("fileOfMember.dat", ios::out);
				id[0] = '*';
				mRead.update_id(id);
				MemberFile.Write(mRead, recaddr_member);
				MemberFile.Close();

				cout << endl << "Delete Success" << endl << endl;
			}
		}
		if (delete_recaddr.size() == 0)
			cout << endl << "No such member id" << endl << endl;
	}

	if (menu == 2) {
		char  lecture_id[LEN_LECTURE_ID + 1];
		Lecture l, lRead;

		cout << "Please enter a ID of lecture to delete" << endl;
		cout << ">> ";
		cin >> lecture_id;

		l.update_lecture_id(lecture_id);
		DelimFieldBuffer buffer('|', LEN_BUFFER);
		RecordFile <Lecture> LectureFile(buffer);

		DelimFieldBuffer buffer2('|', LEN_BUFFER);
		RecordFile <Purchase> PurchaseFile(buffer2);

		LectureFile.Open("fileOfLecture.dat", ios::in);

		int recaddr_lecture;
		vector<int> delete_recaddr;
		vector<Purchase> delete_purchase;
		while ((recaddr_lecture = LectureFile.Read(lRead)) != -1) {
			if (lRead == l) {
				LectureFile.Close();

				Purchase p, pRead;
				PurchaseFile.Open("fileOfPurchase.dat", ios::in);

				int recaddr_purchase;
				while ((recaddr_purchase = PurchaseFile.Read(pRead)) != -1) {
					if (!strncmp(lecture_id, pRead.get_lecture_id(), LEN_LECTURE_ID)) {
						char purchase_id[LEN_PURCHASE_ID + 1];
						strncpy(purchase_id, pRead.get_purchase_id(), LEN_PURCHASE_ID);
						purchase_id[0] = '*';	// delete symbol
						pRead.update_purchase_id(purchase_id);
						delete_recaddr.push_back(recaddr_purchase);
						delete_purchase.push_back(pRead);
					}
				}
				PurchaseFile.Close();

				/* 삭제될 부분을 미리 표시해두고 해당 id의 첫글자를 *로 표기하여 다시 씀 */
				PurchaseFile.Open("fileOfPurchase.dat", ios::out);
				for (int i = 0; i < delete_recaddr.size(); i++)
					PurchaseFile.Write(delete_purchase[i], delete_recaddr[i]);
				PurchaseFile.Close();

				LectureFile.Open("fileOfLecture.dat", ios::out);
				lecture_id[0] = '*';
				lRead.update_lecture_id(lecture_id);
				LectureFile.Write(lRead, recaddr_lecture);
				LectureFile.Close();

				cout << endl << "Delete Success" << endl << endl;
			}
		}

		if (delete_recaddr.size() == 0)
			cout << endl << "No such lecture id" << endl << endl;
	}

	if (menu == 3) {
		char purchase_id[LEN_PURCHASE_ID + 1];
		Purchase p, pRead;

		cout << "Please enter a ID of purchase to delete" << endl;
		cout << ">> ";
		cin >> purchase_id;

		p.update_purchase_id(purchase_id);

		DelimFieldBuffer buffer('|', LEN_BUFFER);
		RecordFile <Purchase> PurchaseFile(buffer);

		PurchaseFile.Open("fileOfPurchase.dat", ios::in);

		int recaddr_purchase;
		bool flag = false;
		while (recaddr_purchase = PurchaseFile.Read(pRead) != -1) {
			if (pRead == p) {
				PurchaseFile.Close();

				flag = true;
				PurchaseFile.Open("fileOfPurchase.dat", ios::out);
				purchase_id[0] = '*';
				pRead.update_purchase_id(purchase_id);
				PurchaseFile.Write(pRead, recaddr_purchase);
				PurchaseFile.Close();

				cout << endl << "Delete Success" << endl << endl;
			}
		}

		if (!flag)
			cout << endl << "No such purchase id" << endl << endl;
	}
}

void modifyRecord() {
	int menu;
	cout << "1. Modify Member record" << endl;
	cout << "2. Modify Lecture record" << endl;
	cout << "3. Modify Purchase record" << endl;
	cout << "0. Back to menu" << endl << endl;
	cout << ">> ";
	cin >> menu;
	cout << endl;

	if (menu == 1) {
		string id;
		Member m, mRead;

		cout << "Please Enter a member ID to modify" << endl;
		cout << ">> ";
		cin.ignore();
		getline(cin, id);
		cout << endl;

		m.update_id(id);

		DelimFieldBuffer buffer('|', LEN_BUFFER);
		RecordFile <Member> MemberFile(buffer);

		MemberFile.Open("fileOfMember.dat", ios::in);

		int recaddr;
		bool flag = false;
		while ((recaddr = MemberFile.Read(mRead)) != -1) {
			if (m == mRead) {
				flag = true;
				MemberFile.Close();

				int select;
				cout << "1. Modify password" << endl;
				cout << "2. Modify name" << endl;
				cout << "3. Modify phoneNumber" << endl;
				cout << "4. Modify address" << endl;
				cout << "5. Modify mileage" << endl;
				cout << "0. Back to menu" << endl << endl;
				cout << ">> ";
				cin >> select;
				cout << endl;

				if (select == 1) {
					string password;
					int len, new_len;
					cout << "Please enter new password" << endl;
					cout << ">> ";
					cin.ignore();
					getline(cin, password);
					cout << endl;

					len = mRead.get_password().length();
					new_len = password.length();

					if (len >= new_len) {
						MemberFile.Close();
						MemberFile.Open("fileOfMember.dat", ios::out);
						password.append(len - new_len, ' ');
						mRead.update_password(password);
						MemberFile.Write(mRead, recaddr);
					}
					else {
						MemberFile.Close();

						/* 기존 record를 삭제 */
						MemberFile.Open("fileOfMember.dat", ios::out);
						string new_id = mRead.get_id();
						string copy = new_id;
						copy[0] = '*';
						mRead.update_id(copy);
						MemberFile.Write(mRead, recaddr);
						MemberFile.Close();

						/* 수정된 record를 새로 추가 */
						MemberFile.Open("fileOfMember.dat", ios::out);
						mRead.update_id(new_id);
						mRead.update_password(password);
						MemberFile.Append(mRead);
						MemberFile.Close();

					}
				}

				else if (select == 2) {
					string name;
					int len, new_len;
					cout << "Please enter new name" << endl;
					cout << ">> ";
					cin.ignore();
					getline(cin, name);
					cout << endl;

					len = mRead.get_name().length();
					new_len = name.length();

					if (len >= new_len) {
						MemberFile.Close();
						MemberFile.Open("fileOfMember.dat", ios::out);
						name.append(len - new_len, ' ');
						mRead.update_name(name);
						MemberFile.Write(mRead, recaddr);
					}
					else {
						MemberFile.Close();

						/* 기존 record를 삭제 */
						MemberFile.Open("fileOfMember.dat", ios::out);
						string new_id = mRead.get_id();
						string copy = new_id;
						copy[0] = '*';
						mRead.update_id(copy);
						MemberFile.Write(mRead, recaddr);
						MemberFile.Close();

						/* 수정된 record를 새로 추가 */
						MemberFile.Open("fileOfMember.dat", ios::out);
						mRead.update_id(new_id);
						mRead.update_name(name);
						MemberFile.Append(mRead);
						MemberFile.Close();
					}
				}

				else if (select == 3) {
					string phoneNumber;
					int len, new_len;
					cout << "Please enter new phoneNumber" << endl;
					cout << ">> ";
					cin.ignore();
					getline(cin, phoneNumber);
					cout << endl;

					len = mRead.get_phoneNumber().length();
					new_len = phoneNumber.length();

					if (len >= new_len) {
						MemberFile.Close();
						MemberFile.Open("fileOfMember.dat", ios::out);
						phoneNumber.append(len - new_len, ' ');
						mRead.update_phoneNumber(phoneNumber);
						MemberFile.Write(mRead, recaddr);
					}
					else {
						MemberFile.Close();

						/* 기존 record를 삭제 */
						MemberFile.Open("fileOfMember.dat", ios::out);
						string new_id = mRead.get_id();
						string copy = new_id;
						copy[0] = '*';
						mRead.update_id(copy);
						MemberFile.Write(mRead, recaddr);
						MemberFile.Close();

						/* 수정된 record를 새로 추가 */
						MemberFile.Open("fileOfMember.dat", ios::out);
						mRead.update_id(new_id);
						mRead.update_phoneNumber(phoneNumber);
						MemberFile.Append(mRead);
						MemberFile.Close();
					}
				}

				else if (select == 4) {
					string address;
					int len, new_len;
					cout << "Please enter new address" << endl;
					cout << ">> ";
					cin.ignore();
					getline(cin, address);
					cout << endl;

					len = mRead.get_address().length();
					new_len = address.length();

					if (len >= new_len) {
						MemberFile.Close();
						MemberFile.Open("fileOfMember.dat", ios::out);
						address.append(len - new_len, ' ');
						mRead.update_address(address);
						MemberFile.Write(mRead, recaddr);
					}
					else {
						MemberFile.Close();

						/* 기존 record를 삭제 */
						MemberFile.Open("fileOfMember.dat", ios::out);
						string new_id = mRead.get_id();
						string copy = new_id;
						copy[0] = '*';
						mRead.update_id(copy);
						MemberFile.Write(mRead, recaddr);
						MemberFile.Close();

						/* 수정된 record를 새로 추가 */
						MemberFile.Open("fileOfMember.dat", ios::out);
						mRead.update_id(new_id);
						mRead.update_address(address);
						MemberFile.Append(mRead);
						MemberFile.Close();
					}
				}

				else if (select == 5) {
					char mileage_char[LEN_MILEAGE];
					string mileage_string;
					int len, new_len;
					cout << "Please enter new mileage" << endl;
					cout << ">> ";
					cin.ignore();
					getline(cin, mileage_string);
					cout << endl;

					memset(mileage_char, '0', LEN_MILEAGE);
					strncpy(mileage_char + LEN_MILEAGE - mileage_string.length(), mileage_string.c_str(), mileage_string.length());

					MemberFile.Close();
					MemberFile.Open("fileOfMember.dat", ios::out);
					mRead.update_mileage(mileage_char);
					MemberFile.Write(mRead, recaddr);

				}

				else if (select == 0)
					return;
			}
		}

		if (!flag)
			cout << "No such id" << endl;
	}

	else if (menu == 2) {
		char lecture_id[LEN_LECTURE_ID + 1];
		Lecture l, lRead;

		cout << "Please Enter a lecture ID to modify" << endl;
		cout << ">> ";
		cin.ignore();
		cin >> lecture_id;
		cout << endl;

		l.update_lecture_id(lecture_id);

		DelimFieldBuffer buffer('|', LEN_BUFFER);
		RecordFile <Lecture> LectureFile(buffer);

		LectureFile.Open("fileOfLecture.dat", ios::in);

		int recaddr;
		bool flag = false;
		while ((recaddr = LectureFile.Read(lRead)) != -1) {
			if (l == lRead) {
				LectureFile.Close();

				int select;
				cout << "1. Modify subject" << endl;
				cout << "2. Modify level" << endl;
				cout << "3. Modify price" << endl;
				cout << "4. Modify extension" << endl;
				cout << "5. Modify due_date" << endl;
				cout << "6. Modify name of teacher" << endl;
				cout << "7. Modify textbook" << endl;
				cout << "0. Back to menu" << endl << endl;
				cout << ">> ";
				cin >> select;
				cout << endl;

				if (select == 1) {
					string subject;
					int len, new_len;
					cout << "Please enter new subject" << endl;
					cout << ">> ";
					cin.ignore();
					getline(cin, subject);
					cout << endl;

					len = lRead.get_subject().length();
					new_len = subject.length();

					if (len >= new_len) {
						LectureFile.Close();
						LectureFile.Open("fileOfLecture.dat", ios::out);
						subject.append(len - new_len, ' ');
						lRead.update_subject(subject);
						LectureFile.Write(lRead, recaddr);
					}
					else {
						LectureFile.Close();

						/* 기존 record를 삭제 */
						LectureFile.Open("fileOfLecture.dat", ios::out);
						char new_id[LEN_LECTURE_ID];
						char copy[LEN_LECTURE_ID];

						strncpy(new_id, lRead.get_lecture_id(), LEN_LECTURE_ID);
						strncpy(copy, lRead.get_lecture_id(), LEN_LECTURE_ID);
						copy[0] = '*';
						lRead.update_lecture_id(copy);
						LectureFile.Write(lRead, recaddr);
						LectureFile.Close();

						/* 수정된 record를 새로 추가 */
						LectureFile.Open("fileOfLecture.dat", ios::out);
						lRead.update_lecture_id(new_id);
						lRead.update_subject(subject);
						LectureFile.Append(lRead);
						LectureFile.Close();

					}
				}

				else if (select == 2) {
					char level;

					cout << "Please enter new level" << endl;
					cout << ">> ";
					cin.ignore();
					cin >> level;
					cout << endl;

					LectureFile.Close();
					LectureFile.Open("fileOfLecture.dat", ios::out);
					lRead.update_level(level);
					LectureFile.Write(lRead, recaddr);

				}

				else if (select == 3) {
					int  price;
					int len, new_len;
					cout << "Please enter new price" << endl;
					cout << ">> ";
					cin.ignore();
					cin >> price;
					cout << endl;

					len = to_string(lRead.get_price()).length();
					new_len = to_string(price).length();

					if (len == new_len) {
						LectureFile.Close();
						LectureFile.Open("fileOfLecture.dat", ios::out);
						lRead.update_price(price);
						LectureFile.Write(lRead, recaddr);
					}
					else {
						LectureFile.Close();

						/* 기존 record를 삭제 */
						LectureFile.Open("fileOfLecture.dat", ios::out);
						char new_id[LEN_LECTURE_ID];
						char copy[LEN_LECTURE_ID];

						strncpy(new_id, lRead.get_lecture_id(), LEN_LECTURE_ID);
						strncpy(copy, lRead.get_lecture_id(), LEN_LECTURE_ID);
						copy[0] = '*';
						lRead.update_lecture_id(copy);
						LectureFile.Write(lRead, recaddr);
						LectureFile.Close();

						/* 수정된 record를 새로 추가 */
						LectureFile.Open("fileOfLecture.dat", ios::out);
						lRead.update_lecture_id(new_id);
						lRead.update_price(price);
						LectureFile.Append(lRead);
						LectureFile.Close();

					}
				}

				else if (select == 4) {
					char extension;

					cout << "Please enter new extension" << endl;
					cout << ">> ";
					cin.ignore();
					cin >> extension;
					cout << endl;

					LectureFile.Close();
					LectureFile.Open("fileOfLecture.dat", ios::out);
					lRead.update_level(extension);
					LectureFile.Write(lRead, recaddr);
				}

				else if (select == 5) {
					int  due_date;
					int len, new_len;
					cout << "Please enter new price" << endl;
					cout << ">> ";
					cin.ignore();
					cin >> due_date;
					cout << endl;

					len = to_string(lRead.get_due_date()).length();
					new_len = to_string(due_date).length();

					if (len == new_len) {
						LectureFile.Close();
						LectureFile.Open("fileOfLecture.dat", ios::out);
						lRead.update_price(due_date);
						LectureFile.Write(lRead, recaddr);
					}
					else {
						LectureFile.Close();

						/* 기존 record를 삭제 */
						LectureFile.Open("fileOfLecture.dat", ios::out);
						char new_id[LEN_LECTURE_ID];
						char copy[LEN_LECTURE_ID];

						strncpy(new_id, lRead.get_lecture_id(), LEN_LECTURE_ID);
						strncpy(copy, lRead.get_lecture_id(), LEN_LECTURE_ID);
						copy[0] = '*';
						lRead.update_lecture_id(copy);
						LectureFile.Write(lRead, recaddr);
						LectureFile.Close();

						/* 수정된 record를 새로 추가 */
						LectureFile.Open("fileOfLecture.dat", ios::out);
						lRead.update_lecture_id(new_id);
						lRead.update_due_date(due_date);
						LectureFile.Append(lRead);
						LectureFile.Close();

					}
				}

				else if (select == 6) {
					string name_of_teacher;
					int len, new_len;
					cout << "Please enter new name of teacher" << endl;
					cout << ">> ";
					cin.ignore();
					getline(cin, name_of_teacher);
					cout << endl;

					len = lRead.get_name_of_teacher().length();
					new_len = name_of_teacher.length();

					if (len >= new_len) {
						LectureFile.Close();
						LectureFile.Open("fileOfLecture.dat", ios::out);
						name_of_teacher.append(len - new_len, ' ');
						lRead.update_name_of_teacher(name_of_teacher);
						LectureFile.Write(lRead, recaddr);
					}
					else {
						LectureFile.Close();

						/* 기존 record를 삭제 */
						LectureFile.Open("fileOfLecture.dat", ios::out);
						char new_id[LEN_LECTURE_ID];
						char copy[LEN_LECTURE_ID];

						strncpy(new_id, lRead.get_lecture_id(), LEN_LECTURE_ID);
						strncpy(copy, lRead.get_lecture_id(), LEN_LECTURE_ID);
						copy[0] = '*';
						lRead.update_lecture_id(copy);
						LectureFile.Write(lRead, recaddr);
						LectureFile.Close();

						/* 수정된 record를 새로 추가 */
						LectureFile.Open("fileOfLecture.dat", ios::out);
						lRead.update_lecture_id(new_id);
						lRead.update_name_of_teacher(name_of_teacher);
						LectureFile.Append(lRead);
						LectureFile.Close();
					}
				}

				else if (select == 7) {
					string textbook;
					int len, new_len;
					cout << "Please enter new textbook" << endl;
					cout << ">> ";
					cin.ignore();
					getline(cin, textbook);
					cout << endl;

					len = lRead.get_textbook().length();
					new_len = textbook.length();

					if (len >= new_len) {
						LectureFile.Close();
						LectureFile.Open("fileOfLecture.dat", ios::out);
						textbook.append(len - new_len, ' ');
						lRead.update_textbook(textbook);
						LectureFile.Write(lRead, recaddr);
					}
					else {
						LectureFile.Close();

						/* 기존 record를 삭제 */
						LectureFile.Open("fileOfLecture.dat", ios::out);
						char new_id[LEN_LECTURE_ID];
						char copy[LEN_LECTURE_ID];

						strncpy(new_id, lRead.get_lecture_id(), LEN_LECTURE_ID);
						strncpy(copy, lRead.get_lecture_id(), LEN_LECTURE_ID);
						copy[0] = '*';
						lRead.update_lecture_id(copy);
						LectureFile.Write(lRead, recaddr);
						LectureFile.Close();

						/* 수정된 record를 새로 추가 */
						LectureFile.Open("fileOfLecture.dat", ios::out);
						lRead.update_lecture_id(new_id);
						lRead.update_textbook(textbook);
						LectureFile.Append(lRead);
						LectureFile.Close();
					}
				}

				else if (select == 0)
					return;
			}
		}
		if (!flag)
			cout << "No such id" << endl;
	}

	else if (menu == 3) {
		char purchase_id[LEN_PURCHASE_ID + 1];
		Purchase p, pRead;

		cout << "Please Enter a purchase ID to modify" << endl;
		cout << ">> ";
		cin.ignore();
		cin >> purchase_id;
		cout << endl;

		p.update_purchase_id(purchase_id);

		DelimFieldBuffer buffer('|', LEN_BUFFER);
		RecordFile <Purchase> PurchaseFile(buffer);

		PurchaseFile.Open("fileOfPurchase.dat", ios::in);

		int recaddr;
		bool flag = false;
		while ((recaddr = PurchaseFile.Read(pRead)) != -1) {
			if (p == pRead) {
				PurchaseFile.Close();

				int select;
				cout << "1. Modify lecture_id" << endl;
				cout << "2. Modify member_id" << endl;
				cout << "3. Modify mileage" << endl;
				cout << "0. Back to menu" << endl << endl;
				cout << ">> ";
				cin >> select;
				cout << endl;

				if (select == 1) {
					char lecture_id_char[LEN_LECTURE_ID];
					string lecture_id_string;
					int len, new_len;
					cout << "Please enter new lecture_id" << endl;
					cout << ">> ";
					cin.ignore();
					getline(cin, lecture_id_string);
					cout << endl;

					memset(lecture_id_char, '0', LEN_LECTURE_ID);
					strncpy(lecture_id_char + LEN_LECTURE_ID - lecture_id_string.length(), lecture_id_string.c_str(), lecture_id_string.length());

					DelimFieldBuffer buffer2('|', LEN_BUFFER);
					RecordFile <Lecture> LectureFile(buffer2);
					Lecture l, lRead;
					l.update_lecture_id(lecture_id_char);
					LectureFile.Open("fileOfLecture.dat", ios::in);

					bool flag2 = false;
					while (LectureFile.Read(lRead) != -1) {
						if (l == lRead) {
							flag2 = true;
							PurchaseFile.Open("fileOfPurchase.dat", ios::out);
							pRead.update_lecture_id(lecture_id_char);
							PurchaseFile.Write(pRead, recaddr);
							PurchaseFile.Close();
						}
					}
					LectureFile.Close();
					if (!flag2)
						cout << "No such lecture id" << endl << endl;
				}

				else if (select == 2) {
					string member_id;
					int len, new_len;
					cout << "Please enter new member_id" << endl;
					cout << ">> ";
					cin.ignore();
					getline(cin, member_id);
					cout << endl;

					len = pRead.get_member_id().length();
					new_len = member_id.length();

					DelimFieldBuffer buffer2('|', LEN_BUFFER);
					RecordFile <Member> MemberFile(buffer2);
					Member m, mRead;

					m.update_id(member_id);
					MemberFile.Open("fileOfMember.dat", ios::in);

					bool flag2 = false;

					while (MemberFile.Read(mRead) != -1) {
						if (m == mRead) {
							flag2 = true;
							if (len >= new_len) {
								PurchaseFile.Close();
								PurchaseFile.Open("fileOfPurchase.dat", ios::out);
								member_id.append(len - new_len, ' ');
								pRead.update_member_id(member_id);
								PurchaseFile.Write(pRead, recaddr);
							}
							else {
								PurchaseFile.Close();

								/* 기존 record를 삭제 */
								PurchaseFile.Open("fileOfPurchase.dat", ios::out);
								char new_id[LEN_PURCHASE_ID];
								char copy[LEN_PURCHASE_ID];

								strncpy(new_id, pRead.get_purchase_id(), LEN_PURCHASE_ID);
								strncpy(copy, pRead.get_purchase_id(), LEN_PURCHASE_ID);
								copy[0] = '*';
								pRead.update_purchase_id(copy);
								PurchaseFile.Write(pRead, recaddr);
								PurchaseFile.Close();

								/* 수정된 record를 새로 추가 */
								PurchaseFile.Open("fileOfPurchase.dat", ios::out);
								pRead.update_purchase_id(new_id);
								pRead.update_member_id(member_id);
								PurchaseFile.Append(pRead);
								PurchaseFile.Close();

							}
						}
					}

					if (!flag2)
						cout << "No such member id" << endl << endl;
				}

				else if (select == 3) {
					char mileage_char[LEN_MILEAGE];
					string mileage_string;
					int len, new_len;
					cout << "Please enter new mileage" << endl;
					cout << ">> ";
					cin.ignore();
					getline(cin, mileage_string);
					cout << endl;

					memset(mileage_char, '0', LEN_MILEAGE);
					strncpy(mileage_char + LEN_MILEAGE - mileage_string.length(), mileage_string.c_str(), mileage_string.length());

					PurchaseFile.Close();
					PurchaseFile.Open("fileOfPurchase.dat", ios::out);
					pRead.update_mileage(mileage_char);
					PurchaseFile.Write(pRead, recaddr);

				}
			}
		}
	}
}
