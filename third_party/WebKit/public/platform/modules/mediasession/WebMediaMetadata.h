// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WebMediaMetadata_h
#define WebMediaMetadata_h

#include "public/platform/WebString.h"

namespace blink {

// Representation of the MediaMetadata interface to the content layer.
struct WebMediaMetadata {
    WebString title;
    WebString artist;
    WebString album;
};

} // namespace blink

#endif // WebMediaMetadata_h
