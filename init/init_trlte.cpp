/*
   Copyright (c) 2016, The Linux Foundation. All rights reserved.
   Copyright (c) 2017-2018, The LineageOS Project. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include <android-base/logging.h>
#include <android-base/properties.h>

#include "property_service.h"
#include "vendor_init.h"

#include "init_apq8084.h"

using android::base::GetProperty;
using android::init::property_set;

void gsm_properties()
{
    property_set("telephony.lteOnGsmDevice", "1");
    property_set("ro.telephony.default_network", "9");
}

void init_target_properties()
{
    std::string platform = GetProperty("ro.board.platform", "");
    if (platform != ANDROID_TARGET)
        return;

    std::string bootloader = GetProperty("ro.bootloader", "");

    if (bootloader.find("N910T") == 0) {
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/trltetmo/trltetmo:6.0.1/MMB29M/N910TUVU2EQI2:user/release-keys");
        property_override("ro.build.description", "trltetmo-user 6.0.1 MMB29M N910TUVU2EQI2 release-keys");
        property_override_dual("ro.product.model", "ro.vendor.product.model", "SM-N910T");
        property_override_dual("ro.product.device", "ro.vendor.product.device", "trltetmo");
        property_override_dual("ro.product.name", "ro.vendor.product.name", "trltetmo");
        gsm_properties();
    } else if (bootloader.find("N910W8") == 0) {
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/trltecan/trltecan:6.0.1/MMB29M/N910W8VLS1DQH2:user/release-keys");
        property_override("ro.build.description", "trltecan-user 6.0.1 MMB29M N910W8VLS1DQH2 release-keys");
        property_override_dual("ro.product.model", "ro.vendor.product.model", "SM-N910W8");
        property_override_dual("ro.product.device", "ro.vendor.product.device", "trltecan");
        property_override_dual("ro.product.name", "ro.vendor.product.name", "trltecan");
        gsm_properties();
    } else {
        gsm_properties();
    }

    std::string device = GetProperty("ro.product.device", "");
    LOG(ERROR) << "Found bootloader id " << bootloader << " setting build properties for " << device << " device" << std::endl;
}
