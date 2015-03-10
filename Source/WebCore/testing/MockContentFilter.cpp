/*
 * Copyright (C) 2015 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "MockContentFilter.h"

#if ENABLE(CONTENT_FILTERING)

#include <mutex>
#include <wtf/text/CString.h>

namespace WebCore {

void MockContentFilter::ensureInstalled()
{
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []{
        ContentFilter::addType<MockContentFilter>();
    });
}

bool MockContentFilter::canHandleResponse(const ResourceResponse&)
{
    return MockContentFilterSettings::singleton().enabled();
}

std::unique_ptr<MockContentFilter> MockContentFilter::create(const ResourceResponse& response)
{
    return std::make_unique<MockContentFilter>(response);
}

MockContentFilter::MockContentFilter(const ResourceResponse&)
{
    maybeDetermineStatus(MockContentFilterSettings::DecisionPoint::AfterResponse);
}

void MockContentFilter::addData(const char* data, int length)
{
    m_replacementData.append(data, length);
    maybeDetermineStatus(MockContentFilterSettings::DecisionPoint::AfterAddData);
}

void MockContentFilter::finishedAddingData()
{
    maybeDetermineStatus(MockContentFilterSettings::DecisionPoint::AfterFinishedAddingData);
}

bool MockContentFilter::needsMoreData() const
{
    return m_status == Status::NeedsMoreData;
}

bool MockContentFilter::didBlockData() const
{
    return m_status == Status::Blocked;
}

const char* MockContentFilter::getReplacementData(int& length) const
{
    length = m_replacementData.size();
    return m_replacementData.data();
}

ContentFilterUnblockHandler MockContentFilter::unblockHandler() const
{
    return { };
}

void MockContentFilter::maybeDetermineStatus(MockContentFilterSettings::DecisionPoint decisionPoint)
{
    if (m_status != Status::NeedsMoreData || decisionPoint != MockContentFilterSettings::singleton().decisionPoint())
        return;

    m_status = MockContentFilterSettings::singleton().decision() == MockContentFilterSettings::Decision::Allow ? Status::Allowed : Status::Blocked;
    if (m_status != Status::Blocked)
        return;

    m_replacementData.clear();
    const CString utf8BlockedString = MockContentFilterSettings::singleton().blockedString().utf8();
    m_replacementData.append(utf8BlockedString.data(), utf8BlockedString.length());
}

} // namespace WebCore

#endif // ENABLE(CONTENT_FILTERING)
