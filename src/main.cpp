#include<random>
#include<hexdump/hexdump.hpp>

int main(int argc, char **argv) 
{
          //std::string s = "hello, world!\n";
          //std::random_device rd;
          //std::mt19937 mt(rd());  //init a random 
          //std::uniform_int_distribution<std::size_t> uid(0, 0xff);
          //for (int i = 0; i < 1000; ++i) {
          //          s.push_back(uid(mt));
          //}
          //hexdump::hexdump(s);

          //std::vector<uint16_t> s;
          //std::random_device rd;
          //std::mt19937 mt(rd());
          //std::uniform_int_distribution<std::int16_t> uid(-0x8000, 0x7fff);
          //for (int i = 0; i < 1000; ++i) {
          //          s.push_back(uid(mt));
          //}
          //hexdump::hexdump(s);

          //int arr[1000]{};
          //std::random_device rd;
          //std::mt19937 mt(rd());
          //std::uniform_int_distribution<int> uidi(INT_MIN, INT_MAX);
          //for (int i = 0; i < 1000; ++i) {
          //          arr[i] = uidi(mt);
          //}
          //hexdump::hexdump(arr);

          //std::string path = "../hamlet.txt";
          //std::ifstream ifs(path);
          //if (!ifs.good()) {
          //          std::cerr << std::strerror(errno) << ": " << path << '\n';
          //          return 1;
          //}
          //hexdump::hexdump(
          //          std::string{ 
          //                    std::istreambuf_iterator<char>(ifs) ,  
          //                    std::istreambuf_iterator<char>() 
          //          } 
          //);
          //ifs.close();
          return 0;
}