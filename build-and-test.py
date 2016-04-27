import subprocess
import shutil
import sys
import os
DIR = os.path.dirname(os.path.realpath(__file__))
cmake_build_dir = os.path.join(os.path.dirname(DIR), "devtools_build")
# cpplint = os.path.join(DIR, "3rdparty/cpplint.py")
cpplint = os.path.join(os.path.join(DIR, "3rdparty"), "cpplint.py")
github_api_repo = "https://api.github.com/repos/UNN-VMK-Software\
                  /devtools-course-practice"
if sys.platform == 'win32':
    make = "mingw32-make"
else:
    make = "make"


def _try(msg):
    if (msg is not None):
        if msg is not 0:
            print("ERROR with", msg, "in ", os.getcwd())
            sys.exit(msg)


def Header(msg):
    print("")
    print("*****************************************************")
    print(msg)
    print("*****************************************************")
    print("")


def CheckGoogleStyleInDir():
    extensions = ["hpp", "h", "cpp", "cxx"]
    print("checking files in dir ", os.getcwd())
    files = os.listdir(os.getcwd())
    for file_ in files:
        for extension in extensions:
            if extension in file_:
                # status = subprocess.call("python")
                status = subprocess.call(["python2.7", cpplint, file_])
                # print(file_)
                if status != 0:
                    return status
    return 0


def CheckGoogleStyle():
    # Go through all directories and check Google style
    dirs = next(os.walk(os.getcwd()))[1]
    if len(dirs) == 0:
        _try(CheckGoogleStyleInDir())
    else:
        for dir in dirs:
            if dir == "3rdparty" or dir[0] == "." or dir == "lab-guide" or dir == "Testing":
                continue
            os.chdir(os.path.join(os.getcwd(), dir))
            CheckGoogleStyle()
    os.chdir(os.path.dirname(os.getcwd()))


def clean():
    shutil.rmtree(cmake_build_dir)


def BuildCMakeProject():
    Header("Build common CMake project")
    os.mkdir(cmake_build_dir)
    os.chdir(cmake_build_dir)
    _try(subprocess.call(["cmake", "-DCOVERAGE=ON", "-DCMAKE_BUILD_TYPE=Debug", DIR]))
    _try(subprocess.call(make))


def CTest():
    Header("Run all CTest tests")
    _try(subprocess.call(["ctest", "--output-on-failure"]))


def GoogleTest():
    Header("Run all GoogleTest tests")
    test_folder = os.path.join(os.getcwd(), "bin")
    os.chdir(test_folder)
    files = os.listdir('.')
    print(files)
    for file_ in files:
        if "test_" in file_:
            Header("Testing {}".format(file_))
            _try(subprocess.call("./{}".format(file_)))


Header("Check \"Google C++ Style\"")
CheckGoogleStyle()
BuildCMakeProject()
CTest()
GoogleTest()
clean()
