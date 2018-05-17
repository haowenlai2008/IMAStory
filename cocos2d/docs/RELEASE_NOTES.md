<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Cocos2d-x 3.14 Release Notes](#cocos2d-x-314-release-notes)
- [Misc Information](#misc-information)
- [v3.14](#v314)
  - [New features](#new-features)
  - [Features in detail](#features-in-detail)
    - [Uses luajit 2.1.0-beta2 for all platforms](#uses-luajit-210-beta2-for-all-platforms)
    - [Sprite supports slice9 feature](#sprite-supports-slice9-feature)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Cocos2d-x 3.14 Release Notes #

# Misc Information

* [Full Changelog](https://github.com/cocos2d/cocos2d-x/blob/v3/CHANGELOG)

# v3.14

## New features

* Adds Spine binary file format support
* Uses luajit 2.1.0-beta2 for all platforms
* Adds new actions: `ResizeBy` and `ResizeTo`
* Can disable multi-touch on Android
* Sprite supports slice9 feature
* Action adds a method to get the number of actions running on a given node with specific tag
* Can set `Button`'s title label
* `EditBox` adds horizontal text alignment
* Supports game controller on Mac

## Features in detail

### Uses luajit 2.1.0-beta2 for all platforms

In previous it is not convenient to generate luajit 64bit bytecode. You need to generate the bytecode in real devices, which means you should generate luajit 64bit bytecode on iOS 64bit devices.

Now, we can generate luajit 64bit bytecode on Mac OS X, windows or linux, so we change to use luajit for all platforms. If you use cocos command with `-m release`, it will generate bytecode automatically. And it will put 64bit bytecode into `64-bit` folder. One exception is that, it doesn't generate luajit bytecode on linux, we don't know whether to generate 32bit or 64bit byte codes. So you should generate luajit bytecode yourself by using `cocos luacompile` command. Please refer to the help information of `cocos luacompile -h` for detail usage.

The generated bytecodes architecture are:

Platform | generate 32bit luajit bytecode | generate 64bit luajit bytecode |
---|---|---
iOS | yes | yes
Android | yes if APP\_ABI not only includes arm64-v8a, such as `APP_ABI := arm64-v8a` | yes if APP_ABI includes arm64-v8a
Mac | not | yes
Windows | yes | no
Linux | no | no

### Sprite supports slice9 feature

Now Sprite supports slice9 feature, you can use it like:

```c++
auto sprite = Sprite::create(...);
// set center rect
// the origin is top-left
sprite->setCenterRectNormalized(Rect(x, y, width, heigh));
```

More detail information please refer to the comments of `Sprite::setCenterNormalized()`.

## Known issue

lua project will crash on iOS simulator if using Xcode 8.2+. The issue is caused by luajit. We thought it is a but of Xcode because there is not problem if using Xcode 8.1 or lower version. 

We can not fix it in v3.14, can track [the issue](https://github.com/cocos2d/cocos2d-x/issues/17043) for the progress of this issue.