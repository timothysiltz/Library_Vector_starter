#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../includes_usr/fileIO.h"

using namespace std;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char *filename) {
	books.clear();

	ifstream myfile;
	myfile.open(filename);

	if (!myfile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	string line;
	string id;
	string state;
	string loanstatus;
	book b;

	while (getline(myfile, line)) {
		stringstream ss(line);

		getline(ss, id, ',');
		b.book_id = stoi(id);
		getline(ss, b.title, ',');
		getline(ss, b.author, ',');
		getline(ss, state, ',');
		b.state = static_cast<book_checkout_state>(stoi(state));
		getline(ss, loanstatus, ',');
		b.loaned_to_patron_id = stoi(loanstatus);

		books.push_back(b);
	}

	if(books.size() == 0){
		return NO_BOOKS_IN_LIBRARY;
	}

	if(myfile.is_open()){
		myfile.close();
	}

	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char *filename) {
	if (books.size() == 0) {
		return NO_BOOKS_IN_LIBRARY;
	}

	ofstream myfile;
	myfile.open(filename);

	if (!myfile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	string mybooks;

	for(int i = 0; i < books.size(); ++i){
		mybooks = to_string(books[i].book_id) + "," + books[i].title + "," +
			books[i].author + "," + to_string(books[i].state) + "," +
			to_string(books[i].loaned_to_patron_id);

		myfile << mybooks << endl;
	}

	if(myfile.is_open()){
		myfile.close();
	}

	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char *filename) {
	patrons.clear();

	ifstream myfile;
	myfile.open(filename);

	if (!myfile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	string line;
	string id;
	string checked;
	patron p;

	while (getline(myfile, line)) {
		stringstream ss(line);

		getline(ss, id, ',');
		p.patron_id = stoi(id);
		getline(ss, p.name, ',');
		getline(ss, checked, ',');
		p.number_books_checked_out = stoi(checked);

		patrons.push_back(p);
	}

	if (patrons.size() == 0) {
		return NO_PATRONS_IN_LIBRARY;
	}

	if (myfile.is_open()){
		myfile.close();
	}

	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char *filename) {
	if (patrons.size() == 0) {
		return NO_PATRONS_IN_LIBRARY;
	}

	ofstream myfile;
	myfile.open(filename);

	if (!myfile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	string myPatrons;

	for(int i = 0; i < patrons.size(); ++i){
		myPatrons = to_string(patrons[i].patron_id) + "," + patrons[i].name
			+ "," +	to_string(patrons[i].number_books_checked_out);

		myfile << myPatrons << endl;
	}

	if (myfile.is_open()){
		myfile.close();
	}

	return SUCCESS;
}
