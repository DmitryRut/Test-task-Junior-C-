#include "LinkedList.h"

int main()
{
	LinkedList text_list;
	std::vector<long> rand_indexes; // вектор индексов rand

	text_list.deserial("inlet.in", rand_indexes); //чтение из текстового файла
	text_list.serial("outlet.out", rand_indexes); //сериализация в бинарный файл
	text_list.serial2("test.txt", rand_indexes); // запись в текстовый файл для проверки
	text_list.printList(); //печать в консоль для проверки
}

