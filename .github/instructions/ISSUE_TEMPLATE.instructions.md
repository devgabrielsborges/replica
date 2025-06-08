# Instructions for Generating Issue Templates (.github/ISSUE_TEMPLATE/\*.md)

## Purpose

Provide structured templates for users and contributors when they create new issues (e.g., bug reports, feature requests). This ensures that maintainers receive consistent and complete information, making it easier to understand, categorize, and address issues.

## General Guidelines for All Issue Templates

- **File Naming**:
  - `bug_report.md` for bug reports.
  - `feature_request.md` for feature requests.
  - Custom templates can have descriptive names (e.g., `documentation_issue.md`, `security_concern.md`).
- **YAML Frontmatter**: Each template should start with YAML frontmatter to configure its behavior in GitHub's new issue interface.
  - `name`: The display name of the template in the issue type chooser.
  - `about`: A short description of what the template is for, shown in the issue type chooser.
  - `title`: (Optional) A suggested title for issues created with this template. Users can change it. Example: `"[BUG]: <Short description of bug>"`.
  - `labels`: (Optional) A list of labels to automatically apply to issues created with this template (e.g., `bug`, `enhancement`, `documentation`).
  - `assignees`: (Optional) A list of users to automatically assign to issues created with this template.
- **Markdown Content**: The body of the template should use Markdown to guide the user.
  - Use headings (`###`) for sections.
  - Use comments (`<!-- ... -->`) to provide instructions or examples that won't appear in the final issue.
  - Use placeholders like `<Describe the bug here>` or ask specific questions.
  - Clearly indicate required vs. optional information.
- **Clarity**: Make templates easy to understand and fill out.
- **Conciseness**: Ask only for necessary information.

## Specific Templates to Create:

### 1. Bug Report (`.github/ISSUE_TEMPLATE/bug_report.md`)

**Purpose**: To collect detailed information about a bug or unexpected behavior.
**Content should prompt for**: - Clear and concise description of the bug. - Steps to reproduce (be specific). - Expected behavior. - Actual behavior. - Environment details (OS, project version, compiler version, relevant dependencies). - Screenshots or logs (if applicable). - Any additional context.
**Example YAML Frontmatter**:

```yaml
name: Bug Report
about: Create a report to help us improve
title: "[BUG]: "
labels: bug
assignees: ""
```

### 2. Feature Request (`.github/ISSUE_TEMPLATE/feature_request.md`)

**Purpose**: To gather ideas for new features or enhancements.
**Content should prompt for**: - Description of the problem the feature would solve ("Is your feature request related to a problem? Please describe."). - Description of the proposed solution ("Describe the solution you'd like"). - Description of alternatives considered ("Describe alternatives you've considered"). - Additional context (use cases, benefits, potential drawbacks).
**Example YAML Frontmatter**:

```yaml
name: Feature Request
about: Suggest an idea for this project
title: "[FEATURE]: "
labels: enhancement
assignees: ""
```

### 3. Custom Template (Example: Documentation Issue - `.github/ISSUE_TEMPLATE/documentation_issue.md`)

**Purpose**: To report issues or suggest improvements related to documentation.
**Content should prompt for**: - Which part of the documentation is affected (e.g., file name, URL, section). - Description of the issue (e.g., unclear, incorrect, missing information). - Suggested improvement. - Why this improvement is needed.
**Example YAML Frontmatter**:

```yaml
name: Documentation Issue
about: Report an issue or suggest an improvement for the documentation
title: "[DOCS]: "
labels: documentation
assignees: ""
```

### 4. Custom Template (Example: Security Concern - `.github/ISSUE_TEMPLATE/security_concern.md`)

**Purpose**: To guide users on how to report security concerns (often directing them to a private channel).
**Content should**: - **Strongly advise against reporting security vulnerabilities publicly.** - Direct users to the `SECURITY.md` file for instructions on how to report vulnerabilities privately. - Provide a link to `SECURITY.md`.
**Example YAML Frontmatter**:

```yaml
name: Security Vulnerability Report
about: Report a security vulnerability (private disclosure instructions)
title: "[SECURITY] Vulnerability Report (Follow Private Disclosure)"
labels: security
```

**Body Content Example for Security Template**:

```markdown
<!--
!!! IMPORTANT !!!
DO NOT report security vulnerabilities publicly here.
Please follow the instructions in our Security Policy to report security issues privately.
-->

## Security Vulnerability Reporting

Thank you for helping keep Replica secure.

To ensure the security of our users and the project, we ask that you **do not create a public GitHub issue for security vulnerabilities.**

Instead, please refer to our [**Security Policy (SECURITY.md)**](../../SECURITY.md) for detailed instructions on how to report your findings privately. This allows us to address the issue before it becomes publicly known.

**[Click here to read our Security Policy](../../SECURITY.md)**

If you have already disclosed details here, please delete this issue immediately and follow the private reporting guidelines.
```

## Location

- Place these files in the `.github/ISSUE_TEMPLATE/` directory.
- (Optional) You can also create a `config.yml` file in `.github/ISSUE_TEMPLATE/` to customize the issue template chooser further (e.g., to disable blank issues or link to external sites).
