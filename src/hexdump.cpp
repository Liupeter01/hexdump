#include<fstream>
#include<hexdump/hexdump.hpp>
#include<cxxopts/cxxopts.hpp>

void prompt(int argc, char** argv)
{
          cxxopts::Options options("hexdump", " Acommand-line utility used to display the contents of a file in hexadecimal, decimal, octal, or ASCII format");
          options.add_options()
                    ("f,file", "File name", cxxopts::value<std::string>()->default_value("-"))
                    ("w,width", "Set Printing Width", cxxopts::value<std::size_t>()->default_value("16"))
                    ("h,help", "Print Usage")
                    ;
          auto result = options.parse(argc, argv);
          if (result.count("help")) {
                    std::cout << options.help() << '\n';
                    return;
          }
          auto path = result["file"].as<std::string>();
          auto width = result["width"].as<std::size_t>();
          if (path == "-") {
                    hexdump::hexdump(
                              std::string{
                                        std::istreambuf_iterator<char>{std::cin },
                                        std::istreambuf_iterator<char>{}
                              }
                              ,width
                    );
          }
          else {
                    std::ifstream ifs(path);
                    if (!ifs.good()) {
                              std::cerr << std::strerror(errno) << ": " << path << '\n';
                              return ;
                    }
                    hexdump::hexdump(
                              std::string{
                                        std::istreambuf_iterator<char>{ifs },
                                        std::istreambuf_iterator<char>{}
                              }
                              , width
                    );
                    ifs.close();
          }
}