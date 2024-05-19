#ifndef UNI_MOBIL_P_DTOADMINCOMMENT_IN_HPP
#define UNI_MOBIL_P_DTOADMINCOMMENT_IN_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DtoAdminComment_IN : public oatpp::DTO {
  DTO_INIT(DtoAdminComment_IN, DTO)

  DTO_FIELD(Int32, UserID);
  DTO_FIELD(Int32, PlaceID);
  DTO_FIELD(String, Content);
  DTO_FIELD(Int32, Likes);

  DTO_FIELD_INFO(UserID) {
    info->required    = true;
    info->description = "User ID";
  }

  DTO_FIELD_INFO(PlaceID) {
    info->required    = true;
    info->description = "Place ID";
  }

  DTO_FIELD_INFO(Content) {
    info->required    = true;
    info->description = "Comment Content";
  }

  DTO_FIELD_INFO(Likes) {
    info->required    = false;
    info->description = "Number of likes";
    info->pattern = "Default: 0";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // UNI_MOBIL_P_DTOADMINCOMMENT_IN_HPP
