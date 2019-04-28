#!/usr/bin/env bash

################################################################################################################################################################

# @project        Toto|Splash
# @file           tools/development/helpers/term.sh
# @author         Lucas Brémond <lucas.bremond@gmail.com>
# @license        MIT License

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
project_directory="${script_directory}/../../.."

pushd "${project_directory}" > /dev/null

screen /dev/tty.USB0 115200

popd > /dev/null

################################################################################################################################################################