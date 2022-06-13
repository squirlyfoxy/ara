# create ./deploy/web folder and copy files to it (wbuild folder)
import os
import shutil
import sys

print("Preparing web environment...")

# parameters: project name
project_name = sys.argv[1]

# call deploy_project.py
os.system("python scripts/deploy_project.py " + project_name)

try:
    os.makedirs("deploy/" + project_name + "/web")
except FileExistsError:
    shutil.rmtree("deploy/" + project_name + "/web")

# copy files from wbuild folder to deploy/web folder (subdirectories too)
shutil.copytree("wbuild", "deploy/" + project_name + "/web")

