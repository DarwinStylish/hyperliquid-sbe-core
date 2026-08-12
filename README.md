# Hyperliquid SBE Core

Zero-copy Simple Binary Encoding (SBE) deserializer for Hyperliquid's native FIX/Binary trade feed.

## Overview

This adapter parses raw Hyperliquid SBE wire frames into the unified `event_t` struct used by the core execution engine. The parser is header-only (`adapter_hl.h` in `hft_core/include`) for zero-overhead inlining on the hot path.

## Features

- **Zero-copy SBE parsing**: Direct struct casting from wire bytes (no intermediate allocations)
- **Template filtering**: Only accepts trade execution messages (`template_id == 97`)
- **Side mapping**: Binary `is_buy` flag mapped to canonical `'B'`/`'S'` representation

## Integration

This module is consumed as a Git submodule by `hft_orchestrator`. All shared headers (`types.h`, `fixed_math.h`, `ring_buffer.h`, `adapter_hl.h`) live in `hft_core/include`.

## Build & Test

```bash
make test
```

## License

Apache 2.0 — see the root [hft_orchestrator LICENSE](https://github.com/DarwinStylish/hft_orchestrator/blob/main/LICENSE).
