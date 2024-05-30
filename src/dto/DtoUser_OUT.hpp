#ifndef UNI_MOBIL_P_DTOUSER_OUT_HPP
#define UNI_MOBIL_P_DTOUSER_OUT_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DtoUser_OUT : public oatpp::DTO {
  DTO_INIT(DtoUser_OUT, DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, username);
  DTO_FIELD(Int32, points);

  DTO_FIELD_INFO(id) {
    info->required    = true;
    info->description = "User ID";
  }

  DTO_FIELD_INFO(username) {
    info->required    = true;
    info->description = "Username";
  }

  DTO_FIELD_INFO(points) {
    info->required    = true;
    info->description = "Points";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // UNI_MOBIL_P_DTOUSER_OUT_HPP
