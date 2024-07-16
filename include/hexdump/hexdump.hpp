#pragma once
#ifndef _HEXDUMP_HPP
#define _HEXDUMP_HPP
#include<iostream>
#include<cctype>
#include<string>
#include<string_view>
#include<iomanip>   //set iostream output
#include<range/v3/view/chunk.hpp>

namespace hexdump 
{
          template<typename Container>
          void hexdump(const Container& view, const std::size_t width = 16); 
}

template<typename Container>
void hexdump::hexdump(const Container& view, const std::size_t width){
          using value_type = typename Container::value_type;

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

                    address += chunks.size();
          }
}

#endif // !_HEXDUMP_HPP