# Instructions for Generating SECURITY.md

## Purpose

Outline how to report security vulnerabilities responsibly to the project maintainers. This helps protect users by ensuring vulnerabilities are disclosed privately and addressed before public announcement.

## Includes

The `SECURITY.md` file should contain the following sections:

- **Supported Versions**:
  - Clearly state which versions of the project are currently supported with security updates. This helps reporters know if their finding is relevant.
  - Example:
    ```
    | Version | Supported          |
    | ------- | ------------------ |
    | 1.1.x   | :white_check_mark: |
    | 1.0.x   | :x:                |
    | < 1.0   | :x:                |
    ```
- **Reporting a Vulnerability**:
  - **Contact Method**: Provide a clear, private method for reporting vulnerabilities. This is typically a dedicated email address (e.g., `security@example.com`) or a link to a private vulnerability reporting feature if available (e.g., GitHub Security Advisories). **Do not** ask users to report security vulnerabilities in public issue trackers.
  - **Information to Include**: Specify what information should be included in the vulnerability report to help the maintainers understand and verify the issue. Examples:
    - Description of the vulnerability.
    - Steps to reproduce the vulnerability.
    - Affected version(s).
    - Potential impact.
    - Any proof-of-concept code (if applicable and safe to share).
    - Your name and contact information (optional, for acknowledgment).
- **Disclosure Policy (Our Process)**:
  - **Acknowledgment**: State that the project maintainers will acknowledge receipt of the vulnerability report, typically within a specific timeframe (e.g., "within 48 hours").
  - **Investigation**: Explain that the report will be investigated to confirm the vulnerability.
  - **Communication**: Describe how the project will communicate with the reporter during the process (e.g., updates on progress, requests for more information).
  - **Fix and Release**: Outline the general process for developing a fix and releasing it.
  - **Public Disclosure**: Explain when and how the vulnerability will be publicly disclosed (e.g., after a fix is available and users have had a reasonable time to update). This might involve coordinating with the reporter, issuing a CVE, and publishing a security advisory.
- **Expected Response Time**:
  - Provide an estimated timeframe for different stages of the process (e.g., initial response, confirmation of vulnerability, timeline for a fix). Be realistic.
  - Example: "We aim to respond to your report within 2 business days and to confirm the vulnerability within 5 business days."
- **Scope**:
  - (Optional) Define what is considered in scope and out of scope for vulnerability reports (e.g., "Vulnerabilities in third-party dependencies should be reported to those projects directly," or "Denial of service attacks against our public demo server are out of scope unless they indicate a vulnerability in the software itself.").
- **Safe Harbor / Bug Bounty Program**:
  - (Optional) If the project has a bug bounty program or a safe harbor statement (promising not to take legal action against researchers acting in good faith), include details here.

## Tone

- Professional, serious, and reassuring.
- Clear and direct.

## Formatting

- Use Markdown.
- Use clear headings for each section.
- Place the `SECURITY.md` file in the root of the project or in the `.github` folder. GitHub specifically looks for `SECURITY.md` in these locations to provide a link on the repository's "Security" tab.
