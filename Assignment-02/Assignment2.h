#include <iostream>
#include <fstream> 
#include <string> 
using namespace std;
template <class T>
struct CBID_NODE;
template <class T>
struct CCID_NODE;
template <class T>
struct CCND_NODE;


template <class T>
struct Queue {
	T data;
	Queue* next;
	Queue(T d)
	{
		data = d;
		next = NULL;
	}
};

template <class T>
class DataPipeline {
	Queue<T>* front;
	Queue<T>* rear;
public:

	DataPipeline() {
		front = NULL;
		rear = NULL;
	}

	/*T front() {
		return T();
	}
	T back() {
		return T();
	}*/

	void enqueue(T data) {
		Queue<T>* temp = new Queue<T>(data);
		if (rear == NULL) {
			front = rear = temp;
			return;
		}
		rear->next = temp;
		rear = temp;
	}

	T dequeue() {
		if (front == NULL)
			return "EMPTY";
		Queue<T>* temp = front;
		front = front->next;

		// If front becomes NULL, then 
		// change rear also as NULL 
		if (front == NULL)
			rear = NULL;
		T answer = temp->data;

		delete (temp);
		return answer;
	}

	bool is_empty() {
		if (front == NULL) {
			return true;
		}
		return false;;
	}
};



template <class T>
struct crime_node {
	T data;
	crime_node<T>* next;
	crime_node() {
		next = NULL;
		data = "";
	}
};

template <class T>
struct CCID_NODE {
	T data;
	CCID_NODE<T>* first;
	CCID_NODE<T>* next;
	CCID_NODE<T>* previous;
	crime_node<T>* crimehead;
	CBID_NODE<T>* CBIDlink;
	CCND_NODE<T>* CCNDlink;
	CCID_NODE() {
		next = NULL;
		previous = NULL;
		first = NULL;
		CBIDlink = NULL;
		CCNDlink = NULL;
		data = "";
	}
};
template <class T>
struct telephone_node {
	T data;
	telephone_node<T>* next;
	telephone_node() {
		next = NULL;
	}
};

template <class T>
struct CCND_NODE {
	T data;
	CCND_NODE<T>* next;
	CCND_NODE<T>* previous;
	CBID_NODE<T>* CBIDlink;
	CCID_NODE<T>* CCIDlink;
	telephone_node<T>* telephonehead;
	CCND_NODE() {
		next = NULL;
		previous = NULL;
		CBIDlink = NULL;
		CCIDlink = NULL;
	}
};

template <class T>
struct CBID_NODE {
	T data;
	CBID_NODE<T>* next;
	CBID_NODE<T>* previous;
	CCID_NODE<T>* CCIDlink;
	CCND_NODE<T>* CCNDlink;
	CBID_NODE() {
		next = NULL;
		previous = NULL;
		CCIDlink = NULL;
		CCNDlink = NULL;
	}
};



template <class T>
class AD {
public:
	CBID_NODE<T>* head;
	AD<T>* next;

	AD() {
		head = NULL;
		next = NULL;
	}

	void push_roll(CBID_NODE<T>*& datas) {
		//cout << "here oushing data" << endl;
		CBID_NODE<T>* newnode = new CBID_NODE<T>;
		newnode->CCIDlink = datas->CCIDlink;
		newnode->CCNDlink = datas->CCNDlink;
		newnode->data = datas->data;
		if (head == NULL) {
			newnode->next = NULL;
			newnode->previous = NULL;
			head = newnode;
		}
		else {
			head->previous = newnode;
			newnode->next = head;
			newnode->previous = NULL;
			head = newnode;
		}
		//cout << head->data << endl;
	}

	T top() {
		return head->data;
	}

	T pop() {
		//cout << "asdsaddsa" << endl;
		//cout << head->data << endl;
		CBID_NODE<T>* ptr = head;
		head = head->next;
		return ptr->data;
	}

	CBID_NODE<T>* pops() {
		//cout << "asdsaddsa" << endl;
		//cout << head->data << endl;
		CBID_NODE<T>* ptr = head;
		head = head->next;
		return ptr;
	}

	bool is_empty() {
		if (head == NULL) {
			return true;
		}
		else {
			return false;
		}
	}

	void empty() {
		while (!is_empty()) {
			pop();
		}
	}
};
template <class T>
class Database {
	CBID_NODE<T>* CBIDhead;
	CCID_NODE<T>* CCIDhead;
	CCND_NODE<T>* CCNDhead;
	//AD<T>* alienhead;
	AD<T> alienhead;
	DataPipeline <T> datapipeline;
public:
	Database(const T& filename1, const T& filename2, const T& filename3) {
		CBIDhead = NULL;
		CCIDhead = NULL;
		CCNDhead = NULL;
		//alienhead = NULL;
		/// doing this for CBID-NODE  ///


		/// Doing it for CCID  ///

		string line = "";
		ifstream myfile(filename2);
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				datapipeline.enqueue(line);
			}
			myfile.close();
		}

		else cout << "Unable to open file";
		while (!datapipeline.is_empty())
		{
			CCID_NODE<T>* newnode1 = new CCID_NODE<T>;
			string data1 = datapipeline.dequeue();
			newnode1->data = data1.substr(0, 4);;
			data1 = data1.substr(5, data1.length() - 1);
			newnode1->previous = NULL;
			newnode1->next = CCIDhead;
			if (CCIDhead != NULL)
				CCIDhead->previous = newnode1;
			CCIDhead = newnode1;
			//cout << datapipeline.dequeue() << endl;;


			if (newnode1->crimehead == NULL) {
				crime_node<T>* temp = new crime_node<T>;
				temp->data = data1;
				temp->next = NULL;
				newnode1->crimehead = temp;
				//cout << "Yes is = " << temp->data << endl;
			}
			else {
				crime_node<T>* temp = new crime_node<T>;
				temp->data = data1;
				temp->next = newnode1->crimehead;
				newnode1->crimehead = temp;
			}


		}

		/// Doing for CCND

		line = "";
		ifstream myfile2(filename3);
		if (myfile2.is_open())
		{
			while (getline(myfile2, line))
			{
				datapipeline.enqueue(line);
			}
			myfile2.close();
		}

		else cout << "Unable to open file";
		while (!datapipeline.is_empty())
		{

			string data1 = datapipeline.dequeue();
			CCND_NODE<T>* newnode1 = new CCND_NODE<T>;
			newnode1->data = data1.substr(0, 4);;
			data1 = data1.substr(5, data1.length() - 1);
			newnode1->previous = NULL;
			newnode1->next = CCNDhead;
			if (CCNDhead != NULL)
				CCNDhead->previous = newnode1;
			CCNDhead = newnode1;

			if (newnode1->telephonehead == NULL) {
				telephone_node<T>* temp = new telephone_node<T>;
				temp->data = data1;
				temp->next = NULL;
				newnode1->telephonehead = temp;
				//cout << "Yes is = " << temp->data << endl;
			}
			else {
				telephone_node<T>* temp = new telephone_node<T>;
				temp->data = data1;
				temp->next = newnode1->telephonehead;
				newnode1->telephonehead = temp;
			}


		}


		/// for cbid 
		/// string line;
		ifstream myfile1(filename1);
		if (myfile1.is_open())
		{

			while (getline(myfile1, line))
			{
				datapipeline.enqueue(line);
			}
			myfile1.close();
		}

		else cout << "Unable to open file";
		while (!datapipeline.is_empty())
		{
			CBID_NODE<T>* newnode = new CBID_NODE<T>;
			newnode->data = datapipeline.dequeue();
			newnode->previous = NULL;
			newnode->next = CBIDhead;
			if (CBIDhead != NULL)
				CBIDhead->previous = newnode;
			CBIDhead = newnode;
			//cout << datapipeline.dequeue() << endl;;

		}
		sort();
		ccidlink();
		ccndlink();
		ccndandccidlink();
	}

	void ccidlink() {
		CBID_NODE<T>* temp = CBIDhead;
		CCID_NODE<T>* ptr = CCIDhead;

		while (ptr != NULL) {
			temp = CBIDhead;
			while (temp != NULL) {
				T data1 = temp->data;
				data1 = data1.substr(0, 4);
				if (data1 == ptr->data) {
					//cout << "here" << endl;
					//cout << temp->data << endl;
					ptr->CBIDlink = temp;
					temp->CCIDlink = ptr;
				}
				temp = temp->next;
			}
			ptr = ptr->next;
		}
	}

	void ccndlink() {
		CBID_NODE<T>* temp = CBIDhead;
		CCND_NODE<T>* ptr = CCNDhead;

		while (ptr != NULL) {
			temp = CBIDhead;
			while (temp != NULL) {
				T data1 = temp->data;
				data1 = data1.substr(0, 4);
				if (data1 == ptr->data) {
					//cout << "here" << endl;
					//cout << temp->data << endl;
					ptr->CBIDlink = temp;
					temp->CCNDlink = ptr;
				}
				temp = temp->next;
			}
			ptr = ptr->next;
		}
	}

	void ccndandccidlink() {
		CCID_NODE<T>* ptr = CCIDhead;
		CCND_NODE<T>* ptr2 = CCNDhead;
		while (ptr != NULL) {
			ptr2 = CCNDhead;
			while (ptr2 != NULL) {
				if (ptr->data == ptr2->data) {
					ptr->CCNDlink = ptr2;
					ptr2->CCIDlink = ptr;
					break;
				}
				ptr2 = ptr2->next;
			}
			ptr = ptr->next;
		}

	}
	/*Return a string in following format "Name FName Gender Address Nationality Crimes(if any) Charges punishment fine number network activation_date deactivation_date status"
	Refer to test cases for further clerification*/
	T CBID_Search_by_CNIC(int cnic) {
		T answer = "";
		CBID_NODE<T>* temp = CBIDhead;
		while (temp != NULL) {
			T data3 = temp->data;
			if (data3 != "") {
				int CNIC = 0;
				data3 = data3.substr(0, 4);
				CNIC = stoi(data3);
				if (cnic == CNIC) {
					answer = answer + temp->data;
					if (temp->CCIDlink != NULL) {
						answer += " ";
						answer += temp->CCIDlink->crimehead->data;
					}

					if (temp->CCNDlink != NULL) {
						answer += " ";
						answer += temp->CCNDlink->telephonehead->data;
					}
				}
				//cout << "CNIC is = " << CNIC << endl;
			}
			temp = temp->next;
		}
		answer = answer.substr(5, answer.length());
		//answer = "Hello";


		return answer;
	}

	T CCID_Search_by_CNIC(int cnic) {
		T answer;
		CCID_NODE<T>* ptr = CCIDhead;
		while (ptr != NULL) {
			if (ptr->data != "") {
				int CNIC = stoi(ptr->data);
				if (cnic == CNIC) {
					if (ptr->CBIDlink != NULL) {
						answer += ptr->CBIDlink->data;
						answer += " ";
					}
					answer += ptr->crimehead->data;

					if (ptr->CCNDlink != NULL) {
						answer += " ";
						answer += ptr->CCNDlink->telephonehead->data;
					}


				}
			}
			ptr = ptr->next;
		}
		answer = answer.substr(5, answer.length());
		//cout << "answer is = " << answer << endl;
		return answer;
	}

	T CCND_Search_by_CNIC(int cnic) {
		T answer;
		CCND_NODE<T>* ptr = CCNDhead;
		while (ptr != NULL) {
			if (ptr->data != "") {
				int CNIC = stoi(ptr->data);
				if (cnic == CNIC) {
					if (ptr->CBIDlink != NULL) {
						answer += ptr->CBIDlink->data;
						answer += " ";
					}

					if (ptr->CCIDlink != NULL) {
						answer += ptr->CCIDlink->crimehead->data;
						answer += " ";
					}
					answer += ptr->telephonehead->data;

				}
			}
			ptr = ptr->next;
		}
		answer = answer.substr(5, answer.length());
		//cout << "answer is = " << answer << endl;
		return answer;
	}

	bool updateCBIDName(T Name, int cnic) {
		bool found = false;
		CBID_NODE<T>* ptr = CBIDhead;
		while (ptr != NULL) {
			if (ptr->data != "") {
				T data1 = ptr->data;
				data1 = data1.substr(0, 4);
				int CNIC = stoi(data1);
				if (CNIC == cnic) {
					found = true;
					data1 = ptr->data;
					T answer = removename(ptr->data, Name);
					ptr->data = answer;
					break;
				}
			}
			ptr = ptr->next;
		}
		return found;
	}

	bool updateCBIDFName(T Name, int cnic) {
		bool found = false;
		CBID_NODE<T>* ptr = CBIDhead;
		while (ptr != NULL) {
			if (ptr->data != "") {
				T data1 = ptr->data;
				data1 = data1.substr(0, 4);
				int CNIC = stoi(data1);
				if (CNIC == cnic) {
					found = true;
					data1 = ptr->data;
					T answer = removeFname(ptr->data, Name);
					//cout << "answer is = " << answer << endl;
					ptr->data = answer;
					break;
				}
			}
			ptr = ptr->next;
		}
		return found;
	}

	bool updateCBIDAddress(T Address, int cnic) {
		bool found = false;
		CBID_NODE<T>* ptr = CBIDhead;
		while (ptr != NULL) {
			if (ptr->data != "") {
				T data1 = ptr->data;
				data1 = data1.substr(0, 4);
				int CNIC = stoi(data1);
				if (CNIC == cnic) {
					found = true;
					data1 = ptr->data;
					T answer = removeaddress(ptr->data, Address);
					//cout << "answer is = " << answer << endl;
					ptr->data = answer;
					break;
				}
			}
			ptr = ptr->next;
		}
		return found;
	}
	bool updateCBIDNationality(T Nationality, int cnic) {
		bool found = false;
		CBID_NODE<T>* temp = CBIDhead;
		while (temp != NULL)
		{
			T data1 = temp->data;
			if (data1 != "") {
				data1 = data1.substr(0, 4);
				T data2 = to_string(cnic);
				if (data1 == data2) {
					found = true;
					T data3 = nationality(temp->data, Nationality);
					cout << "data 3 is = " << data3 << endl;
					temp->data = data3;
					break;
				}


			}
			temp = temp->next;
		}

		//cout << "not found = " << endl;
		return found;
	}

	T nationality(T data, T add) {
		T data2;
		int space = 0;
		int i = 0;
		while (data[i] != '\0') {
			i += 1;
			if (data[i] == ' ') {
				space = i;
			}
		}
		data2 = data.substr(0, space);
		data2 = data2 + " " + add;
		// cout << "data is = " << data2 << endl;
		return data2;

	}

	bool addCrime(T cnic, T charges, T punishment, T fine) {
		/*update and return true when crime found else return false*/
		bool found = false;
		CBID_NODE<T>* ptr = CBIDhead;
		while (ptr != NULL) {
			T data1 = ptr->data;
			if (ptr->data != "") {
				data1 = data1.substr(0, 4);
				if (data1 == cnic) {
					found = true;

					CCID_NODE<T>* temp = new CCID_NODE<T>;
					crime_node<T>* crime = new crime_node<T>;
					temp->data = cnic;
					T data2 = "";
					data2 = data2 + charges + " " + punishment + " " + fine;
					crime->data = data2;
					crime->next = NULL;
					temp->crimehead = crime;
					ptr->CCIDlink = temp;
					//cout << ptr->CCIDlink->crimehead->data << endl;

					break;
				}
			}

			ptr = ptr->next;
		}



		return found;
	}
	bool updateCrime(T cnic, T charges, T punishment, T fine) {
		/*update and return true when crime found else return false*/
		bool found = false;
		CBID_NODE<T>* ptr = CBIDhead;
		while (ptr != NULL) {
			T data1 = ptr->data;
			if (ptr->data != "") {
				data1 = data1.substr(0, 4);
				if (data1 == cnic) {
					if (ptr->CCIDlink != NULL) {
						found = true;
						//cout << "found = " << endl;
						T data2 = "";
						data2 = data2 + charges + " " + punishment + " " + fine;
						//cout << "data 2 is = " << data2 << endl;
						ptr->CCIDlink->crimehead->data = data2;

					}

					//cout << ptr->CCIDlink->crimehead->data << endl;

					break;
				}
			}

			ptr = ptr->next;
		}
		return found;

	}
	bool deleteCrime(T cnic, T charges, T punishment, T fine) {
		/*update and return true when crime found else return false*/
		bool found = false;
		CBID_NODE<T>* ptr = CBIDhead;
		while (ptr != NULL) {
			T data1 = ptr->data;
			if (ptr->data != "") {
				data1 = data1.substr(0, 4);
				if (data1 == cnic) {
					if (ptr->CCIDlink != NULL) {
						found = true;
						//cout << "found = " << endl;
						delete ptr->CCIDlink;
						ptr->CCIDlink = NULL;
						if (ptr->CCIDlink == NULL) {
							//cout << "It is = NULL" << endl;
						}

					}

					//cout << ptr->CCIDlink->crimehead->data << endl;

					break;
				}
			}

			ptr = ptr->next;
		}
		return found;
	}

	int addNumber(T cnic, T number) {
		int numbers = 0;
		int numbers1 = checkRegistred_No(cnic);
		if (numbers1 < 4) {
			/*return number of cell-numbers registered on given cnic after adding this number*/
			CCND_NODE<T>* ptr = CCNDhead;
			while (ptr != NULL) {
				if (cnic == ptr->data) {
					telephone_node<T>* temp = new telephone_node<T>;
					T data2 = ptr->telephonehead->data;
					data2 = data2.substr(7, data2.length());
					data2 = number + " " + data2;
					temp->data = data2;
					temp->next = NULL;
					ptr->telephonehead->next = temp;

					string data1 = ptr->CBIDlink->data;
					CCND_NODE<T>* newnode1 = new CCND_NODE<T>;
					newnode1->data = data1.substr(0, 4);;
					data1 = data1.substr(5, data1.length() - 1);
					newnode1->previous = NULL;
					newnode1->next = CCNDhead;
					if (CCNDhead != NULL)
						CCNDhead->previous = newnode1;
					CCNDhead = newnode1;
					newnode1->telephonehead = temp;


					break;
				}

				ptr = ptr->next;
			}
			telephone_node<T>* pptr = ptr->telephonehead;
			while (pptr != NULL) {
				numbers += 1;
				pptr = pptr->next;
			}
		}
		return numbers;
	}
	int checkRegistred_No(T cnic) {
		int number = 0;
		/*return number of cell-numbers registered on given cnic*/
		CCND_NODE<T>* ptr = CCNDhead;
		while (ptr != NULL) {
			if (cnic == ptr->data) {
				T data2 = ptr->telephonehead->data;
				int i = 0;
				int spaces = 0;
				while (data2[i] != '\0') {
					if (data2[i] == ' ') {
						spaces = i;
					}
					i++;
				}

				data2 = data2.substr(spaces + 1, data2.length());
				//cout << "Data 2 is = " << data2 << endl;
				T data3 = "unactive";
				if (data3 == data2) {

				}
				else {
					number += 1;
				}

			}
			ptr = ptr->next;
		}

		//cout << "numbers are = " << number << endl;
		return number;
	}

	T removeaddress(T info, T addaddress) {
		T answer;
		int count = 0;
		int spaces = 0;
		while (spaces < 4) {
			if (info[count] == ' ') {
				spaces += 1;
			}
			count += 1;
		}
		answer = info.substr(0, count - 1);
		info = info.substr(count, info.length());
		count = 0;
		spaces = 0;
		while (spaces < 3) {
			if (info[count] == ' ') {
				spaces += 1;
			}
			count += 1;
		}
		info = info.substr(count, info.length());
		//cout << "info is = " << info << endl;
		answer = answer + " " + addaddress + " " + info;
		//cout << "answer is = " << answer << endl;

		return answer;
	}
	T removeFname(T name, T addname) {
		T answer;
		int count = 0;
		int spaces = 0;
		while (spaces < 2) {
			if (name[count] == ' ') {
				spaces += 1;
			}
			count += 1;
		}
		answer = name.substr(0, count - 1);

		name = name.substr(count, name.length());
		count = 0;
		spaces = 0;
		while (spaces < 1) {
			if (name[count] == ' ') {
				spaces += 1;
			}
			count += 1;
		}
		name = name.substr(count, name.length());
		answer = answer + " " + addname + " " + name;
		//cout << "name is = " << name << endl;
		//cout << "answer is = " << answer << endl;

		return answer;
	}

	T removename(T name, T addname) {
		T cnic = name.substr(0, 4);
		name = name.substr(5, name.length());
		int spaces = 0;
		int count = 0;
		int i = 0;
		while (spaces < 1) {
			if (name[i] == ' ') {
				spaces += 1;
			}
			i += 1;
			count += 1;
		}
		name = name.substr(count, name.length());

		name = cnic + " " + addname + " " + name;
		return name;
	}
	int printcount() {
		CCND_NODE<T>* ptr = CCNDhead;
		int numbers = 0;
		while (ptr != NULL) {
			numbers += 1;
			ptr = ptr->next;
		}
		return numbers;
	}
	T declareAlien(T cnic) {
		T answer;
		CBID_NODE<T>* ptr = CBIDhead;

		while (ptr != NULL) {
			if (ptr->data != "") {
				T data2 = ptr->data;
				T temp = data2;
				//answer = data2;
				data2 = data2.substr(0, 4);
				if (data2 == cnic) {
					//cout << "data2 is = " << data2 << endl;
					//cout << ptr->data << endl;
					answer = temp;
					ptr->previous->next = ptr->next;
					alienhead.push_roll(ptr);
				}
			}
			ptr = ptr->next;
		}

		//cout << "answer is = " << answer << endl;
		return answer;
	}
	bool verifyAlienDBUpdate(T cnic) {
		/*Verify that given CNIC is moved from CBID to AD, Also add test-case for this function yourself*/
		bool found = false;
		while (!alienhead.is_empty()) {
			CBID_NODE<T>* ptr = alienhead.pops();
			T data2 = ptr->data;
			T temp = data2;
			data2 = data2.substr(0, 4);
			//cout << temp << endl;
			if (cnic == data2) {
				found = true;
				alienhead.push_roll(ptr);
				break;
			}
			alienhead.push_roll(ptr);
		}

		return found;

	}
	bool swap(T cnic, T cnic1, T number, T number1) {
		bool found1 = false;
		bool found2 = false;
		CCND_NODE<T>* ptr = CCNDhead;
		CCND_NODE<T>* ptr1 = CCNDhead;

		while (ptr != NULL) {
			if (ptr->data != "") {
				if (ptr->data == cnic) {
					found1 = true;
					break;
				}
			}
			ptr = ptr->next;
		}

		while (ptr1 != NULL) {
			if (ptr1->data != "") {
				if (ptr1->data == cnic) {
					found2 = true;
					break;
				}
			}
			ptr1 = ptr1->next;
		}

		if (found1 == true && found2 == true) {
			T temp = ptr->telephonehead->data;
			ptr->telephonehead->data = ptr1->telephonehead->data;
			ptr1->telephonehead->data = temp;
			return true;
		}
		return false;
	}
	void display() {
		CBID_NODE<T>* ptr = CBIDhead;
		//telephone_node<T>* ptr1 = telephonehead;
		while (ptr != NULL) {
			cout << ptr->data << endl;
			ptr = ptr->next;
		}
	}

	void sort() {
		CBID_NODE<T>* temp = CBIDhead;
		bool swapped = true;
		while (swapped == true) {
			temp = CBIDhead;
			swapped = false;
			while (temp->next != NULL) {
				if (temp->data != "") {
					T data1 = temp->data;
					T data2 = temp->next->data;
					data1 = data1.substr(0, 4);
					data2 = data2.substr(0, 4);
					int t1 = stoi(data1);
					int t2 = stoi(data2);
					if (t1 > t2) {
						T tempdata = temp->data;
						temp->data = temp->next->data;
						temp->next->data = tempdata;
						swapped = true;
					}

				}
				temp = temp->next;
			}

		}


	}

	void Display_AD() {
		/*Display data as instructed in point (xiv) of PDF*/
		AD<T> temp;
		while (!alienhead.is_empty()) {
			CBID_NODE<T>* ptr = alienhead.pops();
			cout << ptr->data << endl;
			temp.push_roll(ptr);
		}

		while (!temp.is_empty()) {
			CBID_NODE<T>* ptr = temp.pops();
			alienhead.push_roll(ptr);
		}

	}
};
/*
int main() {
	string filename1 = "CBID.txt";
	string filename2 = "CCID.txt";
	string filename3 = "CCND.txt";
	Database<string> database(filename1, filename2, filename3);
	//database.display();
	//database.CBID_Search_by_CNIC(3740);
	//database.CCID_Search_by_CNIC(5960);
	//database.CCND_Search_by_CNIC(6287);
	//database.removeaddress("7183 Demelza Penley f 22 Ann Street british", "12 Ann Street");
	//database.updateCBIDName("Alice", 9831);
	//cout<<database.updateCBIDName("Doc", 9832);
	//database.updateCBIDFName("Kevin", 9177);
	//database.updateCBIDAddress("12 Ann Street", 8372);
	//database.addCrime("7564", "Robbery", "2 years in prison", "1000");
	//database.updateCrime("5960", "murder", "20 years in prison", "10000");
	//database.deleteCrime("5960", "burglary", "6 years in prison", "7000");
	//database.addNumber("9630", "123480");
	database.checkRegistred_No("9630");
	//database.updateCBIDNationality("Alienna", 9630);
	//database.declareAlien("7183");
	//cout << database.verifyAlienDBUpdate("7183");
	//database.Display_AD();
}*/

