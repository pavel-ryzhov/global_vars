#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
string ch;
string path;
string filename;
cin >> path;

ifstream infile(path.c_str());
if(infile.is_open()){
while(!infile.eof()) {
	getline(infile, ch);
	filename += ch += "\n";
}
infile.close();

} else{
      cout << "Can't open the file!" << endl; }

//...........................................................
int pos0;
  pos0 = filename.find ("%@@@@@@@@@%......%@%");
  if (pos0 == -1) {
	  cout << ""; }
  else {
    cout << "0"; }

  int pos7;
  pos7 = filename.find ("@@@@@@@@@@@@@@@");
  if (pos7 == -1) {
	  cout << ""; }
  else {
    cout << "7"; }

  int pos1;
  pos1 = filename.find (".%@@@@@@@@@@%.");
  if (pos1 == -1) {
	  cout << ""; }
  else {
    cout << "1"; }


  int pos2;
  pos2 = filename.find ("@@@@@@@@@@@@@@@.....@@@@@@@@@@@@@@");
  if (pos2 == -1) {
	  cout << ""; }
  else {
    cout << "2"; }

  int pos3;
  pos3 = filename.find ("@@.............@@@@");
  if (pos3 == -1) {
	  cout << ""; }
  else {
    cout << "2"; }

  int pos4;
  pos4 = filename.find ("@@@@@@@@@@@@@@@@@.");
  if (pos4 == -1) {
	  cout << ""; }
  else {
    cout  << "4"; }

  int pos5;
  pos5 = filename.find ("@@@@@@@@@@@@....@@@@@@@@");
  if (pos5 == -1) {
	  cout << ""; }
  else {
    cout << "5"; }

  int pos6;
  pos6 = filename.find ("@@..@@@@@@");
  if (pos6 == -1) {
	  cout << ""; }
  else {
    cout << "6"; }


  int pos8;
  pos8 = filename.find ("#@@@@%.....#@%");
  if (pos8 == -1) {
	  cout << ""; }
  else {
    cout << "8"; }

int pos9;
  pos9 = filename.find ("@@@..........@@@");
  if (pos9 == -1) {
	  cout << ""; }
  else {
    cout << "9"; }


	return 0;
}