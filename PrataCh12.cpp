#include <iostream>
#include <cstdlib>
#include <ctime>
#include "queue.h"
const int MIN_PER_HR = 60;

bool newcustomer(double x); 									// появился ли новый клиент


int main() {
	using std::cin;
	using std::cout;
	using std::endl;
	using std::ios_base;

	// Подготовка
	std::srand(std::time(0));									// случайная инициализация rand()
	cout << "Case Study: Bank of Heather Automatic Teller\n";
	cout << "Enter maximum size of queue: "; 					// ввод максимального размера очереди
	int qs;
	cin >> qs;
	Queue line(qs);
	cout << "Enter the number of simulation hours: ";
	int hours;
	cin >> hours;

	// Эмуляция будет запускать один цикл в минуту
	long cyclemint = MIN_PER_HR * hours;						// количество циклов
	cout << "Enter the average number of customers per hour: ";
	double perhour;												// среднее количество появлений за час
	cin >> perhour;
	double min_per_cust;										// среднее время между появлениями
	min_per_cust = MIN_PER_HR / perhour;
	Item temp;													// данные нового клиенат
	long turnaways = 0;											// не допущены в полную очередь
	long customers = 0;											// присоеденены к очереди
	long served = 0;											// обслужены во время эмуляции
	long sum_line = 0;											// общая длина очереди
	int wait_time = 0;											// время до освобождения банкомата
	long line_wait = 0;											// общее время в очереди

	// Запуск моделирования
	for (int cycle = 0; cycle < cyclemint; cycle++) {
		if (newcustomer(min_per_cust)) {						// есть подошедший клиент
			if (line.isfull()) {
				turnaways++;
			} else {
				customers++;
				temp.set(cycle);								// cycle = время прибытия
				line.enqueue(temp);								// добавление новичка в очередь
			}
		}
		if (wait_time <= 0 && !line.isempty()) {
			line.dequeue(temp);									// обслуживание следующего клиента
			wait_time = temp.ptime();							// в течении wait_time минут
			line_wait += cycle - temp.when();
			served++;
		}
		if (wait_time > 0) {
			wait_time--;
		}
		sum_line += line.queuecount();
	}

	// Вывод результатов
	if (customers > 0) {
		cout << "customers accepted: " << customers << endl; 	// принято клиентов
		cout << " customers served: " << served << endl;		// обслужено клиентов
		cout << " turnaways: " << turnaways << endl; 			// не принято клиентов
		cout << "average queue size: ";							// средний размер очереди
		cout.precision(2);
		cout.setf(ios_base::fixed, ios_base::floatfield);
		cout << (double) sum_line / cyclemint << endl;
		cout << " average wait time: " 							// среднее время ожидания (минут)
			 << (double) line_wait / served << " minutes\n";
	} else
		cout << "No customers!\n";
	cout << "Done!\n";
	return 0;
}

// x = среднее время в минутах между клиентами
// возвращается значение true, если в эту минуту появляется клиент
bool newcustomer(double x) {
	return (std::rand() * x / RAND_MAX < 1);
}
