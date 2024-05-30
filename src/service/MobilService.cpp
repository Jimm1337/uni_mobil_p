#include "MobilService.hpp"
#include <memory>
#include "dto/DtoAuth_DB.hpp"
#include "dto/DtoComment_OUT.hpp"
#include "dto/DtoError.hpp"
#include "dto/DtoPlace_OUT.hpp"
#include "dto/DtoUser_OUT.hpp"
#include "dto/DtoVisit_OUT.hpp"
#include "enum/EnumErrorType.hpp"
#include "fmt/core.h"

// todo

// LOGIN API ENDPOINTS ---------------------------------------------------------

MobilService::Response MobilService::POST_login(const oatpp::String& login) {
  const auto fixedLogin = fixInputString(login);
  auto       dbResult   = m_database->getUsersLogin(fixedLogin);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in fetch user";
    return { MobilService::Status::CODE_500, dtoError };
  }

  const auto dtoSuccess =
    *dbResult->fetch< oatpp::Vector< oatpp::Object< DtoUser_OUT > > >()
       ->begin();

  return { MobilService::Status::CODE_200, dtoSuccess };
}

MobilService::Response MobilService::POST_register(
  const oatpp::String& username,
  const oatpp::String& login,
  const oatpp::String& password) {
  const auto fixedUsername = fixInputString(username);
  const auto fixedLogin    = fixInputString(login);
  const auto fixedPassword = fixInputString(password);

  auto dbResultCheck = m_database->existsUsers(fixedUsername, fixedLogin);

  if (!dbResultCheck->isSuccess())
  {
    OATPP_LOGD("", dbResultCheck->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in check conflict user";
    return { MobilService::Status::CODE_500, dtoError };
  }

  if (dbResultCheck->hasMoreToFetch())
  {
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::CONTENT_EXISTS;
    dtoError->message = "User with this username or login already exists";
    return { MobilService::Status::CODE_409, dtoError };
  }

  auto dbResult =
    m_database->postRegister(fixedUsername, fixedLogin, fixedPassword);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in register user";
    return { MobilService::Status::CODE_500, dtoError };
  }

  const auto dtoSuccess =
    *dbResult->fetch< oatpp::Vector< oatpp::Object< DtoUser_OUT > > >()
       ->begin();

  return { MobilService::Status::CODE_201, dtoSuccess };
}

MobilService::Response MobilService::GET_logout() {
  return { MobilService::Status::CODE_401, oatpp::String() };
}

// USER API ENDPOINTS ----------------------------------------------------------

MobilService::Response MobilService::GET_places(const Queries& queries) {
  if (queries.getSize() == 0)
  {
    auto dbResult = m_database->getPlacesAll();

    if (!dbResult->isSuccess())
    {
      OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
      auto dtoError     = DtoError::createShared();
      dtoError->type    = ErrorType::SERVER_DATABASE;
      dtoError->message = "Error in fetch all places";
      return { MobilService::Status::CODE_500, dtoError };
    }

    if (!dbResult->hasMoreToFetch())
    { return { MobilService::Status::CODE_204, {} }; }

    const auto dtoSuccess =
      dbResult->fetch< oatpp::Vector< oatpp::Object< DtoPlace_OUT > > >();

    return { MobilService::Status::CODE_200, dtoSuccess };
  }

  if (!isMultiQuerySingle(queries))
  {
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::INPUT_BAD_STRUCTURE;
    dtoError->message = "Multiple queries not supported";
    return { MobilService::Status::CODE_400, dtoError };
  }

  const auto queryID          = queries.get("placeID");
  const auto queryName        = queries.get("name");
  const auto queryLocation    = queries.get("location");
  const auto queryDescription = queries.get("description");

  if (queryID)
  {
    const auto fixedID =
      oatpp::utils::conversion::strToInt32(fixInputString(*queryID)->c_str());
    auto dbResult = m_database->getPlacesID(fixedID);

    if (!dbResult->isSuccess())
    {
      OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
      auto dtoError     = DtoError::createShared();
      dtoError->type    = ErrorType::SERVER_DATABASE;
      dtoError->message = "Error in fetch place by ID";
      return { MobilService::Status::CODE_500, dtoError };
    }

    if (!dbResult->hasMoreToFetch())
    { return { MobilService::Status::CODE_204, {} }; }

    const auto dtoSuccess =
      dbResult->fetch< oatpp::Vector< oatpp::Object< DtoPlace_OUT > > >();

    return { MobilService::Status::CODE_200, dtoSuccess };
  }

  if (queryName)
  {
    const auto fixedName = fixInputString(*queryName);
    auto       dbResult  = m_database->getPlacesName(fixedName);

    if (!dbResult->isSuccess())
    {
      OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
      auto dtoError     = DtoError::createShared();
      dtoError->type    = ErrorType::SERVER_DATABASE;
      dtoError->message = "Error in fetch place by name";
      return { MobilService::Status::CODE_500, dtoError };
    }

    if (!dbResult->hasMoreToFetch())
    { return { MobilService::Status::CODE_204, {} }; }

    const auto dtoSuccess =
      dbResult->fetch< oatpp::Vector< oatpp::Object< DtoPlace_OUT > > >();

    return { MobilService::Status::CODE_200, dtoSuccess };
  }

  if (queryLocation)
  {
    const auto fixedLocation = fixInputString(*queryLocation);
    auto       dbResult      = m_database->getPlacesLocation(fixedLocation);

    if (!dbResult->isSuccess())
    {
      OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
      auto dtoError     = DtoError::createShared();
      dtoError->type    = ErrorType::SERVER_DATABASE;
      dtoError->message = "Error in fetch place by location";
      return { MobilService::Status::CODE_500, dtoError };
    }

    if (!dbResult->hasMoreToFetch())
    { return { MobilService::Status::CODE_204, {} }; }

    const auto dtoSuccess =
      dbResult->fetch< oatpp::Vector< oatpp::Object< DtoPlace_OUT > > >();

    return { MobilService::Status::CODE_200, dtoSuccess };
  }

  if (queryDescription)
  {
    const auto fixedDescription = fixInputString(*queryDescription);
    auto       dbResult = m_database->getPlacesDescription(fixedDescription);

    if (!dbResult->isSuccess())
    {
      OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
      auto dtoError     = DtoError::createShared();
      dtoError->type    = ErrorType::SERVER_DATABASE;
      dtoError->message = "Error in fetch place by description";
      return { MobilService::Status::CODE_500, dtoError };
    }

    if (!dbResult->hasMoreToFetch())
    { return { MobilService::Status::CODE_204, {} }; }

    const auto dtoSuccess =
      dbResult->fetch< oatpp::Vector< oatpp::Object< DtoPlace_OUT > > >();

    return { MobilService::Status::CODE_200, dtoSuccess };
  }

  auto dbResult = m_database->getPlacesAll();

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in fetch all places";
    return { MobilService::Status::CODE_500, dtoError };
  }

  if (!dbResult->hasMoreToFetch())
  { return { MobilService::Status::CODE_204, {} }; }

  const auto dtoSuccess =
    dbResult->fetch< oatpp::Vector< oatpp::Object< DtoPlace_OUT > > >();

  return { MobilService::Status::CODE_200, dtoSuccess };
}

MobilService::Response MobilService::GET_users(const Queries& queries) {
  if (queries.getSize() == 0)
  {
    auto dbResult = m_database->getUsersAll();

    if (!dbResult->isSuccess())
    {
      OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
      auto dtoError     = DtoError::createShared();
      dtoError->type    = ErrorType::SERVER_DATABASE;
      dtoError->message = "Error in fetch all users";
      return { MobilService::Status::CODE_500, dtoError };
    }

    if (!dbResult->hasMoreToFetch())
    { return { MobilService::Status::CODE_204, {} }; }

    const auto dtoSuccess =
      dbResult->fetch< oatpp::Vector< oatpp::Object< DtoUser_OUT > > >();

    return { MobilService::Status::CODE_200, dtoSuccess };
  }

  if (!isMultiQuerySingle(queries))
  {
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::INPUT_BAD_STRUCTURE;
    dtoError->message = "Multiple queries not supported";
    return { MobilService::Status::CODE_400, dtoError };
  }

  const auto queryID = queries.get("userID");

  if (queryID)
  {
    const auto fixedID =
      oatpp::utils::conversion::strToInt32(fixInputString(*queryID)->c_str());
    auto dbResult = m_database->getUsersID(fixedID);

    if (!dbResult->isSuccess())
    {
      OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
      auto dtoError     = DtoError::createShared();
      dtoError->type    = ErrorType::SERVER_DATABASE;
      dtoError->message = "Error in fetch user by ID";
      return { MobilService::Status::CODE_500, dtoError };
    }

    if (!dbResult->hasMoreToFetch())
    { return { MobilService::Status::CODE_204, {} }; }

    const auto dtoSuccess =
      dbResult->fetch< oatpp::Vector< oatpp::Object< DtoUser_OUT > > >();

    return { MobilService::Status::CODE_200, dtoSuccess };
  }

  auto dbResult = m_database->getUsersAll();

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in fetch all users";
    return { MobilService::Status::CODE_500, dtoError };
  }

  if (!dbResult->hasMoreToFetch())
  { return { MobilService::Status::CODE_204, {} }; }

  const auto dtoSuccess =
    dbResult->fetch< oatpp::Vector< oatpp::Object< DtoUser_OUT > > >();

  return { MobilService::Status::CODE_200, dtoSuccess };
}

MobilService::Response MobilService::GET_comments(
  const oatpp::Int32& placeId,
  const oatpp::Int32& start,
  const oatpp::Int32& end) {
  if (!isRangeValid(start, end))
  {
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::DATA_FORMAT;
    dtoError->message = "Bad range values";
    return { MobilService::Status::CODE_416, dtoError };
  }

  auto dbResult = m_database->getComments(placeId, start, end);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in fetch comments";
    return { MobilService::Status::CODE_500, dtoError };
  }

  if (!dbResult->hasMoreToFetch())
  { return { MobilService::Status::CODE_204, {} }; }

  const auto dtoSuccess =
    dbResult->fetch< oatpp::Vector< oatpp::Object< DtoComment_OUT > > >();

  return { MobilService::Status::CODE_200, dtoSuccess };
}

MobilService::Response MobilService::GET_visitsByPlace(
  const oatpp::Int32& placeId,
  const oatpp::Int32& start,
  const oatpp::Int32& end) {
  if (!isRangeValid(start, end))
  {
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::DATA_FORMAT;
    dtoError->message = "Bad range values";
    return { MobilService::Status::CODE_416, dtoError };
  }

  auto dbResult = m_database->getVisitsByPlace(placeId, start, end);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in fetch visits by place";
    return { MobilService::Status::CODE_500, dtoError };
  }

  if (!dbResult->hasMoreToFetch())
  { return { MobilService::Status::CODE_204, {} }; }

  const auto dtoSuccess =
    dbResult->fetch< oatpp::Vector< oatpp::Object< DtoVisit_OUT > > >();

  return { MobilService::Status::CODE_200, dtoSuccess };
}

MobilService::Response MobilService::GET_visitsByUser(
  const oatpp::Int32& userId,
  const oatpp::Int32& start,
  const oatpp::Int32& end) {
  if (!isRangeValid(start, end))
  {
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::DATA_FORMAT;
    dtoError->message = "Bad range values";
    return { MobilService::Status::CODE_416, dtoError };
  }

  auto dbResult = m_database->getVisitsByUser(userId, start, end);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in fetch visits by user";
    return { MobilService::Status::CODE_500, dtoError };
  }

  if (!dbResult->hasMoreToFetch())
  { return { MobilService::Status::CODE_204, {} }; }

  const auto dtoSuccess =
    dbResult->fetch< oatpp::Vector< oatpp::Object< DtoVisit_OUT > > >();

  return { MobilService::Status::CODE_200, dtoSuccess };
}

MobilService::Response MobilService::GET_ranking(
  const oatpp::Int32& start, const oatpp::Int32& end) {
  if (!isRangeValid(start, end))
  {
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::DATA_FORMAT;
    dtoError->message = "Bad range values";
    return { MobilService::Status::CODE_416, dtoError };
  }

  auto dbResult = m_database->getRanking(start, end);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in fetch ranking";
    return { MobilService::Status::CODE_500, dtoError };
  }

  if (!dbResult->hasMoreToFetch())
  { return { MobilService::Status::CODE_204, {} }; }

  const auto dtoSuccess =
    dbResult->fetch< oatpp::Vector< oatpp::Object< DtoUser_OUT > > >();

  return { MobilService::Status::CODE_200, dtoSuccess };
}

MobilService::Response MobilService::POST_visits(
  const oatpp::String& authUser, const oatpp::String& key) {
  const auto fixedAuthUser = fixInputString(authUser);
  const auto fixedKey      = fixInputString(key);

  auto dbResult = m_database->postVisitsValidate(fixedKey);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in validate visit";
    return { MobilService::Status::CODE_500, dtoError };
  }

  if (!dbResult->hasMoreToFetch())
  {
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::BAD_KEY;
    dtoError->message = "Place with this key not found";
    return { MobilService::Status::CODE_422, dtoError };
  }

  const auto newPlaceId =
    dbResult->fetch< oatpp::Vector< oatpp::Object< DtoPlace_OUT > > >()
      ->front()
      ->id;

  dbResult = m_database->getVisitsByUser(
    m_database->getUsersLogin(authUser)
      ->fetch< oatpp::Vector< oatpp::Object< DtoUser_OUT > > >()
      ->front()
      ->id,
    0,
    INT_MAX);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in fetch visits by user";
    return { MobilService::Status::CODE_500, dtoError };
  }

  const auto visitVec =
    dbResult->fetch< oatpp::Vector< oatpp::Object< DtoVisit_OUT > > >();

  for (const auto& visit : *visitVec)
  {
    if (visit->placeid == newPlaceId)
    {
      auto dtoError     = DtoError::createShared();
      dtoError->type    = ErrorType::CONTENT_EXISTS;
      dtoError->message = "User already visited this place";
      return { MobilService::Status::CODE_409, dtoError };
    }
  }

  dbResult = m_database->postVisitsInsert(
    m_database->getUsersLogin(authUser)
      ->fetch< oatpp::Vector< oatpp::Object< DtoUser_OUT > > >()
      ->front()
      ->username,
    newPlaceId);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in insert visit";
    return { MobilService::Status::CODE_500, dtoError };
  }

  const auto dtoSuccess =
    dbResult->fetch< oatpp::Vector< oatpp::Object< DtoVisit_OUT > > >()->back();

  return { MobilService::Status::CODE_201, dtoSuccess };
}

MobilService::Response MobilService::POST_comments(
  const oatpp::String& authUser,
  const oatpp::Int32&  placeId,
  const oatpp::String& content) {
  const auto fixedAuthUser = fixInputString(authUser);
  const auto fixedContent  = fixInputString(content);

  auto dbResult = m_database->getUsersLogin(fixedAuthUser);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in fetch user";
    return { MobilService::Status::CODE_500, dtoError };
  }

  const auto user = dbResult->fetch< oatpp::Vector<oatpp::Object< DtoUser_OUT >> >()->front();

  dbResult = m_database->postCommentsValidate(user->username, placeId);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in validate comment";
    return { MobilService::Status::CODE_500, dtoError };
  }

  if (content->size() > 499)
  {
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::DATA_FORMAT;
    dtoError->message = "Content too long";
    return { MobilService::Status::CODE_422, dtoError };
  }

  if (!dbResult->hasMoreToFetch())
  {
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::BAD_KEY;
    dtoError->message = "User did not visit this place";
    return { MobilService::Status::CODE_412, dtoError };
  }

  dbResult =
    m_database->postCommentsInsert(user->username, placeId, fixedContent);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in insert comment";
    return { MobilService::Status::CODE_500, dtoError };
  }

  const auto dtoSuccess =
    dbResult->fetch< oatpp::Vector< oatpp::Object< DtoComment_OUT > > >()
      ->back();

  return { MobilService::Status::CODE_201, dtoSuccess };
}

// ADMIN API ENDPOINTS ---------------------------------------------------------

MobilService::Response MobilService::PUT_places(
  const oatpp::String& name,
  const oatpp::String& description,
  const oatpp::String& location,
  const oatpp::String& key) {
  const auto fixedName        = fixInputString(name);
  const auto fixedDescription = fixInputString(description);
  const auto fixedLocation    = fixInputString(location);
  const auto fixedKey         = fixInputString(key);

  auto dbResult = m_database->getPlacesName(fixedName);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in check conflict place";
    return { MobilService::Status::CODE_500, dtoError };
  }

  if (dbResult->hasMoreToFetch())
  {
    const auto updatedId =
      dbResult->fetch< oatpp::Vector< oatpp::Object<DtoPlace_OUT > >>()->front()->id;

    dbResult = m_database->putPlacesUpdate(
      updatedId, fixedName, fixedDescription, fixedLocation, fixedKey);

    if (!dbResult->isSuccess())
    {
      OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
      auto dtoError     = DtoError::createShared();
      dtoError->type    = ErrorType::CONTENT_EXISTS;
      dtoError->message = "Field conflict in update place";
      return { MobilService::Status::CODE_409, dtoError };
    }

    const auto dtoSuccess =
      dbResult->fetch< oatpp::Vector< oatpp::Object< DtoPlace_OUT > > >()
        ->back();

    return { MobilService::Status::CODE_200, dtoSuccess };
  }

  dbResult = m_database->putPlacesInsert(
    fixedName, fixedDescription, fixedLocation, fixedKey);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in insert place";
    return { MobilService::Status::CODE_500, dtoError };
  }

  const auto dtoSuccess =
    dbResult->fetch< oatpp::Vector< oatpp::Object< DtoPlace_OUT > > >()->back();

  return { MobilService::Status::CODE_201, dtoSuccess };
}

MobilService::Response MobilService::DELETE_places(
  const oatpp::Int32& placeId) {
  auto dbResult = m_database->getPlacesID(placeId);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in fetch place by ID";
    return { MobilService::Status::CODE_500, dtoError };
  }

  if (!dbResult->hasMoreToFetch())
  {
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::BAD_KEY;
    dtoError->message = "Place with this ID not found";
    return { MobilService::Status::CODE_404, dtoError };
  }

  dbResult = m_database->deletePlaces(placeId);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in delete place";
    return { MobilService::Status::CODE_500, dtoError };
  }

  return { MobilService::Status::CODE_204, oatpp::String() };
}

MobilService::Response MobilService::PUT_users(
  const oatpp::String&  username,
  const oatpp::String&  login,
  const oatpp::String&  password,
  const oatpp::Boolean& isAdmin,
  const oatpp::Int32&   points) {
  const auto fixedUsername = fixInputString(username);
  const auto fixedLogin    = fixInputString(login);
  const auto fixedPassword = fixInputString(password);

  auto dbResult = m_database->getUsersUsername(fixedUsername);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in check conflict user";
    return { MobilService::Status::CODE_500, dtoError };
  }

  if (dbResult->hasMoreToFetch())
  {
    const auto updatedId =
      dbResult->fetch< oatpp::Vector< oatpp::Object<DtoUser_OUT >> >()->front()->id;

    dbResult = m_database->putUsersUpdate(
      updatedId, fixedUsername, fixedLogin, fixedPassword, isAdmin, points);

    if (!dbResult->isSuccess())
    {
      OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
      auto dtoError     = DtoError::createShared();
      dtoError->type    = ErrorType::CONTENT_EXISTS;
      dtoError->message = "Field conflict in update user";
      return { MobilService::Status::CODE_409, dtoError };
    }

    const auto dtoSuccess =
      dbResult->fetch< oatpp::Vector< oatpp::Object< DtoUser_OUT > > >()
        ->back();

    return { MobilService::Status::CODE_200, dtoSuccess };
  }

  dbResult = m_database->putUsersInsert(
    fixedUsername, fixedLogin, fixedPassword, isAdmin, points);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in insert user";
    return { MobilService::Status::CODE_500, dtoError };
  }

  const auto dtoSuccess =
    dbResult->fetch< oatpp::Vector< oatpp::Object< DtoUser_OUT > > >()->back();

  return { MobilService::Status::CODE_201, dtoSuccess };
}

MobilService::Response MobilService::DELETE_users(const oatpp::Int32& userId) {
  auto dbResult = m_database->getUsersID(userId);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in fetch user by ID";
    return { MobilService::Status::CODE_500, dtoError };
  }

  if (!dbResult->hasMoreToFetch())
  {
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::BAD_KEY;
    dtoError->message = "User with this ID not found";
    return { MobilService::Status::CODE_404, dtoError };
  }

  dbResult = m_database->deleteUsers(userId);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in delete user";
    return { MobilService::Status::CODE_500, dtoError };
  }

  return { MobilService::Status::CODE_204, oatpp::String() };
}

MobilService::Response MobilService::PUT_visits(
  const oatpp::Int32& userId, const oatpp::Int32& placeId) {
  auto dbResult = m_database->existsVisits(-1, userId, placeId);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in check conflict visit";
    return { MobilService::Status::CODE_500, dtoError };
  }

  if (dbResult->hasMoreToFetch())
  {
    const auto updatedId =
      dbResult->fetch< oatpp::Vector< oatpp::Object<DtoVisit_OUT> > >()->front()->id;

    dbResult = m_database->putVisitsUpdate(updatedId, userId, placeId);

    if (!dbResult->isSuccess())
    {
      OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
      auto dtoError     = DtoError::createShared();
      dtoError->type    = ErrorType::CONTENT_EXISTS;
      dtoError->message = "Field conflict in update visit";
      return { MobilService::Status::CODE_409, dtoError };
    }

    const auto dtoSuccess =
      dbResult->fetch< oatpp::Vector< oatpp::Object< DtoVisit_OUT > > >()
        ->back();

    return { MobilService::Status::CODE_200, dtoSuccess };
  }

  dbResult = m_database->putVisitsInsert(userId, placeId);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in insert visit";
    return { MobilService::Status::CODE_500, dtoError };
  }

  const auto dtoSuccess =
    dbResult->fetch< oatpp::Vector< oatpp::Object< DtoVisit_OUT > > >()->back();

  return { MobilService::Status::CODE_201, dtoSuccess };
}

MobilService::Response MobilService::DELETE_visits(
  const oatpp::Int32& visitId) {
  auto dbResult = m_database->existsVisits(visitId, -1, -1);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in fetch visit by ID";
    return { MobilService::Status::CODE_500, dtoError };
  }

  if (!dbResult->hasMoreToFetch())
  {
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::BAD_KEY;
    dtoError->message = "Visit with this ID not found";
    return { MobilService::Status::CODE_404, dtoError };
  }

  dbResult = m_database->deleteVisits(visitId);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in delete visit";
    return { MobilService::Status::CODE_500, dtoError };
  }

  return { MobilService::Status::CODE_204, oatpp::String() };
}

MobilService::Response MobilService::PUT_comments(
  const oatpp::Int32&  userId,
  const oatpp::Int32&  placeId,
  const oatpp::String& content,
  const oatpp::Int32&  likes) {
  const auto fixedContent = fixInputString(content);

  auto dbResult = m_database->existsComments(-1, userId, placeId);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in check conflict comment";
    return { MobilService::Status::CODE_500, dtoError };
  }

  if (dbResult->hasMoreToFetch())
  {
    const auto updatedId =
      dbResult->fetch< oatpp::Vector<oatpp::Object< DtoComment_OUT > >>()->front()->id;

    dbResult =
      m_database->putCommentsUpdate(updatedId, userId, placeId, fixedContent);

    if (!dbResult->isSuccess())
    {
      OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
      auto dtoError     = DtoError::createShared();
      dtoError->type    = ErrorType::CONTENT_EXISTS;
      dtoError->message = "Field conflict in update comment";
      return { MobilService::Status::CODE_409, dtoError };
    }

    const auto dtoSuccess =
      dbResult->fetch< oatpp::Vector< oatpp::Object< DtoComment_OUT > > >()
        ->back();

    return { MobilService::Status::CODE_200, dtoSuccess };
  }

  dbResult = m_database->putCommentsInsert(userId, placeId, fixedContent);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in insert comment";
    return { MobilService::Status::CODE_500, dtoError };
  }

  const auto dtoSuccess =
    dbResult->fetch< oatpp::Vector< oatpp::Object< DtoComment_OUT > > >()
      ->back();

  return { MobilService::Status::CODE_201, dtoSuccess };
}

MobilService::Response MobilService::DELETE_comments(
  const oatpp::Int32& commentId) {
  auto dbResult = m_database->existsComments(commentId, -1, -1);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in fetch comment by ID";
    return { MobilService::Status::CODE_500, dtoError };
  }

  if (!dbResult->hasMoreToFetch())
  {
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::BAD_KEY;
    dtoError->message = "Comment with this ID not found";
    return { MobilService::Status::CODE_404, dtoError };
  }

  dbResult = m_database->deleteComments(commentId);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    auto dtoError     = DtoError::createShared();
    dtoError->type    = ErrorType::SERVER_DATABASE;
    dtoError->message = "Error in delete comment";
    return { MobilService::Status::CODE_500, dtoError };
  }

  return { MobilService::Status::CODE_204, oatpp::String() };
}

// AUTHORIZATION ---------------------------------------------------------------

MobilService::Auth MobilService::authorize(const AuthObject& authObject) {
  const auto fixedLogin    = fixInputString(authObject->userId);
  const auto fixedPassword = fixInputString(authObject->password);

  auto dbResult = m_database->authorize(fixedLogin, fixedPassword);

  if (!dbResult->isSuccess())
  {
    OATPP_LOGD("", dbResult->getErrorMessage()->c_str());
    return Auth::ERR;
  }
  if (!dbResult->hasMoreToFetch()) { return Auth::BAD_CREDENTIALS; }

  const auto dtoSuccess =
    *dbResult->fetch< oatpp::Vector< oatpp::Object< DtoAuth_DB > > >()->begin();

  if (dtoSuccess->admin) { return Auth::ADMIN; }

  return Auth::USER;
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
  return start >= 0 && end >= 0 && start < end;
}
