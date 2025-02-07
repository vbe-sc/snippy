//===-- RISCV.h -------------------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#pragma once

#include "../../../../Model/DBModel/SnippyDB.hpp"

#include "snippy/Support/DynLibLoader.h"

namespace llvm {
namespace snippy {
    class DBManager {
        rvdb::RVDB_FunctionPointers DBTable;
        rvdb::State::Builder Builder;
        rvdb::State State;
    public:
        DBManager(std::string, std::string);
        static const rvdb::RVDB_FunctionPointers &getDbEntryPoint(llvm::snippy::DynamicLibrary &DbLib);
        rvdb::RVDB_FunctionPointers getDBTable() const { return DBTable; };
        const rvdb::State& getState() const { return State; }
    };   
} // namespace snippy
} // namespace llvm
