/*
 * string1.h - исправлненное и расширенное объявление строкового класса
 *
 *  Created on: 24 янв. 2020 г.
 *      Author: s.semenchuk
 */

#ifndef STRING1_H_
#define STRING1_H_
#include <iostream>

using std::ostream;
using std::istream;

class String {
private:
	char * str;						// указатель
	int len;						// длина строки
	static int num_strings;			// количество объектов
	static const int CINLIM = 80;	// предел ввода для cin
public:
	// Конструкторы и другие методы
	String(const char * s); 		// конструктор
	String();						// конструктор по умолчанию
	String(const String &);			// конструктор копирования
	~String();
	int length() const {return len;}

	// Методы перегруженных операций
	String & operator=(const String &);
	String & operator=(const char *);
	char & operator[](int i);
	const char & operator[](int i) const;

	// Дружественные функции перегруженных операций
	friend bool operator<(const String &st, const String &st2);
	friend bool operator>(const String &st1, const String &st2);
	friend bool operator==(const String &st, const String &st2);
	friend ostream & operator<<(ostream & os, const String & st);
	friend istream & operator>>(istream & is, String & st);

	// Статическая функция
	static int HowMany();
};

#endif /* STRING1_H_ */
