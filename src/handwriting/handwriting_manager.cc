// Copyright 2010-2017, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Handwriting module manager class

#include <set>

#include "base/logging.h"
#include "base/singleton.h"
#include "handwriting/handwriting_manager.h"

namespace mozc {
namespace handwriting {

class HandwritingManagerImpl {
 public:
  HandwritingManagerImpl() : module_(NULL) {}
  virtual ~HandwritingManagerImpl() {}

  void SetHandwritingModule(HandwritingInterface *module) {
    module_ = module;
  }

  HandwritingStatus Recognize(const Strokes &strokes,
                              std::vector<string> *candidates) const {
    DCHECK(module_);
    DCHECK(candidates);
    candidates->clear();
    return module_->Recognize(strokes, candidates);
  }

  HandwritingStatus Commit(const Strokes &strokes, const string &result) {
    DCHECK(module_);
    return module_->Commit(strokes, result);
  }

 private:
  HandwritingInterface * module_;
};

// static
void HandwritingManager::SetHandwritingModule(HandwritingInterface *module) {
  Singleton<HandwritingManagerImpl>::get()->SetHandwritingModule(module);
}

// static
HandwritingStatus HandwritingManager::Recognize(
    const Strokes &strokes, std::vector<string> *candidates) {
  return Singleton<HandwritingManagerImpl>::get()->Recognize(strokes,
                                                             candidates);
}

// static
HandwritingStatus HandwritingManager::Commit(const Strokes &strokes,
                                const string &result) {
  return Singleton<HandwritingManagerImpl>::get()->Commit(strokes, result);
}

}  // namespace handwriting
}  // namespace mozc
