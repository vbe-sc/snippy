//===-- RVM.hpp -------------------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#pragma once
#include "DBTable.h"

#include <cassert>
#include <cctype>
#include <cstdint>
#include <memory>

namespace rvdb {

class State {
  struct StateDeleter {
    const RVDB_FunctionPointers *DBTable;

    void operator()(RVDBState *State) const {
      if (State) {
        assert(DBTable);
        DBTable->closeDatabase(State);
      }
    }
  };

  std::unique_ptr<RVDBState, StateDeleter> pimpl;

public:
  class Builder {
    RVDBConfig DBConfig = {};
    const RVDB_FunctionPointers *DBTable;

  public:
    Builder(const RVDB_FunctionPointers *DBTable) : DBTable(DBTable) {
      assert(DBTable);
    }

    Builder(const Builder &) = delete;
    Builder(Builder &&OldBuild) = default;
    Builder &operator=(const Builder &) = delete;
    Builder &operator=(Builder &&OldBuild) = default;
    Builder() = default;
    ~Builder() = default;

    Builder &setDataBasePath(const char* dataBasePath) {
      DBConfig.dataBasePath = dataBasePath;
      return *this;
    }
    
    State build() { return State{DBTable, &DBConfig}; }
  };

  State(const RVDB_FunctionPointers *DBTable, const RVDBConfig *Config)
      : pimpl(DBTable->initDatabase(Config), StateDeleter{DBTable}) {
    assert(DBTable);
  }
  State() = default;
  RVDBState *get() { return pimpl.get(); }
  const RVDBState *get() const { return pimpl.get(); }
};

}