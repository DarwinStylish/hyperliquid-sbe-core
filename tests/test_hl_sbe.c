#include <stdio.h>
#include <assert.h>
#include "adapter_hl.h"

int main() {
    printf("[*] Running Hyperliquid SBE Client Verification...\n");
    
    /* Happy path: valid trade template */
    uint8_t raw_wire[37] = {0};
    hl_sbe_trade_t* mock_sbe = (hl_sbe_trade_t*)raw_wire;
    mock_sbe->template_id = HL_SBE_TRADE_TEMPLATE_ID;
    mock_sbe->price_scaled = 6000000000000LL;
    mock_sbe->is_buy = 1;
    
    event_t out;
    assert(parse_hl_sbe(raw_wire, &out));
    assert(out.venue_id == VENUE_HYPERLIQUID);
    assert(out.side == 'B');
    
    printf("[+] Successfully parsed Hyperliquid SBE binary feed.\n");
    printf("[+] Price mapped: %ld\n", (long)out.price);
    
    /* Negative test: invalid template */
    uint8_t bad_wire[37] = {0};
    hl_sbe_trade_t* bad = (hl_sbe_trade_t*)bad_wire;
    bad->template_id = 0;
    assert(parse_hl_sbe(bad_wire, &out) == false);
    printf("[+] Invalid template_id correctly rejected.\n");
    
    printf("\n[SUCCESS] Hyperliquid SBE tests passed.\n");
    return 0;
}
