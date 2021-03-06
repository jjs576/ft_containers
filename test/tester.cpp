#include "utils.hpp"
#include <iostream>
#include <string>
#include <__config>
#include "vector_tester.hpp"
#include "non_member_test.hpp"
#include "stack_tester.hpp"
#include "map_tester.hpp"
#include "deque_tester.hpp"
#include "queue_tester.hpp"
#include "list_tester.hpp"
int main()
{
	system("clear");
	std::cout << " █████▒▄▄▄█████▓ ▄████▄   ▒█████   ███▄    █ ▄▄▄█████▓ ▄▄▄       ██▓ ███▄    █ ▓█████  ██▀███    ██████   " <<std::endl;
	std::cout << " ▓██   ▒ ▓  ██▒ ▓▒▒██▀ ▀█  ▒██▒  ██▒ ██ ▀█   █ ▓  ██▒ ▓▒▒████▄    ▓██▒ ██ ▀█   █ ▓█   ▀ ▓██ ▒ ██▒▒██    ▒ " <<std::endl;
	std::cout << " ▒████ ░ ▒ ▓██░ ▒░▒▓█    ▄ ▒██░  ██▒▓██  ▀█ ██▒▒ ▓██░ ▒░▒██  ▀█▄  ▒██▒▓██  ▀█ ██▒▒███   ▓██ ░▄█ ▒░ ▓██▄   " <<std::endl;
	std::cout << " ░▓█▒  ░ ░ ▓██▓ ░ ▒▓▓▄ ▄██▒▒██   ██░▓██▒  ▐▌██▒░ ▓██▓ ░ ░██▄▄▄▄██ ░██░▓██▒  ▐▌██▒▒▓█  ▄ ▒██▀▀█▄    ▒   ██▒" <<std::endl;
	std::cout << " ░▒█░      ▒██▒ ░ ▒ ▓███▀ ░░ ████▓▒░▒██░   ▓██░  ▒██▒ ░  ▓█   ▓██▒░██░▒██░   ▓██░░▒████▒░██▓ ▒██▒▒██████▒▒" <<std::endl;
	std::cout << "  ▒ ░      ▒ ░░   ░ ░▒ ▒  ░░ ▒░▒░▒░ ░ ▒░   ▒ ▒   ▒ ░░    ▒▒   ▓▒█░░▓  ░ ▒░   ▒ ▒ ░░ ▒░ ░░ ▒▓ ░▒▓░▒ ▒▓▒ ▒ ░" <<std::endl;
	std::cout << "  ░          ░      ░  ▒     ░ ▒ ▒░ ░ ░░   ░ ▒░    ░      ▒   ▒▒ ░ ▒ ░░ ░░   ░ ▒░ ░ ░  ░  ░▒ ░ ▒░░ ░▒  ░ ░" <<std::endl;
	std::cout << "  ░ ░      ░      ░        ░ ░ ░ ▒     ░   ░ ░   ░        ░   ▒    ▒ ░   ░   ░ ░    ░     ░░   ░ ░  ░  ░  " <<std::endl;
	std::cout << " ▄▄▄█████▓▓█████  ░██████ ▄▄▄█████▓▓█████  ██▀███             ░  ░ ░           ░    ░  ░   ░           ░  " <<std::endl;
	std::cout << " ▓  ██▒ ▓▒▓█   ▀ ▒██    ▒ ▓  ██▒ ▓▒▓█   ▀ ▓██ ▒ ██▒                                                       " <<std::endl;
	std::cout << " ▒ ▓██░ ▒░▒███   ░ ▓██▄   ▒ ▓██░ ▒░▒███   ▓██ ░▄█ ▒                                                       " <<std::endl;
	std::cout << " ░ ▓██▓ ░ ▒▓█  ▄   ▒   ██▒░ ▓██▓ ░ ▒▓█  ▄ ▒██▀▀█▄                                                         " <<std::endl;
	std::cout << "   ▒██▒ ░ ░▒████▒▒██████▒▒  ▒██▒ ░ ░▒████▒░██▓ ▒██▒                                                       " <<std::endl;
	std::cout << "   ▒ ░░   ░░ ▒░ ░▒ ▒▓▒ ▒ ░  ▒ ░░   ░░ ▒░ ░░ ▒▓ ░▒▓░                                                       " <<std::endl;
	std::cout << "     ░     ░ ░  ░░ ░▒  ░ ░    ░     ░ ░  ░  ░▒ ░ ▒░                                                       " <<std::endl;
	std::cout << "   ░         ░   ░  ░  ░    ░         ░     ░░   ░                                                        " <<std::endl;
	std::cout << "             ░  ░      ░              ░  ░   ░                                                            " <<std::endl;
	std::cout << " " <<std::endl;
	std::cout << "__cplusplus : " << __cplusplus << std::endl;
	std::cout << "__apple_build_version__ : " << __apple_build_version__ << std::endl;
	std::cout << "_GNUC_VER : " << _GNUC_VER << std::endl;
	std::cout << "_LIBCPP_STD_VER : " << _LIBCPP_STD_VER << std::endl << std::endl;
	wait_input();
	std::string a ="0";
	srand(time(0));
	while (a != "exit")
	{
		system("clear");

		std::cout << "1 : vector test\n2 : list test\n3 : map test\n4 : stack test\n5 : queue test\n6 : deque test\n";
		std::cin >> a;
		if (a == "1")
			vector_test();
		else if (a == "2")
			list_test();
		else if (a == "3")
			map_test();
		else if (a == "4")
			stack_test();
		else if (a == "5")
			queue_test();
		else if (a == "6")
			deque_test();
		else
			break;
	}
	non_member_test();
}
