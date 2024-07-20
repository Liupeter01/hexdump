# hexdump
## Description
C++17 Toy hexdump tool, using ranges-v3 and cxxopt libraries

## Function Test
### 1. Test with basic std::string
```c++
std::string s = "hello, world!\n";
hexdump::hexdump(s);
```

### 2.Test with mt19937 random number with uint8_t distribution
```c++
std::string s;
std::random_device rd;
std::mt19937 mt(rd());  
std::uniform_int_distribution<std::size_t> uid(0, 0xff);
for (int i = 0; i < 100; ++i) {
        s.push_back(uid(mt));
}
hexdump::hexdump(s);
```

### 3.Tesing with non uin8_t, int8_t, char datatypes
```c++
std::vector<uint16_t> s;
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<std::int16_t> uid(-0x8000, 0x7fff);
for (int i = 0; i < 1000; ++i) {
      s.push_back(uid(mt));
}
hexdump::hexdump(s);
```

### 4.Testing with trivial array
```c++
int arr[1000]{};
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> uidi(INT_MIN, INT_MAX);
for (int i = 0; i < 1000; ++i) {
        arr[i] = uidi(mt);
}
hexdump::hexdump(arr);
```

### 5.Testing with File stream
```c++
std::string path = "../hamlet.txt";
std::ifstream ifs(path);
if (!ifs.good()) {
        std::cerr << std::strerror(errno) << ": " << path << '\n';
        return 1;
}
hexdump::hexdump(
        std::string{ 
                  std::istreambuf_iterator<char>(ifs) ,  
                  std::istreambuf_iterator<char>() 
        } 
);
ifs.close();
```

## Developer Quick Start
### Platform Support
Windows, Linux, MacOS(Intel and M Serious Chip)

### Building hexdump
```bash
git clone https://github.com/Liupeter01/hexdump
cd hexdump
cmake -Bbuild
cmake --build build
```