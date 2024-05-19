#ifndef UNI_MOBIL_P_DTOCOMMENT_IN_HPP
#define UNI_MOBIL_P_DTOCOMMENT_IN_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DtoComment_IN : public oatpp::DTO {
  DTO_INIT(DtoComment_IN, DTO)

  DTO_FIELD(Int32, PlaceID);
  DTO_FIELD(String, Content);

  DTO_FIELD_INFO(PlaceID) {
    info->required    = true;
    info->description = "Place ID";
  }

  DTO_FIELD_INFO(Content) {
    info->required    = true;
    info->description = "Comment Content";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // UNI_MOBIL_P_DTOCOMMENT_IN_HPP
