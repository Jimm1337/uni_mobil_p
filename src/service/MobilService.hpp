#ifndef CRUD_USERSERVICE_HPP
#define CRUD_USERSERVICE_HPP

#include <variant>
#include "db/MobilDatabase.hpp"
#include "dto/DtoError.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/protocol/http/Http.hpp"

class MobilService {
private:
  using Status = oatpp::web::protocol::http::Status;

  OATPP_COMPONENT(
    std::shared_ptr< MobilDatabase >, m_database); // Inject database component

public:
  // USER API ENDPOINTS --------------------------------------------------------

  // ADMIN API ENDPOINTS -------------------------------------------------------

private:
  static oatpp::String fixInputString(const oatpp::String& input);
};

#endif // CRUD_USERSERVICE_HPP