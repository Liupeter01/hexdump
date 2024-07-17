#pragma once
#ifndef _HEXDUMP_HPP
#define _HEXDUMP_HPP
#include<iostream>
#include<cctype>
#include<string>
#include<string_view>
#include<iomanip>   //set iostream output
#include<type_traits>
#include<range/v3/view/chunk.hpp>

namespace hexdump 
{
          template<class, class = void>
          struct has_iterator_member 
                    : std::false_type {};

          template<typename Container>
          struct has_iterator_member<Container,
                    std::void_t<decltype(std::declval<std::decay_t<Container>>().begin()),
                                       decltype(std::declval<std::decay_t<Container>>().end())>>
                    : std::true_type {};

          template<class, class = void>
          struct has_trivial_pointer
                    : std::false_type {};

          template<typename _Ty>
          struct has_trivial_pointer< _Ty, std::void_t<decltype(std::declval<std::decay_t<_Ty>>()[0])>> : std::true_type  {
                    using value_type = decltype(std::declval<std::decay_t<_Ty>>()[0]);
          };

          template<typename _Ty, typename = void>
          struct value_type_traits;

          template<typename _Ty>
          struct value_type_traits<_Ty, typename std::enable_if<has_iterator_member<_Ty>::value, void>::type> {
                    using value_type = typename _Ty::value_type;
          };

          template<typename _Ty>
          struct value_type_traits <_Ty, typename std::enable_if<!has_iterator_member<_Ty>::value, void>::type> {
                    using value_type = std::decay_t<typename has_trivial_pointer< _Ty>::value_type>;
          };

          template<typename Container>
          void hexdump(const Container& view, const std::size_t width = 16); 
}

template<typename Container>
void hexdump::hexdump(const Container& view, const std::size_t width){
          using value_type = typename value_type_traits<Container>::value_type;

          /*using ranges-v3 library! 8 characters are as a block*/
          std::size_t address{};
          for (auto chunks : view | ranges::views::chunk(width)) {
                    /*display address info*/
                    std::cout << std::hex << std::setw(8) << std::setfill('0') << address << "     ";

                    /*display hex code*/
                    for (auto c : chunks/*size = width*/) {
                              auto cast = std::make_unsigned_t<value_type>(c);
                              std::cout << std::hex << std::setfill('0') << std::setw(2 * sizeof(value_type)) 
                                             << static_cast<unsigned long long>(cast) << ' ';
                    }

                    /*only uin8_t, int8_t, char datatypes could have access to ASCII code*/
                    if constexpr (std::is_same_v<value_type, std::uint8_t> ||
                              std::is_same_v<value_type, std::int8_t> ||
                              std::is_same_v < value_type, char>) {

                              /*add redundant space(' ')*/
                              for (std::size_t i = 0; i < (width - chunks.size()) * std::strlen("   "); ++i) {
                                        std::cout << ' ';
                              }

                              /*start to display ASCII code*/
                              std::cout << "     | ";
                              for (auto c : chunks/*size = width*/) {
                                        /*should not be control character*/
                                        unsigned char cast = static_cast<unsigned char>(c);
                                        std::cout << (!std::isprint(cast) ? '.' : static_cast<char>(cast));
                              }

                              /*add redundant space(' ')*/
                              for (std::size_t i = 0; i < (width - chunks.size()); ++i) {
                                        std::cout << ' ';
                              }
                              std::cout << " |";
                    }
                    std::cout << '\n';

                    address += chunks.size() * sizeof(value_type);
          }
          std::cout << '\n';
}

#endif // !_HEXDUMP_HPP