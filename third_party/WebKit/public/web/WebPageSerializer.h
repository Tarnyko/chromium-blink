/*
 * Copyright (C) 2009 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WebPageSerializer_h
#define WebPageSerializer_h

#include "../platform/WebCString.h"
#include "../platform/WebCommon.h"
#include "../platform/WebData.h"
#include "../platform/WebString.h"
#include "../platform/WebURL.h"
#include "../platform/WebVector.h"

#include <utility>

namespace blink {

class WebPageSerializerClient;
class WebFrame;
class WebLocalFrame;
template <typename T> class WebVector;

// Serialization of frame contents into html or mhtml.
// TODO(lukasza): Rename this class to WebFrameSerializer?
class WebPageSerializer {
public:
    // Generates and returns an MHTML header.
    //
    // Contents of the header (i.e. title and mime type) will be based
    // on the frame passed as an argument (which typically should be
    // the main, top-level frame).
    //
    // Same |boundary| needs to used for all generateMHTMLHeader and
    // generateMHTMLParts and generateMHTMLFooter calls that belong to the same
    // MHTML document (see also rfc1341, section 7.2.1, "boundary" description).
    BLINK_EXPORT static WebData generateMHTMLHeader(
        const WebString& boundary, WebLocalFrame*);

    // Generates and returns MHTML parts for the given frame and all the
    // savable resources underneath.
    //
    // Same |boundary| needs to used for all generateMHTMLHeader and
    // generateMHTMLParts and generateMHTMLFooter calls that belong to the same
    // MHTML document (see also rfc1341, section 7.2.1, "boundary" description).
    //
    // |frameToContentID| is used for 1) emitting cid: scheme uri links for
    // subframes and 2) emitting MIME Content-ID headers.
    // See rfc2557 - section 8.3 - "Use of the Content-ID header and CID URLs".
    // Format note - |frameToContentID| should contain strings of the form
    // "<foo@bar.com>" (i.e. the strings should include the angle brackets).
    BLINK_EXPORT static WebData generateMHTMLParts(
        const WebString& boundary, WebLocalFrame*, bool useBinaryEncoding,
        const WebVector<std::pair<WebFrame*, WebString>>& frameToContentID);

    // Generates and returns an MHTML footer.
    //
    // Same |boundary| needs to used for all generateMHTMLHeader and
    // generateMHTMLParts and generateMHTMLFooter calls that belong to the same
    // MHTML document (see also rfc1341, section 7.2.1, "boundary" description).
    BLINK_EXPORT static WebData generateMHTMLFooter(const WebString& boundary);

    // IMPORTANT:
    // The API below is an older implementation of a pageserialization that
    // will be removed soon.

    // This function will serialize the specified frame to HTML data.
    // We have a data buffer to temporary saving generated html data. We will
    // sequentially call WebPageSeriazlierClient once the data buffer is full.
    //
    // Return false means if no data has been serialized (i.e. because
    // the target frame didn't have a valid url).
    //
    // The parameter frame specifies which frame need to be serialized.
    // The parameter client specifies the pointer of interface
    // WebPageSerializerClient providing a sink interface to receive the
    // individual chunks of data to be saved.
    // The parameter urlsToLocalPaths contains a mapping between original URLs
    // of saved resources and corresponding local file paths.
    BLINK_EXPORT static bool serialize(
        WebLocalFrame*,
        WebPageSerializerClient*,
        const WebVector<std::pair<WebURL, WebString>>& urlsToLocalPaths);

    // FIXME: The following are here for unit testing purposes. Consider
    // changing the unit tests instead.

    // Generate the META for charset declaration.
    BLINK_EXPORT static WebString generateMetaCharsetDeclaration(const WebString& charset);
    // Generate the MOTW declaration.
    BLINK_EXPORT static WebString generateMarkOfTheWebDeclaration(const WebURL&);
    // Generate the default base tag declaration.
    BLINK_EXPORT static WebString generateBaseTagDeclaration(const WebString& baseTarget);
};

} // namespace blink

#endif
