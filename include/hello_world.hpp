#ifndef __HELLO_WORLD_HPP__
#define __HELLO_WORLD_HPP__

#include <tuple>
#include <array>
#include <utility>
#include <type_traits>
#include <algorithm>


namespace hello_world {
    static constexpr int HWLEN = 13;

    template <int N>
    using _int = std::integral_constant<int, N>;
    template <typename l>
    using decrement = _int<l::value-1>;

    static constexpr unsigned int diff[HWLEN] = {
    	0b00011101, 0000000007, 0x9^0b1001,
    	0x00000003, 0xffffffbd, 0xfffffff4,
    	0000000127, 0xfffffff8, 0x00000003,
    	0xfffffffa, 0xfffffff8, 0xffffffbd,
    	0xffffffe9
    };

    template <std::size_t...Seq>
    constexpr unsigned int sum(std::index_sequence<Seq...>) {
    	return ( 0x48 + ... + diff[Seq] );
    }

    template <typename L, typename R>
    struct append;
    template <typename ...L, typename ...R>
    struct append<std::tuple<L...>, std::tuple<R...>> {
    	using type = std::tuple<L..., R...>;
    };

    template <typename N>
    struct range {
    	using type = typename append< typename range<decrement<N>>::type, std::tuple<N> >::type;
    };
    template <>
    struct range<_int<0>> {
    	using type = std::tuple<_int<0>>;
    };

    template <typename Tuple>
    struct tuple_to_array;
    template <int ...seq>
    struct tuple_to_array< std::tuple<_int<seq>...> > {
    	static constexpr std::array<unsigned int, sizeof...(seq)> world{
    	    { sum(std::make_index_sequence<seq>{})... }
    	};
    };

    template <int N>
    using hello = tuple_to_array< typename range<_int<N>>::type >;

    static void say() {
        constexpr auto a = hello_world::hello<HWLEN>::world;
        std::for_each(a.begin(), a.end(), [](char n) { std::cout << n; });
    }
} // end hello_world namespace
#endif

