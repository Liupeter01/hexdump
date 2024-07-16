#include<random>
#include<hexdump/hexdump.hpp>

int main() 
{
          std::string s = "hello, world!\n";
          std::random_device rd;
          std::mt19937 mt(rd());  //init a random 
          std::uniform_int_distribution<std::size_t> uid(0, 0xff);
          for (int i = 0; i < 1000; ++i) {
                    s.push_back(uid(mt));
          }
          hexdump::hexdump(s);
}