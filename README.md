# cfbd-cli

A lightweight command-line client for the [College Football Data API](https://collegefootballdata.com/) — a streamlined alternative to hand-writing `curl` commands.

## Features

- Pass any CFBD API endpoint as an argument (e.g. `/games`, `/teams`)
- Optional `--year` and `--team` query parameters
- Reads your API key from an environment variable (no key in shell history or source code)
- Prints raw JSON to stdout — pipe to `jq` or a file as needed

## Requirements

- CMake 3.14+
- Ninja
- [vcpkg](https://github.com/microsoft/vcpkg)
- A CFBD API key ([get one here](https://collegefootballdata.com/key))

### Dependencies (via vcpkg)

- [CLI11](https://github.com/CLIUtils/CLI11) — argument parsing
- [cpr](https://github.com/libcpr/cpr) — HTTP requests

## Setup

### 1. Install dependencies

```bash
vcpkg add port cli11 cpr
```

### 2. Set your API key

```bash
export CFBD_API_KEY="your_key_here"
```

Add this to your shell profile (`.bashrc`, `.zshrc`, etc.) to persist it across sessions.

### 3. Configure and build

This project uses CMake presets tied to vcpkg. Make sure `VCPKG_ROOT` is set in your environment:

```bash
export VCPKG_ROOT=/path/to/vcpkg
```

Configure:

```bash
cmake --preset vcpkg
```

Build (choose a configuration):

```bash
cmake --build --preset debug
# or
cmake --build --preset release
# or
cmake --build --preset relwithdebinfo
```

The compiled binary will be located under `build/`.

## Usage

```bash
./cfbd-cli <endpoint> [-y|--year YEAR] [-t|--team TEAM]
```

### Examples

Get all games for a team in a given season:

```bash
./cfbd-cli /games --year 2023 --team Georgia
```

Get team info for a season:

```bash
./cfbd-cli /teams -y 2024
```

Pretty-print with `jq`:

```bash
./cfbd-cli /games --year 2023 --team Georgia | jq
```

## Notes

- The leading `/` on the endpoint is optional — `cfbd-cli games` and `cfbd-cli /games` behave the same.
- If `CFBD_API_KEY` is not set, the tool exits with an error before making a request.
- This is a barebones client: it does not currently validate which parameters are required or optional per endpoint. Refer to the [CFBD API docs](https://api.collegefootballdata.com/api/docs/?url=/api-docs.json) for endpoint-specific requirements.

