// -*- C++ -*-
//
// Copyright 2025 Dmitry Igrishin
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef DMITIGR_NIX_ERROR_HPP
#define DMITIGR_NIX_ERROR_HPP

#include <cstring>
#include <string>

namespace dmitigr::nix {

/// @returns String describing OS error code.
inline std::string error_message(const int code)
{
  char buf[1024];
#if ((_POSIX_C_SOURCE >= 200112L) && !_GNU_SOURCE) || __APPLE__
  const int e = ::strerror_r(code, buf, sizeof(buf));
  return !e ? buf : "unknown error";
#elif _GNU_SOURCE
  const char* const msg = ::strerror_r(code, buf, sizeof(buf));
  return msg ? msg : "unknown error";
#else
#error Supported version of strerror_r() is not available.
#endif
}

} // namespace dmitigr::nix

#endif  // DMITIGR_NIX_ERROR_HPP
