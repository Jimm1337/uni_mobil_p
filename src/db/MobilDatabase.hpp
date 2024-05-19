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

  // TODO: Add queries
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif // BDDatabase_hpp