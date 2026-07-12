#ifndef ADAPTER_HL_H
#define ADAPTER_HL_H

#include "types.h"
#include <stdbool.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t block_length; 
    uint16_t template_id;  
    uint16_t schema_id;
    uint16_t version;
    
    uint64_t timestamp_ns;
    int64_t  price_scaled; 
    int64_t  size_scaled;
    uint32_t coin_id;
    uint8_t  is_buy;
} hl_sbe_trade_t;
#pragma pack(pop)

static inline bool parse_hl_sbe(const uint8_t* wire_buffer, event_t* out_event) {
    const hl_sbe_trade_t* wire_data = (const hl_sbe_trade_t*)wire_buffer;
    
    if (wire_data->template_id != 97) return false;

    out_event->receive_timestamp_ns = wire_data->timestamp_ns;
    out_event->price = (fixed_t)wire_data->price_scaled;
    out_event->quantity = (fixed_t)wire_data->size_scaled;
    out_event->instrument_id = wire_data->coin_id;
    out_event->side = (wire_data->is_buy == 1) ? 'B' : 'S';
    out_event->venue_id = VENUE_HYPERLIQUID;
    out_event->event_type = EVENT_ORDER_FILL;
    
    return true;
}

#endif // ADAPTER_HL_H
