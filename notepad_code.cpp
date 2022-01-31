#include"Header.h"
#include<iostream>
#include <string>
#include <fstream>
#include<ctime> 
#include <stdio.h>
#include <time.h>
#pragma warning(disable : 4996)
using namespace std;

void color()
{
	int col = 0;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 11);
	cout << "----------------------------------------------------------------" << endl;
	cout << "                Choose a color to print your note  " << endl;
	cout << "1__for Blue               2__for Green           3__for Cyan" << endl;
	cout << "4__for Red                5__for Magenta         6__for Brown" << endl;
	cout << "9__for LightBlue          14__for Yellow         12__for LightRed" << endl;
	cout << "                          15__for white" << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << "-> ";
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 15);
	cin >> col;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (col == 1)
	{
		SetConsoleTextAttribute(h, 1);
	}
	else if (col == 2)
	{
		SetConsoleTextAttribute(h, 2);
	}
	else if (col == 3)
	{
		SetConsoleTextAttribute(h, 3);
	}
	else if (col == 4)
	{
		SetConsoleTextAttribute(h, 4);
	}
	else if (col == 5)
	{
		SetConsoleTextAttribute(h, 5);
	}
	else if (col == 6)
	{
		SetConsoleTextAttribute(h, 6);
	}
	else if (col == 14)
	{
		SetConsoleTextAttribute(h, 14);
	}
	else if (col == 15)
	{
		SetConsoleTextAttribute(h, 15);
	}
	else if (col == 9)
	{
		SetConsoleTextAttribute(h, 9);
	}
	else if (col == 12)
	{
		SetConsoleTextAttribute(h, 12);

	}
	return;
}

class doublyLinkedList
{
private:
	//class node
	class node
	{
	public:
		char data;
		node* next;
		node* prev;
		node()
		{
			data = '\0';
			next = prev = nullptr;
		}
		node(char d)
		{
			data = d;
			next = prev = nullptr;
		}
	};
	//end
	node* head;
	node* tail;
	node* cursorPos;
	int curr = 0, textSize;
public:
	doublyLinkedList() //constructor
	{
		head = new node; //dummy head
		tail = new node; //dummy tail
		head->data = ' ';
		//head->next = tail;
		head->prev = NULL;
		tail->next = NULL;
		tail->prev = head;
		cursorPos = NULL;
		textSize = 0;
	}
	doublyLinkedList(node* h, node* t, node* c, int s)
	{
		head = h;
		tail = t;
		cursorPos = c;
		textSize = s;
	}
	doublyLinkedList& operator=(const doublyLinkedList& obj)
	{
		head = obj.head;
		tail = obj.tail;
		cursorPos = obj.cursorPos;
		return *this;
	}
	void moveCursorRight() {//right arrow
		if (cursorPos != tail) {
			cursorPos = cursorPos->next;
			curr++;
		}
		gotoxy(curr, 0);
	}
	void moveCursorLeft() {//left arrow
		if (cursorPos != head->prev)
			cursorPos = cursorPos->prev;
		curr--;
		if (cursorPos == head->prev)
			curr = 0;
		gotoxy(curr, 0);
	}
	void insertAchar(char const element) //insertion of a single char
	{
		node* in = new node;
		in->data = element;
		if (textSize == 0) { //null
			head->next = in;
			in->prev = head;
			tail->prev = in;
			in->next = tail;
			head = tail = in;
			curr = 1;
		}
		else if (cursorPos == head->prev) {
			head->prev->next = in;
			in->prev = head->prev;
			head->prev = in;
			in->next = head;
			head = in;
			curr = 1;
		}
		else if (cursorPos == tail) { //insert at end
			in->next = tail->next;
			in->prev = tail;
			tail->next->prev = in;
			tail->next = in;
			tail = in;
			curr = textSize + 1;
		}
		else {
			in->next = cursorPos->next;
			in->prev = cursorPos;
			cursorPos->next->prev = in;
			cursorPos->next = in;
			curr++;
		}
		cursorPos = in;
		textSize++;
	}
	void delCharAtCursorPos() {//when bksp pressed
		if (textSize != 0) {
			if (textSize == 1) {
				node* del = head;
				//head->prev->next= head->next;
				head = head->next;
				head = head->prev;
				tail = head->next;
				delete del;
				cursorPos = NULL;
				textSize = 0;
				curr = 0;
			}
			else if (cursorPos == head && cursorPos != tail) {
				node* del = head;
				head->prev->next = head->next;
				head->next->prev = head->prev;
				head = head->next;
				delete del;
				cursorPos = head;
				textSize--;
				curr = 1;
			}
			else if (cursorPos != head && cursorPos == tail) {
				node* del = tail;
				tail->prev->next = tail->next;
				tail->next->prev = tail->prev;
				tail = tail->prev;
				cursorPos = tail;
				delete del;
				textSize--;
				curr = textSize;
			}
			else if (cursorPos != head->prev) {
				node* del = cursorPos;
				cursorPos->prev->next = cursorPos->next;
				cursorPos->next->prev = cursorPos->prev;
				cursorPos = cursorPos->prev;
				delete del;
				textSize--;
				curr--;
			}
		}
	}
	void print()
	{
		system("CLS");
		if (textSize != 0) {
			for (node* i = head->prev; i != tail->next; i = i->next)
				cout << i->data;
		}
		gotoxy(curr, 0);
	}
	inline bool textToLeft() {
		return (cursorPos != NULL && cursorPos->prev != NULL);
	}
	inline bool textToRight() {
		return (cursorPos != NULL);
	}
	void Print() {
		node* ptr = head;
		while (ptr != nullptr) {
			cout << ptr->data;
			ptr = ptr->next;
		}
		cout << endl;
	}
	int getListSize()
	{
		node* ptr = head;

		int count = 0;
		while (ptr != nullptr)
		{
			count++;
			ptr = ptr->next;
		}
		return count;
	}
	void setListSize(int s)
	{
		textSize = s;
	}
	char* GetList(int count) {

		node* ptr = head;

		char* arr = new char[count];
		for (int i = 0; i < count; i++) {
			arr[i] = ptr->data;
			ptr = ptr->next;
		}
		arr[count] = '\0';
		return arr;
	}
	~doublyLinkedList() {//delete the list
		for (node* i = head; i != NULL; i = i->next) {
			delete i->prev;
			i->prev = NULL;
		}
	};

};//end of doubly Linked List

class Notepad
{
private:

	class Note // each node of AVL is a note
	{
	public:

		//public data members of class note
		int IdOfNote; //each node has a unique ID
		Note* lChild;
		Note* rChild;
		doublyLinkedList dataOfNote; //making list object
		char* timeOfNote;
		int height;
		Note() //default constructor
		{
			lChild = nullptr;
			rChild = nullptr;
			IdOfNote = 0;
			timeOfNote = nullptr;
			height = 0;
		}
		void SetID(int id) {
			IdOfNote = id;
		}
		void setDoubly(char* arr)
		{
			for (int i = 0; arr[i] != '\0'; i++)
			{
				dataOfNote.insertAchar(arr[i]);
			}
		}
		void Input()
		{
			int key = 0, count = 0, n = 0;
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(h, 14);
			cout << "Press ESC(escape) to exit your note.\nYou can start writing your note " << endl;
			h = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(h, 15);
			key = _getch();
			while (key != ESCAPE)
			{
				if (SPECIAL_KEY(key)) {
					key = _getch();
					switch (key) {
					case ARROW_LEFT:
						if (dataOfNote.textToLeft()) {
							moveScreenCursorLeft();
							dataOfNote.moveCursorLeft();
						}
						break;
					case ARROW_RIGHT:
						if (dataOfNote.textToRight()) {
							moveScreenCursorRight();
							dataOfNote.moveCursorRight();
						}
						break;
					};
				}
				else if (key == BACKSPACE) {
					if (count == 2)
						count = 0;
					dataOfNote.delCharAtCursorPos();
					dataOfNote.print();
				}
				else {
					if (count == 2)
						count = 0;
					dataOfNote.insertAchar(char(key));
					dataOfNote.print();
				}
				key = _getch();
			}
		}
		int getIdOfNote()
		{
			return IdOfNote;
		}
		void setId(int x)
		{
			IdOfNote = x;
		}
		void Print() {
			//color();
			cout << "ID: " << IdOfNote << endl;
			cout << "Time of Insertion: ";
			cout << timeOfNote << endl;
			cout << "Note: " << endl;
			dataOfNote.Print();
			cout << "--------------------------------------------------------------" << endl;
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(h, 15);
		}
		void setTime(char* time)
		{
			int size = strlen(time);
			timeOfNote = new char[size];
			for (int i = 0; i < size; i++)
			{
				timeOfNote[i] = time[i];
			}
			timeOfNote[size] = '\0';
		}
		char* GetSystemTime() {
			time_t my_time = time(NULL);
			return ctime(&my_time);
		}
		char* getTime()
		{
			return timeOfNote;
		}
		void filing(const char* filename) {
			ofstream file;
			file.open(filename, ios_base::app);
			int size = dataOfNote.getListSize();
			char* arr = dataOfNote.GetList(size);
			int id = getIdOfNote();
			file << id << endl;
			file << arr << endl;
			file << getTime() << endl;
			file.close();
		}
	};
	Note* root;
	int NoOfNotes;
public:
	Note* returnNote()
	{
		Note* ptr = new Note;
		Note* temp = new Note;
		int id;
		while (temp != nullptr) {
			cout << "Enter ID of the note: " << endl;
			id;
			cin >> id;
			temp = SearchID(id);
			if (temp != nullptr) {
				cout << "ID already exists, enter another ID please " << endl;
			}
		}
		ptr->setId(id);
		ptr->Input();
		ptr->setTime(ptr->GetSystemTime());

		//ptr->timeOfNote = ptr->GetSystemTime();
		return ptr;
	}
	Notepad()
	{
		root = nullptr;

		NoOfNotes = 0;
	}
	Notepad(Note* temp)
	{
		NoOfNotes = 0;
		root = temp;

	}
	Notepad(Notepad& obj)
	{
		root = obj.root;

		NoOfNotes = obj.NoOfNotes;
	}
	bool isEmpty()
	{
		if (root == nullptr)
		{
			return true;
		}
		else
			return false;
	}
	int maximum(int a, int b)
	{
		if (a > b)
			return a;
		else
			return b;
	}
	int height(Note* temp) //function to calculate height
	{
		int h = 0;
		if (temp == nullptr)
		{
			return 0;
		}
		else
		{
			int l_height = height(temp->lChild);
			int r_height = height(temp->rChild);
			h = maximum(l_height, r_height) + 1;
		}
		return h;
	}
	int diff(Note* temp) //difference of heights of left and right subtrees
	{
		if (temp == nullptr)
			return 0;
		else
		{
			return height(temp->lChild) - height(temp->rChild);
		}
	}
	int diff()
	{
		return diff(root);
	}
	Note* balance(Note*& temp)
	{
		int balFactor = diff(temp);
		if (balFactor > 1) {
			if (diff(temp->lChild) > 0) {
				temp = rotateLeft(temp);
			}
			else
				temp = rotateLeftRight(temp);
		}
		else if (balFactor < -1) {
			if (diff(temp->rChild) > 0) {
				temp = rotateRightLeft(temp);
			}
			else temp = rotateRight(temp);
		}
		return temp;
	}
	Note* Insert(Note*& r, Note* newN) { //inserts a note in avl tree
		if (r == nullptr) {
			r = new Note;
			r = newN;
			r->lChild = nullptr;
			r->rChild = nullptr;
			if (this->root == nullptr) {
				this->root = r;
			}
			NoOfNotes++;
			return r;
		}
		else if (newN->getIdOfNote() < r->IdOfNote) {
			r->lChild = Insert(r->lChild, newN);
			r = balance(r);
		}
		else if (newN->getIdOfNote() >= r->IdOfNote) {
			r->rChild = Insert(r->rChild, newN);
			r = balance(r);
		}
		//NoOfNotes++;
		//return r;
	}
	void InsertFromFile(Note* temp)
	{
		Insert(root, temp);
	}
	void insertNote(string filename) //recursive function that allows to make new note and inserting in avl tree
	{
		Note* ptr = returnNote();
		Insert(root, ptr);
	}
	Note* SearchID(int id, Note* ptr) // searching a note through id and returning note
	{
		if (!isEmpty())
		{
			if (ptr == nullptr) {
				return nullptr;
			}
			if (ptr->getIdOfNote() == id)
			{
				return ptr;
			}
			if (id > ptr->getIdOfNote())
			{
				return SearchID(id, ptr->rChild);
			}
			if (id < ptr->getIdOfNote())
			{
				return SearchID(id, ptr->lChild);
			}
		}
		else
			return nullptr;
	}
	Note* SearchID(int id)
	{
		return SearchID(id, root);
	}
	void PrintNote() { //printing a single note searched through id
		if (root == nullptr) {
			cout << "------------------------" << endl;
			cout << "Currently No Notes Exist" << endl;
			cout << "------------------------" << endl;
			return;
		}
		int id;
		cout << "Enter ID of note: " << endl;
		cin >> id;
		Note* temp;
		temp = SearchID(id);
		if (temp != nullptr) {
			//print text
			color();
			temp->Print();
		}
		else {
			cout << "Note of this ID does not exist" << endl;
		}
	}
	void inorder(Note* p)
	{
		if (!isEmpty())
		{
			if (p == nullptr)
			{
				return;
			}
			inorder(p->lChild);
			p->Print();
			inorder(p->rChild);
		}
		else
			return;
	}
	void PrintNotepad() {
		if (root != nullptr) {
			cout << "--------------------------------------------------------------" << endl;
			inorder(root);
			cout << endl;
		}
		else
		{
			cout << "------------------------" << endl;
			cout << "Currently No Notes Exist" << endl;
			cout << "------------------------" << endl;
		}
	}
	Note* rotateRight(Note* ptr)//left rotation
	{
		Note* temp;
		temp = ptr->rChild;
		ptr->rChild = temp->lChild;
		temp->lChild = ptr;
		return temp;
	}
	Note* rotateLeft(Note* ptr) //right rotation
	{
		Note* temp;
		temp = ptr->lChild;
		ptr->lChild = temp->rChild;
		temp->rChild = ptr;
		return temp;
	}
	Note* rotateLeftRight(Note* ptr) //left subtree of a right subtree
	{

		Note* temp;
		temp = ptr->lChild;
		ptr->lChild = rotateRight(temp);
		return rotateLeft(ptr);
	}
	Note* rotateRightLeft(Note* ptr)//right subtree of a left subtree
	{
		Note* temp;
		temp = ptr->rChild;
		ptr->rChild = rotateLeft(temp);
		return rotateRight(ptr);
	}
	Note* minValueNode(Note* node)
	{
		Note* current = node;

		/* loop down to find the leftmost leaf */
		while (current->lChild != NULL)
			current = current->lChild;

		return current;
	}
	Note* deleteNode(Note* root, int id)
	{
		if (root == NULL)
			return root;

		if (id < root->getIdOfNote())
			root->lChild = deleteNode(root->lChild, id);

		else if (id > root->getIdOfNote())
			root->rChild = deleteNode(root->rChild, id);

		else
		{
			if ((root->lChild == NULL) ||
				(root->rChild == NULL))
			{
				Note* temp = root->lChild ?
					root->lChild :
					root->rChild;


				if (temp == NULL)
				{
					temp = root;
					root = NULL;
				}
				else
					*root = *temp;
				delete temp;
				NoOfNotes--;
			}
			else
			{
				Note* temp = minValueNode(root->rChild);

				root->IdOfNote = temp->getIdOfNote();

				root->rChild = deleteNode(root->rChild, temp->getIdOfNote());
			}
		}
		if (root == NULL)
			return root;

		root->height = 1 + max(height(root->lChild), height(root->rChild));

		root = balance(root);
		return root;
	}
	void deletedata(const char* s) {
		if (root == nullptr) {
			cout << "------------------------" << endl;
			cout << "Currently No Notes Exist" << endl;
			cout << "------------------------" << endl;
			return;
		}
		int data;
		cout << "Enter ID of note: " << endl;
		cin >> data;
		Note* temp = SearchID(data);
		if (temp == nullptr)
		{
			cout << "Note of this ID does not exist" << endl;
		}
		else
		{
			deleteFromFile(data, s);
			root = deleteNode(root, data);
			cout << "Note is succesfully deleted" << endl;
		}
	}
	void deleteFromFile(int id, const char* s)
	{
		Note* temp = new Note;

		ofstream newFile;
		newFile.open("temp.txt");

		int num;
		char arr[100], time[100];
		ifstream oldFile; //for reading records
		oldFile.open(s);
		if (oldFile)
		{
			for (int i = 0; i < NoOfNotes; i++)
			{
				oldFile >> num;
				oldFile.ignore(100, '\n');
				oldFile.getline(arr, 1000, '\n');
				oldFile.getline(time, 1000, '\n');
				if (num != id)
				{

					newFile << num << endl;
					newFile << arr << endl;
					newFile << time << endl;
					newFile << endl;
				}
			}
			oldFile.close();
		}
		newFile.close();
		remove(s);
		rename("temp.txt", s);
		//checkIfempty(s);
	}
	bool is_empty(std::ifstream& pFile)
	{
		return pFile.peek() == std::ifstream::traits_type::eof();
	}
	void writeIntoFile(Note* p, const char* s) {

		if (!isEmpty())
		{
			if (p == nullptr)
			{
				return;
			}
			writeIntoFile(p->lChild, s);
			p->filing(s);
			writeIntoFile(p->rChild, s);
		}
		else
			return;
	}
	void writeIntoFile(const char* s) {
		writeIntoFile(root, s);
	}
	void UpdateNote(const char* s) {
		if (root == nullptr) {
			cout << "------------------------" << endl;
			cout << "Currently No Notes Exist" << endl;
			cout << "------------------------" << endl;
			return;
		}
		int id;
		cout << "Enter ID of note: " << endl;
		cin >> id;
		Note* temp = SearchID(id);
		if (temp != nullptr) {
			temp->Input();
			temp->timeOfNote = temp->GetSystemTime();
			system("CLS");
		}
		else {
			cout << "Note of this ID does not exist" << endl;
		}
	}
	void loadExistingNotes(const char* filename)
	{
		ifstream f;
		f.open(filename);
		if (is_empty(f) != true)
		{
			ifstream fin(filename);
			char time[100];
			char arr[1000];
			int num = 0;
			if (fin.is_open())
			{

				ifstream numFile("numofnotes.txt");
				int s = 0;
				numFile >> s;
				//cout << NoOfNotes;
				for (int i = 0; i < s; i++)
				{
					Note* temp = new Note;
					fin >> num;
					temp->SetID(num);
					fin.ignore(100, '\n');
					fin.getline(arr, 1000, '\n');
					//fin.ignore(100, '\n');
					fin.getline(time, 1000, '\n');
					temp->setTime(time);
					temp->setDoubly(arr);
					InsertFromFile(temp);
					temp = 0;
					delete temp;
				}
				fin.close();

			}
			else
			{
				cout << "------------------------" << endl;
				cout << "Currently No Notes Exist" << endl;
				cout << "------------------------" << endl;
			}
		}

	}
	int returnNumofNotes() {
		//cout << NoOfNotes;
		return NoOfNotes;
	}
	void destroy(Note*& cur) {
		if (cur != nullptr) {

			if ((cur->lChild == nullptr) && (cur->rChild == nullptr)) {
				delete cur;
				cur = nullptr;
			}
			else {
				destroy(cur->lChild);
				destroy(cur->rChild);
			}
		}

		return;
	}
	~Notepad() {//destructor
		destroy(root);
	}
};

int main()
{
	GetConsoleWindowDims();
	int choice = 1, id;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 8);
	cout << "\nN.O.T.E.P.A.D" << endl;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 15);
	Notepad object;
	object.loadExistingNotes("NotePad.txt");
	//cout << "--------------------------------------------------------------" << endl;
	object.PrintNotepad();
	const char* file = "NotePad.txt";
	while (choice != 0) {
		h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 11);
		cout << "| ------------------------------------------------------------ |" << endl;
		cout << "|                   ENTER YOUR CHOICE:                         |" << endl;
		cout << "|                                                              |" << endl;
		cout << "| 1. Insert Note                       2. Search Note and Print|" << endl;
		cout << "| 3. Print NotePad                     4. Update Note          |" << endl;
		cout << "| 5. Delete Note                       0. To exit              |" << endl;
		cout << "| ------------------------------------------------------------ |" << endl;
		cout << "-> ";
		h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 15);
		cin >> choice;

		if (choice == 1) {
			object.insertNote(file);
			cout << endl;
			system("CLS");
		}
		else if (choice == 2) {

			object.PrintNote();
		}
		else if (choice == 3) {
			//Print all notes;
			object.PrintNotepad();
		}
		else if (choice == 4) {
			//update note
			object.UpdateNote(file);

		}
		else if (choice == 5) {
			//get id, delete note

			object.deletedata(file);
		}
		h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 8);
		cout << "\nN.O.T.E.P.A.D" << endl;
		h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 15);
	}
	ofstream newFile;
	newFile.open("numofnotes.txt");
	newFile << object.returnNumofNotes();
	//clear
	std::ofstream ofs;
	ofs.open(file, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	//write in file
	object.writeIntoFile(file);
	return 0;
}