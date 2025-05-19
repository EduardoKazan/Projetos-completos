# This setup.py file is used to package the PID control library as a Python
# package.
# It includes metadata about the package, such as its name, version, author,
# and description.

from setuptools import setup, find_packages

with open("README.md", "r") as f:
    page_description = f.read()

with open("requirements.txt") as f:
    requirements = f.read().splitlines()

setup(
    name="pid_control",
    version="0.0.1",
    author="EduardoKazan",
    author_email="eduardo_kazan@hotmail.com",
    description="A Python library for implementing PID control algorithms.",
    long_description=page_description,
    long_description_content_type="text/markdown",
    url="my_github_repository_project_link",
    packages=find_packages(),
    install_requires=requirements,
    python_requires='>=3.8',
)
