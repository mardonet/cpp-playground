# C++ OpenGL Teapot

This project renders three rotating teapots using different shading models: Flat, Gouraud, and Phong.

## Demo

https://youtu.be/uFcgsR97JEI

## Dependencies

This project requires the OpenGL Utility Toolkit (GLUT) to be installed.

## Installation on Linux

You can install the necessary libraries using your distribution's package manager.

### For Debian/Ubuntu-based systems:

Open a terminal and run the following command:
```bash
sudo apt-get update
sudo apt-get install -y freeglut3-dev
```

### For Fedora/CentOS/RHEL-based systems:

Open a terminal and run the following command:
```bash
sudo dnf install -y freeglut-devel
```
(Use `yum` instead of `dnf` on older systems).

## Compilation and Execution

Once the dependencies are installed, you can compile and run the project.

1.  Navigate to the `cpp-glteapot` directory:
    ```bash
    cd cpp-glteapot
    ```
2.  Compile the code using the provided Makefile:
    ```bash
    make
    ```
3.  Run the executable:
    ```bash
    ./cpp-glteapot
    ```
