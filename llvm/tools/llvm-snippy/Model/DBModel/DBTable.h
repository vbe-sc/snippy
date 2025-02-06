//===-- DBTable.h ------------------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#pragma once
#include "SnippyDB.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

namespace rvdb {

struct RVDB_FunctionPointers {
  rvdb_initDatabase_t initDatabase;
  rvdb_getOperandsByRows_t getOperandsByRows;
  rvdb_closeDatabase_t closeDatabase;
};

}

#ifdef __cplusplus
} // namespace rvdb
#endif // __cplusplus
