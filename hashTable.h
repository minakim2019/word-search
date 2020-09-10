/*
hashTable.h
Mina Kim, mk3bnb
2/29/2020
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <vector>
#include <list>
#include <cstdlib>
#include <iostream>

using namespace std;

class hashTable {
 public:
  hashTable(int size);
  bool contains(string s);
  void insert(string s);
  int hash(string s);

 private:
  int htsize;
  vector<list<string>> table;
  
};
 bool checkprime(unsigned int p);
 int getNextPrime(unsigned int n);

#endif
