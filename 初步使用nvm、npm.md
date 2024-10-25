# 安装和简单使用

根据官网[https://github.com/nvm-sh/nvm?tab=readme-ov-file](https://github.com/nvm-sh/nvm?tab=readme-ov-file)指示，使用curl或者wget安装nvm，然后source ~/.zshrc
要安装特定版本的节点：
```
nvm install 14.7.0 # or 16.3.0, 12.22.1, etc
```
在终端打开相应文件夹，在终端输入 安装相关插件
```
npm i # or npm install
```

运行项目。
```
npm run dev 
```

# nvm、npm的功能

## 1. npm
    

npm是 Node.js 的包管理工具，它的主要作用是帮助开发者在项目中安装、更新、管理以及分享 JavaScript 包。这些包可以包括用于前端开发的库、框架，也可以包括用于后端开发的工具和依赖项。Node.js中自带npm。

## 2.  nvm
    

nvm全名叫做 nodejs version manage，是Node.js的版本管理工具，主要是通过命令行实现nodejs版本的安装、切换当前使用的nodejs版本，nvm可以实现电脑安装和管理多个版本的node.js