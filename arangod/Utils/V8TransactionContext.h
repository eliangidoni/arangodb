////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2014-2016 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Jan Steemann
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGOD_UTILS_V8_TRANSACTION_CONTEXT_H
#define ARANGOD_UTILS_V8_TRANSACTION_CONTEXT_H 1

#include "Basics/Common.h"
#include "Utils/TransactionContext.h"

struct TRI_transaction_t;
struct TRI_vocbase_t;

namespace arangodb {

class V8TransactionContext final : public TransactionContext {

 public:

  //////////////////////////////////////////////////////////////////////////////
  /// @brief create the context
  //////////////////////////////////////////////////////////////////////////////

  V8TransactionContext(TRI_vocbase_t*, bool);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief destroy the context
  //////////////////////////////////////////////////////////////////////////////

  ~V8TransactionContext() = default;
  
  //////////////////////////////////////////////////////////////////////////////
  /// @brief order a custom type handler
  //////////////////////////////////////////////////////////////////////////////

  std::shared_ptr<VPackCustomTypeHandler> orderCustomTypeHandler() override final;
  
  //////////////////////////////////////////////////////////////////////////////
  /// @brief return the resolver
  //////////////////////////////////////////////////////////////////////////////

  CollectionNameResolver const* getResolver() override final;
  
  //////////////////////////////////////////////////////////////////////////////
  /// @brief get parent transaction (if any)
  //////////////////////////////////////////////////////////////////////////////

  struct TRI_transaction_t* getParentTransaction() const override;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief register the transaction in the context
  //////////////////////////////////////////////////////////////////////////////

  int registerTransaction(struct TRI_transaction_t* trx) override;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief unregister the transaction from the context
  //////////////////////////////////////////////////////////////////////////////

  void unregisterTransaction() override;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief whether or not the transaction is embeddable
  //////////////////////////////////////////////////////////////////////////////

  bool isEmbeddable() const override;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief make this transaction context a global context
  //////////////////////////////////////////////////////////////////////////////

  void makeGlobal();
  
  //////////////////////////////////////////////////////////////////////////////
  /// @brief whether or not the transaction context is a global one
  //////////////////////////////////////////////////////////////////////////////

  bool isGlobal() const;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief check whether the transaction is embedded
  //////////////////////////////////////////////////////////////////////////////

  static bool IsEmbedded();
  
  //////////////////////////////////////////////////////////////////////////////
  /// @brief create a context, returned in a shared ptr
  //////////////////////////////////////////////////////////////////////////////

  static std::shared_ptr<V8TransactionContext> Create(TRI_vocbase_t*, bool);

 private:

  //////////////////////////////////////////////////////////////////////////////
  /// @brief the v8 thread-local "global" transaction context
  //////////////////////////////////////////////////////////////////////////////

  V8TransactionContext* _sharedTransactionContext;

  V8TransactionContext* _mainScope;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief the currently ongoing transaction
  //////////////////////////////////////////////////////////////////////////////

  struct TRI_transaction_t* _currentTransaction;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief whether or not further transactions can be embedded
  //////////////////////////////////////////////////////////////////////////////

  bool const _embeddable;
};
}

#endif
