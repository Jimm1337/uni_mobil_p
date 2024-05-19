#ifndef DtoError_hpp
#define DtoError_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "enum/EnumErrorType.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class DtoError : public oatpp::DTO {
  DTO_INIT(DtoError, DTO)

  DTO_FIELD(Enum<ErrorType>::AsString, type);
  DTO_FIELD(String , message);

  DTO_FIELD_INFO(type) {
    info->required    = true;
    info->description = "Error type";
  }

  DTO_FIELD_INFO(message) {
    info->required    = true;
    info->description = "Error message";
  }
};

#include OATPP_CODEGEN_END(DTO)

#endif // DtoError_hpp