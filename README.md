# Replica (`rpc`)

Replica (`rpc`) is a cross-platform command-line utility written in C for managing and copying default prompt and instruction templates. It is designed to streamline the setup of new projects by providing quick initialization of README, release notes, and other template files. The tool is lightweight, fast, and suitable for both individual developers and teams.

## Features

- **Template Initialization**: Quickly set up new projects with predefined README, release notes, and post templates.
- **Cross-Platform Support**: Works on Linux, macOS, and Windows.
- **AUR Package**: Easy installation for Arch Linux users via the AUR (`rpc-git`).
- **Automated Dependency Checks**: Installation scripts verify and install required dependencies.
- **Robust File Copying**: Handles file and directory copying with error handling and support for recursive operations.

## Installation

### Linux/macOS

```sh
./install.sh
```

### Windows

Run `install.bat` from a command prompt:

```bat
install.bat
```

### Arch Linux (AUR)

```sh
yay -S rpc-git
```

## Usage

After installation, use the `rpc` command:

```sh
rpc init <destination>
# or for specific templates:
rpc init --readme <destination>
rpc init --release-notes <destination>
rpc init --post <destination>
```

For help:

```sh
rpc help
```

## Project Structure

- `src/` — C source code for the utility
  - `main.c` — Command-line interface and argument parsing
  - `copy.c`/`copy.h` — File and directory copy logic, template operations
  - `print_utils.c`/`print_utils.h` — Help and output utilities
- `install.sh` — Installation script for Linux/macOS
- `install.bat` — Installation script for Windows
- `meson.build` — Meson build configuration
- `replica-aur/PKGBUILD` — Arch Linux AUR packaging
- `.github/` — Project prompts and instructions
- `CHANGELOG.md` — Project changelog
- `LICENSE` — MIT License

> **Note:** Build artifacts and the `builddir/` directory are ignored (see `.gitignore`).

## Contributing

Contributions are welcome! Please open issues or submit pull requests on GitHub.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Credits

- Developed by Gabriel Souza Borges
- Thanks to the open source community and contributors
