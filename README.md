# Replica

Replica is a command-line utility for copying default prompt and instructions templates, designed to streamline the setup of agentic applications.

## Usage

The primary command for using Replica is `init`. This command initializes a new project by copying predefined templates and configuration files to a specified destination directory.

```bash
rpc init <destination_directory>
```

This will copy all default files, including README templates, release notes templates, and social media post templates.

### Options

You can specify which files to copy using the following options:

*   `--readme`: Copies only the README-related files.
    ```bash
    rpc init --readme <destination_directory>
    ```
*   `--release-notes`: Copies only the release notes-related files.
    ```bash
    rpc init --release-notes <destination_directory>
    ```
*   `--post`: Copies only the social media post-related files (e.g., for LinkedIn).
    ```bash
    rpc init --post <destination_directory>
    ```

### Help

To display the help message, use:

```bash
rpc help
```

or

```bash
rpc -h
```

or

```bash
rpc --help
```

## Project Structure

The project is structured as follows:

*   `src/`: Contains the source code for the Replica utility.
    *   `main.c`: The main entry point of the application, handling command-line arguments.
    *   `copy.c`/`copy.h`: Contains functions for copying files and directories.
    *   `print_utils.c`/`print_utils.h`: Contains utility functions for printing help messages and other information.
*   `meson.build`: The build configuration file for the Meson build system.

## Building the Project

To build the project, you will need Meson and Ninja installed.

1.  Navigate to the project directory.
2.  Create a build directory: `meson setup builddir`
3.  Compile the project: `meson compile -C builddir`

The executable will be located at `builddir/replica`.

## Examples

**Note:** The following examples assume you have successfully built the project and the `replica` executable is in your current path or you are running it from the `builddir`.

Let's say you want to initialize a new project in a directory named `my_new_project`.

1.  **Initialize with all files:**
    ```bash
    rpc init my_new_project
    ```
    This will create `my_new_project` (if it doesn't exist) and copy all standard templates into it, organized under a `.github` directory structure similar to the `replica` project itself.

2.  **Initialize with only README files:**
    ```bash
    rpc init --readme my_new_project
    ```
