# Instructions for Generating .github/PULL_REQUEST_TEMPLATE.md

## Purpose

Provide a consistent template for contributors to use when creating pull requests. This helps ensure that PRs include all necessary information for reviewers, streamlining the review process.

## Content

The `PULL_REQUEST_TEMPLATE.md` should guide the contributor to provide:

- **Summary of Changes**:
  - A clear and concise description of what the pull request does.
  - Why these changes are being made (e.g., what problem it solves, what feature it adds).
- **Related Issue Number**:
  - A space to link to any relevant GitHub issues (e.g., "Fixes #123", "Closes #456", "Related to #789").
  - This helps track the context and resolution of issues.
- **Type of Change**:
  - A checklist or prompt to categorize the change (e.g., Bug fix, New feature, Documentation update, Refactoring, Build system changes, etc.).
  - Example:
    ```markdown
    Please check the type of change that applies to this PR:

    - [ ] Bug fix (non-breaking change which fixes an issue)
    - [ ] New feature (non-breaking change which adds functionality)
    - [ ] Breaking change (fix or feature that would cause existing functionality to not work as expected)
    - [ ] Documentation update
    - [ ] Refactoring
    - [ ] Build related changes
    - [ ] Other (please describe):
    ```
- **Checklist for Contributor**:
  - A pre-submission checklist to ensure the contributor has performed essential tasks.
  - Examples:
    - `[ ] I have read the [CONTRIBUTING.md](CONTRIBUTING.md) document.`
    - `[ ] My code follows the style guidelines of this project.`
    - `[ ] I have performed a self-review of my own code.`
    - `[ ] I have commented my code, particularly in hard-to-understand areas.`
    - `[ ] I have made corresponding changes to the documentation (if applicable).`
    - `[ ] My changes generate no new warnings.`
    - `[ ] I have added tests that prove my fix is effective or that my feature works (if applicable).`
    - `[ ] New and existing unit tests pass locally with my changes.`
    - `[ ] Any dependent changes have been merged and published in downstream modules.`
    - `[ ] I have updated `CHANGELOG.md` for user-facing changes.`
- **Test Plan/Testing Done**:
  - A section for the contributor to describe how they tested their changes.
  - What specific tests were performed (manual, unit, integration).
  - Steps for reviewers to reproduce the testing if necessary.
- **Screenshots or Gifs (if applicable)**:
  - For UI changes, encourage contributors to add visual aids.
- **Further Comments/Questions for Reviewers**:
  - A space for the contributor to add any other notes, ask specific questions, or highlight areas they'd like particular attention on during the review.

## Tone

- Clear, guiding, and helpful.

## Formatting

- Use Markdown.
- Use headings (`##`, `###`) for sections.
- Use checklists (`- [ ]`) for actionable items.
- Use comments (`<!-- ... -->`) for instructions to the contributor that shouldn't appear in the final PR description.

## Location

- Place the file as `PULL_REQUEST_TEMPLATE.md` directly in the `.github/` directory.
- It can also be named `pull_request_template.md` (lowercase) or be placed in a `.github/PULL_REQUEST_TEMPLATE/` directory if you need multiple PR templates (though a single one is most common).
