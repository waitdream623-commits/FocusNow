# AGENTS.md

Guidance for AI coding agents working in this repository.

## What this is

FocusNow (window title / README use "FcousNow") — a brain-training game combining
typing and attention exercises, built in C++14 with raylib 5.0.

## Build & run

- Toolchain (Windows): MinGW via w64devkit at `C:/raylib/w64devkit/bin`; raylib at `C:/raylib/raylib`.
- Use the VS Code build tasks (default: **build debug**, also **build release**).
- Manual build (Windows):
  `C:/raylib/w64devkit/bin/mingw32-make.exe RAYLIB_PATH=C:/raylib/raylib PROJECT_NAME=main OBJS=src/*.cpp BUILD_MODE=DEBUG`
- Run/debug via `.vscode/launch.json` (configs `Debug` and `Run`).

> ⚠️ The build task uses `PROJECT_NAME=${fileBasenameNoExtension}`, so the output
> `.exe` is named after the **currently focused file**. Keep `src/main.cpp` focused
> (or pass `PROJECT_NAME=main`) so the binary is `main.exe`, not `type.exe` / `mouse.exe`.

## Layout

- `src/main.cpp` — entry point: window init (1280×960), game loop.
- `src/type.h` / `src/type.cpp` — `type` class: core typing/attention game logic.
- `src/mouse.h` / `src/mouse.cpp` — `mouse` class: cursor and trail effect.
- `src/data.h` — plain data structs only (`KeyEvent`, `LetterData`). No globals, no logic.
- `assets/font/` — fonts, loaded with cwd-relative paths (e.g. `assets/font/monogram.ttf`).
- `lib/` — MinGW runtime DLLs (`libgcc_s_dw2-1.dll`, `libstdc++-6.dll`) needed to run the exe. Do not remove.
- `Makefile` — raylib's standard template; build variables are overridden by the VS Code task.

## Conventions

- C++14 (`-std=c++14`). Headers use `#pragma once`.
- Constants are `constexpr` globals in headers (`MAX_LETTER_LENGTH`, `RADIUS`, `SESSION_DURATION`, `MAX_TRAIL_LENGTH`).
- Class-based: private members, public methods. Game state lives in classes, **not** global
  variables (a past bug put a global `std::vector<KeyEvent>` in `data.h` — avoid repeating this).
- Comments and README are written in Chinese; match that style when editing existing files.
- raylib API throughout (`GetTime`, `GetCharPressed`, `GetMousePosition`, `DrawCircle`, `DrawTextEx`, `TraceLog`).

## Pitfalls

- `type::IsPreesedCorret()` (note the existing misspelling — leave as-is unless renaming is intentional)
  checks input against `letters[0]` only; on success the array shifts left and a new letter spawns at the end.
- `srand(time(0))` is called in both `type` constructors; `<random>` is included but unused. Randomness is `rand()`-based.
- Assets are loaded with relative paths — run/debug from the workspace root (`cwd` is already set in launch.json).
