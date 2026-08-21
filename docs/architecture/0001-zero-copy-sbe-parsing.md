# 1. Zero-Copy SBE Parsing

Date: 2026-07-12

## Status

Accepted

## Context

Hyperliquid utilizes Simple Binary Encoding (SBE) for its L2 book and trade feeds. SBE is inherently designed for low-latency financial systems by avoiding variable-length encodings, but standard generated decoders can still introduce unnecessary branching or intermediate variables.

## Decision

We employ **zero-copy pointer overlay parsing**.
- We define C11 structs annotated with `__attribute__((packed))` that perfectly mirror the byte layout of the SBE schema.
- Upon receiving a packet, we cast the raw network byte buffer pointer directly to our C11 struct pointer.
- We read the values directly from the memory-mapped struct.

## Consequences

**Positive:**
- Near-zero CPU overhead. The parsing step is effectively eliminated, taking `O(1)` time with no memory copying required.

**Negative (Mitigated):**
- Requires strict reliance on host architecture endianness (little-endian for x86-64 matching the wire format).
- Compiler padding directives (`packed`) must be meticulously maintained to prevent misaligned memory access faults, which could crash the gateway.
- *Mitigation:* We enforced strict compile-time invariants. We added `__BYTE_ORDER__` checks to guarantee little-endian compilation. Furthermore, we implemented rigorous `_Static_assert` checks using `offsetof()` to mathematically guarantee exact byte-alignment for every struct field. Any deviation immediately fails the build with an `"SBE padding error"`, entirely preventing runtime memory alignment faults.
