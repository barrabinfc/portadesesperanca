#!/usr/bin/env bash
# A script to bootstrap porta da esperanca 
# It expects to be run on Ubuntu 14.04 via 'sudo'
# It checks out the porta source code from Github into ~/portadesesperanca and then runs 'make install' .

set -eo pipefail
export DEBIAN_FRONTEND=noninteractive
export PORTA_REPO=${PORTA_REPO:-"https://github.com/barrabinfc/portadesesperanca.git"}

if ! command -v apt-get &>/dev/null
then
  echo "This installation script requires apt-get. For manual installation instructions, consult http://progrium.viewdocs.io/dokku/advanced-installation ."
  exit 1
fi

apt-get update
apt-get install -qq -y git make curl software-properties-common man-db help2man

cd /home/pi
su - pi
mkdir -p porta
mkdir -p porta/movies
mkdir -p porta/scripts
mkdir -p porta/bin
test -d portadesesperanca || git clone $PORTA_REPO
cd portadesesperanca
git fetch origin

if [[ -n $PORTA_BRANCH ]]; then
  git checkout origin/$PORTA_BRANCH
elif [[ -n $PORTA_TAG ]]; then
  git checkout $PORTA_TAG
fi

sudo make install

echo
echo "Almost done! Now copy the movies to ~/porta/movies/"
