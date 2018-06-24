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
//!  An encapsulation of a HiDes modulator device.
//!
//----------------------------------------------------------------------------

#pragma once
#include "tsHiDesDeviceInfo.h"
#include "tsTunerParametersDVBT.h"
#include "tsTSPacket.h"
#include "tsCerrReport.h"

namespace ts {
    //!
    //! Encapsulation of a HiDes modulator device.
    //! @ingroup hardware
    //!
    class TSDUCKDLL HiDesDevice
    {
    public:
        //!
        //! Constructor.
        //!
        HiDesDevice();

        //!
        //! Destructor.
        //!
        virtual ~HiDesDevice();

        //!
        //! Get all HiDes devices in the system.
        //! @param [out] devices Returned list of devices.
        //! @param [in,out] report Where to report errors.
        //! @return True on success, false on error.
        //!
        static bool GetAllDevices(HiDesDeviceInfoList& devices, Report& report = CERR);

        //!
        //! Open the HiDes device by adapter number.
        //! @param [in] index Adapter number.
        //! @param [in,out] report Where to report errors.
        //! @return True on success, false on error.
        //!
        bool open(int index, Report& report = CERR);

        //!
        //! Open the HiDes device by adapter name or device name.
        //! @param [in] name Adapter name or device name.
        //! @param [in,out] report Where to report errors.
        //! @return True on success, false on error.
        //!
        bool open(const UString& name, Report& report = CERR);

        //!
        //! Check if the HiDes device is open.
        //! @return True if the HiDes device is open.
        //!
        bool isOpen() const { return _is_open; }

        //!
        //! Get information about the device.
        //! @param [out] info Returned information.
        //! @param [in,out] report Where to report errors.
        //! @return True on success, false on error.
        //!
        bool getInfo(HiDesDeviceInfo& info, Report& report = CERR) const;

        //!
        //! Close the device.
        //! @param [in,out] report Where to report errors.
        //! @return True on success, false on error.
        //!
        bool close(Report& report = CERR);

        //!
        //! Set the output gain in dB.
        //! @param [in,out] gain The gain (if positive) or attenuation (if negative) in dB.
        //! Upon return, @a gain contains the actually set value. The range of valid gain
        //! values depends on the frequency and the bandwidth.
        //! @param [in,out] report Where to report errors.
        //! @return True on success, false on error.
        //! @see getGainRange()
        //!
        bool setGain(int& gain, Report& report = CERR);

        //!
        //! Get the output gain in dB.
        //! @param [out] gain The gain (if positive) or attenuation (if negative) in dB.
        //! @param [in,out] report Where to report errors.
        //! @return True on success, false on error.
        //!
        bool getGain(int& gain, Report& report = CERR);

        //!
        //! Get the allowed range of output gain in dB.
        //! The range of valid gain values depends on the frequency and the bandwidth.
        //! @param [out] minGain Minimum allowed gain value in dB.
        //! @param [out] maxGain Maximum allowed gain value in dB.
        //! @param [in] frequency Target frequency in Hz.
        //! @param [in] bandwidth Target bandwidth.
        //! @param [in,out] report Where to report errors.
        //! @return True on success, false on error.
        //!
        bool getGainRange(int& minGain, int& maxGain, uint64_t frequency, BandWidth bandwidth, Report& report = CERR);

        //!
        //! Tune the modulator with DVB-T modulation parameters.
        //! @param [in] params Tuning parameters.
        //! @param [in,out] report Where to report errors.
        //! @return True on success, false on error.
        //!
        bool tune(const TunerParametersDVBT& params, Report& report = CERR);

        //!
        //! Start transmission (after having set tuning parameters).
        //! @param [in,out] report Where to report errors.
        //! @return True on success, false on error.
        //!
        bool startTransmission(Report& report = CERR);

        //!
        //! Stop transmission.
        //! @param [in,out] report Where to report errors.
        //! @return True on success, false on error.
        //!
        bool stopTransmission(Report& report = CERR);

        //!
        //! Send TS packets.
        //! @param [in] data Address of first TS packet to send.
        //! @param [in] packet_count Number of contiguous packets to send.
        //! @param [in,out] report Where to report errors.
        //! @return True on success, false on error.
        //!
        bool send(const TSPacket* data, size_t packet_count, Report& report = CERR);

    private:
        // The implementation is highly system-dependent.
        // Redirect it to an internal system-dependent "guts" class.
        class Guts;

        bool  _is_open;
        Guts* _guts;

        // Inaccessible operations.
        HiDesDevice(const HiDesDevice&) = delete;
        HiDesDevice& operator=(const HiDesDevice&) = delete;
    };
}