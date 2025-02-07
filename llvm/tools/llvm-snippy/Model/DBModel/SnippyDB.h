#pragma once

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define RVDBAPI_ENTRY_POINT_SYMBOL RVDBVTable
#define RVDBAPI_VERSION_SYMBOL RVDBInterfaceVersion
#define RVDBAPI_CURRENT_INTERFACE_VERSION 9u

namespace llvm {
namespace snippy {
namespace database {

class SnippyDB {
    public:
        struct Operands {
          uint64_t* Data;
          uint64_t Num;
          uint64_t Size;
        };

        enum Order {Rand, SeqFromStart};

        virtual ~SnippyDB() = default; 
        virtual bool open() = 0; 
        virtual void close() = 0; 
        virtual void getRows(uint64_t rows, const struct Operands* ops, Order order, uint64_t opType) = 0; 
    };
  
} // namespace database
} // namespace snippy
} // namespace llvm

namespace rvdb {

struct RVDBConfig;
typedef struct RVDBConfig RVDBConfig;

struct RVDBConfig {
  const char* dataBasePath;
};

typedef struct RVDBState RVDBState;

typedef RVDBState* (*rvdb_initDatabase_t)(const RVDBConfig *);
typedef void (*rvdb_getOperandsByRows_t)(
  const RVDBState *,
  const struct llvm::snippy::database::SnippyDB::Operands*,
  uint64_t,
  llvm::snippy::database::SnippyDB::Order,
  uint64_t
);
typedef void (*rvdb_closeDatabase_t)(RVDBState *);

}

#ifdef __cplusplus
}
#endif // __cplusplus

