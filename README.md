# hlib

[![Build Status](https://travis-ci.com/imhele/hlib.svg?branch=master)](https://travis-ci.com/imhele/hlib)

English | [简体中文](https://github.com/imhele/hlib/blob/master/README_zh-CN.md)

C Library based on ECMAScript grammar and thought.

> Attention: All files were written with UTF-8.
> 
> GCC 7.0+

## Usage

### Download

```bash
$ git clone https://github.com/imhele/hlib.git --depth=1
```

### Test

Test files are located in the folder [`tests`](https://github.com/imhele/hlib/tree/master/tests) , executing the following command will recursively scan all `* .c` files in that folder to compile and execute:

```bash
$ sh scripts/test.sh
```

Or you can test specific directory / file:

```bash
$ sh scripts/test.sh test/utils
$ sh scripts/test.sh test/utils/helpers/closure.c
```

### Build Index

By convention, all directories in `src` have a corresponding header file with a same basename, which serves as an index of files and subdirectories in the directory. Support for executing [NodeJS](https://nodejs.org/) script to build automatically:

```bash
$ node scripts/buildindex.js
```

The `excludes` ignore condition can be configured in the `.indexconfig.json` file, and each item in the array will be converted to a regular expression for matching:

```json
{
  "root": "src",
  "extname": ".h",
  "entry": "main",
  "macroprefix": "__HLIB",
  "excludes": []
}
```

## License

MIT - [imhele](https://github.com/imhele)
