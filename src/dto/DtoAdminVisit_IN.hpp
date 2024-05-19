#ifndef UNI_MOBIL_P_DTOADMINVISIT_IN_HPP
#define UNI_MOBIL_P_DTOADMINVISIT_IN_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DtoAdminVisit_IN : public oatpp::DTO {
  DTO_INIT(DtoAdminVisit_IN, DTO)

  DTO_FIELD(Int32, UserID);
  DTO_FIELD(Int32, PlaceID);

  DTO_FIELD_INFO(UserID) {
    info->required    = true;
    info->description = "User ID";
  }

  DTO_FIELD_INFO(PlaceID) {
    info->required    = true;
    info->description = "Place ID";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // UNI_MOBIL_P_DTOADMINVISIT_IN_HPP
