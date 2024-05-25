#ifndef BDDatabase_hpp
#define BDDatabase_hpp

#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * UserDb client definitions.
 */
class MobilDatabase : public oatpp::orm::DbClient {
public:
  MobilDatabase(const std::shared_ptr< oatpp::orm::Executor >& executor):
    oatpp::orm::DbClient(executor) {
    // TODO: uncomment to enable migrations

    //    oatpp::orm::SchemaMigration migration(executor);
    //    migration.addFile(1, DATABASE_MIGRATIONS "/001_init.sql");
    //    Add more migrations here.
    //    migration.migrate(); // <-- run migrations. This guy will throw
    //
    //    auto version = executor->getSchemaVersion();
    //    OATPP_LOGD("UserDb", "Migration - OK. Version=%lld.", version);
  }

  // todo

  // GENERAL -------------------------------------------------------------------

  QUERY(
    existsPlaces,
    "SELECT * FROM F_EXISTS_PLACES(:placeName);",
    PARAM(oatpp::String, placeName))

  QUERY(
    existsUsers,
    "SELECT * FROM F_EXISTS_USERS(:username);",
    PARAM(oatpp::String, username))

  QUERY(
    existsVisits,
    "SELECT * FROM F_EXISTS_VISITS(:userID, :placeID);",
    PARAM(oatpp::Int32, userID),
    PARAM(oatpp::Int32, placeID))

  // LOGIN API -----------------------------------------------------------------

  QUERY(
    postLogin,
    "SELECT * FROM F_POST_LOGIN(:login, :password);",
    PARAM(oatpp::String, login),
    PARAM(oatpp::String, password))

  QUERY(
    postRegister,
    "SELECT * FROM F_POST_REGISTER(:username, :login, :password);",
    PARAM(oatpp::String, username),
    PARAM(oatpp::String, login),
    PARAM(oatpp::String, password))

  // USER API ------------------------------------------------------------------

  QUERY(
    getPlacesID, "SELECT * FROM F_GET_PLACES(:placeID);", PARAM(oatpp::Int32, placeID))

  QUERY(
    getPlacesName,
    "SELECT * FROM F_GET_PLACES_NAME(:name);",
    PARAM(oatpp::String, name))

  QUERY(
    getPlacesLocation,
    "SELECT * FROM F_GET_PLACES_LOCATION(:location);",
    PARAM(oatpp::String, location))

  QUERY(
    getPlacesDescription,
    "SELECT * FROM F_GET_PLACES_DESC(:description);",
    PARAM(oatpp::String, description))

  QUERY(
    getUsersID,
    "SELECT * FROM F_GET_USERS_ID(:userID);",
    PARAM(oatpp::Int32, userID))

  QUERY(
    getUsersUsername,
    "SELECT * FROM F_GET_USERS_USERNAME(:username);",
    PARAM(oatpp::String, username))

  QUERY(
    getComments,
    "SELECT * FROM F_GET_COMMENTS(:placeID);",
    PARAM(oatpp::Int32, placeID))

  QUERY(
    getVisitsByPlace,
    "SELECT * FROM F_GET_VISITS_PLACE(:placeID);",
    PARAM(oatpp::Int32, placeID))

  QUERY(
    getVisitsByUser,
    "SELECT * FROM F_GET_VISITS_USER(:userID);",
    PARAM(oatpp::Int32, userID))

  QUERY(getRanking, "SELECT * FROM F_GET_RANKING();")

  QUERY(
    postVisitsValidate,
    "SELECT * FROM F_POST_VISITS_VALIDATE(:key);",
    PARAM(oatpp::String, key))

  QUERY(
    postVisitsInsert,
    "SELECT * FROM F_POST_VISITS_INSERT(:username, :placeID);",
    PARAM(oatpp::String, username),
    PARAM(oatpp::Int32, placeID))

  QUERY(
    postCommentsValidate,
    "SELECT * FROM F_POST_COMMENTS_VALIDATE(:username, :placeID);",
    PARAM(oatpp::String, username),
    PARAM(oatpp::Int32, placeID))

  QUERY(
    postCommentsInsert,
    "SELECT * FROM F_POST_COMMENTS_INSERT(:username, :placeID, :content);",
    PARAM(oatpp::String, username),
    PARAM(oatpp::Int32, placeID),
    PARAM(oatpp::String, content))

  // ADMIN API -----------------------------------------------------------------

  QUERY(
    putPlacesUpdate,
    "SELECT * FROM F_PUT_PLACES_UPDATE(:placeID, :name, :description, "
    ":location, "
    ":key);",
    PARAM(oatpp::Int32, placeID),
    PARAM(oatpp::String, name),
    PARAM(oatpp::String, description),
    PARAM(oatpp::String, location),
    PARAM(oatpp::String, key))

  QUERY(
    putPlacesInsert,
    "SELECT * FROM F_PUT_PLACES_INSERT(:name, :description, :location, :key);",
    PARAM(oatpp::String, name),
    PARAM(oatpp::String, description),
    PARAM(oatpp::String, location),
    PARAM(oatpp::String, key))

  QUERY(
    deletePlaces,
    "SELECT * FROM F_DELETE_PLACES(:placeID);",
    PARAM(oatpp::Int32, placeID))

  QUERY(
    putUsersUpdate,
    "SELECT * FROM F_PUT_USERS_UPDATE(:userID, :username, :login, :password, "
    ":isAdmin, :points);",
    PARAM(oatpp::Int32, userID),
    PARAM(oatpp::String, username),
    PARAM(oatpp::String, login),
    PARAM(oatpp::String, password),
    PARAM(oatpp::Boolean, isAdmin),
    PARAM(oatpp::Int32, points))

  QUERY(
    putUsersInsert,
    "SELECT * FROM F_PUT_USERS_INSERT(:username, :login, :password, :isAdmin, "
    ":points);",
    PARAM(oatpp::String, username),
    PARAM(oatpp::String, login),
    PARAM(oatpp::String, password),
    PARAM(oatpp::Boolean, isAdmin),
    PARAM(oatpp::Int32, points))

  QUERY(
    deleteUsers,
    "SELECT * FROM F_DELETE_USERS(:userID);",
    PARAM(oatpp::Int32, userID))

  QUERY(
    putVisitsUpdate,
    "SELECT * FROM F_PUT_VISITS_UPDATE(:visitID, :userID, :placeID);",
    PARAM(oatpp::Int32, visitID),
    PARAM(oatpp::Int32, userID),
    PARAM(oatpp::Int32, placeID))

  QUERY(
    putVisitsInsert,
    "SELECT * FROM F_PUT_VISITS_INSERT(:userID, :placeID);",
    PARAM(oatpp::Int32, userID),
    PARAM(oatpp::Int32, placeID))

  QUERY(
    deleteVisits,
    "SELECT * FROM F_DELETE_VISITS(:visitID);",
    PARAM(oatpp::Int32, visitID))

  QUERY(
    putCommentsUpdate,
    "SELECT * FROM F_PUT_COMMENTS_UPDATE(:commentID, :userID, :placeID, "
    ":content);",
    PARAM(oatpp::Int32, commentID),
    PARAM(oatpp::Int32, userID),
    PARAM(oatpp::Int32, placeID),
    PARAM(oatpp::String, content))

  QUERY(
    putCommentsInsert,
    "SELECT * FROM F_PUT_COMMENTS_INSERT(:userID, :placeID, :content);",
    PARAM(oatpp::Int32, userID),
    PARAM(oatpp::Int32, placeID),
    PARAM(oatpp::String, content))

  QUERY(
    deleteComments,
    "SELECT * FROM F_DELETE_COMMENTS(:commentID);",
    PARAM(oatpp::Int32, commentID))

  // AUTHORIZATION -------------------------------------------------------------

  QUERY(
    authorize,
    "SELECT * FROM F_AUTHORIZE(:login, :password);",
    PARAM(oatpp::String, login),
    PARAM(oatpp::String, password))
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif // BDDatabase_hpp