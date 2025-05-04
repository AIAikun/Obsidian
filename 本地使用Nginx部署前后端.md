1. ## 打包前端文件
    

打开前端所在文件夹，打开终端，输入

```Go
npm run build
```

打包生成dist文件夹

2. ## 启动wsl、ubuntu
    

在ubuntu中启动redis客户端

```Go
redis-cli
```

启动redis服务端

```Go
/etc/init.d/redis-server start
```

wsl中安装nginx

```Go
sudo apt-get install -y nginx//安装
```

之后启动Nginx

```Go
sudo service nginx start
```

访问 `http://localhost`

![](https://hustdian.feishu.cn/space/api/box/stream/download/asynccode/?code=NjE2NDQzZmU0NTBmNjkyMTE5NDhlZmM4OTlkMTBjYTlfQUI2ZXA5MTB1Y1l3cmJkM0pzTVRBTnFLelVDTjVBU2lfVG9rZW46SldrcGJXTVN4b1VHRFJ4YzhraGN0QU14bk1lXzE3NDYzNTA5OTc6MTc0NjM1NDU5N19WNA)

出现这个界面，说明安装成功。

3. ## 后端
    

将后端文件夹copy到wsl

```Go
cp /mnt/e/dianwang/server/server/ruoyi-admin.jar ./
```

注意是“/”，还有磁盘e后面没有“：”

启动后端

```Go
nohup java -jar ruoyi-admin.jar >server.log 2>&1 &//后台运行后端程序
tail -f server.log//查看运行日志golang
```

4. ## 前端
    

将dist文件移动到相应nginx目录中

```Go
cp /mnt/e/dianwang/weather/dist /var/lib/nginx/html
```

5. ## 配置nginx
    

编辑配置文件

```Go
vim /etc/nginx/nginx.conf
```

按照下面配置

![](https://hustdian.feishu.cn/space/api/box/stream/download/asynccode/?code=MDc5ZDE4ZjQ5OGY4ZjI5YWJmYjIwNmUzNjI1NDg1OGZfbGk3RVZBVlkxR1o4UEdkOVd4dzZPMlhNdmFPQjJhaldfVG9rZW46TjdXVWI0c1ROb0NVQ2d4VHJjRmNNQUpCbmZkXzE3NDYzNTA5OTc6MTc0NjM1NDU5N19WNA)

由于是wsl2，运行的端口不再是127.0.0.1，需要看wsl的接口

```Go
ifconfig//查看端口
```

![](https://hustdian.feishu.cn/space/api/box/stream/download/asynccode/?code=ODhlZWYyNTA1N2E5NDEwYjE0MzVkNGJhNzdlNzRmZjJfOTA2NGtMUE5SUUQ4eG16cEU0SXRpNDJnT3dxOTV5c2pfVG9rZW46UkhoQmJNckdtb1licXl4S3FBRWNyYlVLbnpnXzE3NDYzNTA5OTc6MTc0NjM1NDU5N19WNA)

```Go
sudo service nginx start
```

6. ## 访问
    

打开浏览器，访问172.17.99.73:8081,即可成功。