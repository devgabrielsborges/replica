# Replica (`rpc`)

Replica (`rpc`) is a cross-platform command-line utility written in C for managing and copying default prompt and instruction templates. It is designed to streamline the setup of new projects by providing quick initialization of README, release notes, and other template files. The tool is lightweight, fast, and suitable for both individual developers and teams.

## Features

- **Template Initialization**: Quickly set up new projects with predefined README, release notes, and other template files.
- **Beautiful CLI Interface**: Modern, colorful output with icons and clear formatting that automatically adapts to terminal capabilities.
- **Verbose Mode**: Detailed progress output for debugging and monitoring operations.
- **Robust Error Handling**: User-friendly error messages with helpful suggestions for resolution.
- **Cross-Platform Support**: Works on Linux, macOS, and Windows with consistent behavior.
- **AUR Package**: Easy installation for Arch Linux users via the AUR (`rpc-git`).
- **Automated Dependency Checks**: Installation scripts verify and install required dependencies.
- **Smart File Operations**: Handles file and directory copying with comprehensive error handling and support for recursive operations.

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
# Initialize with default templates (README + release notes)
rpc init <destination>

# Copy specific templates
rpc init --readme <destination>
rpc init --release-notes <destination>
rpc init --all <destination>

# Use verbose mode for detailed output
rpc init --verbose --readme <destination>

# Get help and version information
rpc --help
rpc --version
```

### Available Templates

The CLI supports the following template categories:

- `--readme` - README generation templates
- `--release-notes` - Release notes templates  
- `--post` - LinkedIn post templates
- `--contributing` - Contributing guidelines templates
- `--license` - License selection templates
- `--security` - Security policy templates
- `--code-of-conduct` - Code of conduct templates
- `--issue-template` - Issue template prompts
- `--pr-template` - Pull request template prompts
- `--architecture` - Architecture documentation templates
- `--roadmap` - Project roadmap templates
- `--support` - Support documentation templates
- `--install` - Installation guide templates
- `--all` - Copy all available templates

### CLI Features

- **Beautiful Output**: Color-coded messages with icons and progress indicators
- **Verbose Mode**: Detailed output with `--verbose` flag
- **Smart Color Detection**: Automatically disables colors when output is piped
- **Robust Error Handling**: Clear error messages with helpful suggestions
- **Cross-Platform**: Works consistently across Linux, macOS, and Windows

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
