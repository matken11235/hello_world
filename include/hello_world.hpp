#ifndef __HELLO_WORLD_HPP__
#define __HELLO_WORLD_HPP__

#include <tuple>
#include <array>
#include <utility>
#include <type_traits>
#include <algorithm>


namespace hello_world {
    static constexpr int HWLEN = 13;

    static constexpr unsigned int diff[HWLEN] = {
        0b00011101, 0000000007, 0x9^0b1001,
        0x00000003, 0xffffffbd, 0xfffffff4,
        0000000127, 0xfffffff8, 0x00000003,
        0xfffffffa, 0xfffffff8, 0xffffffbd,
        0xffffffe9
    };

    template <std::size_t... Seq>
    static constexpr char say_impl2(std::index_sequence<Seq...>) {
        return static_cast<char>(( 0x48 + ... + diff[Seq] ));
    }
    template <std::size_t... Seq>
    void say_impl1(std::index_sequence<Seq...>) {
        (std::cout << ... << say_impl2(std::make_index_sequence<Seq>{})) << std::endl;
    }
    template <int N=HWLEN>
    void say() {
        say_impl1(std::make_index_sequence<N>{});
    }
} // end hello_world namespace
#endif

