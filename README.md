# hexdump

## Description
C++17 Toy hexdump tool, using ranges-v3 library

## Issue
Currently, only support char, signed char, uint8_t datatypes

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

