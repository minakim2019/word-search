/*
hashTable.cpp
Mina Kim, mk3bnb
2/29/2020
*/

#include "hashTable.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

hashTable::hashTable(int size){
  table.resize(size);
  htsize = size;
  
}
bool hashTable::contains(string s){
  list<string> chain = table.at(hash(s));
  for(list<string>::iterator i = chain.begin(); i != chain.end(); i++){
    string element = *i;
    if(element == s){
      return true;
    }
  }
  return false;
}

void hashTable::insert(string s){
  if(contains(s)){ //check for duplicate
    return;
  }
  int index = hash(s);
  table.at(index).push_back(s); //if not found, insert
}
//returns index that the string hashed to
int hashTable::hash(string s){
  int numCharacters = s.size();
  unsigned int sum = 0;

  //array of powers of 37 for efficiency
  int arr[numCharacters];
  int power = 1;
  for(int k = 0; k < numCharacters; k++){
    arr[k] = power;
    power *= 37;
  } 
  //hash function #3,  given in slide 5.13
  for(int i = 0; i < numCharacters; i++){
    sum += s[i]*arr[i]; 
  }
  return sum % htsize;
}

bool checkprime(unsigned int p) {
    if ( p <= 1 ) // 0 and 1 are not primes; the are both special cases
        return false;
    if ( p == 2 ) // 2 is prime
        return true;
    if ( p % 2 == 0 ) // even numbers other than 2 are not prime
        return false;
    for ( int i = 3; i*i <= p; i += 2 ) // only go up to the sqrt of p
        if ( p % i == 0 )
            return false;
    return true;
}

int getNextPrime (unsigned int n) {
    while ( !checkprime(++n) );
    return n; // all your primes are belong to us
}
