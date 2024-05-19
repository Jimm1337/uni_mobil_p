#ifndef UNI_MOBIL_P_DTOREGISTER_IN_HPP
#define UNI_MOBIL_P_DTOREGISTER_IN_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DtoRegister_IN : public oatpp::DTO {
  DTO_INIT(DtoRegister_IN, DTO)

  DTO_FIELD(String, Username);
  DTO_FIELD(String, Login);
  DTO_FIELD(String, Password);

  DTO_FIELD_INFO(Username) {
    info->required    = true;
    info->description = "Username";
  }

  DTO_FIELD_INFO(Login) {
    info->required    = true;
    info->description = "Login";
  }

  DTO_FIELD_INFO(Password) {
    info->required    = true;
    info->description = "Password";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // UNI_MOBIL_P_DTOREGISTER_IN_HPP
