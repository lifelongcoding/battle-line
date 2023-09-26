# Battle Line Game Project - Contribution Guidelines

Welcome to the Battle Line Game project! We greatly appreciate your interest and contributions. Please read the following guidelines carefully before contributing to ensure a smooth participation process.

## Reporting Issues

If you encounter problems or discover bugs while using the game, please report them on the project's [GitHub Issues](https://github.com/lifelongcoding/battle-line/issues) page. When reporting issues, please provide the following information:

- Game version (if available).
- Description of your operating system and environment.
- Detailed steps to reproduce the problem for easy replication.
- If possible, include screenshots or error logs.

## Submitting Code

If you wish to contribute code to the project, your participation is very welcome. Please follow these steps:

> **Note**
>
> Please note that there are two repositories here. One is the **main repository**, and you do not have permission to make changes to this repository. The other is the main repository that you have forked, which we will refer to as the **forked repository**. In a sense, this is considered your own repository, so you can make any modifications to this repository.

1. **Fork the Repository**: First, fork the project's GitHub repository into your own GitHub account by clicking the "Fork" button in the upper right corner of the project's GitHub page.

2. **Clone Your Fork**: Clone your forked repository to your local development environment.

   ```shell
   git clone git@github.com:<your-github-username>/battle-line.git
   ```
    > **Warning**
    >
    > You may see below errors that prevent you from connecting to the remote repository, or timeout errors when you do push operations, especially if you are using the HTTP protocol.
    >
    > ```bash
    > Permission denied (publickey).
    > fatal: Could not read from remote repository.
    > fatal: unable to access 'https://github.com/<your-github-username>/battle-line.git/': Recv failure: Connection was reset.
    > fatal: unable to access 'https://github.com/<your-github-username>/battle-line.git/': The requested URL returned error : 403.
    > ```
    >
    > Solution:
    >
    > 1. Use [SSH protocol](https://docs.github.com/en/authentication/connecting-to-github-with-ssh) to access the repo if you face network issue.
    > 2. Try more times in case the push operation fails occasionally.

3. **Set Upstream**: After you have cloned the forked repository to your local machine, you need to set the main repository as the upstream for future updates to your forked repository.

   ```bash
   git remote add upstream https://github.com/lifelongcoding/battle-line.git
   ```

   >When you have cloned your forked repository and set up the upstream repository successfully, running `git remote -v` should display the following:
   >
   >```
   >origin  git@github.com:<your-github-username>/battle-line.git (fetch)
   >origin  git@github.com:<your-github-username>/battle-line.git (push)
   >upstream  https://github.com/lifelongcoding/battle-line.git (fetch)
   >upstream  https://github.com/lifelongcoding/battle-line.git (push)
   >```
   >
   >Here, `origin` points to your forked repository, while `upstream` points to the main repository (the original repository). 

   > **Note**
   >
   > **Please note that before you start developing a new feature each time, make sure your branch up to date with the main repository.**
   >
   > With this configuration, you can use `git pull upstream master` to fetch the latest changes from the main repository to your local branch, keeping it up to date.

4. **Create a Branch**: Create a new branch for your contribution.

   ```shell
   git checkout -b <your-feature-name>
   ```

5. **Write Code**: Develop your code on the new branch, making sure it adheres to the project's coding standards and style guidelines.

6. **Commit Changes**: Commit your changes to your branch.

   ```shell
   git add .
   git commit -m "Describe your changes"
   ```

7. **Push the Branch**: Push your branch to your forked repository on GitHub.

   ```shell
   git push origin <your-feature-name>
   ```

8. **Create a Pull Request**: Create a Pull Request (PR) on the project's GitHub page by navigating to your forked repository and clicking "New Pull Request." Describe your changes and their purpose. We will review your code and provide feedback.

9. **Code Review**: Once the PR is created, team members will review the code. Please actively engage in any discussions and improvements.

10. **Merge the PR**: Once your PR passes review, it will be merged into the master branch of the project's repository.

## Code Standards

To maintain code quality and consistency, we strongly recommend adhering to Google's [C++ Style Guide](https://google.github.io/styleguide/cppguide.html). This style guide provides detailed guidelines for writing clean and readable C++ code.

- Use meaningful variable and function names following the guidelines.
- Maintain consistent indentation and code style as per Google's recommendations.
- Add appropriate comments and documentation as outlined in the style guide.
- Follow best practices for C++ programming, as advocated by Google.

You can also refer to Google's [Style Guide Repository](https://github.com/google/styleguide) for additional resources.

We encourage you to read and apply these guidelines to your code contributions, ensuring that your code aligns with the project's standards.

## Commit Messages

When submitting code, please provide meaningful commit messages to help other developers and team members understand your changes. A good commit message should include:

- A concise description summarizing your changes.
- Detailed explanations of why the change is necessary and how it was implemented.
- References to relevant GitHub issues if applicable.

## License

Please note that by contributing code or in any other way participating in the project, you agree to distribute and share your contributions under the project's open-source license.

Thank you for your participation and contributions! We hope you have a pleasant experience with the Battle Line Game project. If you have any questions or need assistance, feel free to contact the project maintainers.