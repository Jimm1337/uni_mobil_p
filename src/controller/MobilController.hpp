#ifndef MyController_hpp
#define MyController_hpp

#include <variant>
#include "dto/DtoAdminComment_IN.hpp"
#include "dto/DtoAdminVisit_IN.hpp"
#include "dto/DtoComment_IN.hpp"
#include "dto/DtoComment_OUT.hpp"
#include "dto/DtoError.hpp"
#include "dto/DtoPlace_IN.hpp"
#include "dto/DtoPlace_OUT.hpp"
#include "dto/DtoRegister_IN.hpp"
#include "dto/DtoUser_IN.hpp"
#include "dto/DtoUser_OUT.hpp"
#include "dto/DtoVisit_OUT.hpp"
#include "enum/EnumErrorType.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "service/MobilService.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class MobilController : public oatpp::web::server::api::ApiController {
  MobilService service; // Create user service.

public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  MobilController(
    OATPP_COMPONENT(std::shared_ptr< ObjectMapper >, objectMapper)):
    oatpp::web::server::api::ApiController(objectMapper) {
    setDefaultAuthorizationHandler(
      std::make_shared<
        oatpp::web::server::handler::BasicAuthorizationHandler >(
        "mobil-realm"));
  }

  static std::shared_ptr< MobilController > createShared(OATPP_COMPONENT(
    std::shared_ptr< ObjectMapper >,
    objectMapper) // Inject objectMapper component here as default parameter
  ) {
    return std::make_shared< MobilController >(objectMapper);
  }

  // LOGIN API ENDPOINTS -------------------------------------------------------

  ENDPOINT_INFO(postLogin) {
    info->summary = "Login user.";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< Object< DtoUser_OUT > >(
      Status::CODE_200, "application/json");
    info->addTag("Login");
    info->addSecurityRequirement("Login");
  }
  ENDPOINT(
    "POST",
    "/login",
    postLogin,
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    if (service.authorize(authObject) == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (service.authorize(authObject) == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] = service.POST_login(authObject->userId);
    return createDtoResponse(status, response);
  }
  ADD_CORS(postLogin, "*", "GET, POST, PUT, DELETE")

  ENDPOINT_INFO(postRegister) {
    info->summary = "Register user.";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_409, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_400, "application/json");
    info->addResponse< Object< DtoUser_OUT > >(
      Status::CODE_201, "application/json");
    info->addConsumes< Object< DtoRegister_IN > >(
      "application/json", "User data");
    info->addTag("Login");
  }
  ENDPOINT(
    "POST",
    "/register",
    postRegister,
    BODY_DTO(Object< DtoRegister_IN >, registerData)) {
    if (
      registerData->Username == nullptr || registerData->Login == nullptr ||
      registerData->Password == nullptr)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::INPUT_BAD_STRUCTURE;
      dto->message = "Invalid json input";
      return createDtoResponse(Status::CODE_400, dto);
    }

    const auto [status, response] = service.POST_register(
      registerData->Username, registerData->Login, registerData->Password);
    return createDtoResponse(status, response);
  }
  ADD_CORS(postRegister, "*", "GET, POST, PUT, DELETE")

  ENDPOINT_INFO(getLogout) {
    info->summary = "Logout user.";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< String >(Status::CODE_401, "text/plain");
    info->addTag("Login");
    info->addSecurityRequirement("Login");
  }
  ENDPOINT(
    "GET",
    "/logout",
    getLogout,
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    if (service.authorize(authObject) == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (service.authorize(authObject) == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] = service.GET_logout();
    return createDtoResponse(status, response);
  }
  ADD_CORS(getLogout, "*", "GET, POST, PUT, DELETE")

  // USER API ENDPOINTS --------------------------------------------------------

  ENDPOINT_INFO(getPlaces) {
    info->summary =
      "Get places by any unique data. Use one data field only. (QueryParams: "
      "placeID, name, location, description)";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_400, "application/json");
    info->addResponse< String >(Status::CODE_204, "text/plain");
    info->addResponse< oatpp::Vector< Object< DtoPlace_OUT > > >(
      Status::CODE_200, "application/json");
    info->addTag("User");
    info->addSecurityRequirement("User");
  }
  ENDPOINT(
    "GET",
    "/places",
    getPlaces,
    QUERIES(QueryParams, queryParams),
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    if (service.authorize(authObject) == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (service.authorize(authObject) == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] = service.GET_places(queryParams);

    if (status == Status::CODE_204)
    { return createResponse(Status::CODE_204, "No content"); }

    return createDtoResponse(status, response);
  }
  ADD_CORS(getPlaces, "*", "GET, POST, PUT, DELETE")

  ENDPOINT_INFO(getUsers) {
    info->summary = "Get users by any unique data. Use one data field only. "
                    "(QueryParams: userID, username)";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_400, "application/json");
    info->addResponse< String >(Status::CODE_204, "text/plain");
    info->addResponse< List< Object< DtoUser_OUT > > >(
      Status::CODE_200, "application/json");
    info->addTag("User");
    info->addSecurityRequirement("User");
  }
  ENDPOINT(
    "GET",
    "/users",
    getUsers,
    QUERIES(QueryParams, queryParams),
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    if (service.authorize(authObject) == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (service.authorize(authObject) == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] = service.GET_users(queryParams);

    if (status == Status::CODE_204)
    { return createResponse(Status::CODE_204, "No content"); }

    return createDtoResponse(status, response);
  }
  ADD_CORS(getUsers, "*", "GET, POST, PUT, DELETE")

  ENDPOINT_INFO(getCommentsForPlace) {
    info->summary =
      "Get comments sorted descending by time for place by placeID in range.";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_416, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< String >(Status::CODE_204, "text/plain");
    info->addResponse< oatpp::Vector< Object< DtoComment_OUT > > >(
      Status::CODE_200, "application/json");
    info->addTag("User");
    info->addSecurityRequirement("User");
  }
  ENDPOINT(
    "GET",
    "/comments/{placeID}",
    getCommentsForPlace,
    PATH(Int32, placeID),
    QUERY(Int32, start),
    QUERY(Int32, end),
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    if (service.authorize(authObject) == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (service.authorize(authObject) == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] = service.GET_comments(placeID, start, end);

    if (status == Status::CODE_204)
    { return createResponse(Status::CODE_204, "No content"); }

    return createDtoResponse(status, response);
  }
  ADD_CORS(getCommentsForPlace, "*", "GET, POST, PUT, DELETE")

  ENDPOINT_INFO(getVisitsForPlace) {
    info->summary =
      "Get visits sorted descending by time for place by placeID in range.";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_416, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< String >(Status::CODE_204, "text/plain");
    info->addResponse< oatpp::Vector< Object< DtoVisit_OUT > > >(
      Status::CODE_200, "application/json");
    info->addTag("User");
    info->addSecurityRequirement("User");
  }
  ENDPOINT(
    "GET",
    "/visits/place/{placeID}",
    getVisitsForPlace,
    PATH(Int32, placeID),
    QUERY(Int32, start),
    QUERY(Int32, end),
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    if (service.authorize(authObject) == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (service.authorize(authObject) == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] =
      service.GET_visitsByPlace(placeID, start, end);

    if (status == Status::CODE_204)
    { return createResponse(Status::CODE_204, "No content"); }

    return createDtoResponse(status, response);
  }
  ADD_CORS(getVisitsForPlace, "*", "GET, POST, PUT, DELETE")

  ENDPOINT_INFO(getVisitsForUser) {
    info->summary =
      "Get visits sorted descending by time for user by userID in range.";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_416, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< String >(Status::CODE_204, "text/plain");
    info->addResponse< oatpp::Vector< Object< DtoVisit_OUT > > >(
      Status::CODE_200, "application/json");
    info->addTag("User");
    info->addSecurityRequirement("User");
  }
  ENDPOINT(
    "GET",
    "/visits/user/{userID}",
    getVisitsForUser,
    PATH(Int32, userID),
    QUERY(Int32, start),
    QUERY(Int32, end),
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    if (service.authorize(authObject) == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (service.authorize(authObject) == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] =
      service.GET_visitsByUser(userID, start, end);

    if (status == Status::CODE_204) {
      return createResponse(Status::CODE_204, "No content");
    }

    return createDtoResponse(status, response);
  }
  ADD_CORS(getVisitsForUser, "*", "GET, POST, PUT, DELETE")

  ENDPOINT_INFO(getUserRanking) {
    info->summary = "Get user ranking in range.";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_416, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< List< Object< DtoUser_OUT > > >(
      Status::CODE_200, "application/json");
    info->addTag("User");
    info->addSecurityRequirement("User");
  }
  ENDPOINT(
    "GET",
    "/ranking",
    getUserRanking,
    QUERY(Int32, start),
    QUERY(Int32, end),
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    if (service.authorize(authObject) == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (service.authorize(authObject) == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] = service.GET_ranking(start, end);
    return createDtoResponse(status, response);
  }
  ADD_CORS(getUserRanking, "*", "GET, POST, PUT, DELETE")

  ENDPOINT_INFO(postVisits) {
    info->summary = "Add visit to place by key for user.";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_422, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_409, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< Object< DtoVisit_OUT > >(
      Status::CODE_201, "application/json");
    info->addTag("User");
    info->addSecurityRequirement("User");
  }
  ENDPOINT(
    "POST",
    "/visits",
    postVisits,
    QUERY(String, key),
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    if (service.authorize(authObject) == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (service.authorize(authObject) == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] =
      service.POST_visits(authObject->userId, key);
    return createDtoResponse(status, response);
  }
  ADD_CORS(postVisits, "*", "GET, POST, PUT, DELETE")

  ENDPOINT_INFO(postAddComments) {
    info->summary = "Add comment to place by placeID for user.";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_422, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_412, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< Object< DtoComment_OUT > >(
      Status::CODE_201, "application/json");
    info->addConsumes< Object< DtoComment_IN > >(
      "application/json", "Comment data");
    info->addTag("User");
    info->addSecurityRequirement("User");
  }
  ENDPOINT(
    "POST",
    "/comments",
    postAddComments,
    BODY_DTO(Object< DtoComment_IN >, comment),
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    if (service.authorize(authObject) == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (service.authorize(authObject) == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] = service.POST_comments(
      authObject->userId, comment->PlaceID, comment->Content);
    return createDtoResponse(status, response);
  }
  ADD_CORS(postAddComments, "*", "GET, POST, PUT, DELETE")

  // ADMIN API ENDPOINTS -------------------------------------------------------

  ENDPOINT_INFO(putAdminAddUpdatePlaces) {
    info->summary = "Add or update place in database. Update when: matching name";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_422, "application/json");
    info->addResponse< Object< DtoPlace_OUT > >(
      Status::CODE_200, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_403, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_409, "application/json");
    info->addResponse< Object< DtoPlace_OUT > >(
      Status::CODE_201, "application/json");
    info->addConsumes< Object< DtoPlace_IN > >(
      "application/json", "Place data");
    info->addTag("Admin");
    info->addSecurityRequirement("Admin");
  }
  ENDPOINT(
    "PUT",
    "/places",
    putAdminAddUpdatePlaces,
    BODY_DTO(Object< DtoPlace_IN >, place),
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    const auto auth = service.authorize(authObject);

    if (auth == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (auth == MobilService::Auth::USER) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_PERMISSION;
      dto->message = "Insufficient permission";
      return createDtoResponse(Status::CODE_403, dto);
    } else if (auth == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] = service.PUT_places(
      place->Name, place->Description, place->Location, place->Key);
    return createDtoResponse(status, response);
  }
  ADD_CORS(putAdminAddUpdatePlaces, "*", "GET, POST, PUT, DELETE")

  ENDPOINT_INFO(deleteAdminRemovePlaces) {
    info->summary = "Remove place from database.";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_404, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_403, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< String >(Status::CODE_204, "text/plain");
    info->addTag("Admin");
    info->addSecurityRequirement("Admin");
  }
  ENDPOINT(
    "DELETE",
    "/places",
    deleteAdminRemovePlaces,
    QUERY(Int32, placeID),
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    const auto auth = service.authorize(authObject);

    if (auth == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (auth == MobilService::Auth::USER) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_PERMISSION;
      dto->message = "Insufficient permission";
      return createDtoResponse(Status::CODE_403, dto);
    } else if (auth == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] = service.DELETE_places(placeID);
    return createDtoResponse(status, response);
  }
  ADD_CORS(deleteAdminRemovePlaces, "*", "GET, POST, PUT, DELETE")

  ENDPOINT_INFO(putAdminAddUpdateUsers) {
    info->summary = "Add or update user in database. Update when: matching "
                    "username";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_422, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_403, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< Object< DtoUser_OUT > >(
      Status::CODE_200, "application/json");
    info->addResponse< Object< DtoUser_OUT > >(
      Status::CODE_201, "application/json");
    info->addConsumes< Object< DtoUser_IN > >("application/json", "User data");
    info->addTag("Admin");
    info->addSecurityRequirement("Admin");
  }
  ENDPOINT(
    "PUT",
    "/users",
    putAdminAddUpdateUsers,
    BODY_DTO(Object< DtoUser_IN >, user),
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    const auto auth = service.authorize(authObject);

    if (auth == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (auth == MobilService::Auth::USER) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_PERMISSION;
      dto->message = "Insufficient permission";
      return createDtoResponse(Status::CODE_403, dto);
    } else if (auth == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] = service.PUT_users(
      user->Username, user->Login, user->Password, user->Admin, user->Points);
    return createDtoResponse(status, response);
  }
  ADD_CORS(putAdminAddUpdateUsers, "*", "GET, POST, PUT, DELETE")

  ENDPOINT_INFO(deleteAdminRemoveUsers) {
    info->summary = "Remove user from database.";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_404, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_403, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< String >(Status::CODE_204, "text/plain");
    info->addTag("Admin");
    info->addSecurityRequirement("Admin");
  }
  ENDPOINT(
    "DELETE",
    "/users",
    deleteAdminRemoveUsers,
    QUERY(Int32, userID),
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    const auto auth = service.authorize(authObject);

    if (auth == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (auth == MobilService::Auth::USER) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_PERMISSION;
      dto->message = "Insufficient permission";
      return createDtoResponse(Status::CODE_403, dto);
    } else if (auth == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] = service.DELETE_users(userID);
    return createDtoResponse(status, response);
  }
  ADD_CORS(deleteAdminRemoveUsers, "*", "GET, POST, PUT, DELETE")

  ENDPOINT_INFO(putAdminAddUpdateComments) {
    info->summary = "Add or update comment in database. Update when: matching placeID and userID";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_422, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_403, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< Object< DtoComment_OUT > >(
      Status::CODE_200, "application/json");
    info->addResponse< Object< DtoComment_OUT > >(
      Status::CODE_201, "application/json");
    info->addConsumes< Object< DtoAdminComment_IN > >(
      "application/json", "Comment data");
    info->addTag("Admin");
    info->addSecurityRequirement("Admin");
  }
  ENDPOINT(
    "PUT",
    "/comments",
    putAdminAddUpdateComments,
    BODY_DTO(Object< DtoAdminComment_IN >, comment),
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    const auto auth = service.authorize(authObject);

    if (auth == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (auth == MobilService::Auth::USER) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_PERMISSION;
      dto->message = "Insufficient permission";
      return createDtoResponse(Status::CODE_403, dto);
    } else if (auth == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] = service.PUT_comments(
      comment->UserID, comment->PlaceID, comment->Content, comment->Likes);
    return createDtoResponse(status, response);
  }
  ADD_CORS(putAdminAddUpdateComments, "*", "GET, POST, PUT, DELETE")

  ENDPOINT_INFO(deleteAdminRemoveComments) {
    info->summary = "Remove comment from database.";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_404, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_403, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< String >(Status::CODE_204, "text/plain");
    info->addTag("Admin");
    info->addSecurityRequirement("Admin");
  }
  ENDPOINT(
    "DELETE",
    "/comments",
    deleteAdminRemoveComments,
    QUERY(Int32, commentID),
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    const auto auth = service.authorize(authObject);

    if (auth == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (auth == MobilService::Auth::USER) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_PERMISSION;
      dto->message = "Insufficient permission";
      return createDtoResponse(Status::CODE_403, dto);
    } else if (auth == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] = service.DELETE_comments(commentID);
    return createDtoResponse(status, response);
  }
  ADD_CORS(deleteAdminRemoveComments, "*", "GET, POST, PUT, DELETE")

  ENDPOINT_INFO(putAdminAddUpdateVisits) {
    info->summary = "Add or update visit in database. Update when: matching "
                    "placeID and userID";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_422, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_403, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< Object< DtoVisit_OUT > >(
      Status::CODE_200, "application/json");
    info->addResponse< Object< DtoVisit_OUT > >(
      Status::CODE_201, "application/json");
    info->addConsumes< Object< DtoAdminVisit_IN > >(
      "application/json", "Visit data");
    info->addTag("Admin");
    info->addSecurityRequirement("Admin");
  }
  ENDPOINT(
    "PUT",
    "/visits",
    putAdminAddUpdateVisits,
    BODY_DTO(Object< DtoAdminVisit_IN >, visit),
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    const auto auth = service.authorize(authObject);

    if (auth == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (auth == MobilService::Auth::USER) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_PERMISSION;
      dto->message = "Insufficient permission";
      return createDtoResponse(Status::CODE_403, dto);
    } else if (auth == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] =
      service.PUT_visits(visit->UserID, visit->PlaceID);
    return createDtoResponse(status, response);
  }
  ADD_CORS(putAdminAddUpdateVisits, "*", "GET, POST, PUT, DELETE")

  ENDPOINT_INFO(deleteAdminRemoveVisits) {
    info->summary = "Remove visit from database.";
    info->addResponse< Object< DtoError > >(
      Status::CODE_500, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_404, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_403, "application/json");
    info->addResponse< Object< DtoError > >(
      Status::CODE_401, "application/json");
    info->addResponse< String >(Status::CODE_204, "text/plain");
    info->addTag("Admin");
    info->addSecurityRequirement("Admin");
  }
  ENDPOINT(
    "DELETE",
    "/visits",
    deleteAdminRemoveVisits,
    QUERY(Int32, visitID),
    AUTHORIZATION(
      std::shared_ptr<
        oatpp::web::server::handler::DefaultBasicAuthorizationObject >,
      authObject)) {
    const auto auth = service.authorize(authObject);

    if (auth == MobilService::Auth::BAD_CREDENTIALS)
    {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_BAD_CREDENTIALS;
      dto->message = "Bad credentials";
      return createDtoResponse(Status::CODE_401, dto);
    } else if (auth == MobilService::Auth::USER) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::AUTH_PERMISSION;
      dto->message = "Insufficient permission";
      return createDtoResponse(Status::CODE_403, dto);
    } else if (auth == MobilService::Auth::ERR) {
      auto dto     = DtoError::createShared();
      dto->type    = ErrorType::SERVER_DATABASE;
      dto->message = "ERROR IN AUTH";
      return createDtoResponse(Status::CODE_500, dto);
    }

    const auto [status, response] = service.DELETE_visits(visitID);
    return createDtoResponse(status, response);
  }
  ADD_CORS(deleteAdminRemoveVisits, "*", "GET, POST, PUT, DELETE")
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */
