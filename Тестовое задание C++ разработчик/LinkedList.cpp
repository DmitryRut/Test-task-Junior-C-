#include "LinkedList.h"

LinkedList::LinkedList() { // конструктор
	head = tail = nullptr;
}

LinkedList::~LinkedList() { // деструктор
	ListNode* node = head;
	while (head) {
		head = head->next;
		delete node;
		node = head;
	}
	head = tail = nullptr;
	size = 0;
}

void LinkedList::add_node(std::string &str) { // добавление нового элемента в конец списка
	ListNode* node = new ListNode;
	node->data = str;
	if (head == nullptr)
		head = tail = node;
	else {
		tail->next = node;
		node->prev = tail;
		tail = node;
	}
	size++;
} 

bool LinkedList::is_empty() const {
	if (size == 0) return true;
	else return false;
}

void LinkedList::deserial(const std::string &file_in, std::vector<long> &rand_indexes) {
	// десериализаци€ списка из текстового файла
	std::ifstream file(file_in);
	if (!file.is_open()) {
		std::cout << "File is not open" << std::endl;
		return;
	}

	std::string line;
	std::vector<ListNode*> node_pointers; //вектор указателей на элементы списка
	//std::vector<long> rand_indexes - вектор индексов rand

	while (std::getline(file, line)) { // читаем построчно из файла, формируем список
		size_t pos = line.find(';');
		if (pos == std::string::npos) {
			std::cout << "Format string error: " << line << std::endl;
			continue;
		}
		std::string str = line.substr(0, pos); // парсим строку
		long index = stoi(line.substr(pos + 1));
		add_node(str); //добавл€ем новый элемент в список
		rand_indexes.push_back(index); // запоминаем индекс rand у данного элемента списка
		node_pointers.push_back(tail); // добавл€ем новый указатель в вектор указателей на элементы списка
	}

	file.close();
	for (size_t i = 0; i < node_pointers.size(); i++) { // расставл€ем указатели rand, когда имеем полное представление о списке
		if (rand_indexes[i] <= -1 || rand_indexes[i] >= size) continue;
		else node_pointers[i]->rand = node_pointers[rand_indexes[i]];
	}
} 

void LinkedList::serial(const std::string& file_out, std::vector<long>& rand_indexes) {
	// сериализаци€ списка в бинарный файл
	std::ofstream file(file_out, std::ios::binary);
	if (!file.is_open()) {
		std::cout << "Ќе удалось открыть файл дл€ записи: " << file_out << std::endl;
		return;
	}
	if (is_empty()) return;
	ListNode* node = head;
	long i = 0;
	while (node) {
		file.write(reinterpret_cast<const char*>(&(node->data)), sizeof(node->data));
		file.write(reinterpret_cast<const char*>(&rand_indexes[i]), sizeof(rand_indexes[i]));
		node = node->next;
		i++;
	}
}

void LinkedList::serial2(const std::string& file_out, std::vector<long>& rand_indexes) {
	// сериализаци€ списка в текстовый файл дл€ проверки
	std::ofstream file(file_out);
	if (!file.is_open()) {
		std::cout << "Ќе удалось открыть файл дл€ записи: " << file_out << std::endl;
		return;
	}
	if (is_empty()) return;
	ListNode* node = head;
	long i = 0;
	while (node) {
		if (rand_indexes[i] > -1) file << node->data << ";" << rand_indexes[i] << " rand data: " << node->rand->data << "\n";
		else file << node->data << ";" << rand_indexes[i] << " rand data: -1\n";
		node = node->next;
		i++;
	}
}

void LinkedList::printList() const { // функци€ печати списка на консоль
	ListNode* current = head;
	long index = 0;
	while (current) {
		std::cout << "Element " << index << ": data=" << current->data;

		if (current->rand) {
			std::cout << ", rand->data=" << current->rand->data;
		}
		else {
			std::cout << ", rand=nullptr";
		}
		std::cout << std::endl;

		current = current->next;
		++index;
	}
}


