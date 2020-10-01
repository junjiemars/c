#!/usr/bin/env bash

_ROOT_DIR_="`cd $(dirname ${BASH_SOURCE[0]}); pwd`"
_TEST_="${_TEST_:-basic}"
_OS_NAME_="`uname -s 2>/dev/null`"
_WIN_ENV_=


case "${_OS_NAME_}" in
  MSYS_NT-*|MINGW??_NT-*) _OS_NAME_="WinNT" ;;
esac

CC="${CC}"
if [ -z "$CC" ]; then
  case `uname -s 2>/dev/null` in
    Darwin)  CC="clang" ;;
    Linux)   CC="gcc"   ;;
    WinNT)   CC="cl"    ;;
  esac
fi

cd "${_ROOT_DIR_}"

# check nore
if [ ! -f "${_ROOT_DIR_%/}/configure" ]; then
  bash <(curl https://raw.githubusercontent.com/junjiemars/nore/master/bootstrap.sh)
  if [ 0 -ne $? ]; then
    echo "!panic: install Nore failed"
    exit 1
  fi
fi

# check cc-env for cl
if [ "WinNT" = "${_OS_NAME_}" -a "cl" = "${CC}" ]; then
  if [ ! -f "${HOME}/.nore/cc-env.sh" ]; then
    echo "!panic: ${HOME}/.nore/cc-env.sh no found"
    exit 1
  fi
  ${HOME}/.nore/cc-env.sh
  if [ ! -f "${HOME}/.nore/cc-env.bat" ]; then
    echo "!panic: ${HOME}/.nore/cc-env.bat no found"
    exit 1
  fi
  _WIN_ENV_="${HOME}/.nore/cc-env.bat"
fi

# basic test
declare -A _TEST_BASIC_=(
  --has-hi
  --has-algo
  --has-ds
  --has-library
  --has-lang
  --has-memory
)

if [ "basic" = "${_TEST_}" ]; then
  for "$baisc" in "${!_TEST_BASIC_[@]}"; do
    ${_ROOT_DIR_%/}/configure "$basic"          \
      && make clean test                        \
        || exit 1
  done
fi

# eof
