#include <stdio.h>
#include <assert.h>
#include "adapter_hl.h"

int main() {
    printf("[*] Running Hyperliquid SBE Client Verification...\n");
    
    uint8_t raw_wire[37] = {0};
    hl_sbe_trade_t* mock_sbe = (hl_sbe_trade_t*)raw_wire;
    mock_sbe->template_id = 97; 
    mock_sbe->price_scaled = 6000000000000LL;
    
    event_t out;
    assert(parse_hl_sbe(raw_wire, &out));
    
    printf("[+] Successfully parsed Hyperliquid SBE binary feed.\n");
    printf("[+] Price mapped: %ld\n", (long)out.price);
    
    return 0;
}
