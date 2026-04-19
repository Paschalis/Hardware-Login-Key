# Security Policy

## Threat Model

The Hardware Login Key implements a **two-piece password split**: the suffix is stored on the device, the prefix exists only in the user's memory. Physical possession of the key alone is insufficient to authenticate.

### What this device protects against

- **Shoulder surfing** — observers cannot see the full password being typed
- **Partial credential capture** — a logged suffix is useless without the prefix
- **Password fatigue** — long, complex suffixes are typed automatically

### What this device does NOT protect against

- **Physical flash extraction** — the password suffix is stored as **plaintext in ATtiny85 flash memory**. An attacker with physical access to the chip and a standard AVR programmer (AVRDUDE + Arduino as ISP) can dump the entire flash in under a minute and read the suffix in any hex editor. This is a fundamental limitation of the ATtiny85: it has no secure boot, no encrypted storage, and no hardware debug lockdown.

- **Compromised host** — the device injects keystrokes via USB HID. A malicious host OS, kernel driver, or keylogger can capture those keystrokes in transit.

- **USB HID spoofing** — the host has no way to verify the device's identity beyond standard HID enumeration.

### Appropriate use

This device is designed for **personal convenience and privacy in low-threat environments** — reducing shoulder-surfing risk when typing long passwords in public. It is **not** a substitute for a hardware security module (HSM), a FIDO2/WebAuthn token, or any device with cryptographic identity verification.

If your threat model includes a motivated attacker with physical access to your hardware, this device does not meet that requirement.

## Reporting Issues

If you discover a firmware bug, an unexpected USB enumeration behaviour, or a security concern related to the V-USB HID implementation, please open a GitHub Issue with as much detail as possible, including:

- Affected firmware variant (`tactile_switch` or `touch_pad`)
- Host operating system and version
- Steps to reproduce
- Expected vs actual behaviour
