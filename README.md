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
    3. If successful, the bottom-left should say: `Dev Container: OBC Onboarding`.

Now you are set up!!

## Usage:
Most operations including building and running the project is done through the `Makefile`. Here are the main commands:

1. `make` or `make build` - runs the default build command.
2. `make protos` - builds the protobuf files 
3. `make run` - runs project / mission_runner
4. `make clean` - empties the build directory

## Tests:
To run unit tests, you can just run `make test`. For integration tests (requires manual verification), make sure you run `make build` first, then cd into `build/` and run `./testname`, where testname is the file of your test (without the .cpp extension).

<<<<<<< HEAD
To add tests yourself, simply put them under `tests/unit` or `tests/integration`.
=======
To add tests yourself, simply put them under `tests/unit` or `tests/integration`.
>>>>>>> 447f9c8 (Add integration test sample)
