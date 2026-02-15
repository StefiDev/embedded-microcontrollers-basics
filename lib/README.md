# Library Directory

This directory (`lib`) is reserved for:
1.  **Shared Libraries**: Custom code (headers `.h` and source `.cpp`) shared across multiple projects (e.g., a custom protocol handler or sensor driver used in both Lab 1 and Lab 2).
2.  **Third-Party Libraries**: Libraries that are not available via the Arduino Library Manager or that you want to bundle with your project to ensure compatibility.
3.  **Project-Specific Headers**: Configuration headers (like `pin_config.h` or `settings.h`) if they are reused.

## Current Status
This folder is currently empty because your existing projects appear to rely on standard Arduino libraries (installed globally via IDE) or self-contained logic within the `.ino` files.

## Usage
To use a library here, simply create a folder for it (e.g., `lib/MyCustomSensor/`) and include it in your sketch.
