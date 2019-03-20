# hlib

[![Build Status](https://travis-ci.com/imhele/hlib.svg?branch=master)](https://travis-ci.com/imhele/hlib)

[English](https://github.com/imhele/hlib/blob/master/README.md) | 简体中文

基于 ECMAScript 语法与思想的 C/C++ 依赖库。

> 注意：所有文件均使用 UTF-8 编码。
> 
> GCC 7.0+

## 开始使用

### 下载

```bash
$ git clone https://github.com/imhele/hlib.git --depth=1
```

### 测试

```bash
$ sh ./test.sh

或者使用 `imhele` ，每次修改文件后自动进行测试

$ npm run dev
```

## 简介

### 类型

- **`null`**: 空值表示通常指向不存在或无效对象或地址的引用。
- **`object`**: 对象是指包含数据和数据使用说明的数据结构。
- **`symbol`**: 具有数据类型 `symbol` 的值可以称为 symbol value ，一旦创建即为匿名的唯一值。
- **`array`**: 数组是数据的有序集合，用于在单个变量中存储多个值。
- **`string`**: 字符串是用于表示文本的字符序列。

## 许可

MIT - [imhele](https://github.com/imhele)
