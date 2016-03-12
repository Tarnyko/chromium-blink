// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef AutoCanvasDrawListener_h
#define AutoCanvasDrawListener_h

#include "core/html/canvas/CanvasDrawListener.h"
#include "platform/heap/Handle.h"
#include "public/platform/WebCanvasCaptureHandler.h"

namespace blink {

class AutoCanvasDrawListener final : public GarbageCollectedFinalized<AutoCanvasDrawListener>, public CanvasDrawListener {
    USING_GARBAGE_COLLECTED_MIXIN(AutoCanvasDrawListener);
public:
    static AutoCanvasDrawListener* create(const PassOwnPtr<WebCanvasCaptureHandler>&);
    ~AutoCanvasDrawListener() {}
    bool needsNewFrame() const override;
    void sendNewFrame(const WTF::PassRefPtr<SkImage>&) override;

    DEFINE_INLINE_TRACE() {}
private:
    AutoCanvasDrawListener(const PassOwnPtr<WebCanvasCaptureHandler>&);

    OwnPtr<WebCanvasCaptureHandler> m_handler;
};

} // namespace blink

#endif