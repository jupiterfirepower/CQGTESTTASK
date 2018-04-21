#ifndef _GROUP_BY_H_
#define _GROUP_BY_H_

#include <map>
#include <vector>

using namespace std;

namespace details
{
	/*
	* return_type
	*/

	template< typename T >
	struct return_type
	{
		typedef typename return_type< typename decay< decltype(&T::operator())>::type >::type type;
	};

	template< typename R, typename C, typename... A >
	struct return_type< R(C::*)(A...) >
	{
		typedef typename decay< R >::type type;
	};

	template< typename R, typename C, typename... A >
	struct return_type< R(C::*)(A...) const >
	{
		typedef typename decay< R >::type type;
	};

	template< typename R, typename... A >
	struct return_type< R(*)(A...) >
	{
		typedef typename decay< R >::type type;
	};

	/*
	* GroupBy
	*/

	template< typename Arg, typename... Ts >
	struct GroupBy;

	template< typename Arg, typename T, typename... Ts >
	struct GroupBy< Arg, T, Ts... >
	{
		typedef map<
			typename details::return_type< typename decay< T >::type >::type,
			typename GroupBy< Arg, Ts... >::return_type
		> return_type;
	};

	template< typename Arg, typename T >
	struct GroupBy< Arg, T >
	{
		typedef map<
			typename return_type< typename decay< T >::type >::type,
			vector< Arg >
		> return_type;
	};

	/*
	* groupByImpl
	*/

	template< typename Map, typename Iterator, typename F >
	void groupByImpl(Map & map, Iterator && current, F && f)
	{
		map[f(*current)].push_back(*current);
	}

	template< typename Map, typename Iterator, typename F, typename... Fs >
	void groupByImpl(Map & map, Iterator && current, F && f, Fs &&... fs)
	{
		groupByImpl(map[f(*current)], current, forward< Fs >(fs)...);
	}
}

/*
* groupBy
*/

template< typename Iterator, typename F, typename... Fs >
typename details::GroupBy< typename iterator_traits< Iterator >::value_type, F, Fs... >::return_type
groupBy(Iterator begin, Iterator const end, F && f, Fs &&... fs)
{
	typename details::GroupBy< typename iterator_traits< Iterator >::value_type, F, Fs... >::return_type result;
	for ( /* empty */; begin != end; ++begin)
	{
		details::groupByImpl(result, begin, forward< F >(f), forward< Fs >(fs)...);
	}

	return result;
}

#endif
