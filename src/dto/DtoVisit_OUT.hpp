#ifndef UNI_MOBIL_P_DTOVISIT_OUT_HPP
#define UNI_MOBIL_P_DTOVISIT_OUT_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DtoVisit_OUT : public oatpp::DTO {
  DTO_INIT(DtoVisit_OUT, DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(Int32, userid);
  DTO_FIELD(Int32, placeid);
  DTO_FIELD(String, timestmp);

  DTO_FIELD_INFO(id) {
    info->required    = true;
    info->description = "Visit ID";
  }

  DTO_FIELD_INFO(userid) {
    info->required    = true;
    info->description = "User ID";
  }

  DTO_FIELD_INFO(placeid) {
    info->required    = true;
    info->description = "Place ID";
  }

  DTO_FIELD_INFO(timestmp) {
    info->required    = true;
    info->description = "Visit Time";
    info->pattern     = "HH24:MM:SS DD/MM/YYYY (UTC)";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // UNI_MOBIL_P_DTOVISIT_OUT_HPP
