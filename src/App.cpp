#include <fmt/core.h>
#include "AppComponent.hpp"
#include "controller/MobilController.hpp"
#include "oatpp-swagger/Controller.hpp"
#include "oatpp/network/Server.hpp"

void run() {
  /* Register Components in scope of run() method */
  AppComponent components;

  /* Get router component */
  OATPP_COMPONENT(std::shared_ptr< oatpp::web::server::HttpRouter >, router);

  /* Create MyController and add all of its endpoints to router */

  oatpp::web::server::api::Endpoints docEndpoints;
  docEndpoints.append(
    router->addController(std::make_shared< MobilController >())->getEndpoints());

  router->addController(
    oatpp::swagger::Controller::createShared(docEndpoints));

  /* Get connection handler component */
  OATPP_COMPONENT(
    std::shared_ptr< oatpp::network::ConnectionHandler >, connectionHandler);

  /* Get connection provider component */
  OATPP_COMPONENT(
    std::shared_ptr< oatpp::network::ServerConnectionProvider >,
    connectionProvider);

  /* Create server which takes provided TCP connections and passes them to HTTP
   * connection handler */
  oatpp::network::Server server(connectionProvider, connectionHandler);

  /* Print info about server port */
  OATPP_LOGI(
    "MyApp",
    "Server running on port %s",
    connectionProvider->getProperty("port").getData());

  /* Run server */
  server.run();
}

/**
 *  main
 */
int main(int /*argc*/, const char* /*argv*/[]) {
  oatpp::base::Environment::init();

  run();

  /* Print how much objects were created during app running, and what have
   * left-probably leaked */
  /* Disable object counting for release builds using '-D
   * OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
  fmt::print("\nEnvironment:\n");
  fmt::print(
    "objectsCount = {}\n", oatpp::base::Environment::getObjectsCount());
  fmt::print(
    "objectsCreated = {}\n\n", oatpp::base::Environment::getObjectsCreated());

  oatpp::base::Environment::destroy();

  return 0;
}
