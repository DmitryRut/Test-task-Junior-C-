#pragma once

#include<string>
#include <fstream>
#include <iostream>
#include <vector>

struct ListNode { // ListNode модифицировать нельзя
	ListNode* prev = nullptr; // указатель на предыдущий элемент или nullptr
	ListNode* next = nullptr;
	ListNode* rand = nullptr; // указатель на произвольный элемент данного списка, либо `nullptr`
	std::string data; // произвольные пользовательские данные
};

class LinkedList
{
	ListNode * head, * tail;
	unsigned long size{0};
	bool is_empty() const;
	void add_node(std::string& str);

	public:
	LinkedList();
	~LinkedList();
	void printList() const;
	void deserial(const std::string &file_in,std::vector<long>& rand_indexes);
	void serial(const std::string &file_out, std::vector<long>& rand_indexes);
	void serial2(const std::string& file_out, std::vector<long>& rand_indexes);

};
