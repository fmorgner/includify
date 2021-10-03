#!/usr/bin/env python3

import argparse
import os
import subprocess
import sys
from pathlib import Path


def result_to_path(result: subprocess.CompletedProcess) -> Path:
    return Path(result.stdout.strip(os.linesep))


def get_repository_root() -> Path:
    return result_to_path(
        subprocess.run(
            ["git", "rev-parse", "--show-toplevel"],
            cwd=Path(__file__).resolve().parent,
            capture_output=True,
            text=True,
        )
    )


def install() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--profile",
        help="Set the Conan profile to be used.",
        default="default",
        type=str,
    )
    args = parser.parse_args()
    subprocess.run(
        [
            "conan",
            "install",
            "--build",
            "missing",
            "--install-folder",
            "build",
            "--profile",
            args.profile,
            ".",
        ],
        cwd=get_repository_root(),
        check=True,
    )


def build() -> None:
    subprocess.run(
        ["conan", "build", "--build-folder", "build", "."],
        cwd=get_repository_root(),
        check=True,
    )


def package() -> None:
    subprocess.run(
        ["conan", "package", "--build-folder", "build", "."],
        cwd=get_repository_root(),
        check=True,
    )


if __name__ == "__main__":
    sys.exit("Scripts is called through Poetry.")
