/*
 * string1.cpp - методы класса String
 *
 *  Created on: 24 янв. 2020 г.
 *      Author: s.semenchuk
 */

#include <cstring>
#include <cctype>
#include "string1.h"
using std::cin;
using std::cout;

// Инициализация статического члена класса
int String::num_strings = 0;

// Статический метод
int String::HowMany() {
	return num_strings;
}

// Методы класса
String::String(const char * s) {		// Создание String из С-строки
	len = std::strlen(s);				// установка размера
	str = new char[len + 1];			// выделение памяти
	std::strcpy(str, s);				// инициализация указателя
	num_strings++;						// корректировка счетчика объектов
}

String::String() { 						// конструктор по умолчанию
	len = 4;
	str = new char[1];
	str[0] = '\0';						// строка по умолчанию
	num_strings++;
}

String::String(const String & st) {
	num_strings++;						// обработка обновления статического члена
	len = st.len;						// длина та же
	str = new char [len + 1];			// выделение памяти
	std::strcpy(str, st.str);			// копирование строки в новое место
}

String::~String() {						// необходимый конструктор
	--num_strings;
	delete [] str;
}

// Методы перегруженных операций
// Присваивание объекта String объекту String
String & String::operator=(const String & st) {
	if (this == &st) {
		return *this;
	}
	delete [] str;
	len = st.len;
	str = new char[len + 1];
	std::strcpy(str, st.str);
	return *this;
}

// Присваивание С-строки объекту String
String & String::operator =(const char * s) {
	delete [] str;
	len = std::strlen(s);
	str = new char[len + 1];
	std::strcpy(str, s);
	return *this;
}

// Доступ для чтения и записи отдельных символов в неконстантном объекте String
char & String::operator[](int i) {
	return str[i];
}

// Доступ только для чтения отдельных символов в констрантном объекте String
const char & String::operator[](int i) const {
	return str[i];
}

// Дружественные функции перегруженных операций
bool operator<(const String & st1, const String &st2) {
	return (std::strcmp(st1.str, st2.str) < 0);
}

bool operator>(const String & st1, const String &st2) {
	return (std::strcmp(st1.str, st2.str) > 0);
}

bool operator==(const String & st1, const String &st2) {
	return (std::strcmp(st1.str, st2.str) == 0);
}

// Простой вывод String
ostream & operator<<(ostream & os, const String & st) {
	os << st.str;
	return os;
}

// Простой ввод String
istream & operator>>(istream & is, String & st) {
	char temp[String::CINLIM];
	is.get(temp, String::CINLIM);
	if (is) {
		st = temp;
	}
	while (is && is.get() != '\n')
	{
		continue;
	}
	return is;
}

String operator+(const String & lhs, const String & rhs) {
	char temp[String::CINLIM]{'\0'};
	std::strcat(temp, lhs.str);
	std::strcat(temp, rhs.str);
	return String(temp);
}

void String::stringlow() {
	for (int i = 0; i < len; i++) {
		str[i] = (char) std::tolower(str[i]);
	}
}

void String::stringup() {
	for (int i = 0; i < len; i++) {
		str[i] = (char) std::toupper(str[i]);
	}
}

int String::chrnum(const char & ch) const {
	int number = 0;
	for (int i = 0; i < len; i++) {
		if (str[i] == ch) {
			number++;
		}
	}
	return number;
}




