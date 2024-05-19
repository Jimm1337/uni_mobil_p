#include "MobilService.hpp"
#include "dto/DtoError.hpp"
#include "enum/EnumErrorType.hpp"
#include "fmt/core.h"

// todo

// LOGIN API ENDPOINTS ---------------------------------------------------------

MobilService::Response MobilService::POST_login(const oatpp::String& username) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

MobilService::Response MobilService::POST_register(
  const oatpp::String& username,
  const oatpp::String& login,
  const oatpp::String& password) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

MobilService::Response MobilService::GET_logout() {
  return { MobilService::Status::CODE_401, oatpp::String() };
}

// USER API ENDPOINTS ----------------------------------------------------------

MobilService::Response MobilService::GET_places(const Queries& queries) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

MobilService::Response MobilService::GET_users(const Queries& queries) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

MobilService::Response MobilService::GET_comments(
  const oatpp::Int32& placeId,
  const oatpp::Int32& start,
  const oatpp::Int32& end) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

MobilService::Response MobilService::GET_visitsByPlace(
  const oatpp::Int32& placeId,
  const oatpp::Int32& start,
  const oatpp::Int32& end) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

MobilService::Response MobilService::GET_visitsByUser(
  const oatpp::Int32& userId,
  const oatpp::Int32& start,
  const oatpp::Int32& end) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

MobilService::Response MobilService::GET_ranking(
  const oatpp::Int32& start, const oatpp::Int32& end) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

MobilService::Response MobilService::POST_visits(
  const oatpp::String& authUser, const oatpp::String& key) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

MobilService::Response MobilService::POST_comments(
  const oatpp::String& authUser,
  const oatpp::Int32&  placeId,
  const oatpp::String& content) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

// ADMIN API ENDPOINTS ---------------------------------------------------------

MobilService::Response MobilService::PUT_places(
  const oatpp::String& name,
  const oatpp::String& description,
  const oatpp::String& location,
  const oatpp::String& key) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

MobilService::Response MobilService::DELETE_places(
  const oatpp::Int32& placeId) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

MobilService::Response MobilService::PUT_users(
  const oatpp::String&  username,
  const oatpp::String&  login,
  const oatpp::String&  password,
  const oatpp::Boolean& isAdmin,
  const oatpp::Int32&   points) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

MobilService::Response MobilService::DELETE_users(const oatpp::Int32& userId) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

MobilService::Response MobilService::PUT_visits(
  const oatpp::Int32& userId, const oatpp::Int32& placeId) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

MobilService::Response MobilService::DELETE_visits(
  const oatpp::Int32& visitId) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

MobilService::Response MobilService::PUT_comments(
  const oatpp::Int32&  userId,
  const oatpp::Int32&  placeId,
  const oatpp::String& content,
  const oatpp::Int32&  likes) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

MobilService::Response MobilService::DELETE_comments(
  const oatpp::Int32& commentId) {
  auto dtoError     = DtoError::createShared();
  dtoError->type    = ErrorType::SERVER_UNKNOWN;
  dtoError->message = "Unknown error";
  return { MobilService::Status::CODE_500, dtoError };
}

// AUTHORIZATION ---------------------------------------------------------------

MobilService::Auth MobilService::authorize(const AuthObject& authObject) {
  if (authObject->userId == "admin" && authObject->password == "admin")
  {
    return Auth::ADMIN;
  } else if (authObject->userId == "user" && authObject->password == "user") {
    return Auth::USER;
  } else {
    return Auth::BAD_CREDENTIALS;
  }
}

// UTILS -----------------------------------------------------------------------

oatpp::String MobilService::fixInputString(const oatpp::String& input) {
  auto correctInput = input;

  for (auto pos = correctInput->find('%'); pos != std::string::npos;
       pos      = correctInput->find('%'))
  {
    const auto codedChar = correctInput->substr(pos, 6);

    // SPACE
    if (codedChar.substr(0, 3) == "%20")
    {
      correctInput->replace(pos, 3, " ");
      continue;
    }

    // PL SPECIAL CHARACTERS
    if (codedChar == "%C4%85")
    {
      correctInput->replace(pos, 6, "ą");
      continue;
    }
    if (codedChar == "%C4%87")
    {
      correctInput->replace(pos, 6, "ć");
      continue;
    }
    if (codedChar == "%C4%99")
    {
      correctInput->replace(pos, 6, "ę");
      continue;
    }
    if (codedChar == "%C5%82")
    {
      correctInput->replace(pos, 6, "ł");
      continue;
    }
    if (codedChar == "%C5%84")
    {
      correctInput->replace(pos, 6, "ń");
      continue;
    }
    if (codedChar == "%C3%B3")
    {
      correctInput->replace(pos, 6, "ó");
      continue;
    }
    if (codedChar == "%C5%9B")
    {
      correctInput->replace(pos, 6, "ś");
      continue;
    }
    if (codedChar == "%C5%BA")
    {
      correctInput->replace(pos, 6, "ź");
      continue;
    }
    if (codedChar == "%C5%BC")
    {
      correctInput->replace(pos, 6, "ż");
      continue;
    }
    if (codedChar == "%C4%84")
    {
      correctInput->replace(pos, 6, "Ą");
      continue;
    }
    if (codedChar == "%C4%86")
    {
      correctInput->replace(pos, 6, "Ć");
      continue;
    }
    if (codedChar == "%C4%98")
    {
      correctInput->replace(pos, 6, "Ę");
      continue;
    }
    if (codedChar == "%C5%81")
    {
      correctInput->replace(pos, 6, "Ł");
      continue;
    }
    if (codedChar == "%C5%83")
    {
      correctInput->replace(pos, 6, "Ń");
      continue;
    }
    if (codedChar == "%C3%93")
    {
      correctInput->replace(pos, 6, "Ó");
      continue;
    }
    if (codedChar == "%C5%9A")
    {
      correctInput->replace(pos, 6, "Ś");
      continue;
    }
    if (codedChar == "%C5%B9")
    {
      correctInput->replace(pos, 6, "Ź");
      continue;
    }
    if (codedChar == "%C5%BB")
    {
      correctInput->replace(pos, 6, "Ż");
      continue;
    }

    // CZ SPECIAL CHARACTERS
    if (codedChar == "%C3%A1")
    {
      correctInput->replace(pos, 6, "á");
      continue;
    }
    if (codedChar == "%C4%8D")
    {
      correctInput->replace(pos, 6, "č");
      continue;
    }
    if (codedChar == "%C4%8F")
    {
      correctInput->replace(pos, 6, "ď");
      continue;
    }
    if (codedChar == "%C3%A9")
    {
      correctInput->replace(pos, 6, "é");
      continue;
    }
    if (codedChar == "%C4%9B")
    {
      correctInput->replace(pos, 6, "ě");
      continue;
    }
    if (codedChar == "%C3%AD")
    {
      correctInput->replace(pos, 6, "í");
      continue;
    }
    if (codedChar == "%C5%88")
    {
      correctInput->replace(pos, 6, "ň");
      continue;
    }
    if (codedChar == "%C3%B3")
    {
      correctInput->replace(pos, 6, "ó");
      continue;
    }
    if (codedChar == "%C5%99")
    {
      correctInput->replace(pos, 6, "ř");
      continue;
    }
    if (codedChar == "%C5%A1")
    {
      correctInput->replace(pos, 6, "š");
      continue;
    }
    if (codedChar == "%C5%A5")
    {
      correctInput->replace(pos, 6, "ť");
      continue;
    }
    if (codedChar == "%C3%BA")
    {
      correctInput->replace(pos, 6, "ú");
      continue;
    }
    if (codedChar == "%C5%AF")
    {
      correctInput->replace(pos, 6, "ů");
      continue;
    }
    if (codedChar == "%C3%BD")
    {
      correctInput->replace(pos, 6, "ý");
      continue;
    }
    if (codedChar == "%C5%BE")
    {
      correctInput->replace(pos, 6, "ž");
      continue;
    }
    if (codedChar == "%C3%81")
    {
      correctInput->replace(pos, 6, "Á");
      continue;
    }
    if (codedChar == "%C4%8C")
    {
      correctInput->replace(pos, 6, "Č");
      continue;
    }
    if (codedChar == "%C4%8E")
    {
      correctInput->replace(pos, 6, "Ď");
      continue;
    }
    if (codedChar == "%C3%89")
    {
      correctInput->replace(pos, 6, "É");
      continue;
    }
    if (codedChar == "%C4%9A")
    {
      correctInput->replace(pos, 6, "Ě");
      continue;
    }
    if (codedChar == "%C3%8D")
    {
      correctInput->replace(pos, 6, "Í");
      continue;
    }
    if (codedChar == "%C5%87")
    {
      correctInput->replace(pos, 6, "Ň");
      continue;
    }
    if (codedChar == "%C3%93")
    {
      correctInput->replace(pos, 6, "Ó");
      continue;
    }
    if (codedChar == "%C5%98")
    {
      correctInput->replace(pos, 6, "Ř");
      continue;
    }
    if (codedChar == "%C5%A0")
    {
      correctInput->replace(pos, 6, "Š");
      continue;
    }
    if (codedChar == "%C5%A4")
    {
      correctInput->replace(pos, 6, "Ť");
      continue;
    }
    if (codedChar == "%C3%9A")
    {
      correctInput->replace(pos, 6, "Ú");
      continue;
    }
    if (codedChar == "%C5%AE")
    {
      correctInput->replace(pos, 6, "Ů");
      continue;
    }
    if (codedChar == "%C3%9D")
    {
      correctInput->replace(pos, 6, "Ý");
      continue;
    }
    if (codedChar == "%C5%BD")
    {
      correctInput->replace(pos, 6, "Ž");
      continue;
    }
  }

  return correctInput;
}

bool MobilService::isMultiQuerySingle(const Queries& queries) {
  return queries.getSize() == 1;
}

bool MobilService::isRangeValid(
  const oatpp::Int32& start, const oatpp::Int32& end) {
  return start >= 0 && end >= 0 && start <= end;
}
