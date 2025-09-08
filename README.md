# TritonUAS OBCpp Onboarding

TODO: Write this

## Setup

1. Pre-requisites
- `git`
- [Docker Desktop/Engine](https://docs.docker.com/get-started/get-docker/)
- [Visual Studio Code](https://code.visualstudio.com/download)
    - After VSC is downloaded, download this extension: [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)


2. Clone the Repository and Open in Visual Studio Code.
```bash
# Navigate to directory where you want to start
git clone git@github.com:tritonuas/onboarding_obcpp_2025.git
cd onboarding_obcpp
code .
```

3. Pull the Dev Container:
    1. In the bottom left of the screen, click on the remote window icon. It should look like two angle brackets next to each other. Also, you can instead press "Ctrl+Shift+P"
    2. Select (or type) reopen in container.
    3. If successful, the bottom-left should say: `Dev Container: TUAS Onboarding`.

Now you are set up!!

## Usage:
Most operations including building and running the project is done through the `Makefile`. Here are the main commands:

1. `make` - runs the default build command.
2. `make clean` - empties the build directory
3. `make run` - runs project / mission_runner