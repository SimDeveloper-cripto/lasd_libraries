
#ifndef MYTEST_HPP
#define MYTEST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../list/list.hpp"
#include "../vector/vector.hpp"
#include "../hashtable/hashtable.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"

#include <iostream>

template<typename Data>
void printHash(Data&, void*);

template<typename Data>
void fold(const Data&, const void*, void*);

int getHashSize();
int getHashImplType();
int getHashTypeData();

template<typename Data>
lasd::Vector<Data> generateRandom(int);

template<>
lasd::Vector<int> generateRandom(int);

template<>
lasd::Vector<double> generateRandom(int);

template<>
lasd::Vector<std::string> generateRandom(int);

// TYPE-CHECKING DEI DATI PER LE STRUTTURE
template<typename Data>
Data& getTypeData(Data& d) { return d; }

template<typename Data>
inline bool isInteger(Data& d) { return false; } 

template<>
inline bool isInteger<int>(int& d) { return true; }

template<typename Data>
inline bool isDouble(Data& d) { return false; } 

template<>
inline bool isDouble<double>(double& d) { return true; }

template<typename Data>
inline bool isString(Data& d) { return false; }

template<>
inline bool isString<std::string>(std::string& d) { return true; }

template<typename Data>
void ifExists(lasd::TestableContainer<Data>&);

template<typename Data>
void InsertElement(lasd::HashTable<Data>&);

template<typename Data>
void RemoveElement(lasd::HashTable<Data>&);

template<typename Data>
void populateLinearContainer(lasd::List<Data>&, int);

template<typename Data>
void exampleTest(lasd::HashTable<Data>&, Data& first_element_typedata);

void startTest();

/* ************************************************************************** */

#endif