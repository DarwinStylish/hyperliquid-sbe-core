// SPDX-License-Identifier: Apache-2.0
// Copyright 2026 Okot Darwin Clay
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

#include <stdio.h>
#include <assert.h>
#include "adapter_hl.h"

int main() {
    printf("[*] Running Hyperliquid SBE Client Verification...\n");
    
    /* Happy path: valid trade template */
    hl_sbe_trade_t mock_sbe = {0};
    mock_sbe.template_id = HL_SBE_TRADE_TEMPLATE_ID;
    mock_sbe.price_scaled = 6000000000000LL;
    mock_sbe.is_buy = 1;
    
    event_t out;
    assert(parse_hl_sbe((const uint8_t*)&mock_sbe, sizeof(mock_sbe), 1, &out));
    assert(out.venue_id == VENUE_HYPERLIQUID);
    assert(out.side == 'B');
    
    printf("[+] Successfully parsed Hyperliquid SBE binary feed.\n");
    printf("[+] Price mapped: %ld\n", (long)out.price);
    
    /* Negative test: invalid template */
    hl_sbe_trade_t bad = {0};
    bad.template_id = 0;
    assert(parse_hl_sbe((const uint8_t*)&bad, sizeof(bad), 2, &out) == false);
    printf("[+] Invalid template_id correctly rejected.\n");

    /* Negative test: buffer too short */
    assert(parse_hl_sbe((const uint8_t*)&mock_sbe, sizeof(mock_sbe) - 1, 3, &out) == false);
    printf("[+] Buffer too short correctly rejected.\n");
    
    printf("\n[SUCCESS] Hyperliquid SBE tests passed.\n");
    return 0;
}
