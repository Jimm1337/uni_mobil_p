#include <fmt/core.h>
#include <oatpp/core/Types.hpp>

void runTests() {
  //TODO: Add tests
}

int main() {
  oatpp::base::Environment::init();

  runTests();

  /* Print how much objects were created during app running, and what have
   * left-probably leaked */
  /* Disable object counting for release builds using '-D
   * OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
  fmt::print("\nEnvironment:\n");
  fmt::print(
    "objectsCount = {}\n", oatpp::base::Environment::getObjectsCount());
  fmt::print(
    "objectsCreated = {}\n\n", oatpp::base::Environment::getObjectsCreated());

  OATPP_ASSERT(oatpp::base::Environment::getObjectsCount() == 0);

  oatpp::base::Environment::destroy();

  return 0;
}
