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

// Handwriting module connecting to the cloud server.

#ifndef MOZC_HANDWRITING_CLOUD_HANDWRITING_H_
#define MOZC_HANDWRITING_CLOUD_HANDWRITING_H_

#include "handwriting/handwriting_manager.h"

namespace mozc {
namespace handwriting {

class CloudHandwriting : public HandwritingInterface {
 public:
  CloudHandwriting() {}
  virtual ~CloudHandwriting() {}

  HandwritingStatus Recognize(const Strokes &strokes,
                              std::vector<string> *candidates) const;

  HandwritingStatus Commit(const Strokes &strokes, const string &result);

  // Parses the server response and fills to |candidates|
  static bool ParseResponse(const string &json,
                            std::vector<string> *candidates);

  // Converts the |strokes| into the request format and returns it as a string.
  static string CreateRequest(const Strokes &strokes);

  // Creates a feedback data from |strokes| and |result| and returns
  // it as a string.
  static string CreateFeedback(const Strokes &strokes, const string &result);

 private:
  DISALLOW_COPY_AND_ASSIGN(CloudHandwriting);
};

}  // namespace handwriting
}  // namespace mozc

#endif  // MOZC_HANDWRITING_CLOUD_HANDWRITING_H_
