#include <cmath>

#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include "binder/binder.h"
#include "common/bustub_instance.h"
#include "common/exception.h"
#include "common/util/string_util.h"
#include "linenoise/linenoise.h"
#include "utf8proc/utf8proc.h"

static std::unique_ptr<bustub::BustubInstance> instance = nullptr;

extern "C" {

auto Test() -> int { return 42; }

auto BustubExecuteQuery(const char *input, char *output, uint16_t len) -> int {
  if (instance == nullptr) {
    std::cout << "Initialize BusTub..." << std::endl;
    auto bustub = std::make_unique<bustub::BustubInstance>("test.db");
    bustub->GenerateMockTable();
    instance = std::move(bustub);
  }
  std::string input_string(input);
  std::cout << input_string << std::endl;
  std::string output_string;
  try {
    auto writer = bustub::HtmlWriter();
    instance->ExecuteSql(input_string, writer);
    output_string = writer.ss_.str();
  } catch (bustub::Exception &ex) {
    output_string = ex.what();
  }
  std::cout << output_string << std::endl;
  strncpy(output, output_string.c_str(), len);
  return 0;
}
}