
#include "utils.hpp"
#include "../deque.hpp"
#include <cstddef>
#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <vector>
#ifndef DEQUE_TESTER_HPP
# define DEQUE_TESTER_HPP
void	deque_test()
{
	system("clear");

	std::cout<<"▓█████▄ ▓█████   █████   █    ██ ▓█████    ▄▄▄█████▓▓█████   ██████ ▄▄▄█████▓\n";
	std::cout<<"▒██▀ ██▌▓█   ▀ ▒██▓  ██▒ ██  ▓██▒▓█   ▀    ▓  ██▒ ▓▒▓█   ▀ ▒██    ▒ ▓  ██▒ ▓▒\n";
	std::cout<<"░██   █▌▒███   ▒██▒  ██░▓██  ▒██░▒███      ▒ ▓██░ ▒░▒███   ░ ▓██▄   ▒ ▓██░ ▒░\n";
	std::cout<<"░▓█▄   ▌▒▓█  ▄ ░██  █▀ ░▓▓█  ░██░▒▓█  ▄    ░ ▓██▓ ░ ▒▓█  ▄   ▒   ██▒░ ▓██▓ ░ \n";
	std::cout<<"░▒████▓ ░▒████▒░▒███▒█▄ ▒▒█████▓ ░▒████▒     ▒██▒ ░ ░▒████▒▒██████▒▒  ▒██▒ ░ \n";
	std::cout<<"▒▒▓  ▒ ░░ ▒░ ░░░ ▒▒░ ▒ ░▒▓▒ ▒ ▒ ░░ ▒░ ░     ▒ ░░   ░░ ▒░ ░▒ ▒▓▒ ▒ ░  ▒ ░░   \n";
	std::cout<<"░ ▒  ▒  ░ ░  ░ ░ ▒░  ░ ░░▒░ ░ ░  ░ ░  ░       ░     ░ ░  ░░ ░▒  ░ ░    ░    \n";
	std::cout<<"░ ░  ░    ░      ░   ░  ░░░ ░ ░    ░        ░         ░   ░  ░  ░    ░      \n";
	std::cout<<"  ░       ░  ░    ░       ░        ░  ░               ░  ░      ░           \n";
	std::cout<<"░                                                                           \n";

	std::deque<for_test> random_b;
	ft::deque<for_test> random_a;
	for (int i = 0; i < 10; i++)
	{
		for_test temp = gen_test();
		random_a.push_back(temp);
		random_b.push_back(temp);
	}
	color_black();
	std::cout << "\ndefalut constructor test\n";
	ft::deque<for_test> a1;
	std::deque<for_test> b1;
	color_blue();
	std::cout << "my : size = " << a1.size() << " max_size = " << a1.max_size() << std::endl;
	color_red();
	std::cout << "or : size = " << b1.size() << " max_size = " << b1.max_size() << std::endl;
	color_black();
	std::cout << "\nfill constructor test\n";
	for_test temp1 =gen_test();
	ft::deque<for_test> a2(7,temp1);
	std::deque<for_test> b2(7, temp1);
	color_blue();
	std::cout << "my : size = " << a2.size() << " max_size = " << a2.max_size() <<  std::endl;
	color_red();
	std::cout << "or : size = " << b2.size() << " max_size = " << b2.max_size() << std::endl;
	color_blue();
	std::cout << "my\n";
	for (ft::deque<for_test>::iterator it = a2.begin(); it != a2.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_red();
	std::cout <<"or\n";
	for (std::deque<for_test>::iterator it = b2.begin(); it != b2.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_black();
	wait_input();
	std::cout << "\nrange constructor test\n";
	ft::deque<for_test> a3(random_a.begin(), random_a.end());
	std::deque<for_test> b3(random_b.begin(), random_b.end());
	color_blue();
	std::cout << "my : size = " << a3.size() << " max_size = " << a3.max_size() << " back = " <<a3.back().a << " front = " << a3.front().a << std::endl;
	color_red();
	std::cout << "or : size = " << b3.size() << " max_size = " << b3.max_size() << " back = " << b3.back().a << " front = " << b3.front().a << std::endl;
	color_blue();
	std::cout << "my\n";
	for (ft::deque<for_test>::iterator it = a3.begin(); it != a3.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_red();
	std::cout <<"or\n";
	for (std::deque<for_test>::iterator it = b3.begin(); it != b3.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_black();
	std::cout << "\ncopy constructor test\n";
	ft::deque<for_test> a4(a3);
	std::deque<for_test> b4(b3);
	color_blue();
	std::cout << "my : size = " << a4.size() << " max_size = " << a4.max_size() << " back = " <<a4.back().a << " front = " << a4.front().a << std::endl;
	color_red();
	std::cout << "or : size = " << b4.size() << " max_size = " << b4.max_size() << " back = " << b4.back().a << " front = " << b4.front().a << std::endl;
	color_blue();
	std::cout << "my\n";
	for (ft::deque<for_test>::iterator it = a4.begin(); it != a4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_red();
	std::cout <<"or\n";
	for (std::deque<for_test>::iterator it = b4.begin(); it != b4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_black();
	wait_input();
	std::cout << "\nrange assign test\n";
	ft::vector<for_test> v1;
	std::vector<for_test> v2;
	for (int i = 0; i < 10; i++)
	{
		for_test temp = gen_test();
		v1.push_back(temp);
		v2.push_back(temp);
	}
	color_blue();
	std::cout << "my base vector : \n";
	for (ft::vector<for_test>::iterator it = v1.begin(); it != v1.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_red();
	std::cout << "or base vector : \n";
	for (std::vector<for_test>::iterator it = v2.begin(); it != v2.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_black();
	std::cout << "assign deque using vector\n";
	a4.assign(v1.begin(), v1.end());
	b4.assign(v2.begin(), v2.end());
	color_blue();
	std::cout << "my : size = " << a4.size() << " max_size = " << a4.max_size() << " back = " <<a4.back().a << " front = " << a4.front().a << std::endl;
	color_red();
	std::cout << "or : size = " << b4.size() << " max_size = " << b4.max_size() << " back = " << b4.back().a << " front = " << b4.front().a << std::endl;
	color_blue();
	std::cout << "my\n";
	for (ft::deque<for_test>::iterator it = a4.begin(); it != a4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_red();
	std::cout <<"or\n";
	for (std::deque<for_test>::iterator it = b4.begin(); it != b4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_black();
	wait_input();
	std::cout << "\nfill assign test\n";
	for_test zero;
	zero.a = 0;
	zero.b = "0";
	zero.c = 0;
	zero.d = 0;
	a4.assign(5, zero);
	b4.assign(5, zero);
	color_blue();
	std::cout << "my : size = " << a4.size() << " max_size = " << a4.max_size() << " back = " <<a4.back().a << " front = " << a4.front().a << std::endl;
	color_red();
	std::cout << "or : size = " << b4.size() << " max_size = " << b4.max_size() << " back = " << b4.back().a << " front = " << b4.front().a << std::endl;
	color_blue();
	std::cout << "my\n";
	for (ft::deque<for_test>::iterator it = a4.begin(); it != a4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_red();
	std::cout <<"or\n";
	for (std::deque<for_test>::iterator it = b4.begin(); it != b4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_black();
	std::cout << "\npush front/pop front test\n";
	a4.pop_front();
	a4.pop_front();
	a4.pop_front();
	b4.pop_front();
	b4.pop_front();
	b4.pop_front();
	a4.push_front(temp1);
	a4.push_front(temp1);
	a4.push_front(temp1);
	b4.push_front(temp1);
	b4.push_front(temp1);
	b4.push_front(temp1);
	color_blue();
	std::cout << "my : size = " << a4.size() << " max_size = " << a4.max_size() << " back = " <<a4.back().a << " front = " << a4.front().a << std::endl;
	color_red();
	std::cout << "or : size = " << b4.size() << " max_size = " << b4.max_size() << " back = " << b4.back().a << " front = " << b4.front().a << std::endl;
	color_blue();
	std::cout << "my\n";
	for (ft::deque<for_test>::iterator it = a4.begin(); it != a4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_red();
	std::cout <<"or\n";
	for (std::deque<for_test>::iterator it = b4.begin(); it != b4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;

	color_black();
	wait_input();
	std::cout << "\npush back/pop back test\n";

	for_test temp2 = gen_test();
	a4.pop_back();
	a4.pop_back();
	b4.pop_back();
	b4.pop_back();
	a4.push_back(temp2);
	a4.push_back(temp2);
	a4.push_back(temp2);
	b4.push_back(temp2);
	b4.push_back(temp2);
	b4.push_back(temp2);
	color_blue();
	std::cout << "my : size = " << a4.size() << " max_size = " << a4.max_size() << " back = " <<a4.back().a << " front = " << a4.front().a << std::endl;
	color_red();
	std::cout << "or : size = " << b4.size() << " max_size = " << b4.max_size() << " back = " << b4.back().a << " front = " << b4.front().a << std::endl;
	color_blue();
	std::cout << "my\n";
	for (ft::deque<for_test>::iterator it = a4.begin(); it != a4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_red();
	std::cout <<"or\n";
	for (std::deque<for_test>::iterator it = b4.begin(); it != b4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;

	wait_input();
	color_black();
	std::cout << "\nsingle element insert test\n";
	ft::deque<for_test>::iterator myit = a4.begin();
	std::deque<for_test>::iterator orit = b4.begin();
	myit++;
	myit++;
	orit++;
	orit++;
	a4.insert(myit, zero);
	b4.insert(orit, zero);
	color_blue();
	std::cout << "my : size = " << a4.size() << " max_size = " << a4.max_size() << " back = " <<a4.back().a << " front = " << a4.front().a << std::endl;
	color_red();
	std::cout << "or : size = " << b4.size() << " max_size = " << b4.max_size() << " back = " << b4.back().a << " front = " << b4.front().a << std::endl;
	color_blue();
	std::cout << "my\n";
	for (ft::deque<for_test>::iterator it = a4.begin(); it != a4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_red();
	std::cout <<"or\n";
	for (std::deque<for_test>::iterator it = b4.begin(); it != b4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;

	color_black();
	std::cout << "\nfill insert test\n";
//	a4.insert(myit, 5, zero);
//	b4.insert(orit, 5, zero); ->맥에서는 stl함수가 기존 it정보 잃어버림
	a4.insert(a4.begin(), 6, zero);
	b4.insert(b4.begin(), 6, zero);
	color_blue();
	std::cout << "my : size = " << a4.size() << " max_size = " << a4.max_size() << " back = " <<a4.back().a << " front = " << a4.front().a << std::endl;
	color_red();
	std::cout << "or : size = " << b4.size() << " max_size = " << b4.max_size() << " back = " << b4.back().a << " front = " << b4.front().a << std::endl;
	color_blue();
	std::cout << "my\n";
	for (ft::deque<for_test>::iterator it = a4.begin(); it != a4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_red();
	std::cout <<"or\n";
	for (std::deque<for_test>::iterator it = b4.begin(); it != b4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;

	wait_input();
	color_black();
	std::cout << "\nrange insert test\n";
//	a4.insert(myit, a3.begin(), a3.end());
//	b4.insert(orit, b3.begin(), b3.end()); //위와 마찬가지
	a4.insert(a4.begin(),a3.begin(), a3.end());
	b4.insert(b4.begin(),b3.begin(), b3.end());
	color_blue();
	std::cout << "my : size = " << a4.size() << " max_size = " << a4.max_size() << " back = " <<a4.back().a << " front = " << a4.front().a << std::endl;
	color_red();
	std::cout << "or : size = " << b4.size() << " max_size = " << b4.max_size() << " back = " << b4.back().a << " front = " << b4.front().a << std::endl;
	color_blue();
	std::cout << "my\n";
	for (ft::deque<for_test>::iterator it = a4.begin(); it != a4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_red();
	std::cout <<"or\n";
	for (std::deque<for_test>::iterator it = b4.begin(); it != b4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;


	color_black();
	std::cout << "\nsingle erase test\n";
	a4.erase(a4.begin());
	b4.erase(b4.begin());
	color_blue();
	std::cout << "my : size = " << a4.size() << " max_size = " << a4.max_size() << " back = " <<a4.back().a << " front = " << a4.front().a << std::endl;
	color_red();
	std::cout << "or : size = " << b4.size() << " max_size = " << b4.max_size() << " back = " << b4.back().a << " front = " << b4.front().a << std::endl;
	color_blue();
	std::cout << "my\n";
	for (ft::deque<for_test>::iterator it = a4.begin(); it != a4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_red();
	std::cout <<"or\n";
	for (std::deque<for_test>::iterator it = b4.begin(); it != b4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;



	color_black();
	std::cout << "\nrange erase test\n";
	std::cout << "My : " << (*myit).a << " " << (*myit).b << std::endl;
	std::cout << "or : " << (*orit).a << " " << (*orit).b << std::endl;
//	a4.erase(myit, a4.end());
//	b4.erase(orit, b4.end());
	a4.erase(a4.begin() + 4, a4.end());
	b4.erase(b4.begin() + 4, b4.end());
	color_blue();
	std::cout << "my : size = " << a4.size() << " max_size = " << a4.max_size() << " back = " <<a4.back().a << " front = " << a4.front().a << std::endl;
	color_red();
	std::cout << "or : size = " << b4.size() << " max_size = " << b4.max_size() << " back = " << b4.back().a << " front = " << b4.front().a << std::endl;
	color_blue();
	std::cout << "my\n";
	for (ft::deque<for_test>::iterator it = a4.begin(); it != a4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;
	color_red();
	std::cout <<"or\n";
	for (std::deque<for_test>::iterator it = b4.begin(); it != b4.end(); it++)
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<std::endl;


	wait_input();
	color_black();
	std::cout << "\nmember function swap test\n";
	ft::deque<int> a_int(14, 16);
	std::deque<int> b_int(14, 16);
	ft::deque<int> a1_int;
	std::deque<int> b1_int;
	for (int i = 0;i < 10; i++)
	{
		int random = rand();
		a1_int.push_back(random);
		b1_int.push_back(random);
	}
	std::cout << "before swap\n";
	color_blue();
	std::cout << "my deque 1 : ";
	for (ft::deque<int>::iterator it = a_int.begin();it != a_int.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nsize = "<<a_int.size();
	std::cout << "\nmy deque 2 : ";
	for (ft::deque<int>::iterator it = a1_int.begin(); it!=a1_int.end();it++)
		std::cout << *it << " ";
	std::cout << "\nsize = "<<a1_int.size();
	std::cout << "\n";
	color_red();
	std::cout << "or deque 1 : ";
	for (std::deque<int>::iterator it = b_int.begin();it != b_int.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nsize = "<<b_int.size();
	std::cout << "\nor deque 2 : ";
	for (std::deque<int>::iterator it = b1_int.begin(); it!=b1_int.end();it++)
		std::cout << *it << " ";
	std::cout << "\nsize = "<<b1_int.size();
	std::cout << "\n";
	a_int.swap(a1_int);
	b_int.swap(b1_int);
	color_black();

	std::cout << "after swap\n";
	color_blue();
	std::cout << "my deque 1 : ";
	for (ft::deque<int>::iterator it = a_int.begin();it != a_int.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nsize = "<<a_int.size();
	std::cout << "\nmy deque 2 : ";
	for (ft::deque<int>::iterator it = a1_int.begin(); it!=a1_int.end();it++)
		std::cout << *it << " ";
	std::cout << "\nsize = "<<a1_int.size();
	color_red();
	std::cout << "\n";
	std::cout << "or deque 1 : ";
	for (std::deque<int>::iterator it = b_int.begin();it != b_int.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nsize = "<<b_int.size();
	std::cout << "\nor deque 2 : ";
	for (std::deque<int>::iterator it = b1_int.begin(); it!=b1_int.end();it++)
		std::cout << *it << " ";
	std::cout << "\nsize = "<<b1_int.size();
	std::cout <<"\n";

	wait_input();
	color_black();
	std::cout << "\nnon member funcition swap test\n";
	ft::swap(a_int, a1_int);
	std::swap(b_int, b1_int);
	color_blue();
	std::cout << "my deque 1 : ";
	for (ft::deque<int>::iterator it = a_int.begin();it != a_int.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nsize = "<<a_int.size();
	std::cout << "\nmy deque 2 : ";
	for (ft::deque<int>::iterator it = a1_int.begin(); it!=a1_int.end();it++)
		std::cout << *it << " ";
	std::cout << "\nsize = "<<a1_int.size();
	std::cout << "\n";
	color_red();
	std::cout << "or deque 1 : ";
	for (std::deque<int>::iterator it = b_int.begin();it != b_int.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nsize = "<<b_int.size();
	std::cout << "\nor deque 2 : ";
	for (std::deque<int>::iterator it = b1_int.begin(); it!=b1_int.end();it++)
		std::cout << *it << " ";
	std::cout << "\nsize = "<<b1_int.size();
	std::cout << "\n";
	color_black();
	std::cout << "reverse iterator test\n";
	color_blue();
	std::cout << "my deque  : ";
	for (ft::deque<int>::reverse_iterator it = a1_int.rbegin();it != a1_int.rend(); it++)
		std::cout << *it << " ";
	std::cout << "\nsize = "<<a1_int.size();
	std::cout << "\n";
	color_red();
	std::cout << "or deque  : ";
	for (std::deque<int>::reverse_iterator it = b1_int.rbegin();it != b1_int.rend(); it++)
		std::cout << *it << " ";
	std::cout << "\nsize = "<<b1_int.size();
	std::cout << "\n";



	color_black();
	wait_input();
	std::cout << "index access test\n";
	color_blue();
	std::cout << "my\n";
	for (size_t i = 0 ; i < a4.size(); i++)
		std::cout << a4[i].a << " " << a4[i].b << " " << a4[i].c << a4[i].d << std::endl;

	color_red();
	std::cout << "or\n";
	for (size_t i = 0 ; i < b4.size(); i++)
		std::cout << b4[i].a << " " << b4[i].b << " " << b4[i].c << b4[i].d << std::endl;



	color_black();
	wait_input();
	std::cout << "many elem push front test\n";
	for (int i = 0 ; i < 1000; i++)
		a4.push_front(zero);
	int te = 0;
	for (ft::deque<for_test>::iterator it =a4.begin();it !=a4.end();it++ )
	{
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<  " " << te++ << std::endl;
	}
	wait_input();
	std::cout <<"many elem push back test\n";
	for (int i = 0 ; i < 1000; i++)
		a4.push_back(zero);
	te = 0;
	for (ft::deque<for_test>::iterator it =a4.begin();it !=a4.end();it++ )
	{
		std::cout << (*it).a <<" " << (*it).b << " "<<(*it).c <<" "<<(*it).d <<  " " << te++ << std::endl;
	}
	wait_input();
	std::cout << "deque test is finish\n";
	wait_input();
}
#endif
