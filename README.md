# Hyperliquid SBE Core


Zero-copy Simple Binary Encoding (SBE) deserializer for Hyperliquid's native FIX/Binary trade feed.

## Overview

This adapter parses raw Hyperliquid SBE wire frames into the unified `event_t` struct used by the core execution engine. The parser is header-only (`adapter_hl.h` in `hft_core/include`) for zero-overhead inlining on the hot path.

## Compiler Requirements
- **GCC**: >= 4.9 with C11 support.
- **Extensions**: `__int128` extension required (supported by GCC/Clang on x86-64 or aarch64).

## Features

- **Zero-copy SBE parsing**: Direct struct casting from wire bytes (no intermediate allocations)
- **Template filtering**: Only accepts trade execution messages (`template_id == 97`)
- **Side mapping**: Binary `is_buy` flag mapped to canonical `'B'`/`'S'` representation

## API Updates
Note: The adapter parser API has been updated. Calling the parsing methods now requires passing both the `wire_len` and `seq_id` parameters to properly support bounds checking and sequence tracking.

## Integration

This module is consumed as a Git submodule by `hft_orchestrator`. All shared headers (`types.h`, `fixed_math.h`, `ring_buffer.h`, `adapter_hl.h`) live in `hft_core/include`.

## Build & Test

```bash
make test
```

## Governance & Architecture

* **Code of Conduct:** Please review our [Code of Conduct](CODE_OF_CONDUCT.md).
* **Architecture Decision Records (ADRs):** 
  * [ADR-0001: Zero-Copy SBE Parsing](docs/architecture/0001-zero-copy-sbe-parsing.md)
  * [ADR-0002: Use C11 for Gateway Performance](docs/architecture/0002-use-c11-for-gateway-performance.md)

## License

This project is licensed under the Apache License 2.0.
