# Instructions for Generating the LICENSE file

## Purpose

Specify the terms under which others can use, modify, and distribute the project's code.

## Content

The `LICENSE` file should contain the full text of the chosen open-source license.

## Choosing a License

- **Identify Project Needs**: Consider the goals of the project. Do you want to encourage broad adoption, ensure contributions remain open source, or protect against patent claims?
- **Popular Options**:
  - **MIT License**: Very permissive, allows for use in proprietary software, simple and short.
  - **Apache License 2.0**: Permissive, provides an express grant of patent rights from contributors to users, good for corporate projects.
  - **GNU General Public License (GPL) v3.0**: Strong copyleft license. Requires that modifications and derivative works also be licensed under GPL. Ensures the software and its derivatives remain open source.
- **Reference**: Use [choosealicense.com](https://choosealicense.com/) to help select an appropriate license based on the project's requirements. The site provides summaries and full texts of common licenses.

## Steps

1. **Select a License**: Based on the project's needs and the information from choosealicense.com. For this project, the current `LICENSE` file uses MIT. Confirm if this is still the desired license.

   ```
   // filepath: /home/borges/dev/replica/LICENSE
   MIT License

   Copyright (c) [2025] [Gabriel Souza Borges]

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
   ```

2. **Obtain the Full Text**: Copy the complete, unmodified text of the chosen license.
3. **Update Placeholders**: If the license text includes placeholders (e.g., `[year]`, `[fullname]`, `[project name]`), replace them with the correct information for this project.
   - For MIT License: `[year]` should be the current year or range of years of copyright. `[fullname]` should be the copyright holder's name (e.g., "Gabriel Souza Borges" or "The Replica Project Authors").
4. **Create/Update the `LICENSE` file**: Place the full license text into a file named `LICENSE` (or `LICENSE.md` if preferred, though `LICENSE` is common) in the root of the project.

## Important Considerations

- **No Modifications**: Do not alter the standard text of the chosen license, other than filling in required placeholders.
- **Consistency**: Ensure the license chosen is compatible with the licenses of any dependencies the project uses.
- **Visibility**: The `LICENSE` file should be in the root directory of the project.
- **README**: Mention the license in the `README.md` file (e.g., "Licensed under the MIT License.").
