# hlib

[![Build Status](https://travis-ci.com/imhele/hlib.svg?branch=master)](https://travis-ci.com/imhele/hlib)

[English](https://github.com/imhele/hlib/blob/master/README.md) | 简体中文

基于 ECMAScript 语法与思想的 C 依赖库。

> 注意：所有文件均使用 UTF-8 编码。
> 
> GCC 7.0+

## 开始使用

### 下载

```bash
$ git clone https://github.com/imhele/hlib.git --depth=1
```

### 测试

测试文件在 [`tests`](https://github.com/imhele/hlib/tree/master/tests) 目录下，执行以下命令会自动递归扫描目录里的所有 `*.c` 文件进行编译并执行：

```bash
$ sh scripts/test.sh
```

或者指定测试目录 / 文件：

```bash
$ sh scripts/test.sh test/utils
$ sh scripts/test.sh test/utils/helpers/closure.c
```

### 构建索引

约定 `src` 内的所有目录都有一个对应的同名头文件，作为目录内的文件与子目录的索引。可选择执行 [NodeJS](https://nodejs.org/) 脚本自动构建：

```bash
$ node scripts/buildindex.js
```

可在 `.indexconfig.json` 文件中配置 `excludes` 忽略条件，每项条件将被转为正则表达式进行匹配：

```json
{
  "root": "src",
  "extname": ".h",
  "entry": "main",
  "macroprefix": "__HLIB",
  "excludes": []
}
```

## 许可

MIT - [imhele](https://github.com/imhele)
