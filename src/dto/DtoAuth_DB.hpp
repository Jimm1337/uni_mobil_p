#ifndef UNI_MOBIL_P_DTOAUTH_DB_HPP
#define UNI_MOBIL_P_DTOAUTH_DB_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DtoAuth_DB : public oatpp::DTO {
  DTO_INIT(DtoAuth_DB, DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, username);
  DTO_FIELD(Boolean, admin);
  DTO_FIELD(Int32, points);
};

#endif // UNI_MOBIL_P_DTOAUTH_DB_HPP
