#ifndef CRUD_USERSERVICE_HPP
#define CRUD_USERSERVICE_HPP

#include <variant>
#include "db/MobilDatabase.hpp"
#include "dto/DtoError.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

class MobilService {
private:
  OATPP_COMPONENT(
    std::shared_ptr< MobilDatabase >, m_database); // Inject database component

public:
  // TYPES ---------------------------------------------------------------------
  using Status   = oatpp::web::protocol::http::Status;
  using Response = std::pair< Status, oatpp::Void >;
  using Queries  = oatpp::data::share::LazyStringMultimap<
     oatpp::data::share::StringKeyLabel >;
  using AuthObject = std::shared_ptr<
    oatpp::web::server::handler::DefaultBasicAuthorizationObject >;

  // USER TYPES ----------------------------------------------------------------
  enum class Auth : std::int_fast8_t {
    BAD_CREDENTIALS = 0,
    USER            = 1,
    ADMIN           = 2,
    ERR             = 3
  };

  // LOGIN API ENDPOINTS -------------------------------------------------------
  Response POST_login(const oatpp::String& login);
  Response POST_register(
    const oatpp::String& username,
    const oatpp::String& login,
    const oatpp::String& password);
  static Response GET_logout();

  // USER API ENDPOINTS --------------------------------------------------------
  Response GET_places(const Queries& queries);
  Response GET_users(const Queries& queries);
  Response GET_comments(
    const oatpp::Int32& placeId,
    const oatpp::Int32& start,
    const oatpp::Int32& end);
  Response GET_visitsByPlace(
    const oatpp::Int32& placeId,
    const oatpp::Int32& start,
    const oatpp::Int32& end);
  Response GET_visitsByUser(
    const oatpp::Int32& userId,
    const oatpp::Int32& start,
    const oatpp::Int32& end);
  Response GET_ranking(const oatpp::Int32& start, const oatpp::Int32& end);
  Response POST_visits(const oatpp::String& authUser, const oatpp::String& key);
  Response POST_comments(
    const oatpp::String& authUser,
    const oatpp::Int32&  placeId,
    const oatpp::String& content);

  // ADMIN API ENDPOINTS -------------------------------------------------------
  Response PUT_places(
    const oatpp::String& name,
    const oatpp::String& description,
    const oatpp::String& location,
    const oatpp::String& key);
  Response DELETE_places(const oatpp::Int32& placeId);
  Response PUT_users(
    const oatpp::String&  username,
    const oatpp::String&  login,
    const oatpp::String&  password,
    const oatpp::Boolean& isAdmin,
    const oatpp::Int32&   points);
  Response DELETE_users(const oatpp::Int32& userId);
  Response PUT_visits(const oatpp::Int32& userId, const oatpp::Int32& placeId);
  Response DELETE_visits(const oatpp::Int32& visitId);
  Response PUT_comments(
    const oatpp::Int32&  userId,
    const oatpp::Int32&  placeId,
    const oatpp::String& content,
    const oatpp::Int32&  likes);
  Response DELETE_comments(const oatpp::Int32& commentId);

  // AUTHORIZATION -------------------------------------------------------------
  Auth authorize(const AuthObject& authObject);

private:
  // UTILS ---------------------------------------------------------------------
  static oatpp::String fixInputString(const oatpp::String& input);
  static bool          isMultiQuerySingle(const Queries& queries);
  static bool isRangeValid(const oatpp::Int32& start, const oatpp::Int32& end);
};

#endif // CRUD_USERSERVICE_HPP