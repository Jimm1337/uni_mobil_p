#ifndef UNI_MOBIL_P_DTOPLACE_OUT_HPP
#define UNI_MOBIL_P_DTOPLACE_OUT_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DtoPlace_OUT : public oatpp::DTO {
  DTO_INIT(DtoPlace_OUT, DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, name);
  DTO_FIELD(String, description);
  DTO_FIELD(String, location);

  DTO_FIELD_INFO(id) {
    info->required    = true;
    info->description = "Place ID";
  }

  DTO_FIELD_INFO(name) {
    info->required    = true;
    info->description = "Place name";
  }

  DTO_FIELD_INFO(description) {
    info->required    = false;
    info->description = "Place description";
  }

  DTO_FIELD_INFO(location) {
    info->required    = true;
    info->description = "Place location";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // UNI_MOBIL_P_DTOPLACE_OUT_HPP
