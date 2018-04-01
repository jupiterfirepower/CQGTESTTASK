#ifndef _MATCH_ENGINE
#define _MATCH_ENGINE

#include "groupBy.h"
#include <iostream>
#include <iterator> // for ostream_iterator
#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include <sstream>
#include <numeric>
#include <cstddef>
#include "naturalcompare.hpp"
#include <cstdlib>
#include <ctime>
#include <functional>

using namespace std;

namespace engine
{
	inline constexpr char sideBuy = 'B';
	inline constexpr char sideSell = 'S';
	inline const string digits = "0123456789";
	inline constexpr char plusstr = '+';
	inline constexpr char minusstr = '-';
	inline constexpr char space = ' ';
	inline constexpr char at = '@';

	static auto extract_digit(const string str)
	{
		const auto last_index = str.find_last_not_of(digits);
		return str.substr(last_index + 1);
	}

	template <typename T> string tostr(const T& t)
	{
		ostringstream os;
		os << t;
		return os.str();
	}

	struct Order
	{
		string TradeIdentifier;
		char Side;
		float Quantity;
		double Price;
		Order* parent = nullptr;

		bool operator<(const Order& rhs) const
		{
			return stoi(extract_digit(TradeIdentifier)) < stoi(extract_digit(rhs.TradeIdentifier)) && Side <= rhs.Side && Price <= rhs.Price;
		}

		string toString() const
		{
			return TradeIdentifier + (Side == sideBuy ? plusstr : minusstr) + tostr(Quantity) + at + tostr(Price);
		}

		string toOrigString() const
		{
			ostringstream os;
			os << TradeIdentifier << space << Side << space << Quantity << space << Price;
			return os.str();
		}

		friend ostream& operator<<(ostream& s, Order const& ord)
		{
			return s << ord.TradeIdentifier << space << ord.Side << space << ord.Quantity << space << ord.Price << endl;
		}
	};

	[[nodiscard]] bool is_reguest(const Order& reguest)
	{
		return (reguest.Side == sideBuy || reguest.Side == sideSell) &&
			reguest.Price > 0 && reguest.Quantity > 0 && !reguest.TradeIdentifier.empty();
	}

	struct natural_less: std::binary_function<std::string, std::string, bool> 
	{
		bool operator()(const Order& a, const Order& b)
		{
			return natural_compare(a.TradeIdentifier, b.TradeIdentifier) < 0 && a.Side <= b.Side && a.Price <= b.Price;
		}
	};

	class SimpleOrderMatchingEngine
	{

	public:
		SimpleOrderMatchingEngine() { }

		vector<pair<Order, Order>> Processing(vector<Order> input) noexcept
		{
			vector<Order> correctinput;
			copy_if(input.begin(), input.end(), back_inserter(correctinput), [](const auto& xitem) { return is_reguest(xitem); });

			vector<Order> v;
			move(unmaped.begin(), unmaped.end(), back_inserter(v));
			move(correctinput.begin(), correctinput.end(), back_inserter(v));
			sort(v.begin(), v.end(), natural_less());

			map< double, vector<Order> >  actual = groupBy(v.begin(), v.end(), [](Order t) { return t.Price; });

			for (auto &[outer_key, inner_map] : actual)
			{
				diagnostic.print(outer_key);

				if (inner_map.size() > 1)
				{
					//sort(inner_map.begin(), inner_map.end());

					vector<Order> filtered;
					vector<Order> sealed;

					//std::vector<int>::iterator bound;
  					auto bound = std::partition (inner_map.begin(), inner_map.end(), [](const auto& ord) { return ord.Side == sideBuy; });

					copy_if(begin(inner_map), end(inner_map), back_inserter(filtered), [](const auto& ord) { return ord.Side == sideBuy; });
					copy_if(begin(inner_map), end(inner_map), back_inserter(sealed), [](const auto& ord) { return ord.Side == sideSell; });

					if (filtered.size() == 0)
						copy(sealed.begin(), sealed.end(), back_inserter(unmaped));

					for (auto& obuy : filtered)
					{
						Order tbuy{obuy};
						const auto finded = find_if(sealed.begin(), sealed.end(), [&tbuy](const auto& x) { return tbuy.Quantity == x.Quantity; });
						if (finded != sealed.end())
						{
							diagnostic.print(tbuy, *finded);

							const auto ord_pair = make_pair(tbuy, *finded);
							maped.push_back(ord_pair);
						}
						else
						{
							while (tbuy.Quantity > 0)
							{
								if (!sealed.empty())
								{
									auto seal = sealed.front();
									Order first{seal};
									const auto cond = tbuy.Quantity > first.Quantity;
									auto new_st = cond ? tbuy : first;
									new_st.Quantity = cond ? first.Quantity : tbuy.Quantity;
									const auto ord_pair = cond ? make_pair(new_st, first) : make_pair(tbuy, new_st);
									maped.push_back(ord_pair);
											
									diagnostic.print(cond ? new_st : tbuy, cond ? first : new_st);
									
									tbuy.Quantity -= cond ? new_st.Quantity : tbuy.Quantity;

									if (!cond)
									{
										first.Quantity -= new_st.Quantity;

										auto part_sealed = first;
										part_sealed.parent = &seal;

										part_sealed.Quantity -= tbuy.Quantity;
										sealed.push_back(part_sealed);
										diagnostic.printpart(part_sealed);
									}

									sealed.erase(sealed.begin());
								}
								else
								{
									tbuy.parent = &obuy;
									unmaped.push_back(tbuy);
									diagnostic.printpart(tbuy);
									break;
								}
							}
							copy(sealed.begin(), sealed.end(), back_inserter(unmaped));
						}

					}
				}
				else if (inner_map.size() > 0)
				{
					unmaped.push_back(inner_map.front());
				}
				diagnostic.print(inner_map);
			}
			return maped;
		}
 
		void clearAll()
		{
			maped.clear();
			unmaped.clear();
		}

		void print() const noexcept
		{
			cout << endl;
			printMapped();
			printAcumulated();
		}
	public:
		static constexpr bool diagnostic_mode = false;
	private:
		vector<pair<Order, Order>> maped;
		vector<Order> unmaped;
		

		class Diagnostic
		{
			public:
				Diagnostic & operator=(Diagnostic const&) = delete;
				template<typename T>
				void print(T& obj) const noexcept
				{
					if constexpr (SimpleOrderMatchingEngine::diagnostic_mode)
						cout << obj << std::endl;
				}
				
				void print(vector<Order>& vo) const noexcept
				{
					if constexpr (SimpleOrderMatchingEngine::diagnostic_mode)
					{
						for (const auto &ord : vo)
						cout << ord;
					}
				}

				void print(Order& ord) const noexcept
				{
					if constexpr (SimpleOrderMatchingEngine::diagnostic_mode)
						cout << "-" << ord.Side << "- " <<ord;
				}

				void printpart(Order& ord) const noexcept
				{
					if constexpr (SimpleOrderMatchingEngine::diagnostic_mode)
					if (ord.parent != nullptr)
						cout << "(-)n* " << ord.toOrigString() << " -> unmaped" << " (*p) - " << ord.parent->toOrigString() << endl;
				}
				
				void print(Order& ordb, Order& ords) const noexcept
				{
					if constexpr (SimpleOrderMatchingEngine::diagnostic_mode)
						cout << "(" << ordb.Side << ") [" << ordb.toOrigString() << "] - [" << ords.toOrigString() << "]" << " (" << ords.Side << ")"  << endl;
				}
		} diagnostic;

		[[maybe_unused]] void printUnMapped() const noexcept
		{
			cout << endl;
			for (auto const unmpcur : unmaped)
			{
				cout << "unmaped: " << unmpcur;
			}
			cout << endl;
		}

		void printMapped() const noexcept
		{
			for (const auto[buy, sell] : maped)
				cout << buy.toString() << space << sell.toString() << endl;
		}

		void printAcumulated() const noexcept
		{
			vector<Order> v;
			vector<Order> vtmp;
			copy(unmaped.begin(), unmaped.end(), back_inserter(v));
			copy(unmaped.begin(), unmaped.end(), back_inserter(vtmp));
			sort(v.begin(), v.end());

			list<Order> acumulated;

			for (const auto cur : v)
			{
				const auto finded = find_if(acumulated.begin(), acumulated.end(), [&cur](auto& ord)
				{
					return ord.TradeIdentifier == cur.TradeIdentifier && ord.Side == cur.Side && ord.Price == cur.Price;
				});

				if (finded == acumulated.end())
				{
					vector<Order> tmp;
					copy_if(vtmp.begin(), vtmp.end(), back_inserter(tmp), [&cur](auto& current)
					{
						return current.TradeIdentifier == cur.TradeIdentifier &&
							current.Side == cur.Side && current.Price == cur.Price;
					});
					Order ordcur{cur};
					ordcur.Quantity = accumulate(tmp.begin(), tmp.end(), 0, [](int sum, const auto x) { return sum + x.Quantity; });
					acumulated.push_back(ordcur);
				}
			}

			ostringstream sl;
			ostringstream sb;

			for (auto nac : acumulated)
				nac.Side == sideSell ? sl << nac.toString() << space : sb << nac.toString() << space;

			cout << sl.str() << space << sb.str() << endl;
		}

	};

}

#endif