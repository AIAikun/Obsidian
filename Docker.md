微软官方文档：[https://learn.microsoft.com/zh-cn/windows/wsl/tutorials/wsl-containers](https://learn.microsoft.com/zh-cn/windows/wsl/tutorials/wsl-containers)
菜鸟教程：[https://www.runoob.com/docker/docker-hello-world.html](https://www.runoob.com/docker/docker-hello-world.html)
官方教程：[https://docs.docker.com/guides/](https://docs.docker.com/guides/)
### **一、镜像管理**

#### **1. 基础操作**

- **`docker images`**  
    列出本地所有镜像（显示镜像ID、仓库名、标签、大小等信息）。
    
    ```bash
    docker images
    ```
    
- **`docker pull <镜像名:标签>`**  
    从仓库（如 Docker Hub）拉取镜像（默认标签 `latest`）。
    
    ```bash
    docker pull nginx:latest
    ```
    
- **`docker rmi <镜像ID/镜像名>`**  
    删除本地镜像（若镜像被容器占用，需先删除容器）。
    
    ```bash
    docker rmi nginx:latest
    ```
    

#### **2. 高级操作**

- **`docker build -t <镜像名:标签> <Dockerfile路径>`**  
    通过 `Dockerfile` 构建自定义镜像（`-t` 指定名称和标签）。
    
    ```bash
    docker build -t my-app:v1 .
    ```
    
- **`docker tag <源镜像> <目标镜像>`**  
    为镜像添加新标签（便于版本管理或推送至不同仓库）。
    
    ```bash
    docker tag my-app:v1 my-registry/my-app:v1
    ```
    
- **`docker push <镜像名:标签>`**  
    将镜像推送到远程仓库（需提前登录）。
    
    ```bash
    docker push my-registry/my-app:v1
    ```
    

---

### **二、容器管理**

#### **1. 容器生命周期**

- **`docker run [选项] <镜像名> [命令]`**  
    创建并启动容器（常用选项：`-d` 后台运行，`-p` 端口映射，`-v` 挂载卷，`--name` 指定名称）。
    
    ```bash
    docker run -d -p 8080:80 --name web nginx
    ```
    
- **`docker start/stop/restart <容器名/容器ID>`**  
    启动、停止或重启容器。
    
    ```bash
    docker stop web
    ```
    
- **`docker rm <容器名/容器ID>`**  
    删除已停止的容器（`-f` 强制删除运行中容器）。
    
    ```bash
    docker rm web
    ```
    

#### **2. 容器状态查看**

- **`docker ps [选项]`**  
    列出容器（默认显示运行中容器，`-a` 显示全部，`-q` 仅显示ID）。
    
    ```bash
    docker ps -a
    ```
    
- **`docker logs <容器名/容器ID>`**  
    查看容器日志（`-f` 实时跟踪，`--tail` 指定行数）。
    
    ```bash
    docker logs -f web
    ```
    
- **`docker inspect <容器名/容器ID>`**  
    获取容器详细信息（JSON格式，包括配置、网络、状态等）。
    
    ```bash
    docker inspect web
    ```
    

#### **3. 容器交互**

- **`docker exec -it <容器名/容器ID> <命令>`**  
    在运行中的容器内执行命令（如进入交互式Shell）。
    
    ```bash
    docker exec -it web /bin/bash
    ```
    
- **`docker cp <源路径> <容器名>:<目标路径>`**  
    在宿主机与容器间复制文件（反向操作需交换源和目标）。
    
    ```bash
    docker cp ./file.txt web:/app/
    ```
    

---

### **三、网络管理**

- **`docker network ls`**  
    列出所有网络（默认包含 `bridge`、`host`、`none`）。
    
- **`docker network create <网络名>`**  
    创建自定义网络（实现容器间通信隔离）。
    
    ```bash
    docker network create my-net
    ```
    
- **`docker run --network=<网络名> <镜像名>`**  
    启动容器并连接至指定网络。
    
    ```bash
    docker run -d --network=my-net --name db mysql
    ```
    

---

### **四、数据持久化**

- **`docker volume ls`**  
    列出所有数据卷（用于持久化存储）。
    
- **`docker volume create <卷名>`**  
    创建数据卷。
    
    ```bash
    docker volume create my-volume
    ```
    
- **`docker run -v <卷名>:<容器路径> <镜像名>`**  
    挂载数据卷至容器（`-v` 或 `--mount` 语法）。
    
    ```bash
    docker run -d -v my-volume:/data --name data-container nginx
    ```
    

---

### **五、实用工具命令**

- **`docker system df`**  
    查看磁盘使用情况（镜像、容器、数据卷的占用空间）。
    
- **`docker system prune`**  
    清理未使用的资源（停止的容器、未被引用的网络、悬空镜像等）。
    
    ```bash
    docker system prune -a  # 删除所有未使用的镜像
    ```
    
- **`docker compose up/down`**  
    通过 `docker-compose.yml` 启动/停止多容器应用（需提前安装 Docker Compose）。
    
    ```bash
    docker compose up -d  # 后台启动服务
    ```
    

---

### **六、常见问题解决**

1. **容器无法访问网络**
    
    - 检查网络模式：`docker inspect <容器ID> | grep NetworkMode`
    - 确保容器连接至正确的网络。
2. **数据卷挂载失败**
    
    - 确认宿主机路径是否存在（若使用绝对路径）。
    - 检查数据卷名称是否正确。
3. **镜像拉取缓慢**
    
    - 配置国内镜像源（如阿里云、腾讯云加速器）。
    - 示例配置 `/etc/docker/daemon.json`：
        
        ```javascript
        {
          "registry-mirrors": ["https://<your-mirror-url>"]
        }
        ```
        

---

### **总结**

Docker 命令体系围绕镜像、容器、网络和数据卷展开，核心操作可归纳为：

- **镜像**：`pull`（拉取）→ `build`（构建）→ `push`（推送）
- **容器**：`run`（启动）→ `exec`（交互）→ `logs`（日志）→ `stop/rm`（停止/删除）
- **网络**：`create`（创建）→ `connect`（连接）
- **数据**：`volume create`（创建卷）→ `-v`（挂载）