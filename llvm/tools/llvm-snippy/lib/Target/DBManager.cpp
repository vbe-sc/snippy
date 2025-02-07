//===-- RISCVSimulator.cpp --------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//


#include "../../Model/DBModel/SnippyDB.hpp"
#include "../../include/snippy/Simulator/Targets/DBManager.h"
#include "snippy/Support/DynLibLoader.h"

#define DEBUG_TYPE "snippy-db-manager"

namespace llvm {

namespace snippy {


#define D_STRINGIFY(S) #S
#define D_XSTRINGIFY(S) D_STRINGIFY(S)
static constexpr const char *DbEntryPointSymbol =
    D_XSTRINGIFY(RVDBAPI_ENTRY_POINT_SYMBOL);
static constexpr const char *DbInterfaceVersionSymbol =
    D_XSTRINGIFY(RVDBAPI_VERSION_SYMBOL);
#undef D_XSTRINGIFY
#undef D_STRINGIFY

DBManager::DBManager(std::string LibraryName) {
    llvm::snippy::DynamicLibrary dbLib(std::move(LibraryName)); // Create a named variable
    DBTable = getDbEntryPoint(dbLib); // Pass the named variable
}


const rvdb::RVDB_FunctionPointers &
DBManager::getDbEntryPoint(llvm::snippy::DynamicLibrary &DbLib) {
    const auto *DBTable = reinterpret_cast<const rvdb::RVDB_FunctionPointers *>(
        DbLib.getAddressOfSymbol(DbEntryPointSymbol)
    );
    // if (!DBTable)
    //     llvm::snippy::fatal(
    //         llvm::snippy::formatv("could not find entry point <{0}> to create db manager",
    //                 DbEntryPointSymbol));
    return *DBTable;
}
    

} // namespace snippy
} // namespace llvm
