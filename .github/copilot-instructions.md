# Copilot Instructions

## Project
- This repository is an early C prototype for a chess game with a dice-based capture mechanic.
- `Chenss.c` contains placeholders and partial sketches, not a complete or currently reliable implementation. Treat comments as intent, not as evidence that behavior exists.
- No compiler standard, build system, or test framework is specified. Do not introduce one without a task-specific reason.

## Working in this codebase
- Keep changes focused on the requested behavior and preserve the existing procedural C style and function names unless a change is needed.
- Before implementing game rules, make the relevant behavior explicit: board representation, coordinate convention, legal moves, turn order, check/checkmate, and dice-based capture outcomes.
- Avoid recursion for retrying user input; use a loop so invalid moves do not grow the call stack.
- Validate input and initialize variables before use. Prefer clear return values or parameters over hidden global state when adding behavior.
- Keep comments concise and consistent with the nearby English/Tagalog comments.
- Run a compile or test check only when the required toolchain and a meaningful check are available; report limitations rather than assuming success.
