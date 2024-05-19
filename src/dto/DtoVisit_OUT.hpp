#ifndef UNI_MOBIL_P_DTOVISIT_OUT_HPP
#define UNI_MOBIL_P_DTOVISIT_OUT_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DtoVisit_OUT : public oatpp::DTO {
  DTO_INIT(DtoVisit_OUT, DTO)

  DTO_FIELD(Int32, VisitID);
  DTO_FIELD(Int32, UserID);
  DTO_FIELD(Int32, PlaceID);
  DTO_FIELD(String, Time);

  DTO_FIELD_INFO(VisitID) {
    info->required    = true;
    info->description = "Visit ID";
  }

  DTO_FIELD_INFO(UserID) {
    info->required    = true;
    info->description = "User ID";
  }

  DTO_FIELD_INFO(PlaceID) {
    info->required    = true;
    info->description = "Place ID";
  }

  DTO_FIELD_INFO(Time) {
    info->required    = true;
    info->description = "Visit Time";
    info->pattern     = "HH:MM DD/MM/YYYY";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // UNI_MOBIL_P_DTOVISIT_OUT_HPP
