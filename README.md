**CURRENT CODE VERSION:** [![SWRRobotics Version](https://img.shields.io/badge/version-3.0.0-blue.svg)](https://github.com/SWRRoboticsTeam/Practice/blob/master/CHANGELOG.md)

# SWRRobotics Team Repository (49627A)
This repository is dedicated to the development of the Shoreham-Wading River Robotics Team RobotC code.

## Adhering To Gitflow
Gitflow Workflow defines a strict branching model designed around the project release. This provides a robust framework for managing larger projects.

### MASTER BRANCH

The master branch stores the official release history tied to a version. Pull requests can only be accepted by a lead developer.

### DEVELOP BRANCH

The develop branch serves as an integration branch for features. Individual developer code should be branched from master but always pushed back to develop for team code reviews. 

- Branches should follow the naming convention {FirstInitial}{LastName}-{Feature#/FeatureName}
  - Ex. NVERTUCCI-Feature1 or NVERTUCCI-TerminatorBot Autonomous Code
- Be sure, as a best practice, to start new feature branches from MASTER as this is the latest and greatest production code available
- When making a pull request, the **base branch** should be the branch you wish to push into while comparing to your feature or development branch
  - To make a PR into develop, select 'Development' as your base branch and compare it to your feature branch

**Currently Active Branches** ([can be viewed here](https://github.com/SWRRoboticsTeam/Robot-Code/branches))
