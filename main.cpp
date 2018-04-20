#include <iostream>
#include <iterator> // for ostream_iterator
#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include <sstream>
#include <chrono>
#include <functional>
#include "matchengine.hpp"

using namespace chrono;
using namespace std;

using namespace engine;
using MatchEngine = engine::SimpleOrderMatchingEngine;
using Order = engine::Order;

template<typename T>
void print_error(T& ex) noexcept(is_base_of<exception, T>::value)
{
	cerr << ex.what() << endl;
}

static bool is_digits(const string &str)
{
	return str.find_first_not_of(digits) == string::npos;
}

int main()
{
	const vector<Order> vorder
	{ {
			Order{ "T1", sideBuy, 5, 30 },
			Order{ "T2", sideSell, 5, 70 },
			Order{ "T3", sideBuy, 1, 40 },
			Order{ "T4", sideSell, 2, 60 },
			Order{ "T5", sideSell, 3, 70 },
			Order{ "T6", sideSell, 20, 80 },
			Order{ "T7", sideSell, 1, 50 },
			Order{ "T2", sideSell, 5, 70 },
			Order{ "T1", sideBuy, 1, 50 },
			Order{ "T1", sideBuy, 3, 60 },
			Order{ "T7", sideSell, 2, 60 },
			Order{ "T8", sideBuy, 10, 90 }
		} };

	try
	{
		vector<Order> inputvorder;

		//MatchEngine engine{true};

		const auto timeexec=[](MatchEngine& me, const vector<Order>& vord, 
			function<vector<pair<Order, Order>>(MatchEngine&, const vector<Order>&)> match = 
			[](MatchEngine& me, const vector<Order>& vord){ return me.Processing(vord); })
		{
			// Get starting timepoint
			const auto start = high_resolution_clock::now();

			auto trades = match(me, vord);

			// Get ending timepoint
			const auto stop = high_resolution_clock::now();

			// Get duration. Substart timepoints to get durarion. 
			// To cast it to proper unit use duration cast method
			auto duration = duration_cast<microseconds>(stop - start);

			cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

			return trades;
		};

		MatchEngine engine{};
		
		//auto maped = engine.Processing(vorder);
		auto maped = timeexec(engine, vorder);
		//auto maped = engine.Processing(vorder);
		engine.print();

		cout << endl;
		cout << "Input request data:" << endl;

		auto split = [](string& line)
		{
			istringstream iss(line);
			return vector<string>((istream_iterator<string>(iss)), istream_iterator<string>());
		};

		try
		{
			string line;

			while (getline(cin, line) && !cin.eof() && line != "exit")
			{
			    if(line == "end" && !inputvorder.empty())
			    {
				engine.clearAll();

				auto maped = timeexec(engine,  inputvorder);
				engine.print();
			    }
		            else
			    {
				auto splitted = split(line);

				if (splitted.size() == 4)
				{
					auto side = splitted[1];
					const float quantity = is_digits(splitted[2]) ? stof(splitted[2]) : -1.0;
					const double price = is_digits(splitted[3]) ? stod(splitted[3]) : -1.0;

					const Order currentord{ splitted[0], side[0], quantity, price };

					if (side.size() >1 || !is_reguest(currentord))
						cout << "Incorrect request format: <Trader Identifier> <Side> <Quantity> <Price> : " << currentord;
					else
						inputvorder.push_back(currentord);
				}
				else
					cout << "Incorrect request, request format: <Trader Identifier> <Side> <Quantity> <Price>." << endl;
			    }
			}
		}
		catch (exception& ex)
		{
			print_error(ex);
		}

		engine.clearAll();

		if (!inputvorder.empty())
		{
			engine.Processing(inputvorder);
			cout << endl;
			engine.print();
		}

		//cin.get();
	}
	catch (const runtime_error& ex)
	{
		print_error(ex);
	}
	catch (exception& ex)
	{
		print_error(ex);
	}
	catch (...)
	{
		cerr << "error ..." << endl;
	}

	return 0;
}