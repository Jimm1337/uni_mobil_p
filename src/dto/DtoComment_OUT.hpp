#ifndef UNI_MOBIL_P_DTOCOMMENT_OUT_HPP
#define UNI_MOBIL_P_DTOCOMMENT_OUT_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DtoComment_OUT : public oatpp::DTO {
  DTO_INIT(DtoComment_OUT, DTO)

  DTO_FIELD(Int32, CommentID);
  DTO_FIELD(Int32, UserID);
  DTO_FIELD(Int32, PlaceID);
  DTO_FIELD(String, Content);
  DTO_FIELD(String, Time);
  DTO_FIELD(Int32, Likes);

  DTO_FIELD_INFO(CommentID) {
    info->required    = true;
    info->description = "Comment ID";
  }

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

  DTO_FIELD_INFO(Time) {
    info->required    = true;
    info->description = "Comment Time";
    info->pattern = "HH:MM DD/MM/YYYY";
  }

  DTO_FIELD_INFO(Likes) {
    info->required    = true;
    info->description = "Number of likes";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // UNI_MOBIL_P_DTOCOMMENT_OUT_HPP
