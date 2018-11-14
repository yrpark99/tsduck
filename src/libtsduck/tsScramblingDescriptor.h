//----------------------------------------------------------------------------
//
// TSDuck - The MPEG Transport Stream Toolkit
// Copyright (c) 2005-2018, Thierry Lelegard
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
// THE POSSIBILITY OF SUCH DAMAGE.
//
//----------------------------------------------------------------------------
//!
//!  @file
//!  Representation of a scrambling_descriptor.
//!
//----------------------------------------------------------------------------

#pragma once
#include "tsAbstractDescriptor.h"
#include "tsNullReport.h"

namespace ts {

    class DescriptorList;

    //!
    //! Representation of a scrambling_descriptor.
    //! @see ETSI 300 468, 6.2.32.
    //! @ingroup descriptor
    //!
    class TSDUCKDLL ScramblingDescriptor : public AbstractDescriptor
    {
    public:
        // ScramblingDescriptor public members:
        uint8_t scrambling_mode;  //!< Scrambling mode.

        //!
        //! Default constructor.
        //! @param [in] mode Scrambling mode.
        //!
        ScramblingDescriptor(uint8_t mode = 0);

        //!
        //! Constructor from a binary descriptor.
        //! @param [in] bin A binary descriptor to deserialize.
        //! @param [in] charset If not zero, character set to use without explicit table code.
        //!
        ScramblingDescriptor(const Descriptor& bin, const DVBCharset* charset = nullptr);

        //!
        //! Decode a command-line Scrambling_descriptor and fills this object with it.
        //! @param [in] value Scrambling descriptor in command-line form: scrambling_mode
        //! The scrambling_mode is integer value, either decimal or hexadecimal.
        //! @param [in,out] report Where to report errors (typically badly formed parameters).
        //! @return True on success, false on error.
        //!
        bool fromCommmandLine(const UString& value, Report& report = NULLREP);

        //!
        //! Static method to decode command-line Scrambling_descriptor and add them in a descriptor list.
        //! @param [in,out] dlist Descriptor list. The new Scrambling descriptors are added in the list.
        //! @param [in] values List of Scrambling descriptors in command-line form: scrambling_mode
        //! @param [in,out] report Where to report errors (typically badly formed parameters).
        //! @return True on success, false on error.
        //! @see fromCommmandLine()
        //!
        static bool AddFromCommandLine(DescriptorList& dlist, const UStringVector& values, Report& report = NULLREP);

        // Inherited methods
        virtual void serialize(Descriptor&, const DVBCharset* = nullptr) const override;
        virtual void deserialize(const Descriptor&, const DVBCharset* = nullptr) override;
        virtual void buildXML(xml::Element*) const override;
        virtual void fromXML(const xml::Element*) override;
        DeclareDisplayDescriptor();
    };
}
