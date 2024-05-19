#ifndef UNI_MOBIL_P_DTOPLACE_IN_HPP
#define UNI_MOBIL_P_DTOPLACE_IN_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DtoPlace_IN : public oatpp::DTO {
  DTO_INIT(DtoPlace_IN, DTO)

  DTO_FIELD(String, Name);
  DTO_FIELD(String, Description);
  DTO_FIELD(String, Location);
  DTO_FIELD(String, Key);

  DTO_FIELD_INFO(Name) {
    info->required    = true;
    info->description = "Place name";
  }

  DTO_FIELD_INFO(Description) {
    info->required    = false;
    info->description = "Place description";
  }

  DTO_FIELD_INFO(Location) {
    info->required    = true;
    info->description = "Place location";
  }

  DTO_FIELD_INFO(Key) {
    info->required    = true;
    info->description = "Place visit key";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // UNI_MOBIL_P_DTOPLACE_IN_HPP
