# Instructions for Generating ROADMAP.md

## Purpose

Share the project's upcoming features, goals, and milestones with the community. This provides transparency, sets expectations, and can encourage contributions towards specific objectives.

## Includes

The `ROADMAP.md` file should typically contain:

- **Introduction**:
  - Briefly explain the purpose of the roadmap and that it's subject to change.
  - Mention how the community can get involved or provide feedback (e.g., link to issue tracker or discussions).
- **Current Status/Version**:
  - (Optional) Briefly mention the current stable version and its key features, or link to the `CHANGELOG.md`.
- **Short-Term Goals (e.g., Next Release / Current Milestone)**:
  - Features and improvements planned for the immediate future.
  - Could be tied to a specific version number or milestone (e.g., "Version 1.2.0", "Q3 2025").
  - For each item, a brief description of the feature/goal.
  - (Optional) Link to relevant GitHub issues or projects.
- **Mid-Term Goals (e.g., Next 6-12 Months)**:
  - Larger features or architectural changes planned for the medium term.
  - These might be less detailed than short-term goals.
- **Long-Term Vision / Goals (e.g., Beyond 1 Year)**:
  - Broader objectives and directions for the project.
  - May include aspirational goals or areas of exploration.
- **Version Goals (if applicable)**:
  - If the project has specific themes or major goals for upcoming versions (e.g., "v2.0 - API Overhaul", "v3.0 - Plugin Architecture").
- **Community Input / Feature Requests**:
  - How the community can suggest features or vote on priorities.
  - Link to the feature request template or discussion forum.
- **Past Achievements / Completed Milestones**:
  - (Optional) A section briefly listing major features or milestones already achieved, possibly linking to past releases in the `CHANGELOG.md`. This shows progress.
- **Disclaimer**:
  - A note that the roadmap is a living document and priorities can change based on feedback, resources, and unforeseen circumstances.

## Tone

- Forward-looking, exciting, and transparent.
- Realistic about timelines and scope.

## Formatting

- Use Markdown.
- Use clear headings for different timeframes or goal categories.
- Use bullet points or numbered lists for features within each section.
- Consider using tables or GitHub Projects for a more structured view if the roadmap is complex.

## Context and Tools

- Review existing `CHANGELOG.md` for past releases and the `[Unreleased]` section for immediate plans.
- Check GitHub Issues, especially those with `enhancement` or `feature-request` labels, and any Milestones defined in the repository.
- The `getCurrentMilestone` and `getReleaseFeatures` tools might be useful if the project uses GitHub Milestones and Releases extensively.
