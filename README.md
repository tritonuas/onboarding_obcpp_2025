# TritonUAS OBCpp Onboarding

If you haven't already, make sure that you have read the onboarding project overview on the [wiki](https://tritonuas.com/wiki/software/onboarding/project/project_overview/), as well as 1.1 to 1.4 in [How to Contribute](https://tritonuas.com/wiki/software/how_to_contribute/).

After you finish setting up the onboarding OBC on your machine, follow the onboarding tasks step by step on the wiki, starting with [OBC Intro](https://tritonuas.com/wiki/software/onboarding/project/tasks/1_obc_intro/)!

## Setup

1. Pre-requisites
- `git`
- [Docker Desktop/Engine](https://docs.docker.com/get-started/get-docker/)
- [Visual Studio Code](https://code.visualstudio.com/download)
    - After VSC is downloaded, download this extension: [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)


2. Clone the Repository
```bash
# Navigate to directory where you want to start
git clone git@github.com:tritonuas/onboarding_obcpp_2025.git
cd onboarding_obcpp_2025
```

Then, open this folder in VS Code.

3. Pull the Dev Container:
    1. In the bottom left of the screen, click on the remote window icon. It should look like two angle brackets next to each other. Also, you can instead press "Ctrl+Shift+P"
    2. Select (or type) reopen in container.
    3. If successful, the bottom-left should say: `Dev Container: OBC Onboarding`.

4. Login to GitHub within the Dev Container (Optional)
    1. In the terminal of your dev container, enter `gh auth login`
    2. Then, answer the questions **exactly** as below with the exception of the passphrase and title of the ssh key, to which you can type in whatever you'd like, or just leave it as default:
    ```
    ? Where do you use GitHub? GitHub.com
    ? What is your preferred protocol for Git operations on this host? SSH
    ? Generate a new SSH key to add to your GitHub account? Yes
    ? How would you like to authenticate GitHub CLI? Login with a web browser
    ```
    3. Complete the remaining on screen instructions
    4. If successful, type in `git fetch`. You shouldn't get any errors.

Now you are set up!!

## Usage:
Most operations including building and running the project is done through the `Makefile`. Here are the main commands:

1. `make` or `make build` - runs the default build command.
2. `make protos` - builds the protobuf files 
3. `make run` - runs project / mission_runner
4. `make clean` - empties the build directory


## Tests:
To run unit tests, you can just run `make test`.

For integration tests (requires manual verification), make sure you run `make integration` first to build the integration test targets, then cd into `build/` and run `./tests/testname`, where testname is the file of your test (without the .cpp extension).

To add tests yourself, simply put them under `tests/unit` or `tests/integration`.

