#ifndef UNI_MOBIL_P_DTOUSER_OUT_HPP
#define UNI_MOBIL_P_DTOUSER_OUT_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DtoUser_OUT : public oatpp::DTO {
  DTO_INIT(DtoUser_OUT, DTO)

  DTO_FIELD(Int32, UserID);
  DTO_FIELD(String, Username);
  DTO_FIELD(Int32, Points);

  DTO_FIELD_INFO(UserID) {
    info->required    = true;
    info->description = "User ID";
  }

  DTO_FIELD_INFO(Username) {
    info->required    = true;
    info->description = "Username";
  }

  DTO_FIELD_INFO(Points) {
    info->required    = true;
    info->description = "Points";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // UNI_MOBIL_P_DTOUSER_OUT_HPP
