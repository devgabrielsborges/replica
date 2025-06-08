# Instructions for Generating ARCHITECTURE.md

## Purpose

Describe the system’s architecture, key components, their interactions, and the rationale behind major design decisions. This document helps new contributors understand the codebase at a high level and provides context for architectural evolution.

## Includes

The `ARCHITECTURE.md` file should aim to cover:

- **Introduction / Overview**:
  - Briefly state the project's main purpose and the overall architectural style (e.g., monolithic, microservices, modular, client-server).
  - What are the main goals of the architecture (e.g., performance, scalability, maintainability, portability)?
- **High-Level Diagrams**:
  - Visual representations of the system's architecture. This could be:
    - Component diagrams.
    - Deployment diagrams.
    - Data flow diagrams.
  - Use simple, clear diagrams. ASCII art, Mermaid.js, or linked images are options.
  - (If using Mermaid.js, provide the code block for it).
- **Key Components / Modules**:
  - List the major components or modules of the system.
  - For each component:
    - **Purpose**: What is its responsibility?
    - **Key Functionality**: What does it do?
    - **Interfaces**: How does it interact with other components (APIs, data formats, events)?
    - **Technologies Used**: (If specific, e.g., a particular library for a module).
  - Refer to the project structure (e.g., `src/` directory, specific files like `copy.c`, `main.c`).
- **Data Management**:
  - How is data stored and managed (if applicable)?
  - Database schema overview (if a database is used).
  - Data flow within the application.
- **Interactions and Flows**:
  - Describe common workflows or sequences of operations, showing how components interact to achieve a task.
  - Example: "When the `rpc init --readme` command is run..."
- **Design Decisions and Rationale**:
  - Document significant design choices made during development.
  - For each decision:
    - **Decision**: What was decided?
    - **Rationale**: Why was this decision made? What alternatives were considered? What are the trade-offs?
    - Examples: Choice of programming language (C), build system (Meson), specific algorithms, error handling strategy.
- **Cross-Cutting Concerns**:
  - How are aspects like error handling, logging, configuration, and security handled across the system?
- **Scalability and Performance Considerations**:
  - (If applicable) How is the system designed to scale? What are known performance characteristics or bottlenecks?
- **Future Architectural Goals / Evolution**:
  - (Optional) Any planned architectural changes or areas for future improvement. Link to `ROADMAP.md` if relevant.

## Tone

- Technical, clear, and precise.
- Objective and informative.

## Formatting

- Use Markdown.
- Use clear headings and subheadings.
- Use diagrams effectively. For Mermaid diagrams, ensure they are in a `mermaid` code block.
- Use code blocks for snippets or to illustrate data structures.

## Context and Tools

- **Project Structure**: Analyze the existing file and directory structure (e.g., using `list_dir` on `src/`).
  ```
  src/
  ├── copy.c
  ├── copy.h
  ├── main.c
  ├── print_utils.c
  └── print_utils.h
  ```
- **Build System**: Review `meson.build` for insights into components and dependencies.
- **Source Code**: Refer to the actual source code to understand component interactions.
- **Existing Documentation**: `README.md` might contain some high-level information.
