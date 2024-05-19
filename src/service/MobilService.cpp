#include "MobilService.hpp"
#include "dto/DtoError.hpp"
#include "enum/EnumErrorType.hpp"
#include "fmt/core.h"



oatpp::String MobilService::fixInputString(const oatpp::String& input) {
  auto correctInput = input;

  for (auto pos = correctInput->find('%'); pos != std::string::npos;
       pos      = correctInput->find('%'))
  {
    const auto codedChar = correctInput->substr(pos, 6);

    if (codedChar.substr(0, 3) == "%20")
    {
      correctInput->replace(pos, 3, " ");
      continue;
    }
    if (codedChar == "%C3%A1")
    {
      correctInput->replace(pos, 6, "á");
      continue;
    }
    if (codedChar == "%C4%8D")
    {
      correctInput->replace(pos, 6, "č");
      continue;
    }
    if (codedChar == "%C4%8F")
    {
      correctInput->replace(pos, 6, "ď");
      continue;
    }
    if (codedChar == "%C3%A9")
    {
      correctInput->replace(pos, 6, "é");
      continue;
    }
    if (codedChar == "%C4%9B")
    {
      correctInput->replace(pos, 6, "ě");
      continue;
    }
    if (codedChar == "%C3%AD")
    {
      correctInput->replace(pos, 6, "í");
      continue;
    }
    if (codedChar == "%C5%88")
    {
      correctInput->replace(pos, 6, "ň");
      continue;
    }
    if (codedChar == "%C3%B3")
    {
      correctInput->replace(pos, 6, "ó");
      continue;
    }
    if (codedChar == "%C5%99")
    {
      correctInput->replace(pos, 6, "ř");
      continue;
    }
    if (codedChar == "%C5%A1")
    {
      correctInput->replace(pos, 6, "š");
      continue;
    }
    if (codedChar == "%C5%A5")
    {
      correctInput->replace(pos, 6, "ť");
      continue;
    }
    if (codedChar == "%C3%BA")
    {
      correctInput->replace(pos, 6, "ú");
      continue;
    }
    if (codedChar == "%C5%AF")
    {
      correctInput->replace(pos, 6, "ů");
      continue;
    }
    if (codedChar == "%C3%BD")
    {
      correctInput->replace(pos, 6, "ý");
      continue;
    }
    if (codedChar == "%C5%BE")
    {
      correctInput->replace(pos, 6, "ž");
      continue;
    }
    if (codedChar == "%C3%81")
    {
      correctInput->replace(pos, 6, "Á");
      continue;
    }
    if (codedChar == "%C4%8C")
    {
      correctInput->replace(pos, 6, "Č");
      continue;
    }
    if (codedChar == "%C4%8E")
    {
      correctInput->replace(pos, 6, "Ď");
      continue;
    }
    if (codedChar == "%C3%89")
    {
      correctInput->replace(pos, 6, "É");
      continue;
    }
    if (codedChar == "%C4%9A")
    {
      correctInput->replace(pos, 6, "Ě");
      continue;
    }
    if (codedChar == "%C3%8D")
    {
      correctInput->replace(pos, 6, "Í");
      continue;
    }
    if (codedChar == "%C5%87")
    {
      correctInput->replace(pos, 6, "Ň");
      continue;
    }
    if (codedChar == "%C3%93")
    {
      correctInput->replace(pos, 6, "Ó");
      continue;
    }
    if (codedChar == "%C5%98")
    {
      correctInput->replace(pos, 6, "Ř");
      continue;
    }
    if (codedChar == "%C5%A0")
    {
      correctInput->replace(pos, 6, "Š");
      continue;
    }
    if (codedChar == "%C5%A4")
    {
      correctInput->replace(pos, 6, "Ť");
      continue;
    }
    if (codedChar == "%C3%9A")
    {
      correctInput->replace(pos, 6, "Ú");
      continue;
    }
    if (codedChar == "%C5%AE")
    {
      correctInput->replace(pos, 6, "Ů");
      continue;
    }
    if (codedChar == "%C3%9D")
    {
      correctInput->replace(pos, 6, "Ý");
      continue;
    }
    if (codedChar == "%C5%BD")
    {
      correctInput->replace(pos, 6, "Ž");
      continue;
    }
  }

  return correctInput;
}
