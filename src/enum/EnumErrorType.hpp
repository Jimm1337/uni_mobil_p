#ifndef DtoEnumErrorType_hpp
#define DtoEnumErrorType_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(
  ErrorType,
  v_int8,
  VALUE(SERVER_UNKNOWN, 0, "Unknown error"),               // 500
  VALUE(SERVER_IMPLEMENTATION, 1, "Implementation error"), // 500
  VALUE(SERVER_DATABASE, 2, "Database error"),             // 500
  VALUE(RANGE_LOW, 3, "Range value too low"),              // 416
  VALUE(RANGE_HIGH, 4, "Range value too high"),            // 416
  VALUE(
    CONTENT_INVALID_ID,
    5,
    "Object of requested type and id does not exist"),                  // 404
  VALUE(CONTENT_EXISTS, 6, "Object already exists"),                    // 409
  VALUE(PRECOND_USER_NO_VISIT, 7, "User did not visit commented site"), // 412
  VALUE(INPUT_BAD_STRUCTURE, 8, "Input data has bad structure"), // 422
  VALUE(AUTH_PERMISSION, 9, "Insufficient permission"), // 403
  VALUE(DATA_FORMAT, 10, "Data format error")); // 400

#include OATPP_CODEGEN_END(DTO)

#endif // DtoEnumErrorType_hpp